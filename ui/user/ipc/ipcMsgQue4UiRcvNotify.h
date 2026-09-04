//
// Created by jinxing on 2026/2/11.
//

#ifndef ZKSL_75_6LC_IPCMSGQUE4UIRCVNOTIFY_H
#define ZKSL_75_6LC_IPCMSGQUE4UIRCVNOTIFY_H

#include "user/core/roeTypes.h"
#include "user/ipc/msg.h"
#include "user/ipc/ipcMsgQue4UiTypeCommon.h"
#include "ui_Self.h"

#pragma pack(push, 1)

/* 1. 磁偏角信息 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_FLOAT magneticDeclination;
} NotifyMagneticDeclination_st;

/* 2. 观察模式信息 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 mainScreenMode; // 0:白光 1:红外 2:融合
    ROE_U8 pipMode; // 0:白光 1:红外 2:融合
} NotifyObserveMode_st;

/* 3. 设备自检结果信息 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 selfCheckState;
    ROE_U8 selfItem[SELF_ITEM_NUM];
    ROE_U8 reserved;
} NotifySelfCheck_st;

/* 4. 电子罗盘信息 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_FLOAT yaw;
    ROE_FLOAT pitch;
    ROE_FLOAT roll;
} NotifyCompass_st;

/* 5. 卫星定位信息 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 valid;
    ROE_U8 satelliteCount;
    ROE_U8 gaussZone;
    ROE_DOUBLE gaussX;
    ROE_DOUBLE gaussY;
    ROE_FLOAT longitude;
    ROE_FLOAT latitude;
    ROE_FLOAT altitude;
} NotifyGps_st;

/* 6. 激光测距信息 */
typedef struct {
    MsgQueHeader4Ui_st head;

    ROE_U8 targetCount;
    ROE_U8 hasLocation;

    ROE_FLOAT firstDistance;
    ROE_FLOAT firstLongitude;
    ROE_FLOAT firstLatitude;
    ROE_FLOAT firstAltitude;
    ROE_U8 firstGaussZone;
    ROE_DOUBLE firstGaussX;
    ROE_DOUBLE firstGaussY;

    ROE_FLOAT lastDistance;
    ROE_FLOAT lastLongitude;
    ROE_FLOAT lastLatitude;
    ROE_FLOAT lastAltitude;
    ROE_U8 lastGaussZone;
    ROE_DOUBLE lastGaussX;
    ROE_DOUBLE lastGaussY;
} NotifyLaser_st;

/* 7. 电量、SD卡容量 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 sdPercent;
    ROE_U8 externalPower;
    ROE_U8 batteryPercent;
    ROE_FLOAT sdAvailableGB;
} NotifyPower_st;

/* 8. 测距倒计时 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U16 countDown;
} NotifyLaserCountDown_st;

/* 9. 拍照操作 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 action;
} NotifyPhoto_st;

/* 10. 录制操作 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_S32 countUpTime;
} NotifyRecord_st;

/* 11. 变倍信息 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_FLOAT zoomValue;
    ROE_U8 precision;
} NotifyZoom_st;

/* 12. 罗盘校准得分 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 score;
    ROE_U32 totalPoints;
    ROE_U32 calibratedPoints;
} NotifyCompassScore_st;

/* 13. 对话框显示 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 dialogType;
    ROE_U8 option;
} NotifyDialog_st;

/* 14. 菜单模式操作 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 action;
    ROE_U8 option;
} NotifyMenuMode_st;

/* 15. 菜单按键信息 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 inMenu;
    ROE_U8 keyCode;
    ROE_U8 keyEvent;
} NotifyMenuKey_st;

/* 16. 测距机状态 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 state;
} NotifyLaserState_st;

/* 17. 资源路径信息 */
typedef struct {
    MsgQueHeader4Ui_st head;
    /* Four length-prefixed strings follow the header. */
    ROE_U8 pathData[];
} NotifyPath_st;

