//
// Created by jinxing on 2026/2/11.
//

#include "ipcMsgQue4UiRcvNotify.h"
#include "ipc_message_dispatch.h"
#include "handleNotify.h"
#include "lvgl/lvgl.h"

typedef IpcMessageHandler FtHandleNotify_st;

static const FtHandleNotify_st f_systemFunction[MSG_4_NOTIFY_SYSTEM_BUTT - MSG_4_NOTIFY_SYSTEM_OFFSET] =
{
    handleInitConfigNotify,
    handleResourcePathNotify,
    handleKeyEventNotify,
    handleMenuNotify,
    handleDialogBoxNotify,
};

static const FtHandleNotify_st f_shootingDifferentiation[MSG_4_NOTIFY_RETICLE_BUTT - MSG_4_NOTIFY_RETICLE_OFFSET] = {
    handleReticleOverallInfoNotify,
    handleReticleInfoUpdatingNotify,
};

static const FtHandleNotify_st f_videoOutputDisplay[MSG_4_NOTIFY_VIDEO_OUTPUT_BUTT - MSG_4_NOTIFY_VIDEO_OUTPUT_OFFSET] = {
    handleOsdShowHideOperateNotify,
    handleOledStatusInfoNotify,
    handleZoomInfoNotify,
    handleVideoInputDeviceFreezingNotify,
    handleVideoInputDeviceMirrorFlipNotify,
    handleVideoInputDeviceRotatingNotify,
};

static const FtHandleNotify_st f_videoCaptureInput[MSG_4_NOTIFY_VIDEO_INPUT_BUTT - MSG_4_NOTIFY_VIDEO_INPUT_OFFSET] = {
    handleVideoInputDeviceSwitchStatusNotify,
    handleObserveModeNotify,
    handleInfraredPseudoColorModeNotify,
};

static const FtHandleNotify_st f_audioInputAndOutput[MSG_4_NOTIFY_AUDIO_BUTT - MSG_4_NOTIFY_AUDIO_OFFSET] = {

};

static const FtHandleNotify_st f_mediaFile[MSG_4_NOTIFY_MEDIA_FILE_BUTT - MSG_4_NOTIFY_MEDIA_FILE_OFFSET] = {
    handleSnapStatusNotify,
    handleRecordStatusNotify,
    handleMediaFilePlayOperateNotify,
};

static const FtHandleNotify_st f_externalDeviceGenerally[
    MSG_4_NOTIFY_PERIPHERAL_GENERAL_BUTT - MSG_4_NOTIFY_PERIPHERAL_GENERAL_OFFSET] = {
    handlePeripheralsAbilityNotify,
    handlePeripheralsPowerStatusNotify,
    handlePeripheralSelfTest,
    handleSdVccVolNotify,
    handleBatteryInfoNotify,
};

static const FtHandleNotify_st f_network[MSG_4_NOTIFY_PERIPHERAL_NETWORK_BUTT - MSG_4_NOTIFY_PERIPHERAL_NETWORK_OFFSET] = {

};

static const FtHandleNotify_st f_visibleLightModule[MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_BUTT -
                                              MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_OFFSET] = {
    handleVideoInputDeviceAuxiliaryLightingNotify,
};

static const FtHandleNotify_st f_infraredModule[MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_BUTT -
                                          MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_OFFSET] = {
    handleInfraredBadPixelThresholdNotify,
    handleInfraredBadPixelNumNotify,
    handleInfraredHotPixelRepairedCorrectedValueNotify,
};

static const FtHandleNotify_st f_electronicCompass[MSG_4_NOTIFY_PERIPHERAL_COMPASS_BUTT -
                                             MSG_4_NOTIFY_PERIPHERAL_COMPASS_OFFSET] = {
    handleCompassData,
    handleMagneticDeclinationNotify,
    handleCompassCalibrationNotify,
};

