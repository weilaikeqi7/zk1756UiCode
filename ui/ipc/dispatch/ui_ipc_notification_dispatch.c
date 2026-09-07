//
// Created by jinxing on 2026/2/11.
//

#include "ui_ipc_notification_types.h"
#include "ui_ipc_dispatch.h"
#include "ui_ipc_dispatch_internal.h"
#include "ui_ipc_notification_handler.h"
#include "lvgl/lvgl.h"

typedef UiIpcMessageHandler UiIpcNotificationHandler;

static const UiIpcNotificationHandler f_systemFunction[MSG_4_NOTIFY_SYSTEM_BUTT - MSG_4_NOTIFY_SYSTEM_OFFSET] =
{
    UiIpcHandleNotificationDeviceInitConfig,
    UiIpcHandleNotificationResourcePathInfo,
    UiIpcHandleNotificationKeyEventInfo,
    UiIpcHandleNotificationMainMenuOperate,
    UiIpcHandleNotificationDialogBoxDisplay,
};

static const UiIpcNotificationHandler f_shootingDifferentiation[MSG_4_NOTIFY_RETICLE_BUTT - MSG_4_NOTIFY_RETICLE_OFFSET] = {
    UiIpcHandleNotificationReticleOverallInfo,
    UiIpcHandleNotificationReticleInfoUpdate,
};

static const UiIpcNotificationHandler f_videoOutputDisplay[MSG_4_NOTIFY_VIDEO_OUTPUT_BUTT - MSG_4_NOTIFY_VIDEO_OUTPUT_OFFSET] = {
    UiIpcHandleNotificationOsdShowSwitch,
    UiIpcHandleNotificationMainDisplayStatus,
    UiIpcHandleNotificationVideoZoomInfo,
    UiIpcHandleNotificationVideoOutputFreezing,
    UiIpcHandleNotificationVideoOutputMirrorFlip,
    UiIpcHandleNotificationVideoOutputRotating,
};

static const UiIpcNotificationHandler f_videoCaptureInput[MSG_4_NOTIFY_VIDEO_INPUT_BUTT - MSG_4_NOTIFY_VIDEO_INPUT_OFFSET] = {
    UiIpcHandleNotificationVideoInputDeviceStatus,
    UiIpcHandleNotificationObserveMode,
    UiIpcHandleNotificationInfraredPseudoColorMode,
};

static const UiIpcNotificationHandler f_mediaFile[MSG_4_NOTIFY_MEDIA_FILE_BUTT - MSG_4_NOTIFY_MEDIA_FILE_OFFSET] = {
    UiIpcHandleNotificationCaptureStatus,
    UiIpcHandleNotificationRecordStatus,
    UiIpcHandleNotificationMediaFilePlayOperate,
};

static const UiIpcNotificationHandler f_externalDeviceGenerally[
    MSG_4_NOTIFY_PERIPHERAL_GENERAL_BUTT - MSG_4_NOTIFY_PERIPHERAL_GENERAL_OFFSET] = {
    UiIpcHandleNotificationDeviceAbility,
    UiIpcHandleNotificationDeviceStatus,
    UiIpcHandleNotificationPeripheralSelfTestInfo,
    UiIpcHandleNotificationPeripheralRealTimeInfo,
    UiIpcHandleNotificationPeripheralBatteryInfo,
};

static const UiIpcNotificationHandler f_visibleLightModule[MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_BUTT -
                                              MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_OFFSET] = {
    UiIpcHandleNotificationAuxiliaryLighting,
};

static const UiIpcNotificationHandler f_infraredModule[MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_BUTT -
                                          MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_OFFSET] = {
    UiIpcHandleNotificationInfraredBadPixelThreshold,
    UiIpcHandleNotificationInfraredBadPixelCount,
    UiIpcHandleNotificationInfraredHotPixelRepairCorrection,
};

