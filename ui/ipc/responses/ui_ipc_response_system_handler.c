//
// Created by jinxing on 2026/3/2.
//

#include "ui_ipc_response_types.h"
#include "lvgl/lvgl.h"
#include "ui_ipc_response_handler.h"
#include "ui_ipc_response_helpers.h"
#include "ui.h"
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

ROE_S32 UiIpcHandleResponseRestoreFactory(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseRestoreFactory);
}

ROE_S32 UiIpcHandleResponseFormatDisk(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseFormatDisk);
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
