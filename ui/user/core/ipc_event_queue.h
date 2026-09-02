#ifndef ZKSL_75_6LC_IPC_EVENT_QUEUE_H
#define ZKSL_75_6LC_IPC_EVENT_QUEUE_H

#include "msg.h"

#define UI_IPC_EVENT_QUEUE_CAPACITY 32

typedef struct {
    ROE_SL msgType;
    RoeIpcMsgQueRawData_st rawData;
} UiIpcEvent_st;

ROE_S32 ui_ipc_event_queue_init(void);
void ui_ipc_event_queue_stop(void);
ROE_S32 ui_ipc_event_queue_push(const UiIpcEvent_st * event);
ROE_S32 ui_ipc_event_queue_pop(UiIpcEvent_st * event);

#endif // ZKSL_75_6LC_IPC_EVENT_QUEUE_H