/* 18. 分划板总体信息 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 weaponTypeCount;
    ROE_U8 reticleTypeCount;
    ROE_U8 colorCount;
    ROE_U8 displaySwitch;
    ROE_U8 rotateSwitch;
    ROE_U8 lumaAdaptiveAdjustSwitch;
    ROE_U8 ballisticSwitch;
    ROE_U8 currentWeaponIndex;
    ROE_U8 maxDistanceCount;
    ROE_U8 defaultDistanceIndex;
    ROE_U16 defaultDistance;
} NotifyReticleInfo_st;

/* 19. 云台水平角度 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_FLOAT angle;
} NotifyGimbalYaw_st;

/* 20. 云台垂直角度 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_FLOAT angle;
} NotifyGimbalPitch_st;

/* 21. 云台水平方向运动状态 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 state;
} NotifyGimbalYawState_st;

/* 22. 云台垂直方向运动状态 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 state;
} NotifyGimbalPitchState_st;

/* 23. 设备能力 */
typedef struct {
    MsgQueHeader4Ui_st head;

    ROE_U8 cameraViNum;
    ROE_U8 lowLigthViNum;
    ROE_U8 infraredViNum;
    ROE_U8 remoteViNum;
    ROE_U8 mcfViNum;

    ROE_U8 mainDisplayNum;
    ROE_U8 extendDisplayNum;
    ROE_U8 remoteDisplayNum;

    ROE_U8 audioInputNum;
    ROE_U8 audioOutputNum;

    ROE_U8 usbNum;
    ROE_U8 wifiNum;
    ROE_U8 bleNum;
    ROE_U8 sleNum;

    ROE_U8 compassNum;
    ROE_U8 gnssNum;
    ROE_U8 rangeFinderNum;
    ROE_U8 panTiltNum;
} NotifyDeviceCapability_st;

/* 24. 红外坏点阈值 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U32 minValue;
    ROE_U32 maxValue;
    ROE_U32 defaultValue;
} NotifyBadPixelThreshold_st;

/* 25. 红外坏点当前数量 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U32 badPixelCount;
} NotifyBadPixelCount_st;

/* 26. 视频输入设备开关 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 cameraType;
    ROE_U8 state;
} NotifyVideoInput_st;

/* 27. 初始配置信息 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 satelliteSystem;
    ROE_U8 language;
    ROE_U8 hotTrackSwitch;
    ROE_U8 targetRecognitionSwitch;
} NotifyInitConfig_st;

/* 28. 电量信息 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 deviceType;
    ROE_U8 deviceId;
    ROE_U8 batteryPercent;
} NotifyBattery_st;

/* 29. 终端操作云台 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 direction;
    ROE_U8 state;
} NotifyGimbalControl_st;

/* 30. OLED屏幕状态 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 state;
} NotifyOled_st;

/* 31. 辅助照明 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 type;
    ROE_U8 brightness;
} NotifyLight_st;

/* 32. 视频冻结 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 state;
} NotifyFreeze_st;

/* 33. 视频镜像 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 lrMirror;
    ROE_U8 udMirror;
} NotifyMirror_st;

/* 34. 视频旋转 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U16 angle;
} NotifyRotate_st;

/* 35. 媒体播放操作 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 action;
} NotifyMediaPlay_st;

/* 36. OSD显示隐藏 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_S8 all;
    ROE_S8 datetime;
} NotifyOsd_st;

/* 37. 设备开关状态 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_S8 wifi;
    ROE_S8 bluetooth;
    ROE_S8 sle;
} NotifyDeviceSwitch_st;

/* 38. 红外伪彩模式 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 mode;
} NotifyPseudoColor_st;

/* 39. 红外热像素修正量 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U32 value;
} NotifyHotPixelFix_st;

/* 40. 分划板信息更新 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_S8 num;
    ROE_U8 dividingPlatesData[];
} NotifyReticleUpdate_st;

typedef struct {
    ROE_S8 state;
    ROE_U16 width;
    ROE_U16 height;
    ROE_S16 displayX;
    ROE_S16 displayY;
    ROE_S16 cuttingX;
    ROE_S16 cuttingY;
    ROE_U16 cuttingWidth;
    ROE_U16 cuttingHeight;
    ROE_U8 nameLen;
    ROE_U8 name[];
} DividingPlates_st;

#pragma pack(pop)

ROE_S32 ParseNotifyMsg(ROE_SL msgType, const RoeIpcMsgQueRawData_st * rawData);

#endif //ZKSL_75_6LC_IPCMSGQUE4UIRCVNOTIFY_H
