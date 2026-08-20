//
// Created by jinxing on 2026/3/2.
//

#include "ipcMsgQue4UiRcvRes.h"
#include "handleRcvRes.h"
#include "mainpage_event_handle.h"

static void update_user_common_from_rsp(ROE_U8 showDateTime,
                                        ROE_U16 standbyTimeout,
                                        ROE_U16 shutdownTimeout,
                                        ROE_U8 distanceUnit)
{
    userCommonConfig.showDateTime = showDateTime;
    userCommonConfig.standbyTimeout = standbyTimeout;
    userCommonConfig.shutdownTimeout = shutdownTimeout;
    userCommonConfig.distanceUnit = distanceUnit;
    ui_apply_user_common_config();
}

static void update_user_media_from_rsp(ROE_U8 burstCount,
                                       ROE_U16 maxRecordDuration,
                                       ROE_U8 recoilPreRecordSwitch,
                                       ROE_U16 recoilPreRecordDuration,
                                       ROE_U8 micSwitch)
{
    userMediaConfig.burstCount = burstCount;
    userMediaConfig.maxRecordDuration = maxRecordDuration;
    userMediaConfig.recoilPreRecordSwitch = recoilPreRecordSwitch;
    userMediaConfig.recoilPreRecordDuration = recoilPreRecordDuration;
    userMediaConfig.micSwitch = micSwitch;
    ui_apply_user_media_config();
}

ROE_S32 handleParseGetUserCommonConfigMsg(ROE_U8 * msgData)
{
    RspGetUserCommonConfig_st * result = (RspGetUserCommonConfig_st *)msgData;
    if(result->result != 0) {
        return ROE_FAILURE;
    }
    LV_LOG_USER("Get showDateTime:%d, standbyTimeout:%d, shutdownTimeout:%d, distanceUnit:%d",
                result->showDateTime,
                result->standbyTimeout,
                result->shutdownTimeout,
                result->distanceUnit);
    update_user_common_from_rsp(result->showDateTime,
                                result->standbyTimeout,
                                result->shutdownTimeout,
                                result->distanceUnit);
    return ROE_SUCCESS;
}

ROE_S32 handleParseSetUserCommonConfigMsg(ROE_U8 * msgData)
{
    RspSetUserCommonConfig_st * result = (RspSetUserCommonConfig_st *)msgData;
    if(result->result != 0) {
        return ROE_FAILURE;
    }
    LV_LOG_USER("Set showDateTime:%d, standbyTimeout:%d, shutdownTimeout:%d, distanceUnit:%d",
                result->showDateTime,
                result->standbyTimeout,
                result->shutdownTimeout,
                result->distanceUnit);
    update_user_common_from_rsp(result->showDateTime,
                                result->standbyTimeout,
                                result->shutdownTimeout,
                                result->distanceUnit);
    return ROE_SUCCESS;
}

ROE_S32 handleParseGetUserMediaConfigMsg(ROE_U8 * msgData)
{
    RspGetUserMediaConfig_st * result = (RspGetUserMediaConfig_st *)msgData;
    if(result->result != 0) {
        return ROE_FAILURE;
    }
    LV_LOG_USER(
        "Get burstCount:%d, maxRecordDuration:%d, recoilPreRecordSwitch:%d, recoilPreRecordDuration:%d, micSwitch:%d",
        result->burstCount,
        result->maxRecordDuration,
        result->recoilPreRecordSwitch,
        result->recoilPreRecordDuration,
        result->micSwitch);
    update_user_media_from_rsp(result->burstCount,
                               result->maxRecordDuration,
                               result->recoilPreRecordSwitch,
                               result->recoilPreRecordDuration,
                               result->micSwitch);
    return ROE_SUCCESS;
}

ROE_S32 handleParseSetUserMediaConfigMsg(ROE_U8 * msgData)
{
    RspSetUserMediaConfig_st * result = (RspSetUserMediaConfig_st *)msgData;
    if(result->result != 0) {
        return ROE_FAILURE;
    }
    LV_LOG_USER(
        "Set burstCount:%d, maxRecordDuration:%d, recoilPreRecordSwitch:%d, recoilPreRecordDuration:%d, micSwitch:%d",
        result->burstCount,
        result->maxRecordDuration,
        result->recoilPreRecordSwitch,
        result->recoilPreRecordDuration,
        result->micSwitch);
    update_user_media_from_rsp(result->burstCount,
                               result->maxRecordDuration,
                               result->recoilPreRecordSwitch,
                               result->recoilPreRecordDuration,
                               result->micSwitch);
    return ROE_SUCCESS;
}