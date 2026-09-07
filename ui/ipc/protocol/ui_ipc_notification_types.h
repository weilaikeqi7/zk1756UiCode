//
// Created by jinxing on 2026/2/11.
//

#ifndef ZKSL_75_6LC_UI_IPC_NOTIFICATION_TYPES_H
#define ZKSL_75_6LC_UI_IPC_NOTIFICATION_TYPES_H

#include "ui/foundation/roeTypes.h"
#include "ui/ipc/protocol/ui_ipc_protocol.h"
#include "ui_Self.h"

/* Wire-format notification payloads. Keep field order and widths aligned
 * with the IPC protocol. */
#pragma pack(push, 1)

/* 3.1.1 设备初始配置信息 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 satelliteSystem;
    ROE_U8 language;
    ROE_U8 hotTrackSwitch;
    ROE_U8 targetRecognitionSwitch;
} UiNotificationDeviceInitConfig;

/* 3.1.2 资源路径信息 */
typedef struct {
    UiIpcMessageHeader header;
    /* Four length-prefixed strings follow the header. */
    ROE_U8 pathData[];
} UiNotificationResourcePathInfo;

/* 3.1.3 按键事件信息 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 inMenu;
    ROE_U8 keyCode;
    ROE_U8 keyEvent;
} UiNotificationKeyEventInfo;

/* 3.1.4 主菜单操作 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 action;
    ROE_U8 option;
} UiNotificationMainMenuOperate;

/* 3.1.5 对话框显示 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 dialogType;
    ROE_U8 option;
} UiNotificationDialogBoxDisplay;

/* 3.2.1.1 分划板总体信息 */
typedef struct {
    UiIpcMessageHeader header;
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
} UiNotificationReticleOverallInfo;

/* 3.2.1.2 分划板信息更新 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_S8 reticleCount;
    ROE_U8 reticleData[];
} UiNotificationReticleInfoUpdate;

/* 3.2.1.2 分划板信息更新的变长条目结构 */
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
    ROE_U8 nameLength;
    ROE_U8 name[];
} UiReticleEntry;

/* 3.3.1 OSD显示隐藏通知 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_S8 all;
    ROE_S8 datetime;
} UiNotificationOsdShowSwitch;

/* 3.3.2 主显示状态 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 state;
} UiNotificationMainDisplayStatus;

/* 3.3.3 视频变倍信息 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_FLOAT zoomValue;
    ROE_U8 precision;
} UiNotificationVideoZoomInfo;

/* 3.3.4 视频画面冻结 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 state;
} UiNotificationVideoOutputFreezing;

/* 3.3.5 视频画面镜像 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 lrMirror;
    ROE_U8 udMirror;
} UiNotificationVideoOutputMirrorFlip;

/* 3.3.6 视频画面旋转 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U16 angle;
} UiNotificationVideoOutputRotating;

/* 3.4.1 视频输入设备状态 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 cameraType;
    ROE_U8 state;
} UiNotificationVideoInputDeviceStatus;

/* 3.4.2 观察模式 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 mainScreenMode; // 0:白光 1:红外 2:融合
    ROE_U8 pipMode; // 0:白光 1:红外 2:融合
} UiNotificationObserveMode;

/* 3.4.3 红外伪彩模式 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 mode;
} UiNotificationInfraredPseudoColorMode;

/* 3.6.1 拍照状态 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 action;
} UiNotificationCaptureStatus;

/* 3.6.2 录制状态 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_S32 countUpTime;
} UiNotificationRecordStatus;

/* 3.6.3 媒体文件播放操作 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 action;
} UiNotificationMediaFilePlayOperate;

/* 3.7.1.1 设备能力 */
typedef struct {
    UiIpcMessageHeader header;

    ROE_U8 cameraVideoInputCount;
    ROE_U8 lowLightVideoInputCount;
    ROE_U8 infraredVideoInputCount;
    ROE_U8 remoteVideoInputCount;
    ROE_U8 mcfVideoInputCount;

    ROE_U8 mainDisplayCount;
    ROE_U8 extendedDisplayCount;
    ROE_U8 remoteDisplayCount;

    ROE_U8 audioInputCount;
    ROE_U8 audioOutputCount;

    ROE_U8 usbCount;
    ROE_U8 wifiCount;
    ROE_U8 bleCount;
    ROE_U8 sleCount;

    ROE_U8 compassCount;
    ROE_U8 gnssCount;
    ROE_U8 rangeFinderCount;
    ROE_U8 panTiltCount;
} UiNotificationDeviceAbility;

