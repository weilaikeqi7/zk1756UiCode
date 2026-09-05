//
// Created by jinxing on 2026/2/10.
//

#include "lvgl/lvgl.h"
#include "ui_ipc_message.h"
#include "ui_ipc_event_queue.h"
#include "ui_ipc_message_validator.h"
#include "ui_ipc_dispatch.h"
#include "ui_ipc_notification_types.h"
#include "ui_ipc_response_types.h"
#include "ui_ipc_protocol.h"

static ROE_S32 parse_notify_or_response(ROE_SL msgType, const UiIpcRawData * rawData)
{
    return msgType >= MSG_4_REQ_RES_INIT ? UiIpcDispatchResponse(msgType, rawData) : UiIpcDispatchNotification(msgType, rawData);
}

void ui_ipc_process_pending_events(void)
{
    /* Limit the work per tick so a burst of notifications cannot starve LVGL. */
    for(ROE_U8 i = 0; i < 8; i++) {
        UiIpcEvent event;
        if(ui_ipc_event_queue_pop(&event) != ROE_SUCCESS) {
            break;
        }

        if(ui_ipc_validate_message(event.msgType, &event.rawData, event.receivedBytes) != ROE_SUCCESS) {
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
