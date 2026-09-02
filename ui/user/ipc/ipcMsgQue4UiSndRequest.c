//
// Created by jinxing on 2026/2/11.
//

#include "ipcMsgQue4UiSndRequest.h"
#include "msg.h"
#include <limits.h>
#include <string.h>

static ROE_SIZE roeStrlen(const char * str)
{
    return str ? strlen(str) : 0;
}

static ROE_S32 setMsgHeader4Ui(MsgQueHeader4Ui_st * head, ROE_U8 version, ROE_U8 concreteType)
{
    head->version = version;
    head->concreteMsgType = concreteType;
    gettimeofday(&head->tv, ROE_NULL);
    return sizeof(MsgQueHeader4Ui_st);
}

static ROE_S32 fillExtendstringToMsg(ROE_U8 * buf, ROE_SIZE bufSize, StringData_st * strData)
{
    if(!buf || !strData || strData->stringNum > UI_MAX_EXTEND_STRING_NUM) {
        return ROE_FAILURE;
    }

    ROE_U8 totalNum = strData->stringNum;
    ROE_S8 ** pStr = strData->pStringList;
    if(totalNum > 0 && !pStr) {
        return ROE_FAILURE;
    }

    ROE_U8 * cur = buf;
    ROE_U8 * pCurStrText;
    ROE_U8 size;
    for(ROE_U8 index = 0; index < totalNum; index++) {
        pCurStrText = (ROE_U8 *)pStr[index];
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
                                       ROE_VOID * arg,
                                       ROE_S32 argSize,
                                       StringData_st * strData)
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

static ROE_S32 SendMsg4Ui(ROE_S32 msgQueId, ROE_SL msgType, ROE_VOID * param)
{
    if(msgQueId < 0 || msgType < 1) {
        return ROE_FAILURE;
    }
    if(!param) {
        return ROE_FAILURE;
    }

    ParamOfMsg4Ui_st * uiParam = param;
    RoeIpcMsgQueBuff_st msgBuf = {.msgType = msgType};
    RoeIpcMsgQueRawData_st * raw = (RoeIpcMsgQueRawData_st *)(msgBuf.msgData);

    raw->dataLength = setMsgHeader4Ui((MsgQueHeader4Ui_st *)raw->data, uiParam->version, uiParam->concreteType);
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

    if(msgsnd(msgQueId, &msgBuf, raw->dataLength + sizeof(raw->dataLength), IPC_NOWAIT) == -1) {
        return ROE_FAILURE;
    }

    return ROE_SUCCESS;
}

static ROE_S32 SendMsg4UiConcreteType(ROE_S32 msgQueId,
                                      ROE_S32 msgType,
                                      void * arg,
                                      ROE_S32 argSize,
                                      StringData_st * pStrData)
{
    ParamOfMsg4Ui_st uiParam = {.version = UI_MSG_VERSION,
                                .concreteType = msgType - MSG_4_REQ_RES_INIT,
                                .pFormatParam = arg,
                                .formatParamSize = argSize};
    if(pStrData) {
        memcpy(&uiParam.strData, pStrData, sizeof(uiParam.strData));
    }
    return SendMsg4Ui(msgQueId, msgType, &uiParam);
}

ROE_S32 SendMsg4UiReq(ROE_S32 msgQueId, ROE_S32 msgType, void * arg, ROE_S32 argSize, StringData_st * pStrData)
{
    return SendMsg4UiConcreteType(msgQueId, msgType, arg, argSize, pStrData);
}
