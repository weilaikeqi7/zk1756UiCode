#include "ui_ipc_message_validator.h"

#include "ui_ipc_notification_types.h"
#include "ui_ipc_response_types.h"
#include "ui_ipc_request_types.h"

typedef struct {
    ROE_SL firstType;
    ROE_SL endType;
} UiIpcMessageTypeRange;

static const UiIpcMessageTypeRange g_requestResponseTypeRanges[] = {
    {MSG_4_REQ_RES_SYSTEM_GENERAL_OFFSET, MSG_4_REQ_RES_SYSTEM_GENERAL_BUTT},
    {MSG_4_REQ_RES_SYSTEM_CONFIG_OFFSET, MSG_4_REQ_RES_SYSTEM_CONFIG_BUTT},
    {MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_OFFSET, MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_BUTT},
    {MSG_4_REQ_RES_RETICLE_GENERAL_OFFSET, MSG_4_REQ_RES_RETICLE_GENERAL_BUTT},
    {MSG_4_REQ_RES_VIDEO_OUTPUT_OFFSET, MSG_4_REQ_RES_VIDEO_OUTPUT_BUTT},
    {MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_BUTT},
    {MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_BUTT},
    {MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_BUTT},
    {MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_BUTT},
    {MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_OFFSET, MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_BUTT},
    {MSG_4_REQ_RES_AUDIO_GENERAL_OFFSET, MSG_4_REQ_RES_AUDIO_BUTT},
    {MSG_4_REQ_RES_MEDIA_FILE_OFFSET, MSG_4_REQ_RES_MEDIA_FILE_BUTT},
    {MSG_4_REQ_RES_PERIPHERAL_USB_OFFSET, MSG_4_REQ_RES_PERIPHERAL_USB_BUTT},
    {MSG_4_REQ_RES_PERIPHERAL_NETWORK_OFFSET, MSG_4_REQ_RES_PERIPHERAL_NETWORK_BUTT},
    {MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_OFFSET, MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_BUTT},
    {MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_OFFSET, MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_BUTT},
    {MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_OFFSET, MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_BUTT},
    {MSG_4_REQ_RES_PERIPHERAL_REMOTE_VIDEO_MODULE_OFFSET,
     MSG_4_REQ_RES_PERIPHERAL_REMOTE_VIDEO_MODULE_BUTT},
    {MSG_4_REQ_RES_PERIPHERAL_COMPASS_OFFSET, MSG_4_REQ_RES_PERIPHERAL_COMPASS_BUTT},
    {MSG_4_REQ_RES_PERIPHERAL_GNSS_OFFSET, MSG_4_REQ_RES_PERIPHERAL_GNSS_BUTT},
    {MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_OFFSET, MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_BUTT},
    {MSG_4_REQ_RES_PERIPHERAL_PANTILT_OFFSET, MSG_4_REQ_RES_PERIPHERAL_PANTILT_BUTT},
};

static const UiIpcMessageTypeRange g_notificationTypeRanges[] = {
    {MSG_4_NOTIFY_SYSTEM_OFFSET, MSG_4_NOTIFY_SYSTEM_BUTT},
    {MSG_4_NOTIFY_RETICLE_OFFSET, MSG_4_NOTIFY_RETICLE_BUTT},
    {MSG_4_NOTIFY_VIDEO_OUTPUT_OFFSET, MSG_4_NOTIFY_VIDEO_OUTPUT_BUTT},
    {MSG_4_NOTIFY_VIDEO_INPUT_OFFSET, MSG_4_NOTIFY_VIDEO_INPUT_BUTT},
    {MSG_4_NOTIFY_AUDIO_OFFSET, MSG_4_NOTIFY_AUDIO_BUTT},
    {MSG_4_NOTIFY_MEDIA_FILE_OFFSET, MSG_4_NOTIFY_MEDIA_FILE_BUTT},
    {MSG_4_NOTIFY_PERIPHERAL_GENERAL_OFFSET, MSG_4_NOTIFY_PERIPHERAL_GENERAL_BUTT},
    {MSG_4_NOTIFY_PERIPHERAL_NETWORK_OFFSET, MSG_4_NOTIFY_PERIPHERAL_NETWORK_BUTT},
    {MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_OFFSET, MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_BUTT},
    {MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_OFFSET, MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_BUTT},
    {MSG_4_NOTIFY_PERIPHERAL_COMPASS_OFFSET, MSG_4_NOTIFY_PERIPHERAL_COMPASS_BUTT},
    {MSG_4_NOTIFY_PERIPHERAL_GNSS_OFFSET, MSG_4_NOTIFY_PERIPHERAL_GNSS_BUTT},
    {MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_OFFSET, MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_BUTT},
    {MSG_4_NOTIFY_PERIPHERAL_PANTILT_OFFSET, MSG_4_NOTIFY_PERIPHERAL_PANTILT_BUTT},
};

