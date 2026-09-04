#include "ui_runtime.h"

#include "lvgl/lvgl.h"
#include "ipc_event_queue.h"
#include "ipc_receiver.h"
#include "msg.h"

#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <unistd.h>

static void * ui_thread_main(void * arg)
{
    GlobalParameters * parameters = arg;

    while(!atomic_load(&parameters->g_quit)) {
        process_pending_ipc_events();

        uint32_t idleTime = lv_timer_handler();
        if(idleTime == 0U) idleTime = 1U;
        if(idleTime > 1000U) idleTime = 1000U;
        ui_ipc_event_queue_wait(idleTime);
    }

    return NULL;
}

static void * signal_thread_main(void * arg)
{
    GlobalParameters * parameters = arg;
    sigset_t signalSet;
    int signalNumber;

    sigemptyset(&signalSet);
    sigaddset(&signalSet, SIGINT);
    sigaddset(&signalSet, SIGTSTP);
    sigaddset(&signalSet, SIGTERM);

    while(sigwait(&signalSet, &signalNumber) == 0) {
        switch(signalNumber) {
        case SIGINT:
        case SIGTERM:
            atomic_store(&parameters->g_quit, 1);
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

ROE_S32 ui_runtime_run_linux(GlobalParameters * parameters)
{
    pthread_t receiverThread;
    pthread_t uiThread;
    pthread_t signalThread;
    int signalThreadCreated;
    int receiverThreadCreated;
    int uiThreadCreated = 0;

    if(!parameters) return ROE_FAILURE;

    LV_LOG_USER("[APP][INIT] starting Linux UI runtime");
    ui_ipc_event_queue_init();
    signalThreadCreated = pthread_create(&signalThread, NULL, signal_thread_main, parameters) == 0;
    receiverThreadCreated = pthread_create(&receiverThread, NULL, ui_ipc_receiver_thread, parameters) == 0;

    while(receiverThreadCreated && !atomic_load(&parameters->g_quit) &&
          !atomic_load(&parameters->ipc_ready)) {
        usleep(1000);
    }

    if(receiverThreadCreated && atomic_load(&parameters->ipc_ready) &&
       !atomic_load(&parameters->g_quit)) {
        uiThreadCreated = pthread_create(&uiThread, NULL, ui_thread_main, parameters) == 0;
    }

    if(!signalThreadCreated || !receiverThreadCreated || !uiThreadCreated) {
        LV_LOG_ERROR("[APP][INIT] failed to create application thread");
        atomic_store(&parameters->g_quit, 1);
        ui_ipc_event_queue_stop();
    }

    if(receiverThreadCreated) pthread_join(receiverThread, NULL);
    if(uiThreadCreated) pthread_join(uiThread, NULL);

    ui_ipc_event_queue_stop();
    if(signalThreadCreated) {
        pthread_cancel(signalThread);
        pthread_join(signalThread, NULL);
    }

    LV_LOG_USER("[APP][EXIT] Linux UI runtime stopped");
    return (!signalThreadCreated || !receiverThreadCreated || !uiThreadCreated) ? ROE_FAILURE : ROE_SUCCESS;
}
