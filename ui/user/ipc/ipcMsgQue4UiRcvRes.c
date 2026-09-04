//
// Created by jinxing on 2026/2/11.
//

#include "ipcMsgQue4UiRcvRes.h"
#include "ipc_message_dispatch.h"
#include "handleRcvRes.h"
#include "lvgl/lvgl.h"

typedef IpcMessageHandler FtHandleReqRes_st;

static const FtHandleReqRes_st f_SystemFunction[MSG_4_REQ_RES_SYSTEM_GENERAL_BUTT - MSG_4_REQ_RES_SYSTEM_GENERAL_OFFSET] = {
    handleParseRegisterMsg,
    handleParseShutdownMsg,
    handleParseGetAppVersionMsg,
    handleParseSetSystemTimeMsg,
    handleParseFormatDiskPartitionMsg,
};

static const FtHandleReqRes_st f_SystemConfiguration[MSG_4_REQ_RES_SYSTEM_CONFIG_BUTT - MSG_4_REQ_RES_SYSTEM_CONFIG_OFFSET] =
{
    handleParseRestoreFactorySettingMsg,
    handleParseSaveLanguageConfigMsg,
    handleParseGetUserCommonConfigMsg,
    handleParseSetUserCommonConfigMsg,
    handleParseGetUserMediaConfigMsg,
    handleParseSetUserMediaConfigMsg,
};

static const FtHandleReqRes_st f_SystemUserInterface[MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_BUTT -
                                               MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_OFFSET] = {
    handleParseExitMenuMsg,
    handleParseExitDialogBoxMsg,
};

static const FtHandleReqRes_st f_ShootingDifferentiation[
    MSG_4_REQ_RES_RETICLE_GENERAL_BUTT - MSG_4_REQ_RES_RETICLE_GENERAL_OFFSET] = {
    handleParseSetReticleCommonConfigMsg,
    handleParseWeaponSetReticleStyleMsg,
    handleParseWeaponSetReticleColorMsg,
    handleParseWeaponBrightnessAdjustMsg,
    handleParseWeaponSaveConfigMsg,
    handleParseWeaponMarkConfigOperateMsg,
    handleParseWeaponSetDefaultShootDistanceMsg,
    handleParseWeaponOperateShootDistanceMsg,
    handleParseWeaponSetShootPositionMsg,
    handleParseWeaponSetShootZeroMsg,
};

static const FtHandleReqRes_st f_VideoOutputDisplay[MSG_4_REQ_RES_VIDEO_OUTPUT_BUTT - MSG_4_REQ_RES_VIDEO_OUTPUT_OFFSET] = {
    handleParseGetVideoOutputParaMsg,
    handleParseAdjustOledBrightnessMsg,
    handleParseAdjustOledContrastMsg,
    handleParseAdjustExtendDisplaySwitchStatusMsg,
    handleParseAdjustPipSwitchStatusMsg,
    handleParseAdjustVideoZoomMsg,
    handleParseFreezeVideoInputMsg,
    handleParseAdjustRecognitionSwitchStatusMsg,
};

static const FtHandleReqRes_st f_VideoCaptureInput[MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_BUTT -
                                             MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_OFFSET] = {
    handleParseGetVideoInputParaMsg,
    handleParseAdjustObserveModeMsg,
    handleParseAdjustPipObserveModeMsg,
};

static const FtHandleReqRes_st f_VisibleLight[MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_BUTT - MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_OFFSET]
    =
    {
        handleParseGetVideoInputCameraParaMsg,
        handleParseAdjustDaynightSwitchStatusMsg,
        handleParseAdjustCameraBrightnessMsg,
        handleParseAdjustCameraContrastMsg,
        handleParseAdjustCameraSaturationMsg,
        handleParseAdjustCameraHueMsg,
        handleParseAdjustFogSwitchStatusMsg,
        handleParseAdjustFogIntensityMsg,
        handleParseAdjustCameraExposureMsg,
    };

static const FtHandleReqRes_st f_LowOllumination[MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_BUTT -
                                           MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_OFFSET] = {
    handleParseGetVideoInputLowLightParaMsg,
};

