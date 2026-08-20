//
// Created by jinxing on 2026/2/11.
//

#include "ipcMsgQue4UiSndRequest.h"
#include "ipcMsgQue4UiSndInternal.h"
ROE_S32 SendMsg4UiGetUserCommonConfigReq(ROE_S32 msgQueId)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_GET_USER_COMMON_CONFIG, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 SendMsg4UiSetUserCommonConfigReq(ROE_S32 msgQueId, ReqSetUserCommonConfig_st * setUserCommonConfig)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_SET_USER_COMMON_CONFIG,
                         setUserCommonConfig,
                         sizeof(ReqSetUserCommonConfig_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiGetUserMediaConfigReq(ROE_S32 msgQueId)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_GET_USER_MEDIA_CONFIG, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 SendMsg4UiSetUserMediaConfigReq(ROE_S32 msgQueId, ReqSetUserMediaConfig_st * setUserMediaConfig)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_SET_USER_MEDIA_CONFIG,
                         setUserMediaConfig,
                         sizeof(ReqSetUserMediaConfig_st),
                         ROE_NULL);
}

