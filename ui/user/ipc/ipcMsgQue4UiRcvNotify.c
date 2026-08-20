//
// Created by jinxing on 2026/2/11.
//

#include "ipcMsgQue4UiRcvNotify.h"
#include "handleNotify.h"

ROE_S32 ParseNotifyMsg(ROE_SL msgType, RoeIpcMsgQueRawData_st * rawData)
{
    ROE_U8 * msgData = rawData->data;

    switch((RoeIpcMsgQue4UiType_e)msgType) {
    case MSG_4_NOTIFY_DEVICE_INIT_CONFIG_INFO:
        return handleInitConfigNotify(msgData);
    case MSG_4_NOTIFY_RESOURCE_PATH_INFO:
        return handleResourcePathNotify(msgData);
    case MSG_4_NOTIFY_KEY_EVENT_INFO:
        return handleKeyEventNotify(msgData);
    case MSG_4_NOTIFY_MAIN_MENU_OPERATE:
        return handleMenuNotify(msgData);
    case MSG_4_NOTIFY_DIALOG_BOX_DISP:
        return handleDialogBoxNotify(msgData);
    case MSG_4_NOTIFY_RETICLE_OVERALL_INFO:
        return handleReticleOverallInfoNotify(msgData);
    case MSG_4_NOTIFY_RETICLE_INFO_UPDATING:
        return handleReticleInfoUpdatingNotify(msgData);
    case MSG_4_NOTIFY_OSD_INFO_SHOW_SWITCH:
        return handleOsdShowHideOperateNotify(msgData);
    case MSG_4_NOTIFY_MAIN_DISPLAY_STATUS:
        return handleOledStatusInfoNotify(msgData);
    case MSG_4_NOTIFY_VIDEO_ZOOM_INFO:
        return handleZoomInfoNotify(msgData);
    case MSG_4_NOTIFY_VIDEO_OUTPUT_FREEZING:
        return handleVideoInputDeviceFreezingNotify(msgData);
    case MSG_4_NOTIFY_VIDEO_OUTPUT_MIRROR_FLIP:
        return handleVideoInputDeviceMirrorFlipNotify(msgData);
    case MSG_4_NOTIFY_VIDEO_OUTPUT_ROTATING:
        return handleVideoInputDeviceRotatingNotify(msgData);
    case MSG_4_NOTIFY_VIDEO_INPUT_DEVICE_STATUS:
        return handleVideoInputDeviceSwitchStatusNotify(msgData);
    case MSG_4_NOTIFY_OBSERVE_MODE:
        return handleObserveModeNotify(msgData);
    case MSG_4_NOTIFY_INFRARED_PSEUDO_COLOR_MODE:
        return handleInfraredPseudoColorModeNotify(msgData);
    case MSG_4_NOTIFY_CAPTURE_STATUS:
        return handleSnapStatusNotify(msgData);
    case MSG_4_NOTIFY_RECORD_STATUS:
        return handleRecordStatusNotify(msgData);
    case MSG_4_NOTIFY_MEDIA_FILE_PLAY_OPERATE:
        return handleMediaFilePlayOperateNotify(msgData);
    case MSG_4_NOTIFY_DEVICE_ABILITY:
        return handlePeripheralsAbilityNotify(msgData);
    case MSG_4_NOTIFY_DEVICE_STATUS:
        return handlePeripheralsPowerStatusNotify(msgData);
    case MSG_4_NOTIFY_PERIPHERAL_SELF_TEST_INFO:
        return handlePeripheralSelfTest(msgData);
    case MSG_4_NOTIFY_PERIPHERAL_REAL_TIME_INFO:
        return handleSdVccVolNotify(msgData);
    case MSG_4_NOTIFY_PERIPHERAL_BAT_VOL_INFO:
        return handleBatteryInfoNotify(msgData);
    case MSG_4_NOTIFY_CAMERA_MODULE_AUXILIARY_LIGHTING:
        return handleVideoInputDeviceAuxiliaryLightingNotify(msgData);
    case MSG_4_NOTIFY_INFRARED_BAD_PIXEL_THRESHOLD:
        return handleInfraredBadPixelThresholdNotify(msgData);
    case MSG_4_NOTIFY_INFRARED_BAD_PIXEL_NUM:
        return handleInfraredBadPixelNumNotify(msgData);
    case MSG_4_NOTIFY_INFRARED_HOT_PIXEL_REPAIRED_CORRECTED_VALUE:
        return handleInfraredHotPixelRepairedCorrectedValueNotify(msgData);
    case MSG_4_NOTIFY_COMPASS_DATA:
        return handleCompassData(msgData);
    case MSG_4_NOTIFY_MAGNETIC_DECLINATION:
        return handleMagneticDeclinationNotify(msgData);
    case MSG_4_NOTIFY_COMPASS_CALIBRATION_SCORE:
        return handleCompassCalibrationNotify(msgData);
    case MSG_4_NOTIFY_GNSS_DATA:
        return handleGpsData(msgData);
    case MSG_4_NOTIFY_RANGE_FINDER_STATUS:
        return handleRangeFinderStatusNotify(msgData);
    case MSG_4_NOTIFY_RANGE_DATA:
        return handleRangeData(msgData);
    case MSG_4_NOTIFY_RANGE_COUNT_DOWN:
        return handleRangeCountdownNotify(msgData);
    case MSG_4_NOTIFY_PANTILT_HORIZONTAL_ANGLE:
        return handlePanTiltHorizontalAngleNotify(msgData);
    case MSG_4_NOTIFY_PANTILT_VERTICAL_ANGLE:
        return handlePanTiltVerticalAngleNotify(msgData);
    case MSG_4_NOTIFY_PANTILT_HORIZONTAL_RUNNING_STATUS:
        return handlePanTiltHorizontalRunningStatusNotify(msgData);
    case MSG_4_NOTIFY_PANTILT_VERTICAL_RUNNING_STATUS:
        return handlePanTiltVerticalRunningStatusNotify(msgData);
    case MSG_4_NOTIFY_PANTILT_OPERATE_INFO:
        return handleRtCtlPanTiltInfoNotify(msgData);
    default:
        break;
    }
    return ROE_FAILURE;
}