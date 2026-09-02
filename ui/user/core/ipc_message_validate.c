#include "ipc_message_validate.h"

#include "ipcMsgQue4UiRcvNotify.h"
#include "ipcMsgQue4UiRcvRes.h"
#include "ipcMsgQue4UiSndRequest.h"

static int is_request_response_type(ROE_SL msgType)
{
    return (msgType >= MSG_4_REQ_RES_SYSTEM_GENERAL_OFFSET && msgType < MSG_4_REQ_RES_SYSTEM_GENERAL_BUTT) ||
           (msgType >= MSG_4_REQ_RES_SYSTEM_CONFIG_OFFSET && msgType < MSG_4_REQ_RES_SYSTEM_CONFIG_BUTT) ||
           (msgType >= MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_OFFSET &&
            msgType < MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_BUTT) ||
           (msgType >= MSG_4_REQ_RES_RETICLE_GENERAL_OFFSET && msgType < MSG_4_REQ_RES_RETICLE_GENERAL_BUTT) ||
           (msgType >= MSG_4_REQ_RES_VIDEO_OUTPUT_OFFSET && msgType < MSG_4_REQ_RES_VIDEO_OUTPUT_BUTT) ||
           (msgType >= MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_OFFSET &&
            msgType < MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_BUTT) ||
           (msgType >= MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_OFFSET &&
            msgType < MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_BUTT) ||
           (msgType >= MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_OFFSET &&
            msgType < MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_BUTT) ||
           (msgType >= MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_OFFSET &&
            msgType < MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_BUTT) ||
           (msgType >= MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_OFFSET &&
            msgType < MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_BUTT) ||
           (msgType >= MSG_4_REQ_RES_AUDIO_GENERAL_OFFSET && msgType < MSG_4_REQ_RES_AUDIO_BUTT) ||
           (msgType >= MSG_4_REQ_RES_MEDIA_FILE_OFFSET && msgType < MSG_4_REQ_RES_MEDIA_FILE_BUTT) ||
           (msgType >= MSG_4_REQ_RES_PERIPHERAL_USB_OFFSET &&
            msgType < MSG_4_REQ_RES_PERIPHERAL_USB_BUTT) ||
           (msgType >= MSG_4_REQ_RES_PERIPHERAL_NETWORK_OFFSET &&
            msgType < MSG_4_REQ_RES_PERIPHERAL_NETWORK_BUTT) ||
           (msgType >= MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_OFFSET &&
            msgType < MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_BUTT) ||
           (msgType >= MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_OFFSET &&
            msgType < MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_BUTT) ||
           (msgType >= MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_OFFSET &&
            msgType < MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_BUTT) ||
           (msgType >= MSG_4_REQ_RES_PERIPHERAL_REMOTED_VIDEO_MODULE_OFFSET &&
            msgType < MSG_4_REQ_RES_PERIPHERAL_REMOTE_VIDEO_MODULE_BUTT) ||
           (msgType >= MSG_4_REQ_RES_PERIPHERAL_COMPASS_OFFSET &&
            msgType < MSG_4_REQ_RES_PERIPHERAL_COMPASS_BUTT) ||
           (msgType >= MSG_4_REQ_RES_PERIPHERAL_GNSS_OFFSET &&
            msgType < MSG_4_REQ_RES_PERIPHERAL_GNSS_BUTT) ||
           (msgType >= MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_OFFSET &&
            msgType < MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_BUTT) ||
           (msgType >= MSG_4_REQ_RES_PERIPHERAL_PANTILT_OFFSET &&
            msgType < MSG_4_REQ_RES_PERIPHERAL_PANTILT_BUTT);
}

