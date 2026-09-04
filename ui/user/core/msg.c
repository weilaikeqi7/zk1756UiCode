//
// Created by jinxing on 2026/2/10.
//

#include "lvgl/lvgl.h"
#include "msg.h"
#include "ipc_event_queue.h"
#include "ipc_message_validate.h"
#include "ipcMsgQue4UiRcvNotify.h"
#include "ipcMsgQue4UiRcvRes.h"
#include "ipcMsgQue4UiTypeCommon.h"

static ROE_S32 parse_notify_or_response(ROE_SL msgType, const RoeIpcMsgQueRawData_st * rawData)
{
    return msgType >= MSG_4_REQ_RES_INIT ? ParseResMsg(msgType, rawData) : ParseNotifyMsg(msgType, rawData);
}

void process_pending_ipc_events(void)
{
    /* Limit the work per tick so a burst of notifications cannot starve LVGL. */
    for(ROE_U8 i = 0; i < 8; i++) {
        UiIpcEvent_st event;
        if(ui_ipc_event_queue_pop(&event) != ROE_SUCCESS) {
            break;
        }

        if(ipc_validate_message(event.msgType, &event.rawData, event.receivedBytes) != ROE_SUCCESS) {
            LV_LOG_WARN("[IPC][DROP] invalid queued message type:%ld receivedBytes:%zu",
                        event.msgType,
                        (size_t)event.receivedBytes);
            continue;
        }

        if(parse_notify_or_response(event.msgType, &event.rawData) != ROE_SUCCESS) {
            LV_LOG_ERROR("[IPC][DISPATCH] handler failed type:%ld", event.msgType);
        }
    }
}
