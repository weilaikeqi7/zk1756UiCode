//
// Created by jinxing on 2026/3/2.
//

#ifndef ZKSL_75_6LC_UI_IPC_NOTIFICATION_HANDLER_H
#define ZKSL_75_6LC_UI_IPC_NOTIFICATION_HANDLER_H

#include "user/core/roeTypes.h"

#define YARDS_PER_METER 1.09361f
#define METERS_PER_YARD 0.9144f

float meterToYard(float meters);

float yardToMeter(float yards);

ROE_S32 UiIpcHandleNotificationInitialMagneticDeclination(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationObserveMode(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationPeripheralSelfTestInfo(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationCompassData(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationGnssData(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationRangeData(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationPeripheralRealTimeInfo(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationRangeCountdown(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationCaptureStatus(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationRecordStatus(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationVideoZoomInfo(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationCompassCalibrationScore(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationDialogBoxDisplay(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationMainMenuOperate(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationKeyEventInfo(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationRangeFinderStatus(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationResourcePathInfo(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationReticleOverallInfo(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationPanTiltHorizontalAngle(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationPanTiltVerticalAngle(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationPanTiltHorizontalRunningStatus(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationPanTiltVerticalRunningStatus(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationDeviceAbility(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationInfraredBadPixelThreshold(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationInfraredBadPixelCount(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationVideoInputDeviceStatus(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationDeviceInitConfig(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationPeripheralBatteryInfo(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationPanTiltOperateInfo(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationMainDisplayStatus(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationAuxiliaryLighting(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationVideoOutputFreezing(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationVideoOutputMirrorFlip(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationVideoOutputRotating(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationMediaFilePlayOperate(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationOsdShowSwitch(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationDeviceStatus(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationInfraredPseudoColorMode(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationInfraredHotPixelRepairCorrection(ROE_U8 * msgData);

ROE_S32 UiIpcHandleNotificationReticleInfoUpdate(ROE_U8 * msgData);
#endif // ZKSL_75_6LC_UI_IPC_NOTIFICATION_HANDLER_H
