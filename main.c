#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lvgl/lvgl.h"
#include "ui/ui.h"
#include <pthread.h>
#include <signal.h>
#include <getopt.h>
#include "ui/user/core/ipc_event_queue.h"

GlobalParameters global_parameters = {.sendMsgQueId = -1, .recvMsgQueId = -1, .ipc_ready = 0, .g_quit = 0};
AppArgs app_args;

static void app_args_init(AppArgs * args)
{
    args->language_index = 0;
    args->self_pass_index = 0;
    args->sendKey = 2027;
    args->recvKey = 2026;
    args->set_w_res = 1024;
    args->set_h_res = 768;
    args->fonts_path = "./assets/fonts/";
}

static void usage(void)
{
    fprintf(stderr,
            "\nUsage: lv_demo [OPTIONS]\n"
            "Options:\n"
            "   -l,--lang       NUM      language index\n"
            "   -p,--selfpass   NUM      self-check page index\n"
            "   -s,--sendkey    NUM      send key number\n"
            "   -r,--recvkey    NUM      receive number\n"
            "   -W,--width      NUM      set screen width resolution\n"
            "   -H,--height     NUM      set screen height resolution\n"
            "   -f,--fontpath   NUM      font assets directory path\n"
            "   -h,--help       NUM      show this help\n\n"
            "Examples:\n"
            "./lv_demo --lang 0 --selfpass 1 -s 2027 -r 2026 -W 1024 -H 768 -f /mnt/data/app/assets/fonts/\n\n"
        );
}

static int parse_init(const char * optstr, int * out_val)
{
    char * endptr = NULL;
    long val = strtol(optstr, &endptr, 10);
    /* endptr==optstr: 完全不是数字; *endptrl!='\0':后面带多余字符 */
    if(endptr == optstr || *endptr != '\0') {
        fprintf(stderr, "error: expect integer, got %s\n", optstr);
        return -1;
    }
    *out_val = (int)val;
    return 0;
}

static void * message_ui_thread(void * arg)
{
    GlobalParameters * global_parameters_ptr = (GlobalParameters *)arg;
    uint32_t idle_time;

    while(!atomic_load(&global_parameters_ptr->g_quit)) {
        process_pending_ipc_events();
        idle_time = lv_timer_handler();
        if(idle_time == 0U) idle_time = 1U;
        if(idle_time > 1000U) idle_time = 1000U;
        ui_ipc_event_queue_wait(idle_time);
    }

    return NULL;
}

static void * message_sig_thread(void * arg)
{
    GlobalParameters * global_parameters_ptr = (GlobalParameters *)arg;
    sigset_t sig_set;
    int sig;

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGINT);
    sigaddset(&sig_set, SIGTSTP);
    sigaddset(&sig_set, SIGTERM);

    while(sigwait(&sig_set, &sig) == 0) {
        switch(sig) {
        case SIGINT:
            atomic_store(&global_parameters_ptr->g_quit, 1);
            ui_ipc_event_queue_stop();
            return NULL;
        case SIGTERM:
            atomic_store(&global_parameters_ptr->g_quit, 1);
            ui_ipc_event_queue_stop();
            return NULL;
        case SIGTSTP:
            raise(SIGSTOP);
            break;
        default:
            break;
        }
    }
    return NULL;
}

static void lv_linux_disp_init(void)
{
    const char * device = "/dev/fb0";
    lv_display_t * disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, device);
}

int main(int argc, char * argv[])
{
    pthread_t recvMsgThread, uiThread, sigThread;
    sigset_t sig_set;
    int opt;

    app_args_init(&app_args);
    static const struct option long_opts[] = {
        {"lang", required_argument, NULL, 'l'},
        {"selfpass", required_argument, NULL, 'p'},
        {"sendkey", required_argument, NULL, 's'},
        {"recvkey", required_argument, NULL, 'r'},
        {"width", required_argument, NULL, 'W'},
        {"height", required_argument, NULL, 'H'},
        {"fontpath", required_argument, NULL, 'f'},
        {"help", no_argument, NULL, 'h'},
    };
    while((opt = getopt_long(argc, argv, "l:p:s:r:W:H:f:h", long_opts, NULL)) != -1) {
        switch(opt) {
        case 'l':
            if(parse_init(optarg, &app_args.language_index)) {
                usage();
                return 1;
            }
            break;
        case 'p':
            if(parse_init(optarg, &app_args.self_pass_index)) {
                usage();
                return 1;
            }
            break;
        case 's':
            if(parse_init(optarg, &app_args.sendKey)) {
                usage();
                return 1;
            }
            break;
        case 'r':
            if(parse_init(optarg, &app_args.recvKey)) {
                usage();
                return 1;
            }
            break;
        case 'W':
            if(parse_init(optarg, &app_args.set_w_res)) {
                usage();
                return 1;
            }
            break;
        case 'H':
            if(parse_init(optarg, &app_args.set_h_res)) {
                usage();
                return 1;
            }
            break;
        case 'f':
            app_args.fonts_path = optarg;
            break;
        case 'h':
            usage();
            return 0;
        case '?':
            usage();
            return 1;
        default:
            break;
        }
    }

    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGINT);
    sigaddset(&sig_set, SIGTSTP);
    sigaddset(&sig_set, SIGTERM);
    if(pthread_sigmask(SIG_BLOCK, &sig_set, NULL) != 0) {
        fprintf(stderr, "failed to block process signals\n");
        return 1;
    }

    lv_init();
    lv_linux_disp_init();
    ui_init();
    ui_ipc_event_queue_init();

    int sigThreadCreated = pthread_create(&sigThread, NULL, message_sig_thread, &global_parameters) == 0;
    int recvMsgThreadCreated = pthread_create(&recvMsgThread, NULL, message_recv_thread, &global_parameters) == 0;
    int uiThreadCreated = 0;

    while(recvMsgThreadCreated && !atomic_load(&global_parameters.g_quit) &&
          !atomic_load(&global_parameters.ipc_ready)) {
        usleep(1000);
    }

    if(recvMsgThreadCreated && atomic_load(&global_parameters.ipc_ready) &&
       !atomic_load(&global_parameters.g_quit)) {
        uiThreadCreated = pthread_create(&uiThread, NULL, message_ui_thread, &global_parameters) == 0;
    }
    if(!sigThreadCreated || !recvMsgThreadCreated || !uiThreadCreated) {
        fprintf(stderr, "failed to create application thread\n");
        atomic_store(&global_parameters.g_quit, 1);
        ui_ipc_event_queue_stop();
    }

    if(recvMsgThreadCreated) pthread_join(recvMsgThread, NULL);
    if(uiThreadCreated) pthread_join(uiThread, NULL);

    ui_ipc_event_queue_stop();
    if(sigThreadCreated) {
        pthread_cancel(sigThread);
        pthread_join(sigThread, NULL);
    }

    ui_font_deinit();
    ui_destroy();
    lv_deinit();

    return 0;
}
