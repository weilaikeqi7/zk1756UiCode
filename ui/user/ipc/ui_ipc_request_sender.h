#ifndef ZKSL_75_6LC_UI_IPC_REQUEST_SENDER_H
#define ZKSL_75_6LC_UI_IPC_REQUEST_SENDER_H

#include "ui_ipc_request_types.h"

ROE_S32 UiIpcSendRegisterRequest(ROE_S32 msgQueId, UiRequestRegister * registerType);

ROE_S32 UiIpcSendExitMenuRequest(ROE_S32 msgQueId);

ROE_S32 UiIpcSendTimeRequest(ROE_S32 msgQueId, UiRequestSetSystemTime * setTime);

ROE_S32 UiIpcSendObserveModeRequest(ROE_S32 msgQueId, UiRequestSwitchMainObserveMode * request);

ROE_S32 UiIpcSendPipObserveModeRequest(ROE_S32 msgQueId, UiRequestSwitchPipObserveMode * request);

ROE_S32 UiIpcSendDayNightRequest(ROE_S32 msgQueId, UiRequestAdjustDayNight * setDayNight);

ROE_S32 UiIpcSendRecognitionSwitchRequest(ROE_S32 msgQueId, UiRequestAdjustRecognitionSwitch * setRecognitionSwitch);

ROE_S32 UiIpcSendCameraBrightnessRequest(ROE_S32 msgQueId, UiRequestAdjustCameraBrightness * cameraBrightness);

ROE_S32 UiIpcSendInfraredBrightnessRequest(ROE_S32 msgQueId, UiRequestAdjustInfraredBrightness * infraredBrightness);

ROE_S32 UiIpcSendCameraContrastRequest(ROE_S32 msgQueId, UiRequestAdjustCameraContrast * cameraContrast);

ROE_S32 UiIpcSendInfraredContrastRequest(ROE_S32 msgQueId, UiRequestAdjustInfraredContrast * infraredContrast);

ROE_S32 UiIpcSendFogSwitchRequest(ROE_S32 msgQueId, UiRequestAdjustFogSwitch * fogSwitch);

ROE_S32 UiIpcSendFogIntensityRequest(ROE_S32 msgQueId, UiRequestAdjustFogIntensity * fogIntensity);

ROE_S32 UiIpcSendCompassSwitchRequest(ROE_S32 msgQueId, UiRequestAdjustCompassSwitch * compassSwitch);

ROE_S32 UiIpcSendStartCompassCalibrationRequest(ROE_S32 msgQueId, UiRequestStartCompassCalibration * compassCalibration);

ROE_S32 UiIpcSendStopCompassCalibrationRequest(ROE_S32 msgQueId, UiRequestStopCompassCalibration * compassCalibration);

ROE_S32 UiIpcSendSetCompassDeclinationRequest(ROE_S32 msgQueId, UiRequestSetCompassDeclination * setCompassDeclination);

ROE_S32 UiIpcSendSaveCompassConfigRequest(ROE_S32 msgQueId);

ROE_S32 UiIpcSendGnssSwitchRequest(ROE_S32 msgQueId, UiRequestAdjustGnssSwitch * gnssSwitch);

ROE_S32 UiIpcSendGnssSystemRequest(ROE_S32 msgQueId, UiRequestAdjustGnssSystem * gnssSystem);

ROE_S32 UiIpcSendCoordinateSystemRequest(ROE_S32 msgQueId, UiRequestAdjustCoordinateSystem * coordinateSystem);

ROE_S32 UiIpcSendRestoreFactoryRequest(ROE_S32 msgQueId);

ROE_S32 UiIpcSendFormatDiskRequest(ROE_S32 msgQueId);

ROE_S32 UiIpcSendWifiSwitchRequest(ROE_S32 msgQueId, UiRequestAdjustWifiSwitch * wifiSwitch);

ROE_S32 UiIpcSendGetWifiInfoRequest(ROE_S32 msgQueId);

ROE_S32 UiIpcSendGetAppVersionRequest(ROE_S32 msgQueId);

ROE_S32 UiIpcSendInfraredPseudoColorRequest(ROE_S32 msgQueId, UiRequestAdjustInfraredPseudoColor * infraredPseudoColor);