static int message_type_in_ranges(ROE_SL msgType,
                                  const UiIpcMessageTypeRange * ranges,
                                  ROE_SIZE rangeCount)
{
    for(ROE_SIZE i = 0; i < rangeCount; i++) {
        if(msgType >= ranges[i].firstType && msgType < ranges[i].endType) return 1;
    }
    return 0;
}

static int is_request_response_type(ROE_SL msgType)
{
    return message_type_in_ranges(msgType,
                                  g_requestResponseTypeRanges,
                                  sizeof(g_requestResponseTypeRanges) / sizeof(g_requestResponseTypeRanges[0]));
}

static int is_notification_type(ROE_SL msgType)
{
    return message_type_in_ranges(msgType,
                                  g_notificationTypeRanges,
                                  sizeof(g_notificationTypeRanges) / sizeof(g_notificationTypeRanges[0]));
}

static ROE_SIZE response_min_size(ROE_SL msgType, int * known)
{
    const ROE_SIZE resultSize = sizeof(UiIpcMessageHeader) + sizeof(ROE_U8);
    *known = is_request_response_type(msgType);
    if(!*known) return 0;

    switch(msgType) {
    case MSG_4_REQ_RES_LOG_IN_OUT:
        return sizeof(UiResponseRegister);
    case MSG_4_REQ_RES_SHUTDOWN:
        return sizeof(UiResponseShutdown);
    case MSG_4_REQ_RES_GET_VERSION_INFO:
        return sizeof(UiResponseGetAppVersion);
    case MSG_4_REQ_RES_SET_SYSTEM_TIME:
        return sizeof(UiResponseSetSystemTime);
    case MSG_4_REQ_RES_FORMAT_DISK_PARTITION:
        return sizeof(UiResponseFormatDisk);
    case MSG_4_REQ_RES_RESTORE_FACTORY_SETTING:
        return sizeof(UiResponseRestoreFactory);
    case MSG_4_REQ_RES_SAVE_LANGUAGE_CONFIG:
        return sizeof(UiResponseSaveLanguageConfig);
    case MSG_4_REQ_RES_GET_USER_COMMON_CONFIG:
        return sizeof(UiResponseGetUserCommonConfig);
    case MSG_4_REQ_RES_SET_USER_COMMON_CONFIG:
        return sizeof(UiResponseSetUserCommonConfig);
    case MSG_4_REQ_RES_GET_USER_MEDIA_CONFIG:
        return sizeof(UiResponseGetUserMediaConfig);
    case MSG_4_REQ_RES_SET_USER_MEDIA_CONFIG:
        return sizeof(UiResponseSetUserMediaConfig);
    case MSG_4_REQ_RES_EXIT_MENU_MODE:
        return sizeof(UiResponseExitMenu);
    case MSG_4_REQ_RES_EXIT_DIALOG_BOX:
        return sizeof(UiResponseExitDialogBox);
    case MSG_4_REQ_RES_SET_RETICLE_COMMON_CONFIG:
        return sizeof(UiResponseSetReticleCommonConfig);
    case MSG_4_REQ_RES_WEAPON_SET_RETICLE_STYLE:
        return sizeof(UiResponseWeaponSetReticleStyle);
    case MSG_4_REQ_RES_WEAPON_SET_RETICLE_COLOR:
        return sizeof(UiResponseWeaponSetReticleColor);
    case MSG_4_REQ_RES_WEAPON_SET_RETICLE_LUMA:
        return sizeof(UiResponseWeaponSetReticleBrightness);
    case MSG_4_REQ_RES_WEAPON_SAVE_CONFIG:
        return sizeof(UiResponseWeaponSaveConfig);
    case MSG_4_REQ_RES_WEAPON_OPERATE_MARK_CONFIG:
        return sizeof(UiResponseWeaponMarkConfigOperate);
    case MSG_4_REQ_RES_WEAPON_SET_DEFAULT_SHOOT_DISTANCE:
        return sizeof(UiResponseWeaponSetDefaultShootDistance);
    case MSG_4_REQ_RES_WEAPON_OPERATE_SHOOT_DISTANCE:
        return sizeof(UiResponseWeaponOperateShootDistance);
    case MSG_4_REQ_RES_WEAPON_SET_SHOOT_POSITION:
        return sizeof(UiResponseWeaponSetShootPosition);
    case MSG_4_REQ_RES_WEAPON_SET_SHOOT_ZERO:
        return sizeof(UiResponseWeaponSetShootZero);
    case MSG_4_REQ_RES_GET_VIDEO_OUTPUT_PARA:
        return sizeof(UiResponseGetVideoOutputParameters);
    case MSG_4_REQ_RES_MAIN_DISPLAY_BRIGHTNESS_ADJUST:
        return sizeof(UiResponseAdjustMainDisplayBrightness);
    case MSG_4_REQ_RES_MAIN_DISPLAY_CONTRAST_ADJUST:
        return sizeof(UiResponseAdjustMainDisplayContrast);
    case MSG_4_REQ_RES_EXTEND_DISPLAY_SWITCH:
        return sizeof(UiResponseAdjustExtendDisplaySwitch);
    case MSG_4_REQ_RES_PIP_SWITCH:
        return sizeof(UiResponseAdjustPipSwitch);
    case MSG_4_REQ_RES_VIDEO_ZOOM:
        return sizeof(UiResponseAdjustVideoZoom);
    case MSG_4_REQ_RES_VIDEO_OUTPUT_FREEZE:
        return sizeof(UiResponseFreezeVideoInput);
    case MSG_4_REQ_RES_OBJECT_RECOGNITION_SWITCH:
        return sizeof(UiResponseAdjustRecognitionSwitch);
    case MSG_4_REQ_RES_GET_VIDEO_INPUT_PARA:
        return sizeof(UiResponseGetVideoInputParameters);
    case MSG_4_REQ_RES_MAIN_OBSERVE_MODE_SWITCHING:
        return sizeof(UiResponseSwitchMainObserveMode);
    case MSG_4_REQ_RES_PIP_OBSERVE_MODE_SWITCHING:
        return sizeof(UiResponseSwitchPipObserveMode);
    case MSG_4_REQ_RES_GET_VIDEO_INPUT_CAMERA_PARA:
        return sizeof(UiResponseGetVideoInputCameraParameters);
    case MSG_4_REQ_RES_CAMERA_DAYNIGHT_MODE_SWITCHING:
        return sizeof(UiResponseAdjustDayNight);
    case MSG_4_REQ_RES_CAMERA_BRIGHTNESS_ADJUST:
        return sizeof(UiResponseAdjustCameraBrightness);
    case MSG_4_REQ_RES_CAMERA_CONTRAST_ADJUST:
        return sizeof(UiResponseAdjustCameraContrast);
    case MSG_4_REQ_RES_CAMERA_SATURATION_ADJUST:
        return sizeof(UiResponseAdjustCameraSaturation);
    case MSG_4_REQ_RES_CAMERA_HUE_ADJUST:
        return sizeof(UiResponseAdjustCameraHue);
    case MSG_4_REQ_RES_CAMERA_DEHAZE_SWITCH:
        return sizeof(UiResponseAdjustFogSwitch);
    case MSG_4_REQ_RES_CAMERA_DEHAZE_STRENGTH_ADJUST:
        return sizeof(UiResponseAdjustFogIntensity);
    case MSG_4_REQ_RES_CAMERA_EXPOSURE_ADJUST:
        return sizeof(UiResponseAdjustCameraExposure);
    case MSG_4_REQ_RES_GET_VIDEO_INPUT_LOW_LIGHT_PARA:
        return sizeof(UiResponseGetVideoInputLowLightParameters);
    case MSG_4_REQ_RES_GET_VIDEO_INPUT_INFRARED_PARA:
        return sizeof(UiResponseGetVideoInputInfraredParameters);
    case MSG_4_REQ_RES_INFRARED_PSEUDOCOLOR_MODE_SWITCHING:
        return sizeof(UiResponseAdjustInfraredPseudoColor);
    case MSG_4_REQ_RES_INFRARED_BRIGHTNESS_ADJUST:
        return sizeof(UiResponseAdjustInfraredBrightness);
    case MSG_4_REQ_RES_INFRARED_CONTRAST_ADJUST:
        return sizeof(UiResponseAdjustInfraredContrast);
    case MSG_4_REQ_RES_INFRARED_IMAGE_ENHANCE_ADJUST:
        return sizeof(UiResponseInfraredEnhanceImage);
    case MSG_4_REQ_RES_INFRARED_SCENARIO_MODE_SWITCHING:
        return sizeof(UiResponseInfraredScenarioMode);
    case MSG_4_REQ_RES_INFRARED_HOTSPOT_TRACKING_SWITCH:
        return sizeof(UiResponseInfraredHotspotTrackingSwitch);
    case MSG_4_REQ_RES_GET_VIDEO_INPUT_REMOTE_PARA:
        return sizeof(UiResponseGetVideoInputRemoteParameters);
    case MSG_4_REQ_RES_GET_AUDIO_PARA:
        return sizeof(UiResponseGetAudioParameters);
    case MSG_4_REQ_RES_CAPTURE_MEDIA_FILE:
        return sizeof(UiResponseCaptureMediaFile);
    case MSG_4_REQ_RES_RECORD_MEDIA_FILE:
        return sizeof(UiResponseRecordMediaFile);
    case MSG_4_REQ_RES_INFRARED_SET_BAD_PIXEL_THRESHOLD:
        return sizeof(UiResponseInfraredSetBadPixelThreshold);
    case MSG_4_REQ_RES_COMPASS_SWITCH:
        return sizeof(UiResponseAdjustCompassSwitch);
    case MSG_4_REQ_RES_COMPASS_SET_MAGNETIC_DECLINATION:
        return sizeof(UiResponseSetCompassDeclination);
    case MSG_4_REQ_RES_COMPASS_SAVE_CONFIG:
        return sizeof(UiResponseSaveCompassConfig);
    case MSG_4_REQ_RES_COMPASS_START_CALIBRATION:
        return sizeof(UiResponseStartCompassCalibration);
    case MSG_4_REQ_RES_COMPASS_STOP_CALIBRATION:
        return sizeof(UiResponseStopCompassCalibration);
    case MSG_4_REQ_RES_GNSS_SWITCH:
        return sizeof(UiResponseAdjustGnssSwitch);
    case MSG_4_REQ_RES_GNSS_POSITION_SYSTEM_SWITCHING:
        return sizeof(UiResponseAdjustGnssSystem);
    case MSG_4_REQ_RES_GNSS_COORDINATE_SYSTEM_SWITCHING:
        return sizeof(UiResponseAdjustCoordinateSystem);
    case MSG_4_REQ_RES_GET_MEDIA_FILE_LIST:
        return sizeof(UiResponseGetMediaFileList);
    case MSG_4_REQ_RES_EXIT_PLAYBACK_MEDIA_LIST:
        return sizeof(UiResponseExitPlaybackList);
    case MSG_4_REQ_RES_DEL_MEDIA_FILE:
        return sizeof(UiResponseDeleteMediaFile);
    case MSG_4_REQ_RES_PLAY_MEDIA_FILE:
        return sizeof(UiResponsePlayMediaFile);
    case MSG_4_REQ_RES_PLAY_ADJACENT_MEDIA_FILE:
        return sizeof(UiResponsePlayAdjacentMediaFile);
    case MSG_4_REQ_RES_STOP_MEDIA_FILE_PLAY:
        return sizeof(UiResponseStopMediaFilePlay);
    case MSG_4_REQ_RES_RANGE_FINDER_OPERATE:
        return sizeof(UiResponseRangeFinderOperate);
    case MSG_4_REQ_RES_RANGE_FREQUENCY_ADJUST:
        return sizeof(UiResponseAdjustRangeFrequency);
    case MSG_4_REQ_RES_RANGE_TIME_DURATION_ADJUST:
        return sizeof(UiResponseAdjustRangeDuration);
    case MSG_4_REQ_RES_WIFI_SWITCH:
        return sizeof(UiResponseAdjustWifiSwitch);
    case MSG_4_REQ_RES_GET_WIFI_INFO:
        return sizeof(UiResponseGetWifiInfo);
    case MSG_4_REQ_RES_GET_PERIPHERAL_USB_PARA:
        return sizeof(UiResponseGetPeripheralUsbParameters);
    case MSG_4_REQ_RES_GET_PERIPHERAL_NETWORK_PARA:
        return sizeof(UiResponseGetPeripheralNetworkParameters);
    case MSG_4_REQ_RES_GET_PERIPHERAL_CAMERA_MODULE_PARA:
        return sizeof(UiResponseGetPeripheralCameraModuleParameters);
    case MSG_4_REQ_RES_GET_PERIPHERAL_LOW_LIGHT_MODULE_PARA:
        return sizeof(UiResponseGetPeripheralLowLightModuleParameters);
    case MSG_4_REQ_RES_GET_PERIPHERAL_INFRARED_MODULE_PARA:
        return sizeof(UiResponseGetPeripheralInfraredModuleParameters);
    case MSG_4_REQ_RES_INFRARED_MANUAL_REMOVE_BAD_PIXEL:
        return sizeof(UiResponseInfraredManualRemoveBadPixel);
    case MSG_4_REQ_RES_PANTILT_MOVING_CONTROL:
        return sizeof(UiResponsePanTiltMoveControl);
    case MSG_4_REQ_RES_PANTILT_MOVING_SPEED_ADJUST:
        return sizeof(UiResponsePanTiltSpeedControl);
    case MSG_4_REQ_RES_INFRARED_BAD_PIXEL_OPERATE:
        return sizeof(UiResponseInfraredBadPixelOperate);
    case MSG_4_REQ_RES_INFRARED_HOT_PIXEL_REPAIR_OPERATE:
        return sizeof(UiResponseInfraredHotPixelRepair);
    case MSG_4_REQ_RES_INFRARED_SD_NUC:
        return sizeof(UiResponseInfraredSdNuc);
    case MSG_4_REQ_RES_GET_PERIPHERAL_REMOTE_VIDEO_MODULE_PARA:
        return sizeof(UiResponseGetPeripheralRemoteVideoModuleParameters);
    case MSG_4_REQ_RES_GET_PERIPHERAL_COMPASS_PARA:
        return sizeof(UiResponseGetPeripheralCompassParameters);
    case MSG_4_REQ_RES_GET_PERIPHERAL_GNSS_PARA:
        return sizeof(UiResponseGetPeripheralGnssParameters);
    case MSG_4_REQ_RES_GET_PERIPHERAL_RANGE_FINDER_PARA:
        return sizeof(UiResponseGetPeripheralRangeFinderParameters);
    case MSG_4_REQ_RES_GET_PERIPHERAL_PANTILT_PARA:
        return sizeof(UiResponseGetPeripheralPanTiltParameters);
    default:
        return resultSize;
    }
}

