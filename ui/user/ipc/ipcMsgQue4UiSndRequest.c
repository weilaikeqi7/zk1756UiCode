//
// Created by jinxing on 2026/2/11.
//

#include "ipcMsgQue4UiSndRequest.h"
#include "msg.h"
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

static ROE_S32 fillExtendstringToMsg(ROE_U8 * buf, StringData_st * strData)
{
    ROE_U8 totalNum = strData->stringNum;
    ROE_S8 ** pStr = strData->pStringList;
    ROE_U8 * cur = buf;
    ROE_U8 * pCurStrText;
    ROE_U8 size;
    for(ROE_U8 index = 0; index < totalNum; index++) {
        pCurStrText = (ROE_U8 *)pStr[index];
        size = roeStrlen((const char *)pCurStrText);
        if(size) {
            size++;
        }
        memcpy(cur++, &size, sizeof(size));
        if(size) {
            memcpy(cur, pCurStrText, size);
            cur += size;
        }
    }
    return (ROE_S32)(cur - buf);
}

static ROE_S32 fillMsg4UiTransmission(ROE_U8 * buf, ROE_VOID * arg, ROE_S32 argSize, StringData_st * strData)
{
    ROE_S32 msgTextAddedSize = (arg ? (memcpy(buf, arg, argSize), argSize) : 0);
    msgTextAddedSize += (strData ? fillExtendstringToMsg(buf + msgTextAddedSize, strData) : 0);
    return msgTextAddedSize;
}

static ROE_S32 SendMsg4Ui(ROE_S32 msgQueId, ROE_SL msgType, ROE_VOID * param)
{
    if(msgQueId < 0 || msgType < 1 || !param) {
        return ROE_FAILURE;
    }
    ParamOfMsg4Ui_st * uiParam = (ParamOfMsg4Ui_st *)param;
    RoeIpcMsgQueBuff_st msgBuf = {.msgType = msgType};
    RoeIpcMsgQueRawData_st * raw = (RoeIpcMsgQueRawData_st *)(msgBuf.msgData);

    raw->dataLength += setMsgHeader4Ui((MsgQueHeader4Ui_st *)raw->data, uiParam->version, uiParam->concreteType);
    raw->dataLength += fillMsg4UiTransmission(
        raw->data + raw->dataLength, uiParam->pFormatParam, uiParam->formatParamSize, &uiParam->strData);

    if(msgsnd(msgQueId, &msgBuf, raw->dataLength + sizeof(raw->dataLength), IPC_NOWAIT) == -1) {
        return ROE_FAILURE;
    }

    return ROE_SUCCESS;
}

static ROE_S32 SendMsg4UiConcreteType(
    ROE_S32 msgQueId, ROE_S32 msgType, ROE_S32 msgTypeInit, void * arg, ROE_S32 argSize, StringData_st * pStrData)
{
    ParamOfMsg4Ui_st uiParam = {.version = UI_MSG_VERSION,
                                .concreteType = msgType - msgTypeInit,
                                .pFormatParam = arg,
                                .formatParamSize = argSize};
    if(pStrData) {
        memcpy(&uiParam.strData, pStrData, sizeof(uiParam.strData));
    }
    return SendMsg4Ui(msgQueId, msgType, &uiParam);
}

ROE_S32 SendMsg4UiReq(ROE_S32 msgQueId, ROE_S32 msgType, void * arg, ROE_S32 argSize, StringData_st * pStrData)
{
    return SendMsg4UiConcreteType(msgQueId, msgType, MSG_4_REQ_RES_INIT, arg, argSize, pStrData);
}