ROE_S32 UiIpcSendGetMediaFileListRequest(ROE_S32 msgQueId, UiRequestGetMediaFileList * getMediaFileList);

ROE_S32 UiIpcSendDeleteMediaFileRequest(ROE_S32 msgQueId, ROE_S8 * filename);

ROE_S32 UiIpcSendPlayMediaFileRequest(ROE_S32 msgQueId, ROE_S8 * filename);

ROE_S32 UiIpcSendPlayAdjacentMediaFileRequest(ROE_S32 msgQueId, ROE_U8 direction);

ROE_S32 UiIpcSendStopMediaFilePlayRequest(ROE_S32 msgQueId);

ROE_S32 UiIpcSendRangeFinderOperateRequest(ROE_S32 msgQueId, UiRequestRangeFinderOperate * rangeFinderOperation);

ROE_S32 UiIpcSendRangeFrequencyRequest(ROE_S32 msgQueId, UiRequestAdjustRangeFrequency * rangeFrequency);

ROE_S32 UiIpcSendAdjustRangeDurationRequest(ROE_S32 msgQueId, UiRequestAdjustRangeDuration * rangeDuration);

ROE_S32 UiIpcSendPipSwitchRequest(ROE_S32 msgQueId, UiRequestAdjustPipSwitch * pipSwitch);

ROE_S32 UiIpcSendExtendDisplaySwitchRequest(ROE_S32 msgQueId, UiRequestAdjustExtendDisplaySwitch * extendDisplaySwitch);

ROE_S32 UiIpcSendMainDisplayBrightnessRequest(ROE_S32 msgQueId, UiRequestAdjustMainDisplayBrightness * mainDisplayBrightness);

ROE_S32 UiIpcSendMainDisplayContrastRequest(ROE_S32 msgQueId, UiRequestAdjustMainDisplayContrast * mainDisplayContrast);

ROE_S32 UiIpcSendVideoZoomRequest(ROE_S32 msgQueId, UiRequestAdjustVideoZoom * adjustVideoZoom);

ROE_S32 UiIpcSendShutdownRequest(ROE_S32 msgQueId);

ROE_S32 UiIpcSendExitDialogBoxRequest(ROE_S32 msgQueId);

ROE_S32 UiIpcSendExitPlaybackListRequest(ROE_S32 msgQueId);

ROE_S32 UiIpcSendPanTiltMoveControlRequest(ROE_S32 msgQueId, UiRequestPanTiltMoveControl * panTiltMoveControl);

ROE_S32 UiIpcSendPanTiltSpeedControlRequest(ROE_S32 msgQueId, UiRequestPanTiltSpeedControl * panTiltSpeedControl);

ROE_S32 UiIpcSendInfraredSetBadPixelThresholdRequest(ROE_S32 msgQueId,
                                                  UiRequestInfraredSetBadPixelThreshold * infraredSetBadPixelThreshold);

ROE_S32 UiIpcSendInfraredBadPixelOperateRequest(ROE_S32 msgQueId, UiRequestInfraredBadPixelOperate * infraredBadPixelOperate);

ROE_S32 UiIpcSendSaveLanguageConfigRequest(ROE_S32 msgQueId, UiRequestSaveLanguageConfig * saveLanguageConfig);

ROE_S32 UiIpcSendInfraredHotPixelRepairRequest(ROE_S32 msgQueId, UiRequestInfraredHotPixelRepair * infraredHotPixelRepair);

ROE_S32 UiIpcSendInfraredHotspotTrackingSwitchRequest(ROE_S32 msgQueId,
                                                   UiRequestInfraredHotspotTrackingSwitch * infraredHotspotTrackingSwitch);

ROE_S32 UiIpcSendInfraredScenarioModeRequest(ROE_S32 msgQueId, UiRequestInfraredScenarioMode * infraredScenarioMode);

ROE_S32 UiIpcSendInfraredEnhanceImageRequest(ROE_S32 msgQueId, UiRequestInfraredEnhanceImage * infraredEnhanceImage);

ROE_S32 UiIpcSendCameraSaturationRequest(ROE_S32 msgQueId, UiRequestAdjustCameraSaturation * cameraSaturation);

