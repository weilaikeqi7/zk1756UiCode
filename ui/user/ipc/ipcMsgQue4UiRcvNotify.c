//
// Created by jinxing on 2026/2/11.
//

#include "ipcMsgQue4UiRcvNotify.h"
#include "handleNotify.h"

typedef ROE_S32 (*FtHandleNotify_st)(ROE_U8 * msgData);

static FtHandleNotify_st f_systemFunction[MSG_4_NOTIFY_SYSTEM_BUTT - MSG_4_NOTIFY_SYSTEM_OFFSET] =
{
    handleInitConfigNotify,
    handleResourcePathNotify,
    handleKeyEventNotify,
    handleMenuNotify,
    handleDialogBoxNotify,
};

static FtHandleNotify_st f_shootingDifferentiation[MSG_4_NOTIFY_RETICLE_BUTT - MSG_4_NOTIFY_RETICLE_OFFSET] = {
    handleReticleOverallInfoNotify,
    handleReticleInfoUpdatingNotify,
};

static FtHandleNotify_st f_videoOutputDisplay[MSG_4_NOTIFY_VIDEO_OUTPUT_BUTT - MSG_4_NOTIFY_VIDEO_OUTPUT_OFFSET] = {
    handleOsdShowHideOperateNotify,
    handleOledStatusInfoNotify,
    handleZoomInfoNotify,
    handleVideoInputDeviceFreezingNotify,
    handleVideoInputDeviceMirrorFlipNotify,
    handleVideoInputDeviceRotatingNotify,
};

static FtHandleNotify_st f_videoCaptureInput[MSG_4_NOTIFY_VIDEO_INPUT_BUTT - MSG_4_NOTIFY_VIDEO_INPUT_OFFSET] = {
    handleVideoInputDeviceSwitchStatusNotify,
    handleObserveModeNotify,
    handleInfraredPseudoColorModeNotify,
};

static FtHandleNotify_st f_audioInputAndOutput[MSG_4_NOTIFY_AUDIO_BUTT - MSG_4_NOTIFY_AUDIO_OFFSET] = {

};

static FtHandleNotify_st f_mediaFile[MSG_4_NOTIFY_MEDIA_FILE_BUTT - MSG_4_NOTIFY_MEDIA_FILE_OFFSET] = {
    handleSnapStatusNotify,
    handleRecordStatusNotify,
    handleMediaFilePlayOperateNotify,
};

static FtHandleNotify_st f_externalDeviceGenerally[
    MSG_4_NOTIFY_PERIPHERAL_GENERAL_BUTT - MSG_4_NOTIFY_PERIPHERAL_GENERAL_OFFSET] = {
    handlePeripheralsAbilityNotify,
    handlePeripheralsPowerStatusNotify,
    handlePeripheralSelfTest,
    handleSdVccVolNotify,
    handleBatteryInfoNotify,
};

static FtHandleNotify_st f_network[MSG_4_NOTIFY_PERIPHERAL_NETWORK_BUTT - MSG_4_NOTIFY_PERIPHERAL_NETWORK_OFFSET] = {

};

static FtHandleNotify_st f_visibleLightModule[MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_BUTT -
                                              MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_OFFSET] = {
    handleVideoInputDeviceAuxiliaryLightingNotify,
};

static FtHandleNotify_st f_infraredModule[MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_BUTT -
                                          MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_OFFSET] = {
    handleInfraredBadPixelThresholdNotify,
    handleInfraredBadPixelNumNotify,
    handleInfraredHotPixelRepairedCorrectedValueNotify,
};

static FtHandleNotify_st f_electronicCompass[MSG_4_NOTIFY_PERIPHERAL_COMPASS_BUTT -
                                             MSG_4_NOTIFY_PERIPHERAL_COMPASS_OFFSET] = {
    handleCompassData,
    handleMagneticDeclinationNotify,
    handleCompassCalibrationNotify,
};

static FtHandleNotify_st f_satellitePositioning[MSG_4_NOTIFY_PERIPHERAL_GNSS_BUTT - MSG_4_NOTIFY_PERIPHERAL_GNSS_OFFSET]
    = {
        handleGpsData,
    };

static FtHandleNotify_st f_rangefinder[MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_BUTT -
                                       MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_OFFSET] = {
    handleRangeFinderStatusNotify,
    handleRangeData,
    handleRangeCountdownNotify,
};

