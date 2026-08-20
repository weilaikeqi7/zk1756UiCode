/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include "lvgl/lvgl.h"
#include "ui/ui.h"
#include <pthread.h>
#include "handleNotify.h"
/*********************
 *      DEFINES
 *********************/
GlobalParameters global_parameters;
sem_t sem;
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
static void lv_linux_disp_init(void)
{
    const char * device = "/dev/fb0";
    lv_display_t * disp = lv_linux_fbdev_create();
    lv_linux_fbdev_set_file(disp, device);
}

void lv_linux_run_loop(void)
{
    uint32_t idle_time;

    /*Handle LVGL tasks*/
    while(1) {
        idle_time = lv_timer_handler(); /*Returns the time to the next timer execution*/
        usleep(idle_time * 1000);
    }
}

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

int main(int argc, char ** argv)
{
    (void)argc; /*Unused*/
    (void)argv; /*Unused*/
    pthread_t recvMsgThread;
    global_parameters.sendKey = 2027;
    global_parameters.recvKey = 2026;
    sem_init(&sem, 0, 0);
    /*Initialize LVGL*/
    lv_init();
    lv_linux_disp_init();
    /*Initialize the HAL (display, input devices, tick) for LVGL*/
    LV_LOG_USER(">>> LVGL init done");

    ui_init();
    InitMutex();
    pthread_create(&recvMsgThread, NULL, message_recv_thread, &global_parameters);
    lv_linux_run_loop();
    lv_deinit();
    ui_font_deinit();
    pthread_join(recvMsgThread, NULL);
    sem_destroy(&sem);

    return 0;
}