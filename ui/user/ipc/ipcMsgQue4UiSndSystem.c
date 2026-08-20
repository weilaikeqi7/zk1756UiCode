//
// Created by jinxing on 2026/2/11.
//

#include "ipcMsgQue4UiSndRequest.h"
#include "ipcMsgQue4UiSndInternal.h"

ROE_S32 SendMsg4UiRegisterReq(ROE_S32 msgQueId, ReqRegister_st * registerType)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_LOG_IN_OUT, registerType, sizeof(ReqRegister_st), ROE_NULL);
}

ROE_S32 SendMsg4UiExitMenuReq(ROE_S32 msgQueId)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_EXIT_MENU_MODE, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 SendMsg4UiTimeReq(ROE_S32 msgQueId, ReqSetSystemTime_st * setTime)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_SET_SYSTEM_TIME, setTime, sizeof(ReqSetSystemTime_st), ROE_NULL);
}

ROE_S32 SendMsg4UiObserveModeReq(ROE_S32 msgQueId, ReqAdjustObserveMode_st * setObserveMode)
{
    return SendMsg4UiReq(
        msgQueId,
        MSG_4_REQ_RES_OBSERVE_MODE_SWITCHING,
        setObserveMode,
        sizeof(ReqAdjustObserveMode_st),
        ROE_NULL);
}

ROE_S32 SendMsg4UiDayNightReq(ROE_S32 msgQueId, ReqAdjustDayNight_st * setDayNight)
{
    return SendMsg4UiReq(
        msgQueId,
        MSG_4_REQ_RES_CAMERA_DAYNIGHT_MODE_SWITCHING,
        setDayNight,
        sizeof(ReqAdjustDayNight_st),
        ROE_NULL);
}