static const UiIpcNotificationHandler f_electronicCompass[MSG_4_NOTIFY_PERIPHERAL_COMPASS_BUTT -
                                             MSG_4_NOTIFY_PERIPHERAL_COMPASS_OFFSET] = {
    UiIpcHandleNotificationCompassData,
    UiIpcHandleNotificationInitialMagneticDeclination,
    UiIpcHandleNotificationCompassCalibrationScore,
};

static const UiIpcNotificationHandler f_satellitePositioning[MSG_4_NOTIFY_PERIPHERAL_GNSS_BUTT - MSG_4_NOTIFY_PERIPHERAL_GNSS_OFFSET]
    = {
        UiIpcHandleNotificationGnssData,
    };

static const UiIpcNotificationHandler f_rangefinder[MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_BUTT -
                                       MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_OFFSET] = {
    UiIpcHandleNotificationRangeFinderStatus,
    UiIpcHandleNotificationRangeData,
    UiIpcHandleNotificationRangeCountdown,
};

static const UiIpcNotificationHandler f_holder[MSG_4_NOTIFY_PERIPHERAL_PANTILT_BUTT - MSG_4_NOTIFY_PERIPHERAL_PANTILT_OFFSET] = {
    UiIpcHandleNotificationPanTiltHorizontalAngle,
    UiIpcHandleNotificationPanTiltVerticalAngle,
    UiIpcHandleNotificationPanTiltHorizontalRunningStatus,
    UiIpcHandleNotificationPanTiltVerticalRunningStatus,
    UiIpcHandleNotificationPanTiltOperateInfo,
};

static const UiIpcHandlerRange g_notifyHandlerRanges[] = {
    {MSG_4_NOTIFY_SYSTEM_OFFSET, MSG_4_NOTIFY_SYSTEM_BUTT, f_systemFunction},
    {MSG_4_NOTIFY_RETICLE_OFFSET, MSG_4_NOTIFY_RETICLE_BUTT, f_shootingDifferentiation},
    {MSG_4_NOTIFY_VIDEO_OUTPUT_OFFSET, MSG_4_NOTIFY_VIDEO_OUTPUT_BUTT, f_videoOutputDisplay},
    {MSG_4_NOTIFY_VIDEO_INPUT_OFFSET, MSG_4_NOTIFY_VIDEO_INPUT_BUTT, f_videoCaptureInput},
    {MSG_4_NOTIFY_MEDIA_FILE_OFFSET, MSG_4_NOTIFY_MEDIA_FILE_BUTT, f_mediaFile},
    {MSG_4_NOTIFY_PERIPHERAL_GENERAL_OFFSET, MSG_4_NOTIFY_PERIPHERAL_GENERAL_BUTT, f_externalDeviceGenerally},
    {MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_OFFSET, MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_BUTT,
     f_visibleLightModule},
    {MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_OFFSET, MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_BUTT, f_infraredModule},
    {MSG_4_NOTIFY_PERIPHERAL_COMPASS_OFFSET, MSG_4_NOTIFY_PERIPHERAL_COMPASS_BUTT, f_electronicCompass},
    {MSG_4_NOTIFY_PERIPHERAL_GNSS_OFFSET, MSG_4_NOTIFY_PERIPHERAL_GNSS_BUTT, f_satellitePositioning},
    {MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_OFFSET, MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_BUTT, f_rangefinder},
    {MSG_4_NOTIFY_PERIPHERAL_PANTILT_OFFSET, MSG_4_NOTIFY_PERIPHERAL_PANTILT_BUTT, f_holder},
};

ROE_S32 UiIpcDispatchNotification(ROE_SL msgType, const UiIpcRawData * rawData)
{
    if(!rawData) return ROE_FAILURE;

    ROE_S32 result = ui_ipc_dispatch_message(msgType,
                                          (ROE_U8 *)rawData->data,
                                          g_notifyHandlerRanges,
                                          sizeof(g_notifyHandlerRanges) / sizeof(g_notifyHandlerRanges[0]));
    if(result != ROE_SUCCESS) {
        LV_LOG_ERROR("[IPC][NOTIFY] no handler or handler failed type:%ld", msgType);
    }
    return result;
}
