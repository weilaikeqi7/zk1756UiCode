//
// Created by jinxing on 2026/3/2.
//

#include "ui_ipc_response_types.h"
#include "lvgl/lvgl.h"
#include "ui_ipc_response_handler.h"
#include "ui_ipc_response_helpers.h"
#include <stdio.h>
#include <string.h>

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

ROE_S32 UiIpcHandleResponseAdjustInfraredPseudoColor(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustInfraredPseudoColor);
}

ROE_S32 UiIpcHandleResponseAdjustCameraSaturation(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustCameraSaturation);
}

ROE_S32 UiIpcHandleResponseAdjustCameraHue(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustCameraHue);
}
