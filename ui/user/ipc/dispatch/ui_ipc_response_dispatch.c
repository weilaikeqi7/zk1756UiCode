//
// Created by jinxing on 2026/2/11.
//

#include "ui_ipc_response_types.h"
#include "ui_ipc_dispatch.h"
#include "ui_ipc_dispatch_internal.h"
#include "ui_ipc_response_handler.h"
#include "lvgl/lvgl.h"

typedef UiIpcMessageHandler UiIpcResponseHandler;

static const UiIpcResponseHandler g_systemGeneralHandlers[MSG_4_REQ_RES_SYSTEM_GENERAL_BUTT - MSG_4_REQ_RES_SYSTEM_GENERAL_OFFSET] = {
    UiIpcHandleResponseRegister,
    UiIpcHandleResponseShutdown,
    UiIpcHandleResponseGetAppVersion,
    UiIpcHandleResponseSetSystemTime,
    UiIpcHandleResponseFormatDisk,
};

static const UiIpcResponseHandler g_systemConfigHandlers[MSG_4_REQ_RES_SYSTEM_CONFIG_BUTT - MSG_4_REQ_RES_SYSTEM_CONFIG_OFFSET] =
{
    UiIpcHandleResponseRestoreFactory,
    UiIpcHandleResponseSaveLanguageConfig,
    UiIpcHandleResponseGetUserCommonConfig,
    UiIpcHandleResponseSetUserCommonConfig,
    UiIpcHandleResponseGetUserMediaConfig,
    UiIpcHandleResponseSetUserMediaConfig,
};

static const UiIpcResponseHandler g_systemUiHandlers[MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_BUTT -
                                               MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_OFFSET] = {
    UiIpcHandleResponseExitMenu,
    UiIpcHandleResponseExitDialogBox,
};

static const UiIpcResponseHandler g_reticleHandlers[
    MSG_4_REQ_RES_RETICLE_GENERAL_BUTT - MSG_4_REQ_RES_RETICLE_GENERAL_OFFSET] = {
    UiIpcHandleResponseSetReticleCommonConfig,
    UiIpcHandleResponseWeaponSetReticleStyle,
    UiIpcHandleResponseWeaponSetReticleColor,
    UiIpcHandleResponseWeaponSetReticleBrightness,
    UiIpcHandleResponseWeaponSaveConfig,
    UiIpcHandleResponseWeaponMarkConfigOperate,
    UiIpcHandleResponseWeaponSetDefaultShootDistance,
    UiIpcHandleResponseWeaponOperateShootDistance,
    UiIpcHandleResponseWeaponSetShootPosition,
    UiIpcHandleResponseWeaponSetShootZero,
};

static const UiIpcResponseHandler g_videoOutputHandlers[MSG_4_REQ_RES_VIDEO_OUTPUT_BUTT - MSG_4_REQ_RES_VIDEO_OUTPUT_OFFSET] = {
    UiIpcHandleResponseGetVideoOutputParameters,
    UiIpcHandleResponseAdjustMainDisplayBrightness,
    UiIpcHandleResponseAdjustMainDisplayContrast,
    UiIpcHandleResponseAdjustExtendDisplaySwitch,
    UiIpcHandleResponseAdjustPipSwitch,
    UiIpcHandleResponseAdjustVideoZoom,
    UiIpcHandleResponseFreezeVideoInput,
    UiIpcHandleResponseAdjustRecognitionSwitch,
};

static const UiIpcResponseHandler g_videoInputHandlers[MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_BUTT -
                                             MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_OFFSET] = {
    UiIpcHandleResponseGetVideoInputParameters,
    UiIpcHandleResponseAdjustObserveMode,
    UiIpcHandleResponseAdjustPipObserveMode,
};

static const UiIpcResponseHandler g_cameraInputHandlers[MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_BUTT - MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_OFFSET]
    =
    {
        UiIpcHandleResponseGetVideoInputCameraParameters,
        UiIpcHandleResponseAdjustDayNight,
        UiIpcHandleResponseAdjustCameraBrightness,
        UiIpcHandleResponseAdjustCameraContrast,
        UiIpcHandleResponseAdjustCameraSaturation,
        UiIpcHandleResponseAdjustCameraHue,
        UiIpcHandleResponseAdjustFogSwitch,
        UiIpcHandleResponseAdjustFogIntensity,
        UiIpcHandleResponseAdjustCameraExposure,
    };

static const UiIpcResponseHandler g_lowLightInputHandlers[MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_BUTT -
                                           MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_OFFSET] = {
    UiIpcHandleResponseGetVideoInputLowLightParameters,
};

