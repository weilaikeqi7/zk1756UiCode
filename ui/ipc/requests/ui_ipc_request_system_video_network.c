//
// Created by jinxing on 2026/2/11.
//

#include "ui_ipc_request_sender.h"
#include "ui_ipc_request_internal.h"

ROE_S32 UiIpcSendRegisterRequest(ROE_S32 msgQueId, UiRequestRegister * registerType)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_LOG_IN_OUT, registerType, sizeof(UiRequestRegister), ROE_NULL);
}

ROE_S32 UiIpcSendExitMenuRequest(ROE_S32 msgQueId)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_EXIT_MENU_MODE, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 UiIpcSendTimeRequest(ROE_S32 msgQueId, UiRequestSetSystemTime * setTime)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_SET_SYSTEM_TIME, setTime, sizeof(UiRequestSetSystemTime), ROE_NULL);
}

ROE_S32 UiIpcSendObserveModeRequest(ROE_S32 msgQueId, UiRequestSwitchMainObserveMode * request)
{
    return UiIpcSendRequest(
        msgQueId,
        MSG_4_REQ_RES_MAIN_OBSERVE_MODE_SWITCHING,
        request,
        sizeof(UiRequestSwitchMainObserveMode),
        ROE_NULL);
}

ROE_S32 UiIpcSendPipObserveModeRequest(ROE_S32 msgQueId, UiRequestSwitchPipObserveMode * request)
{
    return UiIpcSendRequest(
        msgQueId,
        MSG_4_REQ_RES_PIP_OBSERVE_MODE_SWITCHING,
        request,
        sizeof(UiRequestSwitchPipObserveMode),
        ROE_NULL);
}

ROE_S32 UiIpcSendDayNightRequest(ROE_S32 msgQueId, UiRequestAdjustDayNight * setDayNight)
{
    return UiIpcSendRequest(
        msgQueId,
        MSG_4_REQ_RES_CAMERA_DAYNIGHT_MODE_SWITCHING,
        setDayNight,
        sizeof(UiRequestAdjustDayNight),
        ROE_NULL);
}

ROE_S32 UiIpcSendRecognitionSwitchRequest(ROE_S32 msgQueId, UiRequestAdjustRecognitionSwitch * setRecognitionSwitch)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_OBJECT_RECOGNITION_SWITCH,
                         setRecognitionSwitch,
                         sizeof(UiRequestAdjustRecognitionSwitch),
                         ROE_NULL);
}

ROE_S32 UiIpcSendCameraBrightnessRequest(ROE_S32 msgQueId, UiRequestAdjustCameraBrightness * cameraBrightness)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_CAMERA_BRIGHTNESS_ADJUST,
                         cameraBrightness,
                         sizeof(UiRequestAdjustCameraBrightness),
                         ROE_NULL);
}

ROE_S32 UiIpcSendInfraredBrightnessRequest(ROE_S32 msgQueId, UiRequestAdjustInfraredBrightness * infraredBrightness)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_INFRARED_BRIGHTNESS_ADJUST,
                         infraredBrightness,
                         sizeof(UiRequestAdjustInfraredBrightness),
                         ROE_NULL);
}

ROE_S32 UiIpcSendCameraContrastRequest(ROE_S32 msgQueId, UiRequestAdjustCameraContrast * cameraContrast)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_CAMERA_CONTRAST_ADJUST,
                         cameraContrast,
                         sizeof(UiRequestAdjustCameraContrast),
                         ROE_NULL);
}

ROE_S32 UiIpcSendInfraredContrastRequest(ROE_S32 msgQueId, UiRequestAdjustInfraredContrast * infraredContrast)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_INFRARED_CONTRAST_ADJUST,
                         infraredContrast,
                         sizeof(UiRequestAdjustInfraredContrast),
                         ROE_NULL);
}

ROE_S32 UiIpcSendFogSwitchRequest(ROE_S32 msgQueId, UiRequestAdjustFogSwitch * fogSwitch)
{
    return UiIpcSendRequest(
        msgQueId,
        MSG_4_REQ_RES_CAMERA_DEHAZE_SWITCH,
        fogSwitch,
        sizeof(UiRequestAdjustFogSwitch),
        ROE_NULL);
}

