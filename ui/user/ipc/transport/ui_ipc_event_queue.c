#include "ui_ipc_event_queue.h"

#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

typedef struct {
    UiIpcEvent items[UI_IPC_EVENT_QUEUE_CAPACITY];
    ROE_SIZE readIndex;
    ROE_SIZE writeIndex;
    ROE_SIZE count;
    int stopped;
    pthread_mutex_t mutex;
    pthread_cond_t notFull;
    pthread_cond_t notEmpty;
} UiIpcEventQueueState;

static UiIpcEventQueueState g_eventQueue = {
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .notFull = PTHREAD_COND_INITIALIZER,
    .notEmpty = PTHREAD_COND_INITIALIZER,
};

ROE_S32 ui_ipc_event_queue_init(void)
{
    pthread_mutex_lock(&g_eventQueue.mutex);
    g_eventQueue.readIndex = 0;
    g_eventQueue.writeIndex = 0;
    g_eventQueue.count = 0;
    g_eventQueue.stopped = 0;
    pthread_cond_broadcast(&g_eventQueue.notFull);
    pthread_cond_broadcast(&g_eventQueue.notEmpty);
    pthread_mutex_unlock(&g_eventQueue.mutex);
    return ROE_SUCCESS;
}

void ui_ipc_event_queue_stop(void)
{
    pthread_mutex_lock(&g_eventQueue.mutex);
    g_eventQueue.stopped = 1;
    pthread_cond_broadcast(&g_eventQueue.notFull);
    pthread_cond_broadcast(&g_eventQueue.notEmpty);
    pthread_mutex_unlock(&g_eventQueue.mutex);
}

ROE_S32 ui_ipc_event_queue_push(const UiIpcEvent * event)
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
    pthread_cond_signal(&g_eventQueue.notEmpty);
    pthread_mutex_unlock(&g_eventQueue.mutex);
    return ROE_SUCCESS;
}

ROE_S32 ui_ipc_event_queue_pop(UiIpcEvent * event)
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

ROE_S32 ui_ipc_event_queue_wait(ROE_U32 timeoutMs)
{
    struct timespec timeout;
    int waitResult = 0;

    pthread_mutex_lock(&g_eventQueue.mutex);
    if(g_eventQueue.count == 0U && !g_eventQueue.stopped && timeoutMs > 0U) {
        if(clock_gettime(CLOCK_REALTIME, &timeout) != 0) {
            pthread_mutex_unlock(&g_eventQueue.mutex);
            return ROE_FAILURE;
        }

        timeout.tv_sec += timeoutMs / 1000U;
        timeout.tv_nsec += (long)(timeoutMs % 1000U) * 1000000L;
        if(timeout.tv_nsec >= 1000000000L) {
            timeout.tv_sec++;
            timeout.tv_nsec -= 1000000000L;
        }

        while(g_eventQueue.count == 0U && !g_eventQueue.stopped) {
            waitResult = pthread_cond_timedwait(&g_eventQueue.notEmpty, &g_eventQueue.mutex, &timeout);
            if(waitResult == ETIMEDOUT) {
                break;
            }
            if(waitResult != 0) {
                pthread_mutex_unlock(&g_eventQueue.mutex);
                return ROE_FAILURE;
            }
        }
    }

    ROE_S32 result = (g_eventQueue.count > 0U) ? ROE_SUCCESS : ROE_FAILURE;
    pthread_mutex_unlock(&g_eventQueue.mutex);
    return result;
}
