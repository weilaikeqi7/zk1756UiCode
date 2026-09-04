//
// Created by jinxing on 2026/3/2.
//

#ifndef ZKSL_75_6LC_HANDLERCVRES_H
#define ZKSL_75_6LC_HANDLERCVRES_H

#include "user/core/roeTypes.h"
#include "user/ipc/msg.h"
#include "user/ipc/ipcMsgQue4UiTypeCommon.h"

ROE_S32 handleParseRegisterMsg(ROE_U8 * msgData);

ROE_S32 handleParseExitMenuMsg(ROE_U8 * msgData);

ROE_S32 handleParseSetSystemTimeMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustObserveModeMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustPipObserveModeMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustDaynightSwitchStatusMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustRecognitionSwitchStatusMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustCameraBrightnessMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustInfraredBrightnessMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustCameraContrastMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustInfraredContrastMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustFogSwitchStatusMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustFogIntensityMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustCompassSwitchStatusMsg(ROE_U8 * msgData);

ROE_S32 handleParseStartCompassCalibrationMsg(ROE_U8 * msgData);

ROE_S32 handleParseStopCompassCalibrationMsg(ROE_U8 * msgData);

ROE_S32 handleParseSetCompassMagneticDeclinationMsg(ROE_U8 * msgData);

ROE_S32 handleParseSaveCompassConfigMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustGnssSwitchStatusMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustGnssPositionSystemMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustCoordinateSystemMsg(ROE_U8 * msgData);

ROE_S32 handleParseRestoreFactorySettingMsg(ROE_U8 * msgData);

ROE_S32 handleParseFormatDiskPartitionMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustWifiSwitchMsg(ROE_U8 * msgData);

ROE_S32 handleParseGetWifiInfoMsg(ROE_U8 * msgData);

ROE_S32 handleParseGetAppVersionMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustInfraredPseudocolorModeMsg(ROE_U8 * msgData);

ROE_S32 handleParseGetMediaFileListMsg(ROE_U8 * msgData);

ROE_S32 handleParseGetMediaFileListPageMsg(ROE_U8 * msgData);

ROE_S32 handleParseDelMediaFileMsg(ROE_U8 * msgData);

ROE_S32 handleParsePlayMediaFileMsg(ROE_U8 * msgData);

ROE_S32 handleParsePlayPriorOrNextMediaFileMsg(ROE_U8 * msgData);

ROE_S32 handleParseExitMediaPlayStatusMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustRangeFinderSwitchStatusMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustRangeFrequencyMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustRangeTimeDurationMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustPipSwitchStatusMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustExtendDisplaySwitchStatusMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustOledBrightnessMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustOledContrastMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustVideoZoomMsg(ROE_U8 * msgData);

ROE_S32 handleParseShutdownMsg(ROE_U8 * msgData);

ROE_S32 handleParseExitDialogBoxMsg(ROE_U8 * msgData);

ROE_S32 handleParseExitPlaybackMediaListMsg(ROE_U8 * msgData);

ROE_S32 handleParsePanTiltMovingControlMsg(ROE_U8 * msgData);

ROE_S32 handleParsePanTiltMovingSpeedControlMsg(ROE_U8 * msgData);

ROE_S32 handleParseInfraredSetBadPixelThresholdMsg(ROE_U8 * msgData);

ROE_S32 handleParseInfraredBadPixelOperateMsg(ROE_U8 * msgData);

ROE_S32 handleParseSaveLanguageConfigMsg(ROE_U8 * msgData);

ROE_S32 handleParseInfraredHotPixelRepairOperateMsg(ROE_U8 * msgData);

ROE_S32 handleParseInfraredSwitchHotspotTrackingMsg(ROE_U8 * msgData);

ROE_S32 handleParseInfraredAdjustScenarioModeMsg(ROE_U8 * msgData);

ROE_S32 handleParseInfraredEnhanceImageMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustCameraSaturationMsg(ROE_U8 * msgData);

ROE_S32 handleParseAdjustCameraHueMsg(ROE_U8 * msgData);

ROE_S32 handleParseFreezeVideoInputMsg(ROE_U8 * msgData);

ROE_S32 handleParseGetUserCommonConfigMsg(ROE_U8 * msgData);

ROE_S32 handleParseSetUserCommonConfigMsg(ROE_U8 * msgData);

ROE_S32 handleParseGetUserMediaConfigMsg(ROE_U8 * msgData);

ROE_S32 handleParseSetUserMediaConfigMsg(ROE_U8 * msgData);

ROE_S32 handleParseSetReticleCommonConfigMsg(ROE_U8 * msgData);

ROE_S32 handleParseWeaponMarkConfigOperateMsg(ROE_U8 * msgData);

ROE_S32 handleParseWeaponSetReticleStyleMsg(ROE_U8 * msgData);

ROE_S32 handleParseWeaponSetReticleColorMsg(ROE_U8 * msgData);

ROE_S32 handleParseWeaponSetDefaultShootDistanceMsg(ROE_U8 * msgData);

ROE_S32 handleParseWeaponOperateShootDistanceMsg(ROE_U8 * msgData);

ROE_S32 handleParseWeaponSetShootPositionMsg(ROE_U8 * msgData);

ROE_S32 handleParseWeaponSetShootZeroMsg(ROE_U8 * msgData);

ROE_S32 handleParseWeaponSaveConfigMsg(ROE_U8 * msgData);

ROE_S32 handleParseWeaponBrightnessAdjustMsg(ROE_U8 * msgData);

/* Framework handlers for protocol operations that currently only need
 * protocol-level parsing and result propagation. */
ROE_S32 handleParseGetVideoOutputParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetVideoInputParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetVideoInputCameraParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetVideoInputLowLightParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetVideoInputInfraredParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetVideoInputRemoteParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseAdjustCameraExposureMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetAudioParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseCaptureMediaFileMsg(ROE_U8 * msgData);
ROE_S32 handleParseRecordMediaFileMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetPeripheralUsbParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetPeripheralNetworkParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetPeripheralCameraModuleParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetPeripheralLowLightModuleParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetPeripheralInfraredModuleParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetPeripheralRemotedVideoModuleParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetPeripheralCompassParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetPeripheralGnssParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetPeripheralRangeFinderParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseGetPeripheralPanTiltParaMsg(ROE_U8 * msgData);
ROE_S32 handleParseInfraredManualRemoveBadPixelMsg(ROE_U8 * msgData);
ROE_S32 handleParseInfraredSdNucMsg(ROE_U8 * msgData);
#endif //ZKSL_75_6LC_HANDLERCVRES_H