static const UiIpcResponseHandler g_infraredInputHandlers[MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_BUTT - MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_OFFSET]
    = {
        UiIpcHandleResponseGetVideoInputInfraredParameters,
        UiIpcHandleResponseAdjustInfraredPseudoColor,
        UiIpcHandleResponseAdjustInfraredBrightness,
        UiIpcHandleResponseAdjustInfraredContrast,
        UiIpcHandleResponseInfraredEnhanceImage,
        UiIpcHandleResponseInfraredScenarioMode,
        UiIpcHandleResponseInfraredHotspotTrackingSwitch,
    };

static const UiIpcResponseHandler g_remoteVideoInputHandlers[MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_BUTT - MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_OFFSET]
    = {
        UiIpcHandleResponseGetVideoInputRemoteParameters,
    };

static const UiIpcResponseHandler g_audioHandlers[MSG_4_REQ_RES_AUDIO_BUTT - MSG_4_REQ_RES_AUDIO_GENERAL_OFFSET] = {
    UiIpcHandleResponseGetAudioParameters,
};

static const UiIpcResponseHandler g_mediaFileHandlers[MSG_4_REQ_RES_MEDIA_FILE_BUTT - MSG_4_REQ_RES_MEDIA_FILE_OFFSET] = {
    UiIpcHandleResponseCaptureMediaFile,
    UiIpcHandleResponseRecordMediaFile,
    UiIpcHandleResponseGetMediaFileList,
    UiIpcHandleResponseExitPlaybackList,
    UiIpcHandleResponseDeleteMediaFile,
    UiIpcHandleResponsePlayMediaFile,
    UiIpcHandleResponsePlayAdjacentMediaFile,
    UiIpcHandleResponseStopMediaFilePlay,
};

static const UiIpcResponseHandler g_usbHandlers[MSG_4_REQ_RES_PERIPHERAL_USB_BUTT - MSG_4_REQ_RES_PERIPHERAL_USB_OFFSET] = {
    UiIpcHandleResponseGetPeripheralUsbParameters,
};

static const UiIpcResponseHandler g_networkHandlers[MSG_4_REQ_RES_PERIPHERAL_NETWORK_BUTT - MSG_4_REQ_RES_PERIPHERAL_NETWORK_OFFSET] = {
    UiIpcHandleResponseGetPeripheralNetworkParameters,
    UiIpcHandleResponseAdjustWifiSwitch,
    UiIpcHandleResponseGetWifiInfo,
};

static const UiIpcResponseHandler g_cameraModuleHandlers[MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_BUTT -
                                              MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_OFFSET] = {
    UiIpcHandleResponseGetPeripheralCameraModuleParameters,
};

static const UiIpcResponseHandler g_lowLightModuleHandlers[MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_BUTT -
                                          MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_OFFSET] = {
    UiIpcHandleResponseGetPeripheralLowLightModuleParameters,
};

static const UiIpcResponseHandler g_infraredModuleHandlers[MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_BUTT -
                                          MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_OFFSET] = {
    UiIpcHandleResponseGetPeripheralInfraredModuleParameters,
    UiIpcHandleResponseInfraredManualRemoveBadPixel,
    UiIpcHandleResponseInfraredSetBadPixelThreshold,
    UiIpcHandleResponseInfraredBadPixelOperate,
    UiIpcHandleResponseInfraredHotPixelRepair,
    UiIpcHandleResponseInfraredSdNuc,
};

static const UiIpcResponseHandler g_remoteVideoModuleHandlers[MSG_4_REQ_RES_PERIPHERAL_REMOTE_VIDEO_MODULE_BUTT -
                                                MSG_4_REQ_RES_PERIPHERAL_REMOTE_VIDEO_MODULE_OFFSET] = {
    UiIpcHandleResponseGetPeripheralRemoteVideoModuleParameters,
};

static const UiIpcResponseHandler g_compassHandlers[MSG_4_REQ_RES_PERIPHERAL_COMPASS_BUTT -
                                             MSG_4_REQ_RES_PERIPHERAL_COMPASS_OFFSET] = {
    UiIpcHandleResponseGetPeripheralCompassParameters,
    UiIpcHandleResponseAdjustCompassSwitch,
    UiIpcHandleResponseSetCompassDeclination,
    UiIpcHandleResponseSaveCompassConfig,
    UiIpcHandleResponseStartCompassCalibration,
    UiIpcHandleResponseStopCompassCalibration,
};

static const UiIpcResponseHandler g_gnssHandlers[MSG_4_REQ_RES_PERIPHERAL_GNSS_BUTT -
                                                MSG_4_REQ_RES_PERIPHERAL_GNSS_OFFSET] = {
    UiIpcHandleResponseGetPeripheralGnssParameters,
    UiIpcHandleResponseAdjustGnssSwitch,
    UiIpcHandleResponseAdjustGnssSystem,
    UiIpcHandleResponseAdjustCoordinateSystem,
};

