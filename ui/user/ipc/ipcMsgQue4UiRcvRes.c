//
// Created by jinxing on 2026/2/11.
//

#include "ipcMsgQue4UiRcvRes.h"
#include "handleRcvRes.h"

typedef ROE_S32 (*FtHandleReqRes_st)(ROE_U8 * msgData);

static FtHandleReqRes_st f_SystemFunction[MSG_4_REQ_RES_SYSTEM_GENERAL_BUTT - MSG_4_REQ_RES_SYSTEM_GENERAL_OFFSET] = {
    handleParseRegisterMsg,
    handleParseShutdownMsg,
    handleParseGetAppVersionMsg,
    handleParseSetSystemTimeMsg,
    handleParseFormatDiskPartitionMsg,
};

static FtHandleReqRes_st f_SystemConfiguration[MSG_4_REQ_RES_SYSTEM_CONFIG_BUTT - MSG_4_REQ_RES_SYSTEM_CONFIG_OFFSET] =
{
    handleParseRestoreFactorySettingMsg,
    handleParseSaveLanguageConfigMsg,
    handleParseGetUserCommonConfigMsg,
    handleParseSetUserCommonConfigMsg,
    handleParseGetUserMediaConfigMsg,
    handleParseSetUserMediaConfigMsg,
};

static FtHandleReqRes_st f_SystemUserInterface[MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_BUTT -
                                               MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_OFFSET] = {
    handleParseExitMenuMsg,
    handleParseExitDialogBoxMsg,
};

static FtHandleReqRes_st f_ShootingDifferentiation[
    MSG_4_REQ_RES_RETICLE_GENERAL_BUTT - MSG_4_REQ_RES_RETICLE_GENERAL_OFFSET] = {
    handleParseSetReticleCommonConfigMsg,
    handleParseWeaponSetReticleStyleMsg,
    handleParseWeaponSetReticleColorMsg,
    NULL,
    handleParseWeaponSaveConfigMsg,
    handleParseWeaponMarkConfigOperateMsg,
    handleParseWeaponSetDefaultShootDistanceMsg,
    handleParseWeaponOperateShootDistanceMsg,
    handleParseWeaponSetShootPositionMsg,
    handleParseWeaponSetShootZeroMsg,
};

static FtHandleReqRes_st f_VideoOutputDisplay[MSG_4_REQ_RES_VIDEO_OUTPUT_BUTT - MSG_4_REQ_RES_VIDEO_OUTPUT_OFFSET] = {
    handleParseAdjustOledBrightnessMsg,
    handleParseAdjustOledContrastMsg,
    handleParseAdjustExtendDisplaySwitchStatusMsg,
    handleParseAdjustPipSwitchStatusMsg,
    handleParseAdjustVideoZoomMsg,
    handleParseFreezeVideoInputMsg,
    handleParseAdjustRecognitionSwitchStatusMsg,
};

static FtHandleReqRes_st f_VideoCaptureInput[MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_BUTT -
                                             MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_OFFSET] = {
    NULL,
    handleParseAdjustObserveModeMsg,
    handleParseAdjustPipObserveModeMsg,
};

static FtHandleReqRes_st f_VisibleLight[MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_BUTT - MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_OFFSET]
    =
    {
        NULL,
        handleParseAdjustDaynightSwitchStatusMsg,
        handleParseAdjustCameraBrightnessMsg,
        handleParseAdjustCameraContrastMsg,
        handleParseAdjustCameraSaturationMsg,
        handleParseAdjustCameraHueMsg,
        handleParseAdjustFogSwitchStatusMsg,
        handleParseAdjustFogIntensityMsg,
        NULL,
    };

static FtHandleReqRes_st f_LowOllumination[MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_BUTT -
                                           MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_OFFSET] = {
    NULL,
};

static FtHandleReqRes_st f_Infrared[MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_BUTT - MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_OFFSET]
    = {
        NULL,
        handleParseAdjustInfraredPseudocolorModeMsg,
        handleParseAdjustInfraredBrightnessMsg,
        handleParseAdjustInfraredContrastMsg,
        handleParseInfraredEnhanceImageMsg,
        handleParseInfraredAdjustScenarioModeMsg,
        handleParseInfraredSwitchHotspotTrackingMsg,
    };

static FtHandleReqRes_st f_RemoteVideo[MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_BUTT - MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_OFFSET]
    = {
        NULL,
    };

static FtHandleReqRes_st f_AudioInputAndOutput[MSG_4_REQ_RES_AUDIO_BUTT - MSG_4_REQ_RES_AUDIO_GENERAL_OFFSET] = {
    NULL,
};