ROE_S32 SendMsg4UiRecognitionSwitchReq(ROE_S32 msgQueId, ReqAdjustRecognitionSwitch_st * setRecognitionSwitch)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_OBJECT_RECOGNITION_SWITCH,
                         setRecognitionSwitch,
                         sizeof(ReqAdjustRecognitionSwitch_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiCameraBrightnessReq(ROE_S32 msgQueId, ReqAdjustCameraBrightness_st * cameraBrightness)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_CAMERA_BRIGHTNESS_ADJUST,
                         cameraBrightness,
                         sizeof(ReqAdjustCameraBrightness_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiInfraredBrightnessReq(ROE_S32 msgQueId, ReqAdjustInfraredBrightness_st * infraredBrightness)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_INFRARED_BRIGHTNESS_ADJUST,
                         infraredBrightness,
                         sizeof(ReqAdjustInfraredBrightness_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiCameraContrastReq(ROE_S32 msgQueId, ReqAdjustCameraContrast_st * cameraContrast)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_CAMERA_CONTRAST_ADJUST,
                         cameraContrast,
                         sizeof(ReqAdjustCameraContrast_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiInfraredContrastReq(ROE_S32 msgQueId, ReqAdjustInfraredContrast_st * infraredContrast)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_INFRARED_CONTRAST_ADJUST,
                         infraredContrast,
                         sizeof(ReqAdjustInfraredContrast_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiFogSwitchReq(ROE_S32 msgQueId, ReqAdjustFogSwitch_st * fogSwitch)
{
    return SendMsg4UiReq(
        msgQueId,
        MSG_4_REQ_RES_CAMERA_DEHAZE_SWITCH,
        fogSwitch,
        sizeof(ReqAdjustFogSwitch_st),
        ROE_NULL);
}

ROE_S32 SendMsg4UiFogIntensityReq(ROE_S32 msgQueId, ReqAdjustFogIntensity_st * fogIntensity)
{
    return SendMsg4UiReq(
        msgQueId,
        MSG_4_REQ_RES_CAMERA_DEHAZE_STRENGTH_ADJUST,
        fogIntensity,
        sizeof(ReqAdjustFogIntensity_st),
        ROE_NULL);
}

ROE_S32 SendMsg4UiCompassSwitchReq(ROE_S32 msgQueId, ReqAdjustCompassSwitch_st * compassSwitch)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_COMPASS_SWITCH,
                         compassSwitch,
                         sizeof(ReqAdjustCompassSwitch_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiStartCompassCalibrationReq(ROE_S32 msgQueId, ReqStartCompassCalibration_st * compassCalibration)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_COMPASS_START_CALIBRATION,
                         compassCalibration,
                         sizeof(ReqStartCompassCalibration_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiStopCompassCalibrationReq(ROE_S32 msgQueId, ReqStopCompassCalibration_st * compassCalibration)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_COMPASS_STOP_CALIBRATION,
                         compassCalibration,
                         sizeof(ReqStopCompassCalibration_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiSetCompassDeclinationReq(ROE_S32 msgQueId, ReqSetCompassDeclination_st * setCompassDeclination)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_COMPASS_SET_MAGNETIC_DECLINATION,
                         setCompassDeclination,
                         sizeof(ReqSetCompassDeclination_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiSaveCompassConfigReq(ROE_S32 msgQueId)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_COMPASS_SAVE_CONFIG, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 SendMsg4UiGnssSwitchReq(ROE_S32 msgQueId, ReqAdjustGnssSwitch_st * gnssSwitch)
{
    return SendMsg4UiReq(
        msgQueId,
        MSG_4_REQ_RES_GNSS_SWITCH,
        gnssSwitch,
        sizeof(ReqAdjustGnssSwitch_st),
        ROE_NULL);
}

ROE_S32 SendMsg4UiGnssSystemReq(ROE_S32 msgQueId, ReqAdjustGnssSystem_st * gnssSystem)
{
    return SendMsg4UiReq(
        msgQueId,
        MSG_4_REQ_RES_GNSS_POSITION_SYSTEM_SWITCHING,
        gnssSystem,
        sizeof(ReqAdjustGnssSystem_st),
        ROE_NULL);
}

ROE_S32 SendMsg4UiCoordinateSystemReq(ROE_S32 msgQueId, ReqAdjustCoordinateSystem_st * coordinateSystem)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_GNSS_COORDINATE_SYSTEM_SWITCHING,
                         coordinateSystem,
                         sizeof(ReqAdjustCoordinateSystem_st),
                         ROE_NULL);
}

ROE_S32 SendMsg4UiRestoreFactoryReq(ROE_S32 msgQueId)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_RESTORE_FACTORY_SETTING, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 SendMsg4UiFormatDiskReq(ROE_S32 msgQueId)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_FORMAT_DISK_PARTITION, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 SendMsg4UiWifiSwitchReq(ROE_S32 msgQueId, ReqAdjustWifiSwitch_st * wifiSwitch)
{
    return SendMsg4UiReq(
        msgQueId,
        MSG_4_REQ_RES_WIFI_SWITCH,
        wifiSwitch,
        sizeof(ReqAdjustWifiSwitch_st),
        ROE_NULL);
}

ROE_S32 SendMsg4UiGetWifiInfoReq(ROE_S32 msgQueId)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_GET_WIFI_INFO, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 SendMsg4UiGetAppVersionReq(ROE_S32 msgQueId)
{
    return SendMsg4UiReq(msgQueId, MSG_4_REQ_RES_GET_VERSION_INFO, ROE_NULL, 0, ROE_NULL);
}

ROE_S32 SendMsg4UiInfraredPseudoColorReq(ROE_S32 msgQueId, ReqAdjustInfraredPseudoColor_st * infraredPseudoColor)
{
    return SendMsg4UiReq(msgQueId,
                         MSG_4_REQ_RES_INFRARED_PSEUDOCOLOR_MODE_SWITCHING,
                         infraredPseudoColor,
                         sizeof(ReqAdjustInfraredPseudoColor_st),
                         ROE_NULL);
}