//
// Created by jinxing on 2026/2/11.
//

#include "ui_ipc_request_sender.h"
#include "ui_ipc_request_internal.h"
#include "ui_ipc_message.h"
#include "lvgl/lvgl.h"
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>

static ROE_SIZE roeStrlen(const char * str)
{
    return str ? strlen(str) : 0;
}

static ROE_S32 setMsgHeader4Ui(UiIpcMessageHeader * head, ROE_U8 version, ROE_U8 concreteType)
{
    struct timeval now;

    if(!head || gettimeofday(&now, ROE_NULL) != 0) {
        return ROE_FAILURE;
    }

    head->version = version;
    head->concreteMsgType = concreteType;
    head->timestamp.seconds = (ROE_S64)now.tv_sec;
    head->timestamp.microseconds = (ROE_S64)now.tv_usec;
    return sizeof(UiIpcMessageHeader);
}

static ROE_S32 fillExtendstringToMsg(ROE_U8 * buf,
                                      ROE_SIZE bufSize,
                                      const UiIpcStringList * strData)
{
    if(!buf || !strData || strData->stringNum > UI_MAX_EXTEND_STRING_NUM) {
        return ROE_FAILURE;
    }

    ROE_U8 totalNum = strData->stringNum;
    const ROE_S8 * const * pStr = strData->pStringList;
    if(totalNum > 0 && !pStr) {
        return ROE_FAILURE;
    }

    ROE_U8 * cur = buf;
    const ROE_U8 * pCurStrText;
    ROE_U8 size;
    for(ROE_U8 index = 0; index < totalNum; index++) {
        pCurStrText = (const ROE_U8 *)pStr[index];
        if(!pCurStrText) {
            return ROE_FAILURE;
        }
        ROE_SIZE strLen = roeStrlen((const char *)pCurStrText);
        if(strLen >= UCHAR_MAX) {
            return ROE_FAILURE;
        }

        size = (ROE_U8)strLen;
        if(size) size++;

        if(bufSize < (ROE_SIZE)size + 1U) {
            return ROE_FAILURE;
        }
        memcpy(cur++, &size, sizeof(size));
        if(size) {
            memcpy(cur, pCurStrText, size);
            cur += size;
        }
        bufSize -= (ROE_SIZE)size + 1U;
    }
    return (ROE_S32)(cur - buf);
}

static ROE_S32 fillMsg4UiTransmission(ROE_U8 * buf,
                                       ROE_SIZE bufSize,
                                       const void * arg,
                                       ROE_S32 argSize,
                                       const UiIpcStringList * strData)
{
    if(!buf || argSize < 0 || (argSize > 0 && !arg) || (ROE_SIZE)argSize > bufSize) {
        return ROE_FAILURE;
    }

    ROE_SIZE msgTextAddedSize = 0;
    if(argSize > 0) {
        memcpy(buf, arg, (ROE_SIZE)argSize);
        msgTextAddedSize = (ROE_SIZE)argSize;
    }

    if(strData) {
        ROE_S32 stringSize = fillExtendstringToMsg(buf + msgTextAddedSize,
                                                    bufSize - msgTextAddedSize,
                                                    strData);
        if(stringSize < 0 || (ROE_SIZE)stringSize > bufSize - msgTextAddedSize) {
            return ROE_FAILURE;
        }
        msgTextAddedSize += (ROE_SIZE)stringSize;
    }

    if(msgTextAddedSize > (ROE_SIZE)INT_MAX) {
        return ROE_FAILURE;
    }
    return msgTextAddedSize;
}

static ROE_S32 UiIpcSendRawMessage(ROE_S32 msgQueId, ROE_SL msgType, ROE_VOID * param)
{
    if(msgQueId < 0 || msgType < 1) {
        return ROE_FAILURE;
    }
    if(!param) {
        return ROE_FAILURE;
    }

    const UiIpcRequestBuildParams * uiParam = param;
    UiIpcMessageBuffer msgBuf = {.msgType = msgType};
    UiIpcRawData * raw = (UiIpcRawData *)(msgBuf.msgData);

    raw->dataLength = setMsgHeader4Ui((UiIpcMessageHeader *)raw->data, uiParam->version, uiParam->concreteType);
    if(raw->dataLength < 0 || (ROE_SIZE)raw->dataLength > sizeof(raw->data)) {
        return ROE_FAILURE;
    }

    ROE_S32 transmissionSize = fillMsg4UiTransmission(
        raw->data + raw->dataLength,
        sizeof(raw->data) - (ROE_SIZE)raw->dataLength,
        uiParam->pFormatParam,
        uiParam->formatParamSize,
        &uiParam->strData);
    if(transmissionSize < 0 || (ROE_SIZE)transmissionSize > sizeof(raw->data) - (ROE_SIZE)raw->dataLength) {
        return ROE_FAILURE;
    }
    raw->dataLength += transmissionSize;

    const size_t messageBytes = (size_t)raw->dataLength + sizeof(raw->dataLength);
    if(msgsnd(msgQueId, &msgBuf, messageBytes, IPC_NOWAIT) == -1) {
        LV_LOG_ERROR("[IPC][SEND] msgsnd failed type:%ld bytes:%zu errno:%d",
                     msgType,
                     messageBytes,
                     errno);
        return ROE_FAILURE;
    }

    LV_LOG_USER("[IPC][SEND] type:%ld concrete:%u payload:%d bytes:%zu",
                msgType,
                (unsigned)uiParam->concreteType,
                raw->dataLength,
                messageBytes);

    return ROE_SUCCESS;
}

static ROE_S32 UiIpcSendMessage(ROE_S32 msgQueId,
                                      ROE_S32 msgType,
                                      const void * arg,
                                      ROE_S32 argSize,
                                      const UiIpcStringList * pStrData)
{
    if(msgType < MSG_4_REQ_RES_INIT || msgType >= MSG_4_REQ_RES_BUTT) {
        LV_LOG_ERROR("[IPC][SEND] invalid request type:%d", msgType);
        return ROE_FAILURE;
    }

    UiIpcRequestBuildParams uiParam = {.version = UI_IPC_MESSAGE_VERSION,
                                .concreteType = ui_ipc_concrete_type(msgType),
                                .pFormatParam = arg,
                                .formatParamSize = argSize,
                                .strData = {0}};
    if(pStrData) uiParam.strData = *pStrData;
    return UiIpcSendRawMessage(msgQueId, msgType, &uiParam);
}

ROE_S32 UiIpcSendRequest(ROE_S32 msgQueId,
                      ROE_S32 msgType,
                      const void * arg,
                      ROE_S32 argSize,
                      const UiIpcStringList * pStrData)
{
    return UiIpcSendMessage(msgQueId, msgType, arg, argSize, pStrData);
}