static FtHandleReqRes_st f_MediaFile[MSG_4_REQ_RES_MEDIA_FILE_BUTT - MSG_4_REQ_RES_MEDIA_FILE_OFFSET] = {
    NULL,
    NULL,
    handleParseGetMediaFileListMsg,
    handleParseExitPlaybackMediaListMsg,
    handleParseDelMediaFileMsg,
    handleParsePlayMediaFileMsg,
    handleParsePlayPriorOrNextMediaFileMsg,
    handleParseExitMediaPlayStatusMsg,
};

static FtHandleReqRes_st F_usb[MSG_4_REQ_RES_PERIPHERAL_USB_BUTT - MSG_4_REQ_RES_PERIPHERAL_USB_OFFSET] = {
    NULL,
};

static FtHandleReqRes_st f_Network[MSG_4_REQ_RES_PERIPHERAL_NETWORK_BUTT - MSG_4_REQ_RES_PERIPHERAL_NETWORK_OFFSET] = {
    NULL,
    handleParseAdjustWifiSwitchMsg,
    handleParseGetWifiInfoMsg,
};

static FtHandleReqRes_st f_VisibleLightModule[MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_BUTT -
                                              MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_OFFSET] = {
    NULL,
};

static FtHandleReqRes_st f_LowLightModule[MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_BUTT -
                                          MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_OFFSET] = {
    NULL,
};

static FtHandleReqRes_st f_InfraredModule[MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_BUTT -
                                          MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_OFFSET] = {
    NULL,
    NULL,
    handleParseInfraredSetBadPixelThresholdMsg,
    handleParseInfraredBadPixelOperateMsg,
    handleParseInfraredHotPixelRepairOperateMsg,
    NULL,
};

static FtHandleReqRes_st f_RomoteVideoEquipment[MSG_4_REQ_RES_PERIPHERAL_REMOTE_VIDEO_MODULE_BUTT -
                                                MSG_4_REQ_RES_PERIPHERAL_REMOTED_VIDEO_MODULE_OFFSET] = {
    NULL,
};

static FtHandleReqRes_st f_ElectronicCompass[MSG_4_REQ_RES_PERIPHERAL_COMPASS_BUTT -
                                             MSG_4_REQ_RES_PERIPHERAL_COMPASS_OFFSET] = {
    NULL,
    handleParseAdjustCompassSwitchStatusMsg,
    handleParseSetCompassMagneticDeclinationMsg,
    handleParseSaveCompassConfigMsg,
    handleParseStartCompassCalibrationMsg,
    handleParseStopCompassCalibrationMsg,
};

static FtHandleReqRes_st f_SatellitePositioning[MSG_4_REQ_RES_PERIPHERAL_GNSS_BUTT -
                                                MSG_4_REQ_RES_PERIPHERAL_GNSS_OFFSET] = {
    NULL,
    handleParseAdjustGnssSwitchStatusMsg,
    handleParseAdjustGnssPositionSystemMsg,
    handleParseAdjustCoordinateSystemMsg,
};

static FtHandleReqRes_st f_RangeFinder[MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_BUTT -
                                       MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_OFFSET] = {
    NULL,
    handleParseAdjustRangeFinderSwitchStatusMsg,
    handleParseAdjustRangeFrequencyMsg,
    handleParseAdjustRangeTimeDurationMsg,
};

static FtHandleReqRes_st f_Holder[MSG_4_REQ_RES_PERIPHERAL_PANTILT_BUTT - MSG_4_REQ_RES_PERIPHERAL_PANTILT_OFFSET] = {
    NULL,
    handleParsePanTiltMovingControlMsg,
    handleParsePanTiltMovingSpeedControlMsg,
};

