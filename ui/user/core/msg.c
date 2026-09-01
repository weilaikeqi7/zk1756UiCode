//
// Created by jinxing on 2026/2/10.
//

#include "msg.h"
#include "ipcMsgQue4UiRcvNotify.h"
#include "ipcMsgQue4UiRcvRes.h"
#include "ipcMsgQue4UiTypeCommon.h"
#include "ipcMsgQue4UiSndRequest.h"
#include "ui.h"

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

void * message_recv_thread(void * arg)
{
    GlobalParameters * msg_args = arg;
    RoeIpcMsgQueBuff_st msgBuf;
    key_t sendKey = app_args.sendKey, recvKey = app_args.recvKey;

    msg_args->sendMsgQueId = msgget(sendKey, 0666);
    if(-1 == msg_args->sendMsgQueId) {
        LV_LOG_USER("creat send msg que failed!\n");
    } else {
        ReqRegister_st reqRegister = {.reg = 1};
        if(SendMsg4UiRegisterReq(msg_args->sendMsgQueId, &reqRegister)) {
            LV_LOG_USER("SendMsg4UiRegisterReq() failed!\n");
        }
    }

    msg_args->recvMsgQueId = msgget(recvKey, 0666);

    if(-1 == msg_args->recvMsgQueId) {
        LV_LOG_USER("creat send msg que failed!\n");
    }

    SendMsg4UiGetUserCommonConfigReq(msg_args->sendMsgQueId);
    SendMsg4UiGetUserMediaConfigReq(msg_args->sendMsgQueId);

    while(!msg_args->g_quit) {
        if(msgrcv(msg_args->recvMsgQueId, &msgBuf, sizeof(msgBuf.msgData), -MSG_4_REQ_RES_BUTT, 0) == -1) {
            LV_LOG_USER("msgrcv() failed, recvMsgQueId: %d\n", msg_args->recvMsgQueId);
            continue;
        }
        lv_lock();
        if(ParseNotifyAndResMsg(msgBuf.msgType, (RoeIpcMsgQueRawData_st *)msgBuf.msgData)) {
            LV_LOG_USER("msgBuf.msgType:%ld ParseNotifyMsg() failed\n", msgBuf.msgType);
        }
        lv_unlock();
    }

    ReqRegister_st reqRegister = {.reg = 0};
    if(SendMsg4UiRegisterReq(msg_args->sendMsgQueId, &reqRegister)) {
        LV_LOG_USER("SendMsg4UiRegisterReq() failed!\n");
    }

    if(-1 != msg_args->sendMsgQueId) {
        msgctl(msg_args->sendMsgQueId, IPC_RMID, NULL);
    }

    if(-1 != msg_args->recvMsgQueId) {
        msgctl(msg_args->recvMsgQueId, IPC_RMID, NULL);
    }
    pthread_exit(NULL);
}