ROE_S32 UiIpcSendCameraHueRequest(ROE_S32 msgQueId, UiRequestAdjustCameraHue * cameraHue);

ROE_S32 UiIpcSendFreezeVideoInputRequest(ROE_S32 msgQueId, UiRequestFreezeVideoInput * freezeVideoInput);

ROE_S32 UiIpcSendGetUserCommonConfigRequest(ROE_S32 msgQueId);

ROE_S32 UiIpcSendSetUserCommonConfigRequest(ROE_S32 msgQueId, UiRequestSetUserCommonConfig * setUserCommonConfig);

ROE_S32 UiIpcSendGetUserMediaConfigRequest(ROE_S32 msgQueId);

ROE_S32 UiIpcSendSetUserMediaConfigRequest(ROE_S32 msgQueId, UiRequestSetUserMediaConfig * setUserMediaConfig);

ROE_S32 UiIpcSendSetReticleCommonConfigRequest(ROE_S32 msgQueId, UiRequestSetReticleCommonConfig * setReticleCommonConfig);

ROE_S32 UiIpcSendWeaponMarkConfigOperateRequest(ROE_S32 msgQueId, UiRequestWeaponMarkConfigOperate * weaponMarkConfigOperate);

ROE_S32 UiIpcSendWeaponSetReticleStyleRequest(ROE_S32 msgQueId, UiRequestWeaponSetReticleStyle * weaponSetReticleStyle);

ROE_S32 UiIpcSendWeaponSetReticleColorRequest(ROE_S32 msgQueId, UiRequestWeaponSetReticleColor * weaponSetReticleColor);

ROE_S32 UiIpcSendWeaponSetDefaultShootDistanceRequest(ROE_S32 msgQueId,
                                              UiRequestWeaponSetDefaultShootDistance * weaponSetDefaultShootDistance);

ROE_S32 UiIpcSendWeaponSetReticleBrightnessRequest(ROE_S32 msgQueId,
                                                   UiRequestWeaponSetReticleBrightness * weaponSetBrightness);

ROE_S32 UiIpcSendWeaponOperateShootDistanceRequest(ROE_S32 msgQueId, UiRequestWeaponOperateShootDistance * weaponSetShootDistance);

ROE_S32 UiIpcSendWeaponSetShootPositionRequest(ROE_S32 msgQueId, UiRequestWeaponSetShootPosition * weaponSetShootPosition);

ROE_S32 UiIpcSendWeaponSetShootZeroRequest(ROE_S32 msgQueId, UiRequestWeaponSetShootZero * weaponSetShootZero);

ROE_S32 UiIpcSendWeaponSaveConfigRequest(ROE_S32 msgQueId);

ROE_S32 UiIpcSendGetVideoOutputParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendGetVideoInputParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendGetVideoInputCameraParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendGetVideoInputLowLightParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendGetVideoInputInfraredParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendGetVideoInputRemoteParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendCameraExposureRequest(ROE_S32 msgQueId, UiRequestAdjustCameraExposure * cameraExposure);
ROE_S32 UiIpcSendGetAudioParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendCaptureMediaFileRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendRecordMediaFileRequest(ROE_S32 msgQueId, UiRequestRecordMediaFile * recordMediaFile);
ROE_S32 UiIpcSendGetPeripheralUsbParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendGetPeripheralNetworkParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendGetPeripheralCameraModuleParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendGetPeripheralLowLightModuleParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendGetPeripheralInfraredModuleParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendGetPeripheralRemoteVideoModuleParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendGetPeripheralCompassParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendGetPeripheralGnssParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendGetPeripheralRangeFinderParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendGetPeripheralPanTiltParametersRequest(ROE_S32 msgQueId);
ROE_S32 UiIpcSendInfraredManualRemoveBadPixelRequest(
    ROE_S32 msgQueId,
    UiRequestInfraredManualRemoveBadPixel * manualRemoveBadPixel);
ROE_S32 UiIpcSendInfraredSdNucRequest(ROE_S32 msgQueId, UiRequestInfraredSdNuc * infraredSdNuc);

#endif // ZKSL_75_6LC_UI_IPC_REQUEST_SENDER_H
