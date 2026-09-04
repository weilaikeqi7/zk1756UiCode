#include "ipc_receiver.h"

#include "lvgl/lvgl.h"
#include "ipc_event_queue.h"
#include "ipc_message_validate.h"
#include "ipcMsgQue4UiSndRequest.h"
#include "msg.h"

#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

static ROE_S32 receiver_reset(GlobalParameters * parameters)
{
    if(!parameters) return ROE_FAILURE;

    atomic_store(&parameters->ipc_ready, 0);
    parameters->sendMsgQueId = -1;
    parameters->recvMsgQueId = -1;
    return ROE_SUCCESS;
}

static void receiver_shutdown(GlobalParameters * parameters)
{
    if(!parameters) return;
    atomic_store(&parameters->ipc_ready, 0);
    ui_ipc_event_queue_stop();
}

void * ui_ipc_receiver_thread(void * arg)
{
    GlobalParameters * parameters = arg;
    RoeIpcMsgQueBuff_st message;
    int registerSent = 0;

    if(receiver_reset(parameters) != ROE_SUCCESS) return NULL;

    parameters->sendMsgQueId = msgget((key_t)app_args.sendKey, 0666);
    if(parameters->sendMsgQueId < 0) {
        LV_LOG_ERROR("[IPC][INIT] open send queue failed key:%d errno:%d", app_args.sendKey, errno);
        atomic_store(&parameters->g_quit, 1);
        goto cleanup;
    }

    ReqRegister_st registerRequest = {.reg = 1};
    if(SendMsg4UiRegisterReq(parameters->sendMsgQueId, &registerRequest) != ROE_SUCCESS) {
        LV_LOG_ERROR("[IPC][INIT] register request failed");
    } else {
        registerSent = 1;
    }

    parameters->recvMsgQueId = msgget((key_t)app_args.recvKey, 0666);
    if(parameters->recvMsgQueId < 0) {
        LV_LOG_ERROR("[IPC][INIT] open receive queue failed key:%d errno:%d", app_args.recvKey, errno);
        atomic_store(&parameters->g_quit, 1);
        goto cleanup;
    }

    if(SendMsg4UiGetUserCommonConfigReq(parameters->sendMsgQueId) != ROE_SUCCESS ||
       SendMsg4UiGetUserMediaConfigReq(parameters->sendMsgQueId) != ROE_SUCCESS) {
        LV_LOG_ERROR("[IPC][INIT] initial user config request failed");
    }
    atomic_store(&parameters->ipc_ready, 1);
    LV_LOG_USER("[IPC][INIT] receiver ready sendQueue:%d receiveQueue:%d",
                parameters->sendMsgQueId, parameters->recvMsgQueId);

    while(!atomic_load(&parameters->g_quit)) {
        ssize_t receivedBytes = msgrcv(parameters->recvMsgQueId,
                                       &message,
                                       sizeof(message.msgData),
                                       -MSG_4_REQ_RES_BUTT,
                                       MSG_NOERROR | IPC_NOWAIT);
        if(receivedBytes < 0) {
            if(errno == ENOMSG) {
                usleep(10000);
                continue;
            }
            if(errno == EINTR) continue;

            LV_LOG_ERROR("[IPC][RECV] msgrcv failed queue:%d errno:%d",
                         parameters->recvMsgQueId, errno);
            atomic_store(&parameters->g_quit, 1);
            break;
        }

        if(ipc_validate_message(message.msgType,
                                (const RoeIpcMsgQueRawData_st *)message.msgData,
                                (ROE_SIZE)receivedBytes) != ROE_SUCCESS) {
            LV_LOG_WARN("[IPC][DROP] invalid message type:%ld receivedBytes:%zd",
                        message.msgType, receivedBytes);
            continue;
        }

        UiIpcEvent_st event = {
            .msgType = message.msgType,
            .receivedBytes = (ROE_SIZE)receivedBytes,
        };
        memcpy(&event.rawData, message.msgData, (ROE_SIZE)receivedBytes);
        if(ui_ipc_event_queue_push(&event) != ROE_SUCCESS) {
            LV_LOG_ERROR("[IPC][QUEUE] event queue stopped or full");
            atomic_store(&parameters->g_quit, 1);
            break;
        }
    }

cleanup:
    if(registerSent && parameters->sendMsgQueId >= 0) {
        ReqRegister_st unregisterRequest = {.reg = 0};
        if(SendMsg4UiRegisterReq(parameters->sendMsgQueId, &unregisterRequest) != ROE_SUCCESS) {
            LV_LOG_ERROR("[IPC][EXIT] unregister request failed");
        }
    }
    receiver_shutdown(parameters);
    return NULL;
}