static int is_notification_type(ROE_SL msgType)
{
    return (msgType >= MSG_4_NOTIFY_SYSTEM_OFFSET && msgType < MSG_4_NOTIFY_SYSTEM_BUTT) ||
           (msgType >= MSG_4_NOTIFY_RETICLE_OFFSET && msgType < MSG_4_NOTIFY_RETICLE_BUTT) ||
           (msgType >= MSG_4_NOTIFY_VIDEO_OUTPUT_OFFSET && msgType < MSG_4_NOTIFY_VIDEO_OUTPUT_BUTT) ||
           (msgType >= MSG_4_NOTIFY_VIDEO_INPUT_OFFSET && msgType < MSG_4_NOTIFY_VIDEO_INPUT_BUTT) ||
           (msgType >= MSG_4_NOTIFY_AUDIO_OFFSET && msgType < MSG_4_NOTIFY_AUDIO_BUTT) ||
           (msgType >= MSG_4_NOTIFY_MEDIA_FILE_OFFSET && msgType < MSG_4_NOTIFY_MEDIA_FILE_BUTT) ||
           (msgType >= MSG_4_NOTIFY_PERIPHERAL_GENERAL_OFFSET &&
            msgType < MSG_4_NOTIFY_PERIPHERAL_GENERAL_BUTT) ||
           (msgType >= MSG_4_NOTIFY_PERIPHERAL_NETWORK_OFFSET &&
            msgType < MSG_4_NOTIFY_PERIPHERAL_NETWORK_BUTT) ||
           (msgType >= MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_OFFSET &&
            msgType < MSG_4_NOTIFY_PERIPHERAL_CAMERA_MODULE_BUTT) ||
           (msgType >= MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_OFFSET &&
            msgType < MSG_4_NOTIFY_PERIPHERAL_INFRARED_MODULE_BUTT) ||
           (msgType >= MSG_4_NOTIFY_PERIPHERAL_COMPASS_OFFSET &&
            msgType < MSG_4_NOTIFY_PERIPHERAL_COMPASS_BUTT) ||
           (msgType >= MSG_4_NOTIFY_PERIPHERAL_GNSS_OFFSET &&
            msgType < MSG_4_NOTIFY_PERIPHERAL_GNSS_BUTT) ||
           (msgType >= MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_OFFSET &&
            msgType < MSG_4_NOTIFY_PERIPHERAL_RANGE_FINDER_BUTT) ||
           (msgType >= MSG_4_NOTIFY_PERIPHERAL_PANTILT_OFFSET &&
            msgType < MSG_4_NOTIFY_PERIPHERAL_PANTILT_BUTT);
}

