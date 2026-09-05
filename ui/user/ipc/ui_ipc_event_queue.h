#ifndef ZKSL_75_6LC_UI_IPC_EVENT_QUEUE_H
#define ZKSL_75_6LC_UI_IPC_EVENT_QUEUE_H

#include "user/ipc/ui_ipc_message.h"

#define UI_IPC_EVENT_QUEUE_CAPACITY 32

typedef struct {
    ROE_SL msgType;
    ROE_SIZE receivedBytes;
    UiIpcRawData rawData;
} UiIpcEvent;

ROE_S32 ui_ipc_event_queue_init(void);
void ui_ipc_event_queue_stop(void);
ROE_S32 ui_ipc_event_queue_push(const UiIpcEvent * event);
ROE_S32 ui_ipc_event_queue_pop(UiIpcEvent * event);
ROE_S32 ui_ipc_event_queue_wait(ROE_U32 timeoutMs);

#endif // ZKSL_75_6LC_UI_IPC_EVENT_QUEUE_H