static const FtHandleNotify_st f_satellitePositioning[MSG_4_NOTIFY_PERIPHERAL_GNSS_BUTT - MSG_4_NOTIFY_PERIPHERAL_GNSS_OFFSET]
    = {
        handleGpsData,
    };

static const FtHandleNotify_st f_rangefinder[MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_BUTT -
                                       MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_OFFSET] = {
    handleRangeFinderStatusNotify,
    handleRangeData,
    handleRangeCountdownNotify,
};

static const FtHandleNotify_st f_holder[MSG_4_NOTIFY_PERIPHERAL_PANTILT_BUTT - MSG_4_NOTIFY_PERIPHERAL_PANTILT_OFFSET] = {
    handlePanTiltHorizontalAngleNotify,
    handlePanTiltVerticalAngleNotify,
    handlePanTiltHorizontalRunningStatusNotify,
    handlePanTiltVerticalRunningStatusNotify,
    handleRtCtlPanTiltInfoNotify,
};

static const IpcMessageHandlerRange_st g_notifyHandlerRanges[] = {
    {MSG_4_NOTIFY_SYSTEM_OFFSET, MSG_4_NOTIFY_SYSTEM_BUTT, f_systemFunction},
    {MSG_4_NOTIFY_RETICLE_OFFSET, MSG_4_NOTIFY_RETICLE_BUTT, f_shootingDifferentiation},
    {MSG_4_NOTIFY_VIDEO_OUTPUT_OFFSET, MSG_4_NOTIFY_VIDEO_OUTPUT_BUTT, f_videoOutputDisplay},
    {MSG_4_NOTIFY_VIDEO_INPUT_OFFSET, MSG_4_NOTIFY_VIDEO_INPUT_BUTT, f_videoCaptureInput},
    {MSG_4_NOTIFY_AUDIO_OFFSET, MSG_4_NOTIFY_AUDIO_BUTT, f_audioInputAndOutput},
    {MSG_4_NOTIFY_MEDIA_FILE_OFFSET, MSG_4_NOTIFY_MEDIA_FILE_BUTT, f_mediaFile},
    {MSG_4_NOTIFY_PERIPHERAL_GENERAL_OFFSET, MSG_4_NOTIFY_PERIPHERAL_GENERAL_BUTT, f_externalDeviceGenerally},
    {MSG_4_NOTIFY_PERIPHERAL_NETWORK_OFFSET, MSG_4_NOTIFY_PERIPHERAL_NETWORK_BUTT, f_network},
    {MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_OFFSET, MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_BUTT,
     f_visibleLightModule},
    {MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_OFFSET, MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_BUTT, f_infraredModule},
    {MSG_4_NOTIFY_PERIPHERAL_COMPASS_OFFSET, MSG_4_NOTIFY_PERIPHERAL_COMPASS_BUTT, f_electronicCompass},
    {MSG_4_NOTIFY_PERIPHERAL_GNSS_OFFSET, MSG_4_NOTIFY_PERIPHERAL_GNSS_BUTT, f_satellitePositioning},
    {MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_OFFSET, MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_BUTT, f_rangefinder},
    {MSG_4_NOTIFY_PERIPHERAL_PANTILT_OFFSET, MSG_4_NOTIFY_PERIPHERAL_PANTILT_BUTT, f_holder},
};

ROE_S32 ParseNotifyMsg(ROE_SL msgType, const RoeIpcMsgQueRawData_st * rawData)
{
    if(!rawData) return ROE_FAILURE;

    ROE_S32 result = ipc_dispatch_message(msgType,
                                          (ROE_U8 *)rawData->data,
                                          g_notifyHandlerRanges,
                                          sizeof(g_notifyHandlerRanges) / sizeof(g_notifyHandlerRanges[0]));
    if(result != ROE_SUCCESS) {
        LV_LOG_ERROR("[IPC][NOTIFY] no handler or handler failed type:%ld", msgType);
    }
    return result;
}