ROE_S32 UiIpcSendFogIntensityRequest(ROE_S32 msgQueId, UiRequestAdjustFogIntensity * fogIntensity)
{
    return UiIpcSendRequest(
        msgQueId,
        MSG_4_REQ_RES_CAMERA_DEHAZE_STRENGTH_ADJUST,
        fogIntensity,
        sizeof(UiRequestAdjustFogIntensity),
        ROE_NULL);
}

ROE_S32 UiIpcSendCompassSwitchRequest(ROE_S32 msgQueId, UiRequestAdjustCompassSwitch * compassSwitch)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_COMPASS_SWITCH,
                         compassSwitch,
                         sizeof(UiRequestAdjustCompassSwitch),
                         ROE_NULL);
}

ROE_S32 UiIpcSendStartCompassCalibrationRequest(ROE_S32 msgQueId, UiRequestStartCompassCalibration * compassCalibration)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_COMPASS_START_CALIBRATION,
                         compassCalibration,
                         sizeof(UiRequestStartCompassCalibration),
                         ROE_NULL);
}

ROE_S32 UiIpcSendStopCompassCalibrationRequest(ROE_S32 msgQueId, UiRequestStopCompassCalibration * compassCalibration)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_COMPASS_STOP_CALIBRATION,
                         compassCalibration,
                         sizeof(UiRequestStopCompassCalibration),
                         ROE_NULL);
}

ROE_S32 UiIpcSendSetCompassDeclinationRequest(ROE_S32 msgQueId, UiRequestSetCompassDeclination * setCompassDeclination)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_COMPASS_SET_MAGNETIC_DECLINATION,
                         setCompassDeclination,
                         sizeof(UiRequestSetCompassDeclination),
                         ROE_NULL);
}

ROE_S32 UiIpcSendSaveCompassConfigRequest(ROE_S32 msgQueId)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_COMPASS_SAVE_CONFIG, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 UiIpcSendGnssSwitchRequest(ROE_S32 msgQueId, UiRequestAdjustGnssSwitch * gnssSwitch)
{
    return UiIpcSendRequest(
        msgQueId,
        MSG_4_REQ_RES_GNSS_SWITCH,
        gnssSwitch,
        sizeof(UiRequestAdjustGnssSwitch),
        ROE_NULL);
}

ROE_S32 UiIpcSendGnssSystemRequest(ROE_S32 msgQueId, UiRequestAdjustGnssSystem * gnssSystem)
{
    return UiIpcSendRequest(
        msgQueId,
        MSG_4_REQ_RES_GNSS_POSITION_SYSTEM_SWITCHING,
        gnssSystem,
        sizeof(UiRequestAdjustGnssSystem),
        ROE_NULL);
}

ROE_S32 UiIpcSendCoordinateSystemRequest(ROE_S32 msgQueId, UiRequestAdjustCoordinateSystem * coordinateSystem)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_GNSS_COORDINATE_SYSTEM_SWITCHING,
                         coordinateSystem,
                         sizeof(UiRequestAdjustCoordinateSystem),
                         ROE_NULL);
}

ROE_S32 UiIpcSendRestoreFactoryRequest(ROE_S32 msgQueId)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_RESTORE_FACTORY_SETTING, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 UiIpcSendFormatDiskRequest(ROE_S32 msgQueId)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_FORMAT_DISK_PARTITION, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 UiIpcSendWifiSwitchRequest(ROE_S32 msgQueId, UiRequestAdjustWifiSwitch * wifiSwitch)
{
    return UiIpcSendRequest(
        msgQueId,
        MSG_4_REQ_RES_WIFI_SWITCH,
        wifiSwitch,
        sizeof(UiRequestAdjustWifiSwitch),
        ROE_NULL);
}

ROE_S32 UiIpcSendGetWifiInfoRequest(ROE_S32 msgQueId)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_GET_WIFI_INFO, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 UiIpcSendGetAppVersionRequest(ROE_S32 msgQueId)
{
    return UiIpcSendRequest(msgQueId, MSG_4_REQ_RES_GET_VERSION_INFO, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 UiIpcSendInfraredPseudoColorRequest(ROE_S32 msgQueId, UiRequestAdjustInfraredPseudoColor * infraredPseudoColor)
{
    return UiIpcSendRequest(msgQueId,
                         MSG_4_REQ_RES_INFRARED_PSEUDOCOLOR_MODE_SWITCHING,
                         infraredPseudoColor,
                         sizeof(UiRequestAdjustInfraredPseudoColor),
                         ROE_NULL);
}
