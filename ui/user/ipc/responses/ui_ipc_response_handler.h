//
// Created by jinxing on 2026/3/2.
//

#ifndef ZKSL_75_6LC_UI_IPC_RESPONSE_HANDLER_H
#define ZKSL_75_6LC_UI_IPC_RESPONSE_HANDLER_H

#include "user/core/roeTypes.h"

ROE_S32 UiIpcHandleResponseRegister(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseExitMenu(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseSetSystemTime(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustObserveMode(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustPipObserveMode(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustDayNight(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustRecognitionSwitch(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustCameraBrightness(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustInfraredBrightness(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustCameraContrast(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustInfraredContrast(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustFogSwitch(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustFogIntensity(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustCompassSwitch(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseStartCompassCalibration(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseStopCompassCalibration(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseSetCompassDeclination(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseSaveCompassConfig(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustGnssSwitch(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustGnssSystem(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustCoordinateSystem(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseRestoreFactory(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseFormatDisk(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustWifiSwitch(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseGetWifiInfo(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseGetAppVersion(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustInfraredPseudoColor(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseGetMediaFileList(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseDeleteMediaFile(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponsePlayMediaFile(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponsePlayAdjacentMediaFile(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseStopMediaFilePlay(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseRangeFinderOperate(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustRangeFrequency(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustRangeDuration(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustPipSwitch(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustExtendDisplaySwitch(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustMainDisplayBrightness(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustMainDisplayContrast(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustVideoZoom(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseShutdown(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseExitDialogBox(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseExitPlaybackList(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponsePanTiltMoveControl(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponsePanTiltSpeedControl(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseInfraredSetBadPixelThreshold(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseInfraredBadPixelOperate(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseSaveLanguageConfig(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseInfraredHotPixelRepair(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseInfraredHotspotTrackingSwitch(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseInfraredScenarioMode(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseInfraredEnhanceImage(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustCameraSaturation(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseAdjustCameraHue(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseFreezeVideoInput(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseGetUserCommonConfig(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseSetUserCommonConfig(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseGetUserMediaConfig(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseSetUserMediaConfig(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseSetReticleCommonConfig(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseWeaponMarkConfigOperate(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseWeaponSetReticleStyle(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseWeaponSetReticleColor(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseWeaponSetDefaultShootDistance(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseWeaponOperateShootDistance(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseWeaponSetShootPosition(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseWeaponSetShootZero(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseWeaponSaveConfig(ROE_U8 * msgData);

ROE_S32 UiIpcHandleResponseWeaponSetReticleBrightness(ROE_U8 * msgData);

/* Framework handlers for protocol operations that currently only need
 * protocol-level parsing and result propagation. */
ROE_S32 UiIpcHandleResponseGetVideoOutputParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetVideoInputParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetVideoInputCameraParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetVideoInputLowLightParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetVideoInputInfraredParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetVideoInputRemoteParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseAdjustCameraExposure(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetAudioParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseCaptureMediaFile(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseRecordMediaFile(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetPeripheralUsbParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetPeripheralNetworkParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetPeripheralCameraModuleParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetPeripheralLowLightModuleParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetPeripheralInfraredModuleParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetPeripheralRemoteVideoModuleParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetPeripheralCompassParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetPeripheralGnssParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetPeripheralRangeFinderParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseGetPeripheralPanTiltParameters(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseInfraredManualRemoveBadPixel(ROE_U8 * msgData);
ROE_S32 UiIpcHandleResponseInfraredSdNuc(ROE_U8 * msgData);
#endif // ZKSL_75_6LC_UI_IPC_RESPONSE_HANDLER_H
