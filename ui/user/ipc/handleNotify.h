//
// Created by jinxing on 2026/3/2.
//

#ifndef ZKSL_75_6LC_HANDLENOTIFY_H
#define ZKSL_75_6LC_HANDLENOTIFY_H

#include "user/core/roeTypes.h"
#include "user/ipc/msg.h"
#include "user/ipc/ipcMsgQue4UiTypeCommon.h"

#define YARDS_PER_METER 1.09361f
#define METERS_PER_YARD 0.9144f

float meterToYard(float meters);

float yardToMeter(float yards);

ROE_S32 handleMagneticDeclinationNotify(ROE_U8 * msgData);

ROE_S32 handleObserveModeNotify(ROE_U8 * msgData);

ROE_S32 handlePeripheralSelfTest(ROE_U8 * msgData);

ROE_S32 handleCompassData(ROE_U8 * msgData);

ROE_S32 handleGpsData(ROE_U8 * msgData);

ROE_S32 handleRangeData(ROE_U8 * msgData);

ROE_S32 handleSdVccVolNotify(ROE_U8 * msgData);

ROE_S32 handleRangeCountdownNotify(ROE_U8 * msgData);

ROE_S32 handleSnapStatusNotify(ROE_U8 * msgData);

ROE_S32 handleRecordStatusNotify(ROE_U8 * msgData);

ROE_S32 handleZoomInfoNotify(ROE_U8 * msgData);

ROE_S32 handleCompassCalibrationNotify(ROE_U8 * msgData);

ROE_S32 handleDialogBoxNotify(ROE_U8 * msgData);

ROE_S32 handleMenuNotify(ROE_U8 * msgData);

ROE_S32 handleKeyEventNotify(ROE_U8 * msgData);

ROE_S32 handleRangeFinderStatusNotify(ROE_U8 * msgData);

ROE_S32 handleResourcePathNotify(ROE_U8 * msgData);

ROE_S32 handleReticleOverallInfoNotify(ROE_U8 * msgData);

ROE_S32 handlePanTiltHorizontalAngleNotify(ROE_U8 * msgData);

ROE_S32 handlePanTiltVerticalAngleNotify(ROE_U8 * msgData);

ROE_S32 handlePanTiltHorizontalRunningStatusNotify(ROE_U8 * msgData);

ROE_S32 handlePanTiltVerticalRunningStatusNotify(ROE_U8 * msgData);

ROE_S32 handlePeripheralsAbilityNotify(ROE_U8 * msgData);

ROE_S32 handleInfraredBadPixelThresholdNotify(ROE_U8 * msgData);

ROE_S32 handleInfraredBadPixelNumNotify(ROE_U8 * msgData);

ROE_S32 handleVideoInputDeviceSwitchStatusNotify(ROE_U8 * msgData);

ROE_S32 handleInitConfigNotify(ROE_U8 * msgData);

ROE_S32 handleBatteryInfoNotify(ROE_U8 * msgData);

ROE_S32 handleRtCtlPanTiltInfoNotify(ROE_U8 * msgData);

ROE_S32 handleOledStatusInfoNotify(ROE_U8 * msgData);

ROE_S32 handleVideoInputDeviceAuxiliaryLightingNotify(ROE_U8 * msgData);

ROE_S32 handleVideoInputDeviceFreezingNotify(ROE_U8 * msgData);

ROE_S32 handleVideoInputDeviceMirrorFlipNotify(ROE_U8 * msgData);

ROE_S32 handleVideoInputDeviceRotatingNotify(ROE_U8 * msgData);

ROE_S32 handleMediaFilePlayOperateNotify(ROE_U8 * msgData);

ROE_S32 handleOsdShowHideOperateNotify(ROE_U8 * msgData);

ROE_S32 handlePeripheralsPowerStatusNotify(ROE_U8 * msgData);

ROE_S32 handleInfraredPseudoColorModeNotify(ROE_U8 * msgData);

ROE_S32 handleInfraredHotPixelRepairedCorrectedValueNotify(ROE_U8 * msgData);

ROE_S32 handleReticleInfoUpdatingNotify(ROE_U8 * msgData);
#endif //ZKSL_75_6LC_HANDLENOTIFY_H
