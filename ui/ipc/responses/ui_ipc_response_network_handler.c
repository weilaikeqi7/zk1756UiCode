//
// Created by jinxing on 2026/3/2.
//

#include "ui_ipc_response_types.h"
#include "lvgl/lvgl.h"
#include "ui_ipc_response_handler.h"
#include "ui_ipc_response_helpers.h"
#include "menu_visibility.h"
#include <string.h>

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
