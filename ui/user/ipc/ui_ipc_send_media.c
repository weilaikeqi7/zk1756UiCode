//
// Created by jinxing on 2026/2/11.
//

#include "ui_ipc_request_sender.h"
#include "ui_ipc_request_internal.h"

ROE_S32 UiIpcSendGetMediaFileListRequest(ROE_S32 msgQueId, UiRequestGetMediaFileList * getMediaFileList)
{
    if(!getMediaFileList || getMediaFileList->requestCount > UI_MAX_MEDIA_FILE_NUM_ONE_PAGE) {
        return ROE_FAILURE;
    }

    return UiIpcSendRequest(
        msgQueId,
        MSG_4_REQ_RES_GET_MEDIA_FILE_LIST,
        getMediaFileList,
        sizeof(UiRequestGetMediaFileList),
        ROE_NULL);
}

static ROE_S32 UiIpcSendDelOrPlayMediaFileRequest(ROE_S32 msgQueId, ROE_S32 concreteType, ROE_S8 * filename)
{
    UiIpcStringList strData = {.stringNum = 1, .pStringList = {filename}};
    return UiIpcSendRequest(msgQueId, concreteType, ROE_NULL, 0, &strData);
}

ROE_S32 UiIpcSendDeleteMediaFileRequest(ROE_S32 msgQueId, ROE_S8 * filename)
{
    return UiIpcSendDelOrPlayMediaFileRequest(msgQueId, MSG_4_REQ_RES_DEL_MEDIA_FILE, filename);
}

ROE_S32 UiIpcSendPlayMediaFileRequest(ROE_S32 msgQueId, ROE_S8 * filename)
{
    return UiIpcSendDelOrPlayMediaFileRequest(msgQueId, MSG_4_REQ_RES_PLAY_MEDIA_FILE, filename);
}

ROE_S32 UiIpcSendPlayAdjacentMediaFileRequest(ROE_S32 msgQueId, ROE_U8 direction)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_PLAY_ADJACENT_MEDIA_FILE, &direction, sizeof(direction), ROE_NULL);
}

ROE_S32 UiIpcSendStopMediaFilePlayRequest(ROE_S32 msgQueId)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_STOP_MEDIA_FILE_PLAY, ROE_NULL, 0, ROE_NULL);
}