static const UiIpcResponseHandler g_rangeFinderHandlers[MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_BUTT -
                                       MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_OFFSET] = {
    UiIpcHandleResponseGetPeripheralRangeFinderParameters,
    UiIpcHandleResponseRangeFinderOperate,
    UiIpcHandleResponseAdjustRangeFrequency,
    UiIpcHandleResponseAdjustRangeDuration,
};

static const UiIpcResponseHandler g_panTiltHandlers[MSG_4_REQ_RES_PERIPHERAL_PANTILT_BUTT - MSG_4_REQ_RES_PERIPHERAL_PANTILT_OFFSET] = {
    UiIpcHandleResponseGetPeripheralPanTiltParameters,
    UiIpcHandleResponsePanTiltMoveControl,
    UiIpcHandleResponsePanTiltSpeedControl,
};

ROE_S32 UiIpcDispatchResponse(ROE_SL msgType, const UiIpcRawData * rawData)
{
    if(!rawData) return ROE_FAILURE;

    static const UiIpcHandlerRange handlerRanges[] = {
        {MSG_4_REQ_RES_SYSTEM_GENERAL_OFFSET, MSG_4_REQ_RES_SYSTEM_GENERAL_BUTT, g_systemGeneralHandlers},
        {MSG_4_REQ_RES_SYSTEM_CONFIG_OFFSET, MSG_4_REQ_RES_SYSTEM_CONFIG_BUTT, g_systemConfigHandlers},
        {MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_OFFSET, MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_BUTT, g_systemUiHandlers},
        {MSG_4_REQ_RES_RETICLE_GENERAL_OFFSET, MSG_4_REQ_RES_RETICLE_GENERAL_BUTT, g_reticleHandlers},
        {MSG_4_REQ_RES_VIDEO_OUTPUT_OFFSET, MSG_4_REQ_RES_VIDEO_OUTPUT_BUTT, g_videoOutputHandlers},
        {MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_BUTT, g_videoInputHandlers},
        {MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_BUTT, g_cameraInputHandlers},
        {MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_BUTT, g_lowLightInputHandlers},
        {MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_BUTT, g_infraredInputHandlers},
        {MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_BUTT, g_remoteVideoInputHandlers},
        {MSG_4_REQ_RES_AUDIO_GENERAL_OFFSET, MSG_4_REQ_RES_AUDIO_BUTT, g_audioHandlers},
        {MSG_4_REQ_RES_MEDIA_FILE_OFFSET, MSG_4_REQ_RES_MEDIA_FILE_BUTT, g_mediaFileHandlers},
        {MSG_4_REQ_RES_PERIPHERAL_USB_OFFSET, MSG_4_REQ_RES_PERIPHERAL_USB_BUTT, g_usbHandlers},
        {MSG_4_REQ_RES_PERIPHERAL_NETWORK_OFFSET, MSG_4_REQ_RES_PERIPHERAL_NETWORK_BUTT, g_networkHandlers},
        {MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_OFFSET, MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_BUTT,
         g_cameraModuleHandlers},
        {MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_OFFSET, MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_BUTT,
         g_lowLightModuleHandlers},
        {MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_OFFSET, MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_BUTT,
         g_infraredModuleHandlers},
        {MSG_4_REQ_RES_PERIPHERAL_REMOTE_VIDEO_MODULE_OFFSET,
         MSG_4_REQ_RES_PERIPHERAL_REMOTE_VIDEO_MODULE_BUTT,
         g_remoteVideoModuleHandlers},
        {MSG_4_REQ_RES_PERIPHERAL_COMPASS_OFFSET, MSG_4_REQ_RES_PERIPHERAL_COMPASS_BUTT, g_compassHandlers},
        {MSG_4_REQ_RES_PERIPHERAL_GNSS_OFFSET, MSG_4_REQ_RES_PERIPHERAL_GNSS_BUTT, g_gnssHandlers},
        {MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_OFFSET, MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_BUTT, g_rangeFinderHandlers},
        {MSG_4_REQ_RES_PERIPHERAL_PANTILT_OFFSET, MSG_4_REQ_RES_PERIPHERAL_PANTILT_BUTT, g_panTiltHandlers},
    };

    ROE_S32 result = ui_ipc_dispatch_message(msgType,
                                          (ROE_U8 *)rawData->data,
                                          handlerRanges,
                                          sizeof(handlerRanges) / sizeof(handlerRanges[0]));
    if(result != ROE_SUCCESS) {
        LV_LOG_ERROR("[IPC][RESPONSE] no handler or handler failed type:%ld", msgType);
    }
    return result;
}
