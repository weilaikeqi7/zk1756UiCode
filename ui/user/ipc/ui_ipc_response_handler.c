//
// Created by jinxing on 2026/3/2.
//

#include "ui_ipc_response_types.h"
#include "lvgl/lvgl.h"
#include "ui_ipc_response_handler.h"
#include "ui_ipc_response_helpers.h"
#include "menu_handle.h"
#include <stdio.h>
#include <string.h>

ROE_S32 UiIpcHandleResponseRegister(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseRegister);
}

ROE_S32 UiIpcHandleResponseExitMenu(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseExitMenu);
}

ROE_S32 UiIpcHandleResponseSetSystemTime(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseSetSystemTime);
}

ROE_S32 UiIpcHandleResponseAdjustObserveMode(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseSwitchMainObserveMode);
}

ROE_S32 UiIpcHandleResponseAdjustPipObserveMode(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseSwitchPipObserveMode);
}

ROE_S32 UiIpcHandleResponseAdjustDayNight(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustDayNight);
}

ROE_S32 UiIpcHandleResponseAdjustRecognitionSwitch(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustRecognitionSwitch);
}

ROE_S32 UiIpcHandleResponseAdjustCameraBrightness(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustCameraBrightness);
}

ROE_S32 UiIpcHandleResponseAdjustInfraredBrightness(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustInfraredBrightness);
}

ROE_S32 UiIpcHandleResponseAdjustCameraContrast(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustCameraContrast);
}

ROE_S32 UiIpcHandleResponseAdjustInfraredContrast(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustInfraredContrast);
}

ROE_S32 UiIpcHandleResponseAdjustFogSwitch(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustFogSwitch);
}

ROE_S32 UiIpcHandleResponseAdjustFogIntensity(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustFogIntensity);
}

ROE_S32 UiIpcHandleResponseAdjustCompassSwitch(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustCompassSwitch);
}

ROE_S32 UiIpcHandleResponseStartCompassCalibration(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseStartCompassCalibration);
}

ROE_S32 UiIpcHandleResponseStopCompassCalibration(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseStopCompassCalibration);
}

ROE_S32 UiIpcHandleResponseSetCompassDeclination(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseSetCompassDeclination);
}

ROE_S32 UiIpcHandleResponseSaveCompassConfig(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseSaveCompassConfig);
}

ROE_S32 UiIpcHandleResponseAdjustGnssSwitch(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustGnssSwitch);
}

ROE_S32 UiIpcHandleResponseAdjustGnssSystem(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustGnssSystem);
}

ROE_S32 UiIpcHandleResponseAdjustCoordinateSystem(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustCoordinateSystem);
}

ROE_S32 UiIpcHandleResponseRestoreFactory(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseRestoreFactory);
}

ROE_S32 UiIpcHandleResponseFormatDisk(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseFormatDisk);
}

ROE_S32 UiIpcHandleResponseAdjustWifiSwitch(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustWifiSwitch);
}

ROE_S32 UiIpcHandleResponseGetWifiInfo(ROE_U8 * msgData)
{
    if(msgData == NULL || ui_infoLabel == NULL) return ROE_FAILURE;
    UiResponseGetWifiInfo * result = (UiResponseGetWifiInfo *)msgData;
    /* 处理 WIFI 信息获取结果 */
    if(result->result != 0U) {
        LV_LOG_WARN("[NETWORK][RSP] get wifi info failed result:%u", (unsigned)result->result);
        return ROE_FAILURE;
    }

    char wifiInfo[3][256] = {{0}}; // 0:ssid, 1:key, 2:rtspServerAddr
    msgData += sizeof(UiResponseGetWifiInfo);

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

ROE_S32 UiIpcHandleResponseGetAppVersion(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiResponseGetAppVersion * result = (UiResponseGetAppVersion *)msgData;
    /* 处理版本信息获取结果 */
    if(result->result != 0U) {
        LV_LOG_WARN("[SYSTEM][RSP] get app version failed result:%u", (unsigned)result->result);
        return ROE_FAILURE;
    }

    char versionStr[256] = {0};
    ROE_SIZE copyLen = result->versionLength;
    if(copyLen >= sizeof(versionStr)) {
        copyLen = sizeof(versionStr) - 1U;
    }
    memcpy(versionStr, result->version, copyLen);
    versionStr[copyLen] = '\0';
    if(ui_infoLabel == NULL) return ROE_FAILURE;
    lv_label_set_text(ui_infoLabel, versionStr);
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleResponseAdjustInfraredPseudoColor(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustInfraredPseudoColor);
}
