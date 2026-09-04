//
// Created by jinxing on 2026/3/2.
//

#include "ipcMsgQue4UiRcvRes.h"
#include "handleRcvRes.h"
#include "ipc_response_helpers.h"
#include "play_handle.h"

ROE_S32 handleParseAdjustRangeFinderSwitchStatusMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustRangefinderSwitch_st);
}

ROE_S32 handleParseAdjustRangeFrequencyMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustRangeFrequency_st);
}

ROE_S32 handleParseAdjustRangeTimeDurationMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustRangeDuration_st);
}

ROE_S32 handleParseAdjustPipSwitchStatusMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustPipSwitch_st);
}

ROE_S32 handleParseAdjustExtendDisplaySwitchStatusMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustExtendDisplaySwitch_st);
}

ROE_S32 handleParseAdjustOledBrightnessMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustOledBrightness_st);
}

ROE_S32 handleParseAdjustOledContrastMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustOledContrast_st);
}

ROE_S32 handleParseAdjustVideoZoomMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustVideoZoom_st);
}

ROE_S32 handleParseShutdownMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspShutdown_st);
}

ROE_S32 handleParseExitDialogBoxMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspExitDialogBox_st);
}

ROE_S32 handleParseExitPlaybackMediaListMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspExitPlaybackList_st);
}

ROE_S32 handleParsePanTiltMovingControlMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspPanTiltMoveControl_st);
}

ROE_S32 handleParsePanTiltMovingSpeedControlMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspPanTiltSpeedControl_st);
}

ROE_S32 handleParseInfraredSetBadPixelThresholdMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspInfraredSetBadPixelThreshold_st);
}

ROE_S32 handleParseInfraredBadPixelOperateMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspInfraredBadPixelOperate_st);
}

ROE_S32 handleParseSaveLanguageConfigMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspSaveLanguageConfig_st);
}

ROE_S32 handleParseInfraredHotPixelRepairOperateMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspInfraredHotPixelRepair_st);
}

ROE_S32 handleParseInfraredSwitchHotspotTrackingMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspInfraredHotspotTrackingSwitch_st);
}

ROE_S32 handleParseInfraredAdjustScenarioModeMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspInfraredScenarioMode_st);
}

ROE_S32 handleParseInfraredEnhanceImageMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspInfraredEnhanceImage_st);
}

ROE_S32 handleParseAdjustCameraSaturationMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustCameraSaturation_st);
}

ROE_S32 handleParseAdjustCameraHueMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspAdjustCameraHue_st);
}

ROE_S32 handleParseFreezeVideoInputMsg(ROE_U8 * msgData)
{
    IPC_RETURN_RESPONSE(msgData, RspFreezeVideoInput_st);
}
