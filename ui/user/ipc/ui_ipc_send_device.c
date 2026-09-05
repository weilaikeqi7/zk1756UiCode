//
// Created by jinxing on 2026/2/11.
//

#include "ui_ipc_request_sender.h"
#include "ui_ipc_request_internal.h"

ROE_S32 UiIpcSendRangeFinderOperateRequest(ROE_S32 msgQueId, UiRequestRangeFinderOperate * rangeFinderOperation)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_RANGE_FINDER_OPERATE,
                         rangeFinderOperation,
                         sizeof(UiRequestRangeFinderOperate),
                         ROE_NULL);
}

ROE_S32 UiIpcSendRangeFrequencyRequest(ROE_S32 msgQueId, UiRequestAdjustRangeFrequency * rangeFrequency)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_RANGE_FREQUENCY_ADJUST,
                         rangeFrequency,
                         sizeof(UiRequestAdjustRangeFrequency),
                         ROE_NULL);
}

ROE_S32 UiIpcSendAdjustRangeDurationRequest(ROE_S32 msgQueId, UiRequestAdjustRangeDuration * rangeDuration)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_RANGE_TIME_DURATION_ADJUST,
                         rangeDuration,
                         sizeof(UiRequestAdjustRangeDuration),
                         ROE_NULL);
}

ROE_S32 UiIpcSendPipSwitchRequest(ROE_S32 msgQueId, UiRequestAdjustPipSwitch * pipSwitch)
{
    return UiIpcSendRequest(
        msgQueId,
        MSG_4_REQ_RES_PIP_SWITCH,
        pipSwitch,
        sizeof(UiRequestAdjustPipSwitch),
        ROE_NULL);
}

ROE_S32 UiIpcSendExtendDisplaySwitchRequest(ROE_S32 msgQueId, UiRequestAdjustExtendDisplaySwitch * extendDisplaySwitch)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_EXTEND_DISPLAY_SWITCH,
                         extendDisplaySwitch,
                         sizeof(UiRequestAdjustExtendDisplaySwitch),
                         ROE_NULL);
}

ROE_S32 UiIpcSendMainDisplayBrightnessRequest(ROE_S32 msgQueId, UiRequestAdjustMainDisplayBrightness * mainDisplayBrightness)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_MAIN_DISPLAY_BRIGHTNESS_ADJUST,
                         mainDisplayBrightness,
                         sizeof(UiRequestAdjustMainDisplayBrightness),
                         ROE_NULL);
}

ROE_S32 UiIpcSendMainDisplayContrastRequest(ROE_S32 msgQueId, UiRequestAdjustMainDisplayContrast * mainDisplayContrast)
{
    return UiIpcSendRequest(
        msgQueId,
        MSG_4_REQ_RES_MAIN_DISPLAY_CONTRAST_ADJUST,
        mainDisplayContrast,
        sizeof(UiRequestAdjustMainDisplayContrast),
        ROE_NULL);
}

ROE_S32 UiIpcSendVideoZoomRequest(ROE_S32 msgQueId, UiRequestAdjustVideoZoom * adjustVideoZoom)
{
    return UiIpcSendRequest(
        msgQueId,
        MSG_4_REQ_RES_VIDEO_ZOOM,
        adjustVideoZoom,
        sizeof(UiRequestAdjustVideoZoom),
        ROE_NULL);
}

ROE_S32 UiIpcSendShutdownRequest(ROE_S32 msgQueId)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_SHUTDOWN, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 UiIpcSendExitDialogBoxRequest(ROE_S32 msgQueId)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_EXIT_DIALOG_BOX, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 UiIpcSendExitPlaybackListRequest(ROE_S32 msgQueId)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_EXIT_PLAYBACK_MEDIA_LIST, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 UiIpcSendPanTiltMoveControlRequest(ROE_S32 msgQueId, UiRequestPanTiltMoveControl * panTiltMoveControl)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_PANTILT_MOVING_CONTROL,
                         panTiltMoveControl,
                         sizeof(UiRequestPanTiltMoveControl),
                         ROE_NULL);
}

