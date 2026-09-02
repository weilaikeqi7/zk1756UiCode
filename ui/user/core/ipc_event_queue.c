#include "ipc_event_queue.h"

#include <pthread.h>
#include <string.h>

typedef struct {
    UiIpcEvent_st items[UI_IPC_EVENT_QUEUE_CAPACITY];
    ROE_SIZE readIndex;
    ROE_SIZE writeIndex;
    ROE_SIZE count;
    int stopped;
    pthread_mutex_t mutex;
    pthread_cond_t notFull;
} UiIpcEventQueueState_st;

static UiIpcEventQueueState_st g_eventQueue = {
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .notFull = PTHREAD_COND_INITIALIZER,
};

ROE_S32 ui_ipc_event_queue_init(void)
{
    pthread_mutex_lock(&g_eventQueue.mutex);
    g_eventQueue.readIndex = 0;
    g_eventQueue.writeIndex = 0;
    g_eventQueue.count = 0;
    g_eventQueue.stopped = 0;
    pthread_cond_broadcast(&g_eventQueue.notFull);
    pthread_mutex_unlock(&g_eventQueue.mutex);
    return ROE_SUCCESS;
}

void ui_ipc_event_queue_stop(void)
{
    pthread_mutex_lock(&g_eventQueue.mutex);
    g_eventQueue.stopped = 1;
    pthread_cond_broadcast(&g_eventQueue.notFull);
    pthread_mutex_unlock(&g_eventQueue.mutex);
}

ROE_S32 ui_ipc_event_queue_push(const UiIpcEvent_st * event)
{
    if(!event) return ROE_FAILURE;

    pthread_mutex_lock(&g_eventQueue.mutex);
    while(g_eventQueue.count == UI_IPC_EVENT_QUEUE_CAPACITY && !g_eventQueue.stopped) {
        pthread_cond_wait(&g_eventQueue.notFull, &g_eventQueue.mutex);
    }

    if(g_eventQueue.stopped) {
        pthread_mutex_unlock(&g_eventQueue.mutex);
        return ROE_FAILURE;
    }

    memcpy(&g_eventQueue.items[g_eventQueue.writeIndex], event, sizeof(*event));
    g_eventQueue.writeIndex = (g_eventQueue.writeIndex + 1U) % UI_IPC_EVENT_QUEUE_CAPACITY;
    g_eventQueue.count++;
    pthread_mutex_unlock(&g_eventQueue.mutex);
    return ROE_SUCCESS;
}

ROE_S32 ui_ipc_event_queue_pop(UiIpcEvent_st * event)
{
    if(!event) return ROE_FAILURE;

    pthread_mutex_lock(&g_eventQueue.mutex);
    if(g_eventQueue.count == 0U) {
        pthread_mutex_unlock(&g_eventQueue.mutex);
        return ROE_FAILURE;
    }

    memcpy(event, &g_eventQueue.items[g_eventQueue.readIndex], sizeof(*event));
    g_eventQueue.readIndex = (g_eventQueue.readIndex + 1U) % UI_IPC_EVENT_QUEUE_CAPACITY;
    g_eventQueue.count--;
    pthread_cond_signal(&g_eventQueue.notFull);
    pthread_mutex_unlock(&g_eventQueue.mutex);
    return ROE_SUCCESS;
}
