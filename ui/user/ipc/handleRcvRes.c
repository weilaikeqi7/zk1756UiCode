//
// Created by jinxing on 2026/3/2.
//

#include "ipcMsgQue4UiRcvRes.h"
#include "handleRcvRes.h"
#include "play_handle.h"

ROE_S32 handleParseRegisterMsg(ROE_U8 * msgData)
{
    RspRegister_st * result = (RspRegister_st *)msgData;
    /* 具体操作 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseExitMenuMsg(ROE_U8 * msgData)
{
    RspExitMenu_st * result = (RspExitMenu_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleParseSetSystemTimeMsg(ROE_U8 * msgData)
{
    RspSetSystemTime_st * result = (RspSetSystemTime_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustObserveModeMsg(ROE_U8 * msgData)
{
    RspAdjustObserveMode_st * result = (RspAdjustObserveMode_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustDaynightSwitchStatusMsg(ROE_U8 * msgData)
{
    RspAdjustDayNight_st * result = (RspAdjustDayNight_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustRecognitionSwitchStatusMsg(ROE_U8 * msgData)
{
    RspAdjustRecognitionSwitch_st * result = (RspAdjustRecognitionSwitch_st *)msgData;
    /* 处理识别开关调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustCameraBrightnessMsg(ROE_U8 * msgData)
{
    RspAdjustCameraBrightness_st * result = (RspAdjustCameraBrightness_st *)msgData;
    /* 处理可见光亮度调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustInfraredBrightnessMsg(ROE_U8 * msgData)
{
    RspAdjustInfraredBrightness_st * result = (RspAdjustInfraredBrightness_st *)msgData;
    /* 处理红外亮度调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustCameraContrastMsg(ROE_U8 * msgData)
{
    RspAdjustCameraContrast_st * result = (RspAdjustCameraContrast_st *)msgData;
    /* 处理可见光对比度调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustInfraredContrastMsg(ROE_U8 * msgData)
{
    RspAdjustInfraredContrast_st * result = (RspAdjustInfraredContrast_st *)msgData;
    /* 处理红外对比度调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustFogSwitchStatusMsg(ROE_U8 * msgData)
{
    RspAdjustFogSwitch_st * result = (RspAdjustFogSwitch_st *)msgData;
    /* 处理可见光透雾开关调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustFogIntensityMsg(ROE_U8 * msgData)
{
    RspAdjustFogIntensity_st * result = (RspAdjustFogIntensity_st *)msgData;
    /* 处理可见光透雾强度调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustCompassSwitchStatusMsg(ROE_U8 * msgData)
{
    RspAdjustCompassSwitch_st * result = (RspAdjustCompassSwitch_st *)msgData;
    /* 处理电子罗盘开关调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseStartCompassCalibrationMsg(ROE_U8 * msgData)
{
    RspStartCompassCalibration_st * result = (RspStartCompassCalibration_st *)msgData;
    /* 处理电子罗盘开始校准结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseStopCompassCalibrationMsg(ROE_U8 * msgData)
{
    RspStopCompassCalibration_st * result = (RspStopCompassCalibration_st *)msgData;
    /* 处理电子罗盘停止校准结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseSetCompassMagneticDeclinationMsg(ROE_U8 * msgData)
{
    RspSetCompassDeclination_st * result = (RspSetCompassDeclination_st *)msgData;
    /* 处理电子罗盘设置磁偏角结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseSaveCompassConfigMsg(ROE_U8 * msgData)
{
    RspSaveCompassConfig_st * result = (RspSaveCompassConfig_st *)msgData;
    /* 处理电子罗盘保存配置结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustGnssSwitchStatusMsg(ROE_U8 * msgData)
{
    RspAdjustGnssSwitch_st * result = (RspAdjustGnssSwitch_st *)msgData;
    /* 处理卫星定位开关调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustGnssPositionSystemMsg(ROE_U8 * msgData)
{
    RspAdjustGnssSystem_st * result = (RspAdjustGnssSystem_st *)msgData;
    /* 处理卫星定位系统调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustCoordinateSystemMsg(ROE_U8 * msgData)
{
    RspAdjustCoordinateSystem_st * result = (RspAdjustCoordinateSystem_st *)msgData;
    /* 处理大地坐标系统调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseRestoreFactorySettingMsg(ROE_U8 * msgData)
{
    RspRestoreFactory_st * result = (RspRestoreFactory_st *)msgData;
    /* 处理恢复出厂设置结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseFormatDiskPartitionMsg(ROE_U8 * msgData)
{
    RspFormatDisk_st * result = (RspFormatDisk_st *)msgData;
    /* 处理磁盘格式化结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustWifiSwitchMsg(ROE_U8 * msgData)
{
    RspAdjustWifiSwitch_st * result = (RspAdjustWifiSwitch_st *)msgData;
    /* 处理 WIFI 开关调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseGetWifiInfoMsg(ROE_U8 * msgData)
{
    RspGetWifiInfo_st * result = (RspGetWifiInfo_st *)msgData;
    ROE_S8 * wifiInfo[3] = {ROE_NULL}; //0:ssid, 1: key 2:rtspServerAddr
    /* 处理 WIFI 信息获取结果 */
    if(result->result == 0) {
        char infoStr[512];
        msgData += sizeof(RspGetWifiInfo_st);
        ROE_U8 curLen;

        for(ROE_U8 index = 0; index < 3; index++) {
            curLen = *msgData;
            msgData += 1;
            wifiInfo[index] = (ROE_S8 *)msgData;
            msgData += curLen;
        }
        lv_strcpy(infoStr, lv_label_get_text(ui_infoLabel));
        LV_LOG_USER("Hotspot Name: %s", wifiInfo[0]);
        LV_LOG_USER("Password: %s", wifiInfo[1]);
        LV_LOG_USER("Video URL: %s", wifiInfo[2]);
        lv_label_set_text_fmt(ui_infoLabel,
                              "Version:%s\nHotspot Name:%s\nPassword:%s\nVideo URL:%s",
                              infoStr,
                              wifiInfo[0],
                              wifiInfo[1],
                              wifiInfo[2]);
        show_menu_page3_itme6_item5();
    }
    return ROE_SUCCESS;
}

ROE_S32 handleParseGetAppVersionMsg(ROE_U8 * msgData)
{
    RspGetAppVersion_st * result = (RspGetAppVersion_st *)msgData;
    /* 处理版本信息获取结果 */
    if(result->result == 0) {
        /* 解析版本号字符串 */
        ROE_U8 * versionStr = result->version;
        // versionStr[0:verLen] 为版本字符串
        lv_label_set_text(ui_infoLabel, (const char *)versionStr);
    }
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustInfraredPseudocolorModeMsg(ROE_U8 * msgData)
{
    RspAdjustInfraredPseudoColor_st * result = (RspAdjustInfraredPseudoColor_st *)msgData;
    /* 处理红外伪彩模式调整结果 */
    return ROE_SUCCESS;
}