static ROE_SIZE notify_min_size(ROE_SL msgType, int * known)
{
    *known = is_notification_type(msgType);
    if(!*known) return 0;

    switch(msgType) {
    case MSG_4_NOTIFY_RESOURCE_PATH_INFO:
        return sizeof(UiNotificationResourcePathInfo);
    case MSG_4_NOTIFY_RETICLE_INFO_UPDATING:
        return sizeof(UiNotificationReticleInfoUpdate);
    case MSG_4_NOTIFY_MAGNETIC_DECLINATION:
        return sizeof(UiNotificationInitialMagneticDeclination);
    case MSG_4_NOTIFY_OBSERVE_MODE:
        return sizeof(UiNotificationObserveMode);
    case MSG_4_NOTIFY_DEVICE_INIT_CONFIG_INFO:
        return sizeof(UiNotificationDeviceInitConfig);
    case MSG_4_NOTIFY_KEY_EVENT_INFO:
        return sizeof(UiNotificationKeyEventInfo);
    case MSG_4_NOTIFY_MAIN_MENU_OPERATE:
        return sizeof(UiNotificationMainMenuOperate);
    case MSG_4_NOTIFY_DIALOG_BOX_DISP:
        return sizeof(UiNotificationDialogBoxDisplay);
    case MSG_4_NOTIFY_RETICLE_OVERALL_INFO:
        return sizeof(UiNotificationReticleOverallInfo);
    case MSG_4_NOTIFY_OSD_INFO_SHOW_SWITCH:
        return sizeof(UiNotificationOsdShowSwitch);
    case MSG_4_NOTIFY_MAIN_DISPLAY_STATUS:
        return sizeof(UiNotificationMainDisplayStatus);
    case MSG_4_NOTIFY_VIDEO_ZOOM_INFO:
        return sizeof(UiNotificationVideoZoomInfo);
    case MSG_4_NOTIFY_VIDEO_OUTPUT_FREEZING:
        return sizeof(UiNotificationVideoOutputFreezing);
    case MSG_4_NOTIFY_VIDEO_OUTPUT_MIRROR_FLIP:
        return sizeof(UiNotificationVideoOutputMirrorFlip);
    case MSG_4_NOTIFY_VIDEO_OUTPUT_ROTATING:
        return sizeof(UiNotificationVideoOutputRotating);
    case MSG_4_NOTIFY_VIDEO_INPUT_DEVICE_STATUS:
        return sizeof(UiNotificationVideoInputDeviceStatus);
    case MSG_4_NOTIFY_CAMERA_MODULE_AUXILIARY_LIGHTING:
        return sizeof(UiNotificationAuxiliaryLighting);
    case MSG_4_NOTIFY_INFRARED_PSEUDO_COLOR_MODE:
        return sizeof(UiNotificationInfraredPseudoColorMode);
    case MSG_4_NOTIFY_CAPTURE_STATUS:
        return sizeof(UiNotificationCaptureStatus);
    case MSG_4_NOTIFY_RECORD_STATUS:
        return sizeof(UiNotificationRecordStatus);
    case MSG_4_NOTIFY_MEDIA_FILE_PLAY_OPERATE:
        return sizeof(UiNotificationMediaFilePlayOperate);
    case MSG_4_NOTIFY_DEVICE_ABILITY:
        return sizeof(UiNotificationDeviceAbility);
    case MSG_4_NOTIFY_DEVICE_STATUS:
        return sizeof(UiNotificationDeviceStatus);
    case MSG_4_NOTIFY_PERIPHERAL_SELF_TEST_INFO:
        return sizeof(UiNotificationPeripheralSelfTestInfo);
    case MSG_4_NOTIFY_PERIPHERAL_REAL_TIME_INFO:
        return sizeof(UiNotificationPeripheralRealTimeInfo);
    case MSG_4_NOTIFY_PERIPHERAL_BAT_VOL_INFO:
        return sizeof(UiNotificationPeripheralBatteryInfo);
    case MSG_4_NOTIFY_INFRARED_BAD_PIXEL_THRESHOLD:
        return sizeof(UiNotificationInfraredBadPixelThreshold);
    case MSG_4_NOTIFY_INFRARED_BAD_PIXEL_NUM:
        return sizeof(UiNotificationInfraredBadPixelCount);
    case MSG_4_NOTIFY_INFRARED_HOT_PIXEL_REPAIRED_CORRECTED_VALUE:
        return sizeof(UiNotificationInfraredHotPixelRepairCorrection);
    case MSG_4_NOTIFY_COMPASS_DATA:
        return sizeof(UiNotificationCompassData);
    case MSG_4_NOTIFY_COMPASS_CALIBRATION_SCORE:
        return sizeof(UiNotificationCompassCalibrationScore);
    case MSG_4_NOTIFY_GNSS_DATA:
        return sizeof(UiNotificationGnssData);
    case MSG_4_NOTIFY_RANGE_FINDER_STATUS:
        return sizeof(UiNotificationRangeFinderStatus);
    case MSG_4_NOTIFY_RANGE_DATA:
        return sizeof(UiNotificationRangeData);
    case MSG_4_NOTIFY_RANGE_COUNT_DOWN:
        return sizeof(UiNotificationRangeCountdown);
    case MSG_4_NOTIFY_PANTILT_HORIZONTAL_ANGLE:
        return sizeof(UiNotificationPanTiltHorizontalAngle);
    case MSG_4_NOTIFY_PANTILT_VERTICAL_ANGLE:
        return sizeof(UiNotificationPanTiltVerticalAngle);
    case MSG_4_NOTIFY_PANTILT_HORIZONTAL_RUNNING_STATUS:
        return sizeof(UiNotificationPanTiltHorizontalRunningStatus);
    case MSG_4_NOTIFY_PANTILT_VERTICAL_RUNNING_STATUS:
        return sizeof(UiNotificationPanTiltVerticalRunningStatus);
    case MSG_4_NOTIFY_PANTILT_OPERATE_INFO:
        return sizeof(UiNotificationPanTiltOperateInfo);
    default:
        return sizeof(UiIpcMessageHeader);
    }
}