ROE_S32 UiIpcSendPanTiltSpeedControlRequest(ROE_S32 msgQueId, UiRequestPanTiltSpeedControl * panTiltSpeedControl)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_PANTILT_MOVING_SPEED_ADJUST,
                         panTiltSpeedControl,
                         sizeof(UiRequestPanTiltSpeedControl),
                         ROE_NULL);
}

ROE_S32 UiIpcSendInfraredSetBadPixelThresholdRequest(ROE_S32 msgQueId,
                                                  UiRequestInfraredSetBadPixelThreshold * infraredSetBadPixelThreshold)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_INFRARED_SET_BAD_PIXEL_THRESHOLD,
                         infraredSetBadPixelThreshold,
                         sizeof(UiRequestInfraredSetBadPixelThreshold),
                         ROE_NULL);
}

ROE_S32 UiIpcSendInfraredBadPixelOperateRequest(ROE_S32 msgQueId, UiRequestInfraredBadPixelOperate * infraredBadPixelOperate)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_INFRARED_BAD_PIXEL_OPERATE,
                         infraredBadPixelOperate,
                         sizeof(UiRequestInfraredBadPixelOperate),
                         ROE_NULL);
}

ROE_S32 UiIpcSendSaveLanguageConfigRequest(ROE_S32 msgQueId, UiRequestSaveLanguageConfig * saveLanguageConfig)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_SAVE_LANGUAGE_CONFIG,
                         saveLanguageConfig,
                         sizeof(UiRequestSaveLanguageConfig),
                         ROE_NULL);
}

ROE_S32 UiIpcSendInfraredHotPixelRepairRequest(ROE_S32 msgQueId, UiRequestInfraredHotPixelRepair * infraredHotPixelRepair)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_INFRARED_HOT_PIXEL_REPAIR_OPERATE,
                         infraredHotPixelRepair,
                         sizeof(UiRequestInfraredHotPixelRepair),
                         ROE_NULL);
}

ROE_S32 UiIpcSendInfraredHotspotTrackingSwitchRequest(ROE_S32 msgQueId,
                                                   UiRequestInfraredHotspotTrackingSwitch * infraredHotspotTrackingSwitch)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_INFRARED_HOTSPOT_TRACKING_SWITCH,
                         infraredHotspotTrackingSwitch,
                         sizeof(UiRequestInfraredHotspotTrackingSwitch),
                         ROE_NULL);
}

ROE_S32 UiIpcSendInfraredScenarioModeRequest(ROE_S32 msgQueId, UiRequestInfraredScenarioMode * infraredScenarioMode)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_INFRARED_SCENARIO_MODE_SWITCHING,
                         infraredScenarioMode,
                         sizeof(UiRequestInfraredScenarioMode),
                         ROE_NULL);
}

ROE_S32 UiIpcSendInfraredEnhanceImageRequest(ROE_S32 msgQueId, UiRequestInfraredEnhanceImage * infraredEnhanceImage)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_INFRARED_IMAGE_ENHANCE_ADJUST,
                         infraredEnhanceImage,
                         sizeof(UiRequestInfraredEnhanceImage),
                         ROE_NULL);
}

ROE_S32 UiIpcSendCameraSaturationRequest(ROE_S32 msgQueId, UiRequestAdjustCameraSaturation * cameraSaturation)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_CAMERA_SATURATION_ADJUST,
                         cameraSaturation,
                         sizeof(UiRequestAdjustCameraSaturation),
                         ROE_NULL);
}

ROE_S32 UiIpcSendCameraHueRequest(ROE_S32 msgQueId, UiRequestAdjustCameraHue * cameraHue)
{
    return UiIpcSendRequest(
        msgQueId,
        MSG_4_REQ_RES_CAMERA_HUE_ADJUST,
        cameraHue,
        sizeof(UiRequestAdjustCameraHue),
        ROE_NULL);
}

ROE_S32 UiIpcSendFreezeVideoInputRequest(ROE_S32 msgQueId, UiRequestFreezeVideoInput * freezeVideoInput)
{
    return UiIpcSendRequest(
        msgQueId,
        MSG_4_REQ_RES_VIDEO_OUTPUT_FREEZE,
        freezeVideoInput,
        sizeof(UiRequestFreezeVideoInput),
        ROE_NULL);
}
