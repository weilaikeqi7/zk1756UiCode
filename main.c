#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include "lvgl/lvgl.h"
#include "ui/ui.h"
#include <getopt.h>
#include "ui/user/core/ui_runtime.h"

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
    LV_LOG_USER("\nUsage: lv_demo [OPTIONS]\n"
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
                "./lv_demo --lang 0 --selfpass 1 -s 2027 -r 2026 -W 1024 -H 768 -f /mnt/data/app/assets/fonts/\n");
}

static int parse_init(const char * optstr, int * out_val)
{
    char * endptr = NULL;
    long val = strtol(optstr, &endptr, 10);
    /* endptr==optstr: 完全不是数字; *endptrl!='\0':后面带多余字符 */
    if(endptr == optstr || *endptr != '\0') {
        LV_LOG_ERROR("[APP][ARGS] expected integer, got %s", optstr);
        return -1;
    }
    *out_val = (int)val;
    return 0;
}

static void lv_linux_disp_init(void)
{
    const char * device = "/dev/fb0";
    lv_display_t * disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, device);
}

int main(int argc, char * argv[])
{
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
        LV_LOG_ERROR("[APP][INIT] failed to block process signals");
        return 1;
    }

    lv_init();
    lv_linux_disp_init();
    ui_init();
    if(ui_runtime_run_linux(&global_parameters) != ROE_SUCCESS) {
        LV_LOG_ERROR("[APP][EXIT] application runtime stopped with an error");
    }

    ui_font_deinit();
    ui_destroy();
    lv_deinit();

    return 0;
}