static ROE_S32 validate_length_prefixed_strings(const ROE_U8 * data,
                                                ROE_SIZE dataLength,
                                                ROE_SIZE fixedSize,
                                                ROE_U8 stringCount)
{
    ROE_SIZE offset = fixedSize;
    for(ROE_U8 i = 0; i < stringCount; i++) {
        if(offset > dataLength || dataLength - offset < sizeof(ROE_U8)) {
            return ROE_FAILURE;
        }

        ROE_SIZE stringLength = data[offset++];
        if(stringLength > dataLength - offset) {
            return ROE_FAILURE;
        }
        offset += stringLength;
    }
    return offset == dataLength ? ROE_SUCCESS : ROE_FAILURE;
}

static ROE_S32 validate_media_items(const ROE_U8 * data,
                                    ROE_SIZE dataLength,
                                    ROE_SIZE fixedSize,
                                    ROE_U8 fileCount)
{
    if(fileCount > UI_MAX_MEDIA_FILE_NUM_ONE_PAGE || fixedSize > dataLength) {
        return ROE_FAILURE;
    }

    ROE_SIZE offset = fixedSize;
    for(ROE_U8 i = 0; i < fileCount; i++) {
        if(dataLength - offset < sizeof(UiMediaFileInfo)) {
            return ROE_FAILURE;
        }

        const UiMediaFileInfo * info = (const UiMediaFileInfo *)(data + offset);
        ROE_SIZE itemSize = sizeof(UiMediaFileInfo) + (ROE_SIZE)info->nameLength;
        if(itemSize > dataLength - offset) {
            return ROE_FAILURE;
        }
        offset += itemSize;
    }
    return offset == dataLength ? ROE_SUCCESS : ROE_FAILURE;
}