static ROE_SIZE response_min_size(ROE_SL msgType, int * known)
{
    const ROE_SIZE resultSize = sizeof(MsgQueHeader4Ui_st) + sizeof(ROE_U8);
    *known = is_request_response_type(msgType);
    if(!*known) return 0;

    switch(msgType) {
    case MSG_4_REQ_RES_LOG_IN_OUT:
        return sizeof(RspRegister_st);
    case MSG_4_REQ_RES_SHUTDOWN:
        return sizeof(RspShutdown_st);
    case MSG_4_REQ_RES_GET_VERSION_INFO:
        return sizeof(RspGetAppVersion_st);
    case MSG_4_REQ_RES_SET_SYSTEM_TIME:
        return sizeof(RspSetSystemTime_st);
    case MSG_4_REQ_RES_FORMAT_DISK_PARTITION:
        return sizeof(RspFormatDisk_st);
    case MSG_4_REQ_RES_RESTORE_FACTORY_SETTING:
        return sizeof(RspRestoreFactory_st);
    case MSG_4_REQ_RES_SAVE_LANGUAGE_CONFIG:
        return sizeof(RspSaveLanguageConfig_st);
    case MSG_4_REQ_RES_GET_USER_COMMON_CONFIG:
        return sizeof(RspGetUserCommonConfig_st);
    case MSG_4_REQ_RES_SET_USER_COMMON_CONFIG:
        return sizeof(RspSetUserCommonConfig_st);
    case MSG_4_REQ_RES_GET_USER_MEDIA_CONFIG:
        return sizeof(RspGetUserMediaConfig_st);
    case MSG_4_REQ_RES_SET_USER_MEDIA_CONFIG:
        return sizeof(RspSetUserMediaConfig_st);
    case MSG_4_REQ_RES_EXIT_MENU_MODE:
        return sizeof(RspExitMenu_st);
    case MSG_4_REQ_RES_EXIT_DIALOG_BOX:
        return sizeof(RspExitDialogBox_st);
    case MSG_4_REQ_RES_SET_RETICLE_COMMON_CONFIG:
        return sizeof(RspSetReticleCommonConfig_st);
    case MSG_4_REQ_RES_WEAPON_SET_RETICLE_STYLE:
        return sizeof(RspWeaponSetReticleStyle_st);
    case MSG_4_REQ_RES_WEAPON_SET_RETICLE_COLOR:
        return sizeof(RspWeaponSetReticleColor_st);
    case MSG_4_REQ_RES_WEAPON_SET_RETICLE_LUMA:
        return sizeof(RspWeaponSetBrightness_st);
    case MSG_4_REQ_RES_WEAPON_SAVE_CONFIG:
        return sizeof(RspWeaponSaveConfig_st);
    case MSG_4_REQ_RES_WEAPON_OPERATE_MARK_CONFIG:
        return sizeof(RspWeaponMarkConfigOperate_st);
    case MSG_4_REQ_RES_WEAPON_SET_DEFAULT_SHOOT_DISTANCE:
        return sizeof(RspWeaponSetDefaultShootDist_st);
    case MSG_4_REQ_RES_WEAPON_OPERATE_SHOOT_DISTANCE:
        return sizeof(RspWeaponOperateShootDist_st);
    case MSG_4_REQ_RES_WEAPON_SET_SHOOT_POSITION:
        return sizeof(RspWeaponSetShootPosition_st);
    case MSG_4_REQ_RES_WEAPON_SET_SHOOT_ZERO:
        return sizeof(RspWeaponSetShootZero_st);
    case MSG_4_REQ_RES_GET_VIDEO_OUTPUT_PARA:
        return sizeof(RspGetVideoOutputPara_st);
    case MSG_4_REQ_RES_MAIN_DISPLAY_BRIGHTNESS_ADJUST:
        return sizeof(RspAdjustOledBrightness_st);
    case MSG_4_REQ_RES_MAIN_DISPLAY_CONTRAST_ADJUST:
        return sizeof(RspAdjustOledContrast_st);
    case MSG_4_REQ_RES_EXTEND_DISPLAY_SWITCH:
        return sizeof(RspAdjustExtendDisplaySwitch_st);
    case MSG_4_REQ_RES_PIP_SWITCH:
        return sizeof(RspAdjustPipSwitch_st);
    case MSG_4_REQ_RES_VIDEO_ZOOM:
        return sizeof(RspAdjustVideoZoom_st);
    case MSG_4_REQ_RES_VIDEO_OUTPUT_FREEZE:
        return sizeof(RspFreezeVideoInput_st);
    case MSG_4_REQ_RES_OBJECT_RECOGNITION_SWITCH:
        return sizeof(RspAdjustRecognitionSwitch_st);
    case MSG_4_REQ_RES_GET_VIDEO_INPUT_PARA:
        return sizeof(RspGetVideoInputPara_st);
    case MSG_4_REQ_RES_MAIN_OBSERVE_MODE_SWITCHING:
        return sizeof(RspAdjustObserveMode_st);
    case MSG_4_REQ_RES_PIP_OBSERVE_MODE_SWITCHING:
        return sizeof(RspAdjustObserveMode_st);
    case MSG_4_REQ_RES_GET_VIDEO_INPUT_CAMERA_PARA:
        return sizeof(RspGetVideoInputCameraPara_st);
    case MSG_4_REQ_RES_CAMERA_DAYNIGHT_MODE_SWITCHING:
        return sizeof(RspAdjustDayNight_st);
    case MSG_4_REQ_RES_CAMERA_BRIGHTNESS_ADJUST:
        return sizeof(RspAdjustCameraBrightness_st);
    case MSG_4_REQ_RES_CAMERA_CONTRAST_ADJUST:
        return sizeof(RspAdjustCameraContrast_st);
    case MSG_4_REQ_RES_CAMERA_SATURATION_ADJUST:
        return sizeof(RspAdjustCameraSaturation_st);
    case MSG_4_REQ_RES_CAMERA_HUE_ADJUST:
        return sizeof(RspAdjustCameraHue_st);
    case MSG_4_REQ_RES_CAMERA_DEHAZE_SWITCH:
        return sizeof(RspAdjustFogSwitch_st);
    case MSG_4_REQ_RES_CAMERA_DEHAZE_STRENGTH_ADJUST:
        return sizeof(RspAdjustFogIntensity_st);
    case MSG_4_REQ_RES_CAMERA_EXPOSURE_ADJUST:
        return sizeof(RspAdjustCameraExposure_st);
    case MSG_4_REQ_RES_GET_VIDEO_INPUT_LOW_LIGHT_PARA:
        return sizeof(RspGetVideoInputLowLightPara_st);
    case MSG_4_REQ_RES_GET_VIDEO_INPUT_INFRARED_PARA:
        return sizeof(RspGetVideoInputInfraredPara_st);
    case MSG_4_REQ_RES_INFRARED_PSEUDOCOLOR_MODE_SWITCHING:
        return sizeof(RspAdjustInfraredPseudoColor_st);
    case MSG_4_REQ_RES_INFRARED_BRIGHTNESS_ADJUST:
        return sizeof(RspAdjustInfraredBrightness_st);
    case MSG_4_REQ_RES_INFRARED_CONTRAST_ADJUST:
        return sizeof(RspAdjustInfraredContrast_st);
    case MSG_4_REQ_RES_INFRARED_IMAGE_ENHANCE_ADJUST:
        return sizeof(RspInfraredEnhanceImage_st);
    case MSG_4_REQ_RES_INFRARED_SCENARIO_MODE_SWITCHING:
        return sizeof(RspInfraredScenarioMode_st);
    case MSG_4_REQ_RES_INFRARED_HOTSPOT_TRACKING_SWITCH:
        return sizeof(RspInfraredHotspotTrackingSwitch_st);
    case MSG_4_REQ_RES_GET_VIDEO_INPUT_REMOTE_PARA:
        return sizeof(RspGetVideoInputRemotePara_st);
    case MSG_4_REQ_RES_GET_AUDIO_PARA:
        return sizeof(RspGetAudioPara_st);
    case MSG_4_REQ_RES_CAPTURE_MEDIA_FILE:
        return sizeof(RspCaptureMediaFile_st);
    case MSG_4_REQ_RES_RECORD_MEDIA_FILE:
        return sizeof(RspRecordMediaFile_st);
    case MSG_4_REQ_RES_INFRARED_SET_BAD_PIXEL_THRESHOLD:
        return sizeof(RspInfraredSetBadPixelThreshold_st);
    case MSG_4_REQ_RES_COMPASS_SWITCH:
        return sizeof(RspAdjustCompassSwitch_st);
    case MSG_4_REQ_RES_COMPASS_SET_MAGNETIC_DECLINATION:
        return sizeof(RspSetCompassDeclination_st);
    case MSG_4_REQ_RES_COMPASS_SAVE_CONFIG:
        return sizeof(RspSaveCompassConfig_st);
    case MSG_4_REQ_RES_COMPASS_START_CALIBRATION:
        return sizeof(RspStartCompassCalibration_st);
    case MSG_4_REQ_RES_COMPASS_STOP_CALIBRATION:
        return sizeof(RspStopCompassCalibration_st);
    case MSG_4_REQ_RES_GNSS_SWITCH:
        return sizeof(RspAdjustGnssSwitch_st);
    case MSG_4_REQ_RES_GNSS_POSITION_SYSTEM_SWITCHING:
        return sizeof(RspAdjustGnssSystem_st);
    case MSG_4_REQ_RES_GNSS_COORDINATE_SYSTEM_SWITCHING:
        return sizeof(RspAdjustCoordinateSystem_st);
    case MSG_4_REQ_RES_GET_MEDIA_FILE_LIST:
        return sizeof(RspGetMediaFileList_st);
    case MSG_4_REQ_RES_EXIT_PLAYBACK_MEDIA_LIST:
        return sizeof(RspExitPlaybackList_st);
    case MSG_4_REQ_RES_DEL_MEDIA_FILE:
        return sizeof(RspDelMediaFile_st);
    case MSG_4_REQ_RES_PLAY_MEDIA_FILE:
        return sizeof(RspPlayMediaFile_st);
    case MSG_4_REQ_RES_PLAY_ADJACENT_MEDIA_FILE:
        return sizeof(RspPlayPriorOrNextMediaFile_st);
    case MSG_4_REQ_RES_STOP_MEDIA_FILE_PLAY:
        return sizeof(RspExitMediaPlay_st);
    case MSG_4_REQ_RES_RANGE_FINDER_OPERATE:
        return sizeof(RspSwitchRange_st);
    case MSG_4_REQ_RES_RANGE_FREQUENCY_ADJUST:
        return sizeof(RspAdjustRangeFrequency_st);
    case MSG_4_REQ_RES_RANGE_TIME_DURATION_ADJUST:
        return sizeof(RspAdjustRangeDuration_st);
    case MSG_4_REQ_RES_WIFI_SWITCH:
        return sizeof(RspAdjustWifiSwitch_st);
    case MSG_4_REQ_RES_GET_WIFI_INFO:
        return sizeof(RspGetWifiInfo_st);
    case MSG_4_REQ_RES_GET_PERIPHERAL_USB_PARA:
        return sizeof(RspGetPeripheralUsbPara_st);
    case MSG_4_REQ_RES_GET_PERIPHERAL_NETWORK_PARA:
        return sizeof(RspGetPeripheralNetworkPara_st);
    case MSG_4_REQ_RES_GET_PERIPHERAL_CAMERA_MODULE_PARA:
        return sizeof(RspGetPeripheralCameraModulePara_st);
    case MSG_4_REQ_RES_GET_PERIPHERAL_LOW_LIGHT_MODULE_PARA:
        return sizeof(RspGetPeripheralLowLightModulePara_st);
    case MSG_4_REQ_RES_GET_PERIPHERAL_INFRARED_MODULE_PARA:
        return sizeof(RspGetPeripheralInfraredModulePara_st);
    case MSG_4_REQ_RES_INFRARED_MANUAL_REMOVE_BAD_PIXEL:
        return sizeof(RspInfraredManualRemoveBadPixel_st);
    case MSG_4_REQ_RES_PANTILT_MOVING_CONTROL:
        return sizeof(RspPanTiltMoveControl_st);
    case MSG_4_REQ_RES_PANTILT_MOVING_SPEED_ADJUST:
        return sizeof(RspPanTiltSpeedControl_st);
    case MSG_4_REQ_RES_INFRARED_BAD_PIXEL_OPERATE:
        return sizeof(RspInfraredBadPixelOperate_st);
    case MSG_4_REQ_RES_INFRARED_HOT_PIXEL_REPAIR_OPERATE:
        return sizeof(RspInfraredHotPixelRepair_st);
    case MSG_4_REQ_RES_INFRARED_SD_NUC:
        return sizeof(RspInfraredSdNuc_st);
    case MSG_4_REQ_RES_GET_PERIPHERAL_REMOTED_VIDEO_MODULE_PARA:
        return sizeof(RspGetPeripheralRemotedVideoModulePara_st);
    case MSG_4_REQ_RES_GET_PERIPHERAL_COMPASS_PARA:
        return sizeof(RspGetPeripheralCompassPara_st);
    case MSG_4_REQ_RES_GET_PERIPHERAL_GNSS_PARA:
        return sizeof(RspGetPeripheralGnssPara_st);
    case MSG_4_REQ_RES_GET_PERIPHERAL_RANGE_FINDER_PARA:
        return sizeof(RspGetPeripheralRangeFinderPara_st);
    case MSG_4_REQ_RES_GET_PERIPHERAL_PANTILT_PARA:
        return sizeof(RspGetPeripheralPanTiltPara_st);
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
        return sizeof(NotifyPath_st);
    case MSG_4_NOTIFY_RETICLE_INFO_UPDATING:
        return sizeof(NotifyReticleUpdate_st);
    case MSG_4_NOTIFY_MAGNETIC_DECLINATION:
        return sizeof(NotifyMagneticDeclination_st);
    case MSG_4_NOTIFY_OBSERVE_MODE:
        return sizeof(NotifyObserveMode_st);
    case MSG_4_NOTIFY_DEVICE_INIT_CONFIG_INFO:
        return sizeof(NotifyInitConfig_st);
    case MSG_4_NOTIFY_KEY_EVENT_INFO:
        return sizeof(NotifyMenuKey_st);
    case MSG_4_NOTIFY_MAIN_MENU_OPERATE:
        return sizeof(NotifyMenuMode_st);
    case MSG_4_NOTIFY_DIALOG_BOX_DISP:
        return sizeof(NotifyDialog_st);
    case MSG_4_NOTIFY_RETICLE_OVERALL_INFO:
        return sizeof(NotifyReticleInfo_st);
    case MSG_4_NOTIFY_OSD_INFO_SHOW_SWITCH:
        return sizeof(NotifyOsd_st);
    case MSG_4_NOTIFY_MAIN_DISPLAY_STATUS:
        return sizeof(NotifyOled_st);
    case MSG_4_NOTIFY_VIDEO_ZOOM_INFO:
        return sizeof(NotifyZoom_st);
    case MSG_4_NOTIFY_VIDEO_OUTPUT_FREEZING:
        return sizeof(NotifyFreeze_st);
    case MSG_4_NOTIFY_VIDEO_OUTPUT_MIRROR_FLIP:
        return sizeof(NotifyMirror_st);
    case MSG_4_NOTIFY_VIDEO_OUTPUT_ROTATING:
        return sizeof(NotifyRotate_st);
    case MSG_4_NOTIFY_VIDEO_INPUT_DEVICE_STATUS:
        return sizeof(NotifyVideoInput_st);
    case MSG_4_NOTIFY_CAMERA_MODULE_AUXILIARY_LIGHTING:
        return sizeof(NotifyLight_st);
    case MSG_4_NOTIFY_INFRARED_PSEUDO_COLOR_MODE:
        return sizeof(NotifyPseudoColor_st);
    case MSG_4_NOTIFY_CAPTURE_STATUS:
        return sizeof(NotifyPhoto_st);
    case MSG_4_NOTIFY_RECORD_STATUS:
        return sizeof(NotifyRecord_st);
    case MSG_4_NOTIFY_MEDIA_FILE_PLAY_OPERATE:
        return sizeof(NotifyMediaPlay_st);
    case MSG_4_NOTIFY_DEVICE_ABILITY:
        return sizeof(NotifyDeviceCapability_st);
    case MSG_4_NOTIFY_DEVICE_STATUS:
        return sizeof(NotifyDeviceSwitch_st);
    case MSG_4_NOTIFY_PERIPHERAL_SELF_TEST_INFO:
        return sizeof(NotifySelfCheck_st);
    case MSG_4_NOTIFY_PERIPHERAL_REAL_TIME_INFO:
        return sizeof(NotifyPower_st);
    case MSG_4_NOTIFY_PERIPHERAL_BAT_VOL_INFO:
        return sizeof(NotifyBattery_st);
    case MSG_4_NOTIFY_INFRARED_BAD_PIXEL_THRESHOLD:
        return sizeof(NotifyBadPixelThreshold_st);
    case MSG_4_NOTIFY_INFRARED_BAD_PIXEL_NUM:
        return sizeof(NotifyBadPixelCount_st);
    case MSG_4_NOTIFY_INFRARED_HOT_PIXEL_REPAIRED_CORRECTED_VALUE:
        return sizeof(NotifyHotPixelFix_st);
    case MSG_4_NOTIFY_COMPASS_DATA:
        return sizeof(NotifyCompass_st);
    case MSG_4_NOTIFY_COMPASS_CALIBRATION_SCORE:
        return sizeof(NotifyCompassScore_st);
    case MSG_4_NOTIFY_GNSS_DATA:
        return sizeof(NotifyGps_st);
    case MSG_4_NOTIFY_RANGE_FINDER_STATUS:
        return sizeof(NotifyLaserState_st);
    case MSG_4_NOTIFY_RANGE_DATA:
        return sizeof(NotifyLaser_st);
    case MSG_4_NOTIFY_RANGE_COUNT_DOWN:
        return sizeof(NotifyLaserCountDown_st);
    case MSG_4_NOTIFY_PANTILT_HORIZONTAL_ANGLE:
        return sizeof(NotifyGimbalYaw_st);
    case MSG_4_NOTIFY_PANTILT_VERTICAL_ANGLE:
        return sizeof(NotifyGimbalPitch_st);
    case MSG_4_NOTIFY_PANTILT_HORIZONTAL_RUNNING_STATUS:
        return sizeof(NotifyGimbalYawState_st);
    case MSG_4_NOTIFY_PANTILT_VERTICAL_RUNNING_STATUS:
        return sizeof(NotifyGimbalPitchState_st);
    case MSG_4_NOTIFY_PANTILT_OPERATE_INFO:
        return sizeof(NotifyGimbalControl_st);
    default:
        return sizeof(MsgQueHeader4Ui_st);
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
        if(dataLength - offset < sizeof(MediaFileInfo_st)) {
            return ROE_FAILURE;
        }

        const MediaFileInfo_st * info = (const MediaFileInfo_st *)(data + offset);
        ROE_SIZE itemSize = sizeof(MediaFileInfo_st) + (ROE_SIZE)info->nameLen;
        if(itemSize > dataLength - offset) {
            return ROE_FAILURE;
        }
        offset += itemSize;
    }
    return offset == dataLength ? ROE_SUCCESS : ROE_FAILURE;
}

