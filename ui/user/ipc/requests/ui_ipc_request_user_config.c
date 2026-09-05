//
// Created by jinxing on 2026/2/11.
//

#include "ui_ipc_request_sender.h"
#include "ui_ipc_request_internal.h"
ROE_S32 UiIpcSendGetUserCommonConfigRequest(ROE_S32 msgQueId)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_GET_USER_COMMON_CONFIG, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 UiIpcSendSetUserCommonConfigRequest(ROE_S32 msgQueId, UiRequestSetUserCommonConfig * setUserCommonConfig)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_SET_USER_COMMON_CONFIG,
                         setUserCommonConfig,
                         sizeof(UiRequestSetUserCommonConfig),
                         ROE_NULL);
}

ROE_S32 UiIpcSendGetUserMediaConfigRequest(ROE_S32 msgQueId)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_GET_USER_MEDIA_CONFIG, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 UiIpcSendSetUserMediaConfigRequest(ROE_S32 msgQueId, UiRequestSetUserMediaConfig * setUserMediaConfig)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_SET_USER_MEDIA_CONFIG,
                         setUserMediaConfig,
                         sizeof(UiRequestSetUserMediaConfig),
                         ROE_NULL);
}

