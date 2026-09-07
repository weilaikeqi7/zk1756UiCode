//
// Created by jinxing on 2026/3/2.
//

#include "ui_ipc_response_types.h"
#include "lvgl/lvgl.h"
#include "ui_ipc_response_handler.h"
#include "menu_event_registry.h"

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

ROE_S32 UiIpcHandleResponseGetUserCommonConfig(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiResponseGetUserCommonConfig * result = (UiResponseGetUserCommonConfig *)msgData;
    if(result->result != 0) {
        LV_LOG_WARN("[IPC][RESPONSE] get user common config failed result:%u", (unsigned)result->result);
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

ROE_S32 UiIpcHandleResponseSetUserCommonConfig(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiResponseSetUserCommonConfig * result = (UiResponseSetUserCommonConfig *)msgData;
    if(result->result != 0) {
        LV_LOG_WARN("[IPC][RESPONSE] set user common config failed result:%u", (unsigned)result->result);
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

ROE_S32 UiIpcHandleResponseGetUserMediaConfig(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiResponseGetUserMediaConfig * result = (UiResponseGetUserMediaConfig *)msgData;
    if(result->result != 0) {
        LV_LOG_WARN("[IPC][RESPONSE] get user media config failed result:%u", (unsigned)result->result);
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

ROE_S32 UiIpcHandleResponseSetUserMediaConfig(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiResponseSetUserMediaConfig * result = (UiResponseSetUserMediaConfig *)msgData;
    if(result->result != 0) {
        LV_LOG_WARN("[IPC][RESPONSE] set user media config failed result:%u", (unsigned)result->result);
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
