//
// Created by jinxing on 2026/2/10.
//

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

#include "msg.h"
#include "ipc_event_queue.h"
#include "ipc_message_validate.h"
#include "ipcMsgQue4UiRcvNotify.h"
#include "ipcMsgQue4UiRcvRes.h"
#include "ipcMsgQue4UiTypeCommon.h"
#include "ipcMsgQue4UiSndRequest.h"
#include "types.h"

static ROE_S32 ParseNotifyAndResMsg(ROE_SL msgType, RoeIpcMsgQueRawData_st * rawData)
{
    ROE_S32 ret = ROE_FAILURE;
    if(msgType >= MSG_4_REQ_RES_INIT) {
        ret = ParseResMsg(msgType, rawData);
    } else {
        ret = ParseNotifyMsg(msgType, rawData);
    }
    return ret;
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
            fprintf(stderr,
                    "discard invalid queued IPC message, msgType:%ld receivedBytes:%ld\n",
                    event.msgType,
                    (long)event.receivedBytes);
            continue;
        }

        if(ParseNotifyAndResMsg(event.msgType, &event.rawData) != ROE_SUCCESS) {
            fprintf(stderr, "msgType:%ld ParseNotifyAndResMsg() failed\n", event.msgType);
        }
    }
}

void * message_recv_thread(void * arg)
{
    GlobalParameters * msg_args = arg;
    RoeIpcMsgQueBuff_st msgBuf;
    key_t sendKey = app_args.sendKey, recvKey = app_args.recvKey;
    int registerSent = 0;

    atomic_store(&msg_args->ipc_ready, 0);
    msg_args->sendMsgQueId = -1;
    msg_args->recvMsgQueId = -1;

    msg_args->sendMsgQueId = msgget(sendKey, 0666);
    if(-1 == msg_args->sendMsgQueId) {
        fprintf(stderr, "open send msg que failed, key:%d errno:%d\n", (int)sendKey, errno);
        atomic_store(&msg_args->g_quit, 1);
        goto cleanup;
    }

    ReqRegister_st reqRegister = {.reg = 1};
    if(SendMsg4UiRegisterReq(msg_args->sendMsgQueId, &reqRegister) != ROE_SUCCESS) {
        fprintf(stderr, "SendMsg4UiRegisterReq() failed\n");
    } else {
        registerSent = 1;
    }

    msg_args->recvMsgQueId = msgget(recvKey, 0666);

    if(-1 == msg_args->recvMsgQueId) {
        fprintf(stderr, "open recv msg que failed, key:%d errno:%d\n", (int)recvKey, errno);
        atomic_store(&msg_args->g_quit, 1);
        goto cleanup;
    }

    if(SendMsg4UiGetUserCommonConfigReq(msg_args->sendMsgQueId) != ROE_SUCCESS ||
       SendMsg4UiGetUserMediaConfigReq(msg_args->sendMsgQueId) != ROE_SUCCESS) {
        fprintf(stderr, "send initial user config request failed\n");
    }
    atomic_store(&msg_args->ipc_ready, 1);

    while(!atomic_load(&msg_args->g_quit)) {
        ssize_t receivedBytes = msgrcv(msg_args->recvMsgQueId,
                                       &msgBuf,
                                       sizeof(msgBuf.msgData),
                                       -MSG_4_REQ_RES_BUTT,
                                       MSG_NOERROR | IPC_NOWAIT);
        if(receivedBytes == -1) {
            if(errno == ENOMSG) {
                usleep(10000);
                continue;
            }
            if(errno == EINTR) {
                continue;
            }
            fprintf(stderr,
                    "msgrcv() failed, recvMsgQueId:%d errno:%d\n",
                    msg_args->recvMsgQueId,
                    errno);
            atomic_store(&msg_args->g_quit, 1);
            ui_ipc_event_queue_stop();
            break;
        }

        if(ipc_validate_message(msgBuf.msgType,
                                (const RoeIpcMsgQueRawData_st *)msgBuf.msgData,
                                (ROE_SIZE)receivedBytes) != ROE_SUCCESS) {
            fprintf(stderr,
                    "discard invalid IPC message, msgType:%ld receivedBytes:%ld\n",
                    msgBuf.msgType,
                    (long)receivedBytes);
            continue;
        }

        UiIpcEvent_st event = {
            .msgType = msgBuf.msgType,
            .receivedBytes = (ROE_SIZE)receivedBytes,
        };
        memcpy(&event.rawData, msgBuf.msgData, (ROE_SIZE)receivedBytes);
        if(ui_ipc_event_queue_push(&event) != ROE_SUCCESS) {
            atomic_store(&msg_args->g_quit, 1);
            break;
        }
    }

cleanup:
    atomic_store(&msg_args->ipc_ready, 0);
    if(registerSent && msg_args->sendMsgQueId >= 0) {
        ReqRegister_st reqRegister = {.reg = 0};
        if(SendMsg4UiRegisterReq(msg_args->sendMsgQueId, &reqRegister) != ROE_SUCCESS) {
            fprintf(stderr, "SendMsg4UiRegisterReq() failed\n");
        }
    }
    ui_ipc_event_queue_stop();

    /* These queues are owned by the peer processes. The UI only opens them,
     * so it must not remove their IPC objects during shutdown. */
    return NULL;
}
