//
// Created by jinxing on 2026/3/2.
//

#include "ipcMsgQue4UiRcvRes.h"
#include "lvgl/lvgl.h"
#include "handleRcvRes.h"
#include "ipc_response_helpers.h"
#include "play_handle.h"
#include "menu_handle.h"
#include <stdio.h>
#include <string.h>

ROE_S32 handleParseRegisterMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspRegister_st);
}

ROE_S32 handleParseExitMenuMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspExitMenu_st);
}

ROE_S32 handleParseSetSystemTimeMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspSetSystemTime_st);
}

ROE_S32 handleParseAdjustObserveModeMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustObserveMode_st);
}

ROE_S32 handleParseAdjustPipObserveModeMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustObserveMode_st);
}

ROE_S32 handleParseAdjustDaynightSwitchStatusMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustDayNight_st);
}

ROE_S32 handleParseAdjustRecognitionSwitchStatusMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustRecognitionSwitch_st);
}

ROE_S32 handleParseAdjustCameraBrightnessMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustCameraBrightness_st);
}

ROE_S32 handleParseAdjustInfraredBrightnessMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustInfraredBrightness_st);
}

ROE_S32 handleParseAdjustCameraContrastMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustCameraContrast_st);
}

ROE_S32 handleParseAdjustInfraredContrastMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustInfraredContrast_st);
}

ROE_S32 handleParseAdjustFogSwitchStatusMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustFogSwitch_st);
}

ROE_S32 handleParseAdjustFogIntensityMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustFogIntensity_st);
}

ROE_S32 handleParseAdjustCompassSwitchStatusMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustCompassSwitch_st);
}

ROE_S32 handleParseStartCompassCalibrationMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspStartCompassCalibration_st);
}

ROE_S32 handleParseStopCompassCalibrationMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspStopCompassCalibration_st);
}

ROE_S32 handleParseSetCompassMagneticDeclinationMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspSetCompassDeclination_st);
}

ROE_S32 handleParseSaveCompassConfigMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspSaveCompassConfig_st);
}

ROE_S32 handleParseAdjustGnssSwitchStatusMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustGnssSwitch_st);
}

ROE_S32 handleParseAdjustGnssPositionSystemMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustGnssSystem_st);
}

ROE_S32 handleParseAdjustCoordinateSystemMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustCoordinateSystem_st);
}

ROE_S32 handleParseRestoreFactorySettingMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspRestoreFactory_st);
}

ROE_S32 handleParseFormatDiskPartitionMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspFormatDisk_st);
}

ROE_S32 handleParseAdjustWifiSwitchMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustWifiSwitch_st);
}

ROE_S32 handleParseGetWifiInfoMsg(ROE_U8 * msgData)
{
    if(msgData == NULL || ui_infoLabel == NULL) return ROE_FAILURE;
    RspGetWifiInfo_st * result = (RspGetWifiInfo_st *)msgData;
    /* 处理 WIFI 信息获取结果 */
    if(result->result != 0U) {
        LV_LOG_WARN("[NETWORK][RSP] get wifi info failed result:%u", (unsigned)result->result);
        return ROE_FAILURE;
    }

    char wifiInfo[3][256] = {{0}}; // 0:ssid, 1:key, 2:rtspServerAddr
    msgData += sizeof(RspGetWifiInfo_st);

    for(ROE_U8 index = 0; index < 3; index++) {
        ROE_U8 curLen = *msgData++;
        ROE_SIZE copyLen = curLen;
        if(copyLen >= sizeof(wifiInfo[index])) {
            copyLen = sizeof(wifiInfo[index]) - 1U;
        }
        memcpy(wifiInfo[index], msgData, copyLen);
        wifiInfo[index][copyLen] = '\0';
        msgData += curLen;
    }

    char infoStr[512];
    lv_snprintf(infoStr, sizeof(infoStr), "%s", lv_label_get_text(ui_infoLabel));
    LV_LOG_USER("Hotspot Name: %s", wifiInfo[0]);
    LV_LOG_USER("Password: %s", wifiInfo[1]);
    LV_LOG_USER("Video URL: %s", wifiInfo[2]);
    lv_label_set_text_fmt(ui_infoLabel,
                          "Version:%s\nHotspot Name:%s\nPassword:%s\nVideo URL:%s",
                          infoStr,
                          wifiInfo[0],
                          wifiInfo[1],
                          wifiInfo[2]);
    show_menu_page3_item6_item5();
    return ROE_SUCCESS;
}

ROE_S32 handleParseGetAppVersionMsg(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    RspGetAppVersion_st * result = (RspGetAppVersion_st *)msgData;
    /* 处理版本信息获取结果 */
    if(result->result != 0U) {
        LV_LOG_WARN("[SYSTEM][RSP] get app version failed result:%u", (unsigned)result->result);
        return ROE_FAILURE;
    }

    char versionStr[256] = {0};
    ROE_SIZE copyLen = result->verLen;
    if(copyLen >= sizeof(versionStr)) {
        copyLen = sizeof(versionStr) - 1U;
    }
    memcpy(versionStr, result->version, copyLen);
    versionStr[copyLen] = '\0';
    if(ui_infoLabel == NULL) return ROE_FAILURE;
    lv_label_set_text(ui_infoLabel, versionStr);
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustInfraredPseudocolorModeMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustInfraredPseudoColor_st);
}