ROE_S32 ParseResMsg(ROE_SL msgType, RoeIpcMsgQueRawData_st * rawData)
{
    ROE_U8 * msgData = rawData->data;

    if(msgType >= MSG_4_REQ_RES_SYSTEM_GENERAL_OFFSET && msgType < MSG_4_REQ_RES_SYSTEM_GENERAL_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_SYSTEM_GENERAL_OFFSET;
        if(f_SystemFunction[idx] != NULL) {
            return f_SystemFunction[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_SYSTEM_CONFIG_OFFSET && msgType < MSG_4_REQ_RES_SYSTEM_CONFIG_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_SYSTEM_CONFIG_OFFSET;
        if(f_SystemConfiguration[idx] != NULL) {
            return f_SystemConfiguration[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_OFFSET && msgType < MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_SYSTEM_USER_INTERFACE_OFFSET;
        if(f_SystemUserInterface[idx] != NULL) {
            return f_SystemUserInterface[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_VIDEO_OUTPUT_OFFSET && msgType < MSG_4_REQ_RES_VIDEO_OUTPUT_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_VIDEO_OUTPUT_OFFSET;
        if(f_VideoOutputDisplay[idx] != NULL) {
            return f_VideoOutputDisplay[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_OFFSET && msgType < MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_VIDEO_INPUT_GENERAL_OFFSET;
        if(f_VideoCaptureInput[idx] != NULL) {
            return f_VideoCaptureInput[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_OFFSET && msgType < MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_VIDEO_INPUT_CAMERA_OFFSET;
        if(f_VisibleLight[idx] != NULL) {
            return f_VisibleLight[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_OFFSET && msgType < MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_VIDEO_INPUT_LOW_LIGHT_OFFSET;
        if(f_LowOllumination[idx] != NULL) {
            return f_LowOllumination[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_OFFSET && msgType < MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_VIDEO_INPUT_INFRARED_OFFSET;
        if(f_Infrared[idx] != NULL) {
            return f_Infrared[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_OFFSET && msgType < MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_VIDEO_INPUT_REMOTE_OFFSET;
        if(f_RemoteVideo[idx] != NULL) {
            return f_RemoteVideo[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_AUDIO_GENERAL_OFFSET && msgType < MSG_4_REQ_RES_AUDIO_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_AUDIO_GENERAL_OFFSET;
        if(f_AudioInputAndOutput[idx] != NULL) {
            return f_AudioInputAndOutput[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_MEDIA_FILE_OFFSET && msgType < MSG_4_REQ_RES_MEDIA_FILE_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_MEDIA_FILE_OFFSET;
        if(f_MediaFile[idx] != NULL) {
            return f_MediaFile[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_PERIPHERAL_USB_OFFSET && msgType < MSG_4_REQ_RES_PERIPHERAL_USB_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_PERIPHERAL_USB_OFFSET;
        if(F_usb[idx] != NULL) {
            return F_usb[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_PERIPHERAL_NETWORK_OFFSET && msgType < MSG_4_REQ_RES_PERIPHERAL_NETWORK_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_PERIPHERAL_NETWORK_OFFSET;
        if(f_Network[idx] != NULL) {
            return f_Network[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_OFFSET && msgType <
       MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_PERIPHERAL_CAMERA_MODULE_OFFSET;
        if(f_VisibleLightModule[idx] != NULL) {
            return f_VisibleLightModule[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_OFFSET && msgType <
       MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_PERIPHERAL_LOW_LIGHT_MODULE_OFFSET;
        if(f_LowLightModule[idx] != NULL) {
            return f_LowLightModule[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_OFFSET && msgType <
       MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_PERIPHERAL_INFRARED_MODULE_OFFSET;
        if(f_InfraredModule[idx] != NULL) {
            return f_InfraredModule[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_PERIPHERAL_REMOTED_VIDEO_MODULE_OFFSET && msgType <
       MSG_4_REQ_RES_PERIPHERAL_REMOTE_VIDEO_MODULE_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_PERIPHERAL_REMOTED_VIDEO_MODULE_OFFSET;
        if(f_RomoteVideoEquipment[idx] != NULL) {
            return f_RomoteVideoEquipment[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_PERIPHERAL_COMPASS_OFFSET && msgType < MSG_4_REQ_RES_PERIPHERAL_COMPASS_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_PERIPHERAL_COMPASS_OFFSET;
        if(f_ElectronicCompass[idx] != NULL) {
            return f_ElectronicCompass[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_PERIPHERAL_GNSS_OFFSET && msgType < MSG_4_REQ_RES_PERIPHERAL_GNSS_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_PERIPHERAL_GNSS_OFFSET;
        if(f_SatellitePositioning[idx] != NULL) {
            return f_SatellitePositioning[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_OFFSET && msgType <
       MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_BUTT) {
        ROE_U32 idx = msgType - MSG_4_REQ_RES_PERIPHERAL_RANGE_FINDER_OFFSET;
        if(f_RangeFinder[idx] != NULL) {
            return f_RangeFinder[idx](msgData);
        }
    }

    if(msgType >= MSG_4_REQ_RES_PERIPHERAL_PANTILT_OFFSET && msgType < MSG_4_REQ_RES_PERIPHERAL_PANTILT_BUTT) {
        if(f_Holder[msgType - MSG_4_REQ_RES_PERIPHERAL_PANTILT_OFFSET] != NULL) {
            return f_Holder[msgType - MSG_4_REQ_RES_PERIPHERAL_PANTILT_OFFSET](msgData);
        }
    }
    return ROE_FAILURE;
}