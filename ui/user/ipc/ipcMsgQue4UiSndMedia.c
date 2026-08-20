//
// Created by jinxing on 2026/2/11.
//

#include "ipcMsgQue4UiSndRequest.h"
#include "ipcMsgQue4UiSndInternal.h"

ROE_S32 SendMsg4UiGetMediaFileListReq(ROE_S32 msgQueId, ReqGetMediaFileList_st * getMediaFileList)
{
    return SendMsg4UiReq(
        msgQueId,
        MSG_4_REQ_RES_GET_MEDIA_FILE_LIST,
        getMediaFileList,
        sizeof(ReqGetMediaFileList_st),
        ROE_NULL);
}

static ROE_S32 SendMsg4UiDelOrPlayMediaFileReq(ROE_S32 msgQueId, ROE_S32 concreteType, ROE_S8 * filename)
{
    StringData_st strData = {.stringNum = 1, .pStringList = {filename}};
    return SendMsg4UiReq(msgQueId, concreteType, ROE_NULL, 0, &strData);
}

ROE_S32 SendMsg4UiDelMediaFileReq(ROE_S32 msgQueId, ROE_S8 * filename)
{
    return SendMsg4UiDelOrPlayMediaFileReq(msgQueId, MSG_4_REQ_RES_DEL_MEDIA_FILE, filename);
}

ROE_S32 SendMsg4UiPlayMediaFileReq(ROE_S32 msgQueId, ROE_S8 * filename)
{
    return SendMsg4UiDelOrPlayMediaFileReq(msgQueId, MSG_4_REQ_RES_PLAY_MEDIA_FILE, filename);
}

ROE_S32 SendMsg4UiPlayPriorOrNextMediaFileReq(ROE_S32 msgQueId, ROE_U8 direction)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_PLAY_ADJACENT_MEDIA_FILE, &direction, sizeof(direction), ROE_NULL);
}

ROE_S32 SendMsg4UiExitMediaPlayReq(ROE_S32 msgQueId)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_STOP_MEDIA_FILE_PLAY, ROE_NULL, 0, ROE_NULL);
}