static FtHandleNotify_st f_holder[MSG_4_NOTIFY_PERIPHERAL_PANTILT_BUTT - MSG_4_NOTIFY_PERIPHERAL_PANTILT_OFFSET] = {
    handlePanTiltHorizontalAngleNotify,
    handlePanTiltVerticalAngleNotify,
    handlePanTiltHorizontalRunningStatusNotify,
    handlePanTiltVerticalRunningStatusNotify,
    handleRtCtlPanTiltInfoNotify,
};

ROE_S32 ParseNotifyMsg(ROE_SL msgType, RoeIpcMsgQueRawData_st * rawData)
{
    ROE_U8 * msgData = rawData->data;

    if(msgType >= MSG_4_NOTIFY_SYSTEM_OFFSET && msgType < MSG_4_NOTIFY_SYSTEM_BUTT) {
        return f_systemFunction[msgType - MSG_4_NOTIFY_SYSTEM_OFFSET](msgData);
    }
    if(msgType >= MSG_4_NOTIFY_RETICLE_OFFSET && msgType < MSG_4_NOTIFY_RETICLE_BUTT) {
        return f_shootingDifferentiation[msgType - MSG_4_NOTIFY_RETICLE_OFFSET](msgData);
    }
    if(msgType >= MSG_4_NOTIFY_VIDEO_OUTPUT_OFFSET && msgType < MSG_4_NOTIFY_VIDEO_OUTPUT_BUTT) {
        return f_videoOutputDisplay[msgType - MSG_4_NOTIFY_VIDEO_OUTPUT_OFFSET](msgData);
    }
    if(msgType >= MSG_4_NOTIFY_VIDEO_INPUT_OFFSET && msgType < MSG_4_NOTIFY_VIDEO_INPUT_BUTT) {
        return f_videoCaptureInput[msgType - MSG_4_NOTIFY_VIDEO_INPUT_OFFSET](msgData);
    }
    if(msgType >= MSG_4_NOTIFY_AUDIO_OFFSET && msgType < MSG_4_NOTIFY_AUDIO_BUTT) {
        return f_audioInputAndOutput[msgType - MSG_4_NOTIFY_AUDIO_OFFSET](msgData);
    }
    if(msgType >= MSG_4_NOTIFY_MEDIA_FILE_OFFSET && msgType < MSG_4_NOTIFY_MEDIA_FILE_BUTT) {
        return f_mediaFile[msgType - MSG_4_NOTIFY_MEDIA_FILE_OFFSET](msgData);
    }
    if(msgType >= MSG_4_NOTIFY_PERIPHERAL_GENERAL_OFFSET && msgType < MSG_4_NOTIFY_PERIPHERAL_GENERAL_BUTT) {
        return f_externalDeviceGenerally[msgType - MSG_4_NOTIFY_PERIPHERAL_GENERAL_OFFSET](msgData);
    }
    if(msgType >= MSG_4_NOTIFY_PERIPHERAL_NETWORK_OFFSET && msgType < MSG_4_NOTIFY_PERIPHERAL_NETWORK_BUTT) {
        return f_network[msgType - MSG_4_NOTIFY_PERIPHERAL_NETWORK_OFFSET](msgData);
    }
    if(msgType >= MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_OFFSET && msgType <
       MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_BUTT) {
        return f_visibleLightModule[msgType - MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_OFFSET](msgData);
    }
    if(msgType >= MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_OFFSET && msgType <
       MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_BUTT) {
        return f_infraredModule[msgType - MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_OFFSET](msgData);
    }
    if(msgType >= MSG_4_NOTIFY_PERIPHERAL_COMPASS_OFFSET && msgType < MSG_4_NOTIFY_PERIPHERAL_COMPASS_BUTT) {
        return f_externalDeviceGenerally[msgType - MSG_4_NOTIFY_PERIPHERAL_COMPASS_OFFSET](msgData);
    }
    if(msgType >= MSG_4_NOTIFY_PERIPHERAL_GNSS_OFFSET && msgType < MSG_4_NOTIFY_PERIPHERAL_GNSS_BUTT) {
        return f_satellitePositioning[msgType - MSG_4_NOTIFY_PERIPHERAL_GNSS_OFFSET](msgData);
    }
    if(msgType >= MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_OFFSET && msgType < MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_BUTT) {
        return f_rangefinder[msgType - MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_OFFSET](msgData);
    }
    if(msgType >= MSG_4_NOTIFY_PERIPHERAL_PANTILT_OFFSET && msgType < MSG_4_NOTIFY_PERIPHERAL_PANTILT_BUTT) {
        return f_holder[msgType - MSG_4_NOTIFY_PERIPHERAL_PANTILT_OFFSET](msgData);
    }
    return ROE_FAILURE;
}