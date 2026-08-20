//
// Created by jinxing on 2026/2/11.
//

#include "ipcMsgQue4UiSndRequest.h"
#include "ipcMsgQue4UiSndInternal.h"

ROE_S32 SendMsg4UiRangeFinderSwitchReq(ROE_S32 msgQueId, ReqAdjustRangefinderSwitch_st * rangefinderSwitch)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_RANGE_FINDER_OPERATE,
                         rangefinderSwitch,
                         sizeof(ReqAdjustRangefinderSwitch_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiRangeFrequencyReq(ROE_S32 msgQueId, ReqAdjustRangeFrequency_st * rangeFrequency)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_RANGE_FREQUENCY_ADJUST,
                         rangeFrequency,
                         sizeof(ReqAdjustRangeFrequency_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiRangeDurationReq(ROE_S32 msgQueId, ReqAdjustRangeDuration_st * rangeDuration)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_RANGE_TIME_DURATION_ADJUST,
                         rangeDuration,
                         sizeof(ReqAdjustRangeDuration_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiPipSwitchReq(ROE_S32 msgQueId, ReqAdjustPipSwitch_st * pipSwitch)
{
    return SendMsg4UiReq(
        msgQueId,
        MSG_4_REQ_RES_PIP_SWITCH,
        pipSwitch,
        sizeof(ReqAdjustPipSwitch_st),
        ROE_NULL);
}

ROE_S32 SendMsg4UiExtendDisplaySwitchReq(ROE_S32 msgQueId, ReqAdjustExtendDisplaySwitch_st * extendDisplaySwitch)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_EXTEND_DISPLAY_SWITCH,
                         extendDisplaySwitch,
                         sizeof(ReqAdjustExtendDisplaySwitch_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiOledBrightnessReq(ROE_S32 msgQueId, ReqAdjustOledBrightness_st * oledBrightness)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_MAIN_DISPLAY_BRIGHTNESS_ADJUST,
                         oledBrightness,
                         sizeof(ReqAdjustOledBrightness_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiOledContrastReq(ROE_S32 msgQueId, ReqAdjustOledContrast_st * oledContrast)
{
    return SendMsg4UiReq(
        msgQueId,
        MSG_4_REQ_RES_MAIN_DISPLAY_CONTRAST_ADJUST,
        oledContrast,
        sizeof(ReqAdjustOledContrast_st),
        ROE_NULL);
}

ROE_S32 SendMsg4UiVideoZoomReq(ROE_S32 msgQueId, ReqAdjustVideoZoom_st * adjustVideoZoom)
{
    return SendMsg4UiReq(
        msgQueId,
        MSG_4_REQ_RES_VIDEO_ZOOM,
        adjustVideoZoom,
        sizeof(ReqAdjustVideoZoom_st),
        ROE_NULL);
}

ROE_S32 SendMsg4UiShutdownReq(ROE_S32 msgQueId)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_SHUTDOWN, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 SendMsg4UiExitDialogBoxReq(ROE_S32 msgQueId)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_EXIT_DIALOG_BOX, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 SendMsg4UiExitPlaybackListReq(ROE_S32 msgQueId)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_EXIT_PLAYBACK_MEDIA_LIST, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 SendMsg4UiPanTiltMoveControlReq(ROE_S32 msgQueId, ReqPanTiltMoveControl_st * panTiltMoveControl)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_PANTILT_MOVING_CONTROL,
                         panTiltMoveControl,
                         sizeof(ReqPanTiltMoveControl_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiPanTiltSpeedControlReq(ROE_S32 msgQueId, ReqPanTiltSpeedControl_st * panTiltSpeedControl)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_PANTILT_MOVING_SPEED_ADJUST,
                         panTiltSpeedControl,
                         sizeof(ReqPanTiltSpeedControl_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiInfraredSetBadPixelThresholdReq(ROE_S32 msgQueId,
                                                  ReqInfraredSetBadPixelThreshold_st * infraredSetBadPixelThreshold)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_INFRARED_SET_BAD_PIXEL_THRESHOLD,
                         infraredSetBadPixelThreshold,
                         sizeof(ReqInfraredSetBadPixelThreshold_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiInfraredBadPixelOperateReq(ROE_S32 msgQueId, ReqInfraredBadPixelOperate_st * infraredBadPixelOperate)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_INFRARED_BAD_PIXEL_OPERATE,
                         infraredBadPixelOperate,
                         sizeof(ReqInfraredBadPixelOperate_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiSaveLanguageConfig(ROE_S32 msgQueId, ReqSaveLanguageConfig_st * saveLanguageConfig)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_SAVE_LANGUAGE_CONFIG,
                         saveLanguageConfig,
                         sizeof(ReqSaveLanguageConfig_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiInfraredHotPixelRepairReq(ROE_S32 msgQueId, ReqInfraredHotPixelRepair_st * infraredHotPixelRepair)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_INFRARED_HOT_PIXEL_REPAIR_OPERATE,
                         infraredHotPixelRepair,
                         sizeof(ReqInfraredHotPixelRepair_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiInfraredHotspotTrackingSwitchReq(ROE_S32 msgQueId,
                                                   ReqInfraredHotspotTrackingSwitch_st * infraredHotspotTrackingSwitch)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_INFRARED_HOT_PIXEL_REPAIR_OPERATE,
                         infraredHotspotTrackingSwitch,
                         sizeof(ReqInfraredHotspotTrackingSwitch_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiInfraredScenarioModeReq(ROE_S32 msgQueId, ReqInfraredScenarioMode_st * infraredScenarioMode)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_INFRARED_SCENARIO_MODE_SWITCHING,
                         infraredScenarioMode,
                         sizeof(ReqInfraredScenarioMode_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiInfraredEnhanceImageReq(ROE_S32 msgQueId, ReqInfraredEnhanceImage_st * infraredEnhanceImage)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_INFRARED_IMAGE_ENHANCE_ADJUST,
                         infraredEnhanceImage,
                         sizeof(ReqInfraredEnhanceImage_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiCameraSaturationReq(ROE_S32 msgQueId, ReqAdjustCameraSaturation_st * cameraSaturation)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_CAMERA_SATURATION_ADJUST,
                         cameraSaturation,
                         sizeof(ReqAdjustCameraSaturation_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiCameraHueReq(ROE_S32 msgQueId, ReqAdjustCameraHue_st * cameraHue)
{
    return SendMsg4UiReq(
        msgQueId,
        MSG_4_REQ_RES_CAMERA_HUE_ADJUST,
        cameraHue,
        sizeof(ReqAdjustCameraHue_st),
        ROE_NULL);
}

ROE_S32 SendMsg4UiFreezeVideoInputReq(ROE_S32 msgQueId, ReqFreezeVideoInput_st * freezeVideoInput)
{
    return SendMsg4UiReq(
        msgQueId,
        MSG_4_REQ_RES_VIDEO_OUTPUT_FREEZE,
        freezeVideoInput,
        sizeof(ReqFreezeVideoInput_st),
        ROE_NULL);
}