/* 3.7.1.2 设备状态 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_S8 wifi;
    ROE_S8 bluetooth;
    ROE_S8 sle;
} UiNotificationDeviceStatus;

/* 3.7.1.3 设备自检信息 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 selfCheckState;
    ROE_U8 selfItem[SELF_ITEM_NUM];
    ROE_U8 reserved;
} UiNotificationPeripheralSelfTestInfo;

/* 3.7.1.4 外设实时信息 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 sdPercent;
    ROE_U8 externalPower;
    ROE_U8 batteryPercent;
    ROE_FLOAT sdAvailableGB;
} UiNotificationPeripheralRealTimeInfo;

/* 3.7.1.5 外设电量信息 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 deviceType;
    ROE_U8 deviceId;
    ROE_U8 batteryPercent;
} UiNotificationPeripheralBatteryInfo;

/* 3.7.3.1 视频输入辅助照明 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 type;
    ROE_U8 brightness;
} UiNotificationAuxiliaryLighting;

/* 3.7.4.1 红外坏点阈值信息 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U32 minValue;
    ROE_U32 maxValue;
    ROE_U32 defaultValue;
} UiNotificationInfraredBadPixelThreshold;

/* 3.7.4.2 红外坏点当前数量 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U32 badPixelCount;
} UiNotificationInfraredBadPixelCount;

/* 3.7.4.3 红外热像素修复修正量 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U32 value;
} UiNotificationInfraredHotPixelRepairCorrection;

/* 3.7.5.1 电子罗盘数据 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_FLOAT yaw;
    ROE_FLOAT pitch;
    ROE_FLOAT roll;
} UiNotificationCompassData;

/* 3.7.5.2 磁偏角信息 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_FLOAT magneticDeclination;
} UiNotificationInitialMagneticDeclination;

/* 3.7.5.3 电子罗盘校准得分 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 score;
    ROE_U32 totalPoints;
    ROE_U32 calibratedPoints;
} UiNotificationCompassCalibrationScore;

/* 3.7.6.1 卫星定位数据 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 valid;
    ROE_U8 satelliteCount;
    ROE_U8 gaussZone;
    ROE_DOUBLE gaussX;
    ROE_DOUBLE gaussY;
    ROE_FLOAT longitude;
    ROE_FLOAT latitude;
    ROE_FLOAT altitude;
} UiNotificationGnssData;

/* 3.7.7.1 测距机状态 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 state;
} UiNotificationRangeFinderStatus;

/* 3.7.7.2 测距数据 */
typedef struct {
    UiIpcMessageHeader header;

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
} UiNotificationRangeData;

/* 3.7.7.3 测距倒计时 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U16 countDown;
} UiNotificationRangeCountdown;

/* 3.7.8.1 云台水平角度 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_FLOAT angle;
} UiNotificationPanTiltHorizontalAngle;

/* 3.7.8.2 云台垂直角度 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_FLOAT angle;
} UiNotificationPanTiltVerticalAngle;

/* 3.7.8.3 云台水平方向运动状态 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 state;
} UiNotificationPanTiltHorizontalRunningStatus;

/* 3.7.8.4 云台垂直方向运动状态 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 state;
} UiNotificationPanTiltVerticalRunningStatus;

/* 3.7.8.5 云台操作信息 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 direction;
    ROE_U8 state;
} UiNotificationPanTiltOperateInfo;

#pragma pack(pop)

#endif // ZKSL_75_6LC_UI_IPC_NOTIFICATION_TYPES_H