static ROE_S32 validate_reticle_items(const ROE_U8 * data, ROE_SIZE dataLength)
{
    const ROE_SIZE fixedSize = sizeof(NotifyReticleUpdate_st);
    if(fixedSize > dataLength) return ROE_FAILURE;

    const NotifyReticleUpdate_st * update = (const NotifyReticleUpdate_st *)data;
    if(update->num < 0 || update->num > UI_MAX_DIVIDING_PLATES_NUM) return ROE_FAILURE;

    ROE_SIZE offset = fixedSize;
    for(ROE_S8 i = 0; i < update->num; i++) {
        if(dataLength - offset < sizeof(DividingPlates_st)) return ROE_FAILURE;

        const DividingPlates_st * plate = (const DividingPlates_st *)(data + offset);
        ROE_SIZE itemSize = sizeof(DividingPlates_st) + (ROE_SIZE)plate->nameLen;
        if(itemSize > dataLength - offset) return ROE_FAILURE;
        offset += itemSize;
    }
    return offset == dataLength ? ROE_SUCCESS : ROE_FAILURE;
}

ROE_S32 ipc_validate_message(ROE_SL msgType,
                             const RoeIpcMsgQueRawData_st * rawData,
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
    if(actualDataLength < sizeof(MsgQueHeader4Ui_st)) return ROE_FAILURE;

    const MsgQueHeader4Ui_st * head = (const MsgQueHeader4Ui_st *)rawData->data;
    if(head->version != UI_MSG_VERSION) return ROE_FAILURE;

    ROE_SL baseType = msgType >= MSG_4_REQ_RES_INIT ? MSG_4_REQ_RES_INIT : MSG_4_NOTIFY_INIT;
    if(head->concreteMsgType != (ROE_U8)(msgType - baseType)) return ROE_FAILURE;

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
        const RspGetAppVersion_st * result = (const RspGetAppVersion_st *)rawData->data;
        ROE_SIZE needed = sizeof(RspGetAppVersion_st) + (ROE_SIZE)result->verLen;
        return needed == actualDataLength ? ROE_SUCCESS : ROE_FAILURE;
    }
    case MSG_4_REQ_RES_GET_WIFI_INFO:
        return validate_length_prefixed_strings(rawData->data,
                                                actualDataLength,
                                                sizeof(RspGetWifiInfo_st),
                                                3);
    case MSG_4_REQ_RES_GET_MEDIA_FILE_LIST: {
        const RspGetMediaFileList_st * result = (const RspGetMediaFileList_st *)rawData->data;
        return validate_media_items(rawData->data,
                                    actualDataLength,
                                    sizeof(RspGetMediaFileList_st),
                                    result->fileCount);
    }
    case MSG_4_NOTIFY_RESOURCE_PATH_INFO:
        return validate_length_prefixed_strings(rawData->data,
                                                actualDataLength,
                                                sizeof(NotifyPath_st),
                                                4);
    case MSG_4_NOTIFY_RETICLE_INFO_UPDATING:
        return validate_reticle_items(rawData->data, actualDataLength);
    default:
        return actualDataLength == minSize ? ROE_SUCCESS : ROE_FAILURE;
    }
}
