//
// Created by jinxing on 2026/3/2.
//

#include "ui_ipc_response_types.h"
#include "ui_ipc_response_handler.h"
#include "ui_ipc_response_helpers.h"

ROE_S32 UiIpcHandleResponseRangeFinderOperate(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseRangeFinderOperate);
}

ROE_S32 UiIpcHandleResponseAdjustRangeFrequency(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustRangeFrequency);
}

ROE_S32 UiIpcHandleResponseAdjustRangeDuration(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustRangeDuration);
}

ROE_S32 UiIpcHandleResponseAdjustPipSwitch(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustPipSwitch);
}

ROE_S32 UiIpcHandleResponseAdjustExtendDisplaySwitch(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustExtendDisplaySwitch);
}

ROE_S32 UiIpcHandleResponseAdjustMainDisplayBrightness(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustMainDisplayBrightness);
}

ROE_S32 UiIpcHandleResponseAdjustMainDisplayContrast(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustMainDisplayContrast);
}

ROE_S32 UiIpcHandleResponseAdjustVideoZoom(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustVideoZoom);
}

ROE_S32 UiIpcHandleResponseShutdown(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseShutdown);
}

ROE_S32 UiIpcHandleResponseExitDialogBox(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseExitDialogBox);
}

ROE_S32 UiIpcHandleResponseExitPlaybackList(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseExitPlaybackList);
}

ROE_S32 UiIpcHandleResponsePanTiltMoveControl(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponsePanTiltMoveControl);
}

ROE_S32 UiIpcHandleResponsePanTiltSpeedControl(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponsePanTiltSpeedControl);
}

ROE_S32 UiIpcHandleResponseInfraredSetBadPixelThreshold(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseInfraredSetBadPixelThreshold);
}

ROE_S32 UiIpcHandleResponseInfraredBadPixelOperate(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseInfraredBadPixelOperate);
}

ROE_S32 UiIpcHandleResponseSaveLanguageConfig(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseSaveLanguageConfig);
}

ROE_S32 UiIpcHandleResponseInfraredHotPixelRepair(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseInfraredHotPixelRepair);
}

ROE_S32 UiIpcHandleResponseInfraredHotspotTrackingSwitch(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseInfraredHotspotTrackingSwitch);
}

ROE_S32 UiIpcHandleResponseInfraredScenarioMode(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseInfraredScenarioMode);
}

ROE_S32 UiIpcHandleResponseInfraredEnhanceImage(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseInfraredEnhanceImage);
}

ROE_S32 UiIpcHandleResponseAdjustCameraSaturation(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustCameraSaturation);
}

ROE_S32 UiIpcHandleResponseAdjustCameraHue(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseAdjustCameraHue);
}

ROE_S32 UiIpcHandleResponseFreezeVideoInput(ROE_U8 * msgData)
{
    UI_IPC_RETURN_RESPONSE(msgData, UiResponseFreezeVideoInput);
}