static const FtHandleReqRes_st f_Infrared[MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_BUTT - MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_OFFSET]
    = {
        handleParseGetVideoInputInfraredParaMsg,
        handleParseAdjustInfraredPseudocolorModeMsg,
        handleParseAdjustInfraredBrightnessMsg,
        handleParseAdjustInfraredContrastMsg,
        handleParseInfraredEnhanceImageMsg,
        handleParseInfraredAdjustScenarioModeMsg,
        handleParseInfraredSwitchHotspotTrackingMsg,
    };

static const FtHandleReqRes_st f_RemoteVideo[MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_BUTT - MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_OFFSET]
    = {
        handleParseGetVideoInputRemoteParaMsg,
    };

static const FtHandleReqRes_st f_AudioInputAndOutput[MSG_4_REQ_RES_AUDIO_BUTT - MSG_4_REQ_RES_AUDIO_GENERAL_OFFSET] = {
    handleParseGetAudioParaMsg,
};

static const FtHandleReqRes_st f_MediaFile[MSG_4_REQ_RES_MEDIA_FILE_BUTT - MSG_4_REQ_RES_MEDIA_FILE_OFFSET] = {
    handleParseCaptureMediaFileMsg,
    handleParseRecordMediaFileMsg,
    handleParseGetMediaFileListMsg,
    handleParseExitPlaybackMediaListMsg,
    handleParseDelMediaFileMsg,
    handleParsePlayMediaFileMsg,
    handleParsePlayPriorOrNextMediaFileMsg,
    handleParseExitMediaPlayStatusMsg,
};

static const FtHandleReqRes_st F_usb[MSG_4_REQ_RES_PERIPHERAL_USB_BUTT - MSG_4_REQ_RES_PERIPHERAL_USB_OFFSET] = {
    handleParseGetPeripheralUsbParaMsg,
};

static const FtHandleReqRes_st f_Network[MSG_4_REQ_RES_PERIPHERAL_NETWORK_BUTT - MSG_4_REQ_RES_PERIPHERAL_NETWORK_OFFSET] = {
    handleParseGetPeripheralNetworkParaMsg,
    handleParseAdjustWifiSwitchMsg,
    handleParseGetWifiInfoMsg,
};

static const FtHandleReqRes_st f_VisibleLightModule[MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_BUTT -
                                              MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_OFFSET] = {
    handleParseGetPeripheralCameraModuleParaMsg,
};

static const FtHandleReqRes_st f_LowLightModule[MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_BUTT -
                                          MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_OFFSET] = {
    handleParseGetPeripheralLowLightModuleParaMsg,
};

static const FtHandleReqRes_st f_InfraredModule[MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_BUTT -
                                          MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_OFFSET] = {
    handleParseGetPeripheralInfraredModuleParaMsg,
    handleParseInfraredManualRemoveBadPixelMsg,
    handleParseInfraredSetBadPixelThresholdMsg,
    handleParseInfraredBadPixelOperateMsg,
    handleParseInfraredHotPixelRepairOperateMsg,
    handleParseInfraredSdNucMsg,
};

static const FtHandleReqRes_st f_RomoteVideoEquipment[MSG_4_REQ_RES_PERIPHERAL_REMOTE_VIDEO_MODULE_BUTT -
                                                MSG_4_REQ_RES_PERIPHERAL_REMOTED_VIDEO_MODULE_OFFSET] = {
    handleParseGetPeripheralRemotedVideoModuleParaMsg,
};

static const FtHandleReqRes_st f_ElectronicCompass[MSG_4_REQ_RES_PERIPHERAL_COMPASS_BUTT -
                                             MSG_4_REQ_RES_PERIPHERAL_COMPASS_OFFSET] = {
    handleParseGetPeripheralCompassParaMsg,
    handleParseAdjustCompassSwitchStatusMsg,
    handleParseSetCompassMagneticDeclinationMsg,
    handleParseSaveCompassConfigMsg,
    handleParseStartCompassCalibrationMsg,
    handleParseStopCompassCalibrationMsg,
};

static const FtHandleReqRes_st f_SatellitePositioning[MSG_4_REQ_RES_PERIPHERAL_GNSS_BUTT -
                                                MSG_4_REQ_RES_PERIPHERAL_GNSS_OFFSET] = {
    handleParseGetPeripheralGnssParaMsg,
    handleParseAdjustGnssSwitchStatusMsg,
    handleParseAdjustGnssPositionSystemMsg,
    handleParseAdjustCoordinateSystemMsg,
};