static ROE_S32 validate_reticle_items(const ROE_U8 * data, ROE_SIZE dataLength)
{
    const ROE_SIZE fixedSize = sizeof(UiNotificationReticleInfoUpdate);
    if(fixedSize > dataLength) return ROE_FAILURE;

    const UiNotificationReticleInfoUpdate * update = (const UiNotificationReticleInfoUpdate *)data;
    if(update->reticleCount < 0 || update->reticleCount > UI_MAX_DIVIDING_PLATES_NUM) return ROE_FAILURE;

    ROE_SIZE offset = fixedSize;
    for(ROE_S8 i = 0; i < update->reticleCount; i++) {
        if(dataLength - offset < sizeof(UiReticleEntry)) return ROE_FAILURE;

        const UiReticleEntry * plate = (const UiReticleEntry *)(data + offset);
        ROE_SIZE itemSize = sizeof(UiReticleEntry) + (ROE_SIZE)plate->nameLength;
        if(itemSize > dataLength - offset) return ROE_FAILURE;
        offset += itemSize;
    }
    return offset == dataLength ? ROE_SUCCESS : ROE_FAILURE;
}

ROE_S32 ui_ipc_validate_message(ROE_SL msgType,
                             const UiIpcRawData * rawData,
                             ROE_SIZE receivedBytes)
{
    if(!rawData || receivedBytes < sizeof(rawData->dataLength) || receivedBytes > sizeof(*rawData)) {
        return ROE_FAILURE;
    }

    ROE_SIZE actualDataLength = receivedBytes - sizeof(rawData->dataLength);
    if(rawData->dataLength < 0 || (ROE_SIZE)rawData->dataLength != actualDataLength ||
       actualDataLength > sizeof(rawData->data)) {
        return ROE_FAILURE;
    }
    if(actualDataLength < sizeof(UiIpcMessageHeader)) return ROE_FAILURE;

    const UiIpcMessageHeader * header = (const UiIpcMessageHeader *)rawData->data;
    if(header->version != UI_IPC_MESSAGE_VERSION) return ROE_FAILURE;

    ROE_SL baseType = msgType >= MSG_4_REQ_RES_INIT ? MSG_4_REQ_RES_INIT : MSG_4_NOTIFY_INIT;
    if(header->concreteMsgType != (ROE_U8)(msgType - baseType)) return ROE_FAILURE;

    int known = 0;
    ROE_SIZE minSize = 0;
    if(msgType >= MSG_4_REQ_RES_INIT) {
        minSize = response_min_size(msgType, &known);
    } else {
        minSize = notify_min_size(msgType, &known);
    }
    if(!known || actualDataLength < minSize) return ROE_FAILURE;

    switch(msgType) {
    case MSG_4_REQ_RES_GET_VERSION_INFO: {
        const UiResponseGetAppVersion * result = (const UiResponseGetAppVersion *)rawData->data;
        ROE_SIZE needed = sizeof(UiResponseGetAppVersion) + (ROE_SIZE)result->versionLength;
        return needed == actualDataLength ? ROE_SUCCESS : ROE_FAILURE;
    }
    case MSG_4_REQ_RES_GET_WIFI_INFO:
        return validate_length_prefixed_strings(rawData->data,
                                                actualDataLength,
                                                sizeof(UiResponseGetWifiInfo),
                                                3);
    case MSG_4_REQ_RES_GET_MEDIA_FILE_LIST: {
        const UiResponseGetMediaFileList * result = (const UiResponseGetMediaFileList *)rawData->data;
        return validate_media_items(rawData->data,
                                    actualDataLength,
                                    sizeof(UiResponseGetMediaFileList),
                                    result->fileCount);
    }
    case MSG_4_NOTIFY_RESOURCE_PATH_INFO:
        return validate_length_prefixed_strings(rawData->data,
                                                actualDataLength,
                                                sizeof(UiNotificationResourcePathInfo),
                                                4);
    case MSG_4_NOTIFY_RETICLE_INFO_UPDATING:
        return validate_reticle_items(rawData->data, actualDataLength);
    default:
        return actualDataLength == minSize ? ROE_SUCCESS : ROE_FAILURE;
    }
}