static const FtHandleReqRes_st f_RangeFinder[MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_BUTT -
                                       MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_OFFSET] = {
    handleParseGetPeripheralRangeFinderParaMsg,
    handleParseAdjustRangeFinderSwitchStatusMsg,
    handleParseAdjustRangeFrequencyMsg,
    handleParseAdjustRangeTimeDurationMsg,
};

static const FtHandleReqRes_st f_Holder[MSG_4_REQ_RES_PERIPHERAL_PANTILT_BUTT - MSG_4_REQ_RES_PERIPHERAL_PANTILT_OFFSET] = {
    handleParseGetPeripheralPanTiltParaMsg,
    handleParsePanTiltMovingControlMsg,
    handleParsePanTiltMovingSpeedControlMsg,
};

ROE_S32 ParseResMsg(ROE_SL msgType, const RoeIpcMsgQueRawData_st * rawData)
{
    if(!rawData) return ROE_FAILURE;

    static const IpcMessageHandlerRange_st handlerRanges[] = {
        {MSG_4_REQ_RES_SYSTEM_GENERAL_OFFSET, MSG_4_REQ_RES_SYSTEM_GENERAL_BUTT, f_SystemFunction},
        {MSG_4_REQ_RES_SYSTEM_CONFIG_OFFSET, MSG_4_REQ_RES_SYSTEM_CONFIG_BUTT, f_SystemConfiguration},
        {MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_OFFSET, MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_BUTT, f_SystemUserInterface},
        {MSG_4_REQ_RES_RETICLE_GENERAL_OFFSET, MSG_4_REQ_RES_RETICLE_GENERAL_BUTT, f_ShootingDifferentiation},
        {MSG_4_REQ_RES_VIDEO_OUTPUT_OFFSET, MSG_4_REQ_RES_VIDEO_OUTPUT_BUTT, f_VideoOutputDisplay},
        {MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_BUTT, f_VideoCaptureInput},
        {MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_BUTT, f_VisibleLight},
        {MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_BUTT, f_LowOllumination},
        {MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_BUTT, f_Infrared},
        {MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_BUTT, f_RemoteVideo},
        {MSG_4_REQ_RES_AUDIO_GENERAL_OFFSET, MSG_4_REQ_RES_AUDIO_BUTT, f_AudioInputAndOutput},
        {MSG_4_REQ_RES_MEDIA_FILE_OFFSET, MSG_4_REQ_RES_MEDIA_FILE_BUTT, f_MediaFile},
        {MSG_4_REQ_RES_PERIPHERAL_USB_OFFSET, MSG_4_REQ_RES_PERIPHERAL_USB_BUTT, F_usb},
        {MSG_4_REQ_RES_PERIPHERAL_NETWORK_OFFSET, MSG_4_REQ_RES_PERIPHERAL_NETWORK_BUTT, f_Network},
        {MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_OFFSET, MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_BUTT,
         f_VisibleLightModule},
        {MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_OFFSET, MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_BUTT,
         f_LowLightModule},
        {MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_OFFSET, MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_BUTT,
         f_InfraredModule},
        {MSG_4_REQ_RES_PERIPHERAL_REMOTED_VIDEO_MODULE_OFFSET,
         MSG_4_REQ_RES_PERIPHERAL_REMOTE_VIDEO_MODULE_BUTT,
         f_RomoteVideoEquipment},
        {MSG_4_REQ_RES_PERIPHERAL_COMPASS_OFFSET, MSG_4_REQ_RES_PERIPHERAL_COMPASS_BUTT, f_ElectronicCompass},
        {MSG_4_REQ_RES_PERIPHERAL_GNSS_OFFSET, MSG_4_REQ_RES_PERIPHERAL_GNSS_BUTT, f_SatellitePositioning},
        {MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_OFFSET, MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_BUTT, f_RangeFinder},
        {MSG_4_REQ_RES_PERIPHERAL_PANTILT_OFFSET, MSG_4_REQ_RES_PERIPHERAL_PANTILT_BUTT, f_Holder},
    };

    ROE_S32 result = ipc_dispatch_message(msgType,
                                          (ROE_U8 *)rawData->data,
                                          handlerRanges,
                                          sizeof(handlerRanges) / sizeof(handlerRanges[0]));
    if(result != ROE_SUCCESS) {
        LV_LOG_ERROR("[IPC][RESPONSE] no handler or handler failed type:%ld", msgType);
    }
    return result;
}
