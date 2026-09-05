//
// Created by jinxing on 2026/2/11.
//

#ifndef ZKSL_75_6LC_UI_IPC_REQUEST_TYPES_H
#define ZKSL_75_6LC_UI_IPC_REQUEST_TYPES_H

#include "user/ipc/ui_ipc_protocol.h"
#include "user/core/roeTypes.h"

/* Wire-format request payloads. Keep field order and widths aligned with
 * the IPC protocol. */
#pragma pack(push, 1)

/* 4.1.1 注册/注销 */
typedef struct {
    ROE_U8 reg; // 0:注销 1:注册
} UiRequestRegister;

/* 4.1.2 关机 */
typedef struct {
} UiRequestShutdown;

/* 4.1.3 版本信息获取 */
typedef struct {
} UiRequestGetAppVersion;

/* 4.1.4 系统时间设置 */
typedef struct {
    ROE_S16 year;
    ROE_S8 month;
    ROE_S8 day;
    ROE_S8 hour;
    ROE_S8 minute;
    ROE_S8 second;
} UiRequestSetSystemTime;

/* 4.1.5 磁盘格式化 */
typedef struct {
} UiRequestFormatDisk;

/* 4.2.1 恢复出厂设置 */
typedef struct {
} UiRequestRestoreFactory;

/* 4.2.2 保存语言配置 */
typedef struct {
    ROE_U8 langType; // 0-255 UI自己对应
} UiRequestSaveLanguageConfig;

/* 4.2.3 用户通用配置获取 */
typedef struct {
} UiRequestGetUserCommonConfig;

/* 4.2.4 用户通用配置修改 */
typedef struct {
    ROE_U8 saveFlag; // 0不保存 1保存
    ROE_S8 showDateTime; // -1不修改 0隐藏 1显示
    ROE_S16 standbyTimeout; // -1不修改 0永不待机 单位秒
    ROE_S16 shutdownTimeout; // -1不修改 0永不关机 单位秒
    ROE_S8 distanceUnit; // -1不修改 0米 1码
    ROE_S8 batteryLevel;
} UiRequestSetUserCommonConfig;

/* 4.2.5 用户媒体配置获取 */
typedef struct {
} UiRequestGetUserMediaConfig;

/* 4.2.6 用户媒体配置修改 */
typedef struct {
    ROE_U8 saveFlag; // 0不保存 1保存
    ROE_S8 burstCount; // -1不修改 0单拍 单位张
    ROE_S16 maxRecordDuration; // -1不修改 0无限制 单位秒
    ROE_S8 recoilPreRecordSwitch; // -1不修改 0关 1开
    ROE_S16 recoilPreRecordDuration; // -1不修改 0不录制 单位秒
    ROE_S8 micSwitch; // -1不修改 0关 1开
} UiRequestSetUserMediaConfig;

/* 4.3.1 退出菜单模式 */
typedef struct {
} UiRequestExitMenu;

/* 4.3.2 退出对话框 */
typedef struct {
} UiRequestExitDialogBox;

/* 5.1.1 分划板通用配置修改 */
typedef struct {
    ROE_U8 saveFlag; // 0不保存 1保存
    ROE_S8 showReticle; // -1不修改 0关 1开
    ROE_S8 rotateReticle; // -1不修改 0关 1开
    ROE_S8 brightnessBall;
    ROE_S8 ballisticSolve; // -1不修改 0关 1开
} UiRequestSetReticleCommonConfig;

/* 5.1.2 武器分划板类型设置 */
typedef struct {
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 reticleTypeIndex; // 分划板类型索引 1-最大索引
} UiRequestWeaponSetReticleStyle;

/* 5.1.3 武器分划板颜色设置 */
typedef struct {
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 reticleColorIndex; // 分划板颜色索引 1-最大索引
} UiRequestWeaponSetReticleColor;

/* 5.1.4 武器分划板亮度调节 */
typedef struct {
    ROE_U8 brightness; //分划板亮度 0-100
} UiRequestWeaponSetReticleBrightness;

/* 5.1.5 武器配置保存 */
typedef struct {
} UiRequestWeaponSaveConfig;

/* 5.1.6 武器型号配置操作 */
typedef struct {
    ROE_U8 videoChannel; // 0主画面 1画中画
    ROE_U8 weaponIndex; // 武器型号索引 1-最大索引
    ROE_U8 opType; // 0查询 1设置当前武器型号 2重置武器配置
} UiRequestWeaponMarkConfigOperate;

/* 5.1.7 武器默认射击距离设置 */
typedef struct {
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 defaultDistanceIndex; // 默认射击距离索引 1-最大索引
} UiRequestWeaponSetDefaultShootDistance;

/* 5.1.8 武器射击距离操作 */
typedef struct {
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 distanceIndex; // 射击距离索引，新增时忽略
    ROE_U16 distanceValue; // 对应射击距离，查询/删除时忽略
    ROE_U8 opType; // 0查询 1新增 2删除 3修改
    ROE_U8 syncMoveReticle; // 0不移动 1移动
} UiRequestWeaponOperateShootDistance;

/* 5.1.9 武器射击位置设置 */
typedef struct {
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 distanceIndex; // 射击距离索引
    ROE_S8 moveDir; // 0上 1下 2左 3右
} UiRequestWeaponSetShootPosition;

/* 5.1.10 武器射击零位设置 */
typedef struct {
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 distanceIndex; // 射击距离索引
    ROE_U8 zeroType; // 0相对 1绝对
} UiRequestWeaponSetShootZero;

/* 6.1 视频输出显示设备参数获取 */
typedef struct {
} UiRequestGetVideoOutputParameters;

/* 6.2 主显示亮度调节 */
typedef struct {
    ROE_U8 brightness; // 0-100
} UiRequestAdjustMainDisplayBrightness;

/* 6.3 主显示对比度调节 */
typedef struct {
    ROE_U8 contrast; // 0-100
} UiRequestAdjustMainDisplayContrast;

/* 6.4 扩展显示开关 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} UiRequestAdjustExtendDisplaySwitch;

/* 6.5 画中画开关 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} UiRequestAdjustPipSwitch;

/* 6.6 视频变倍 */
typedef struct {
    ROE_U8 direction; // 0:反向 1:正向
} UiRequestAdjustVideoZoom;

/* 6.7 视频画面冻结 */
typedef struct {
    ROE_U8 freeze; // 0:解冻 1:冻结
} UiRequestFreezeVideoInput;

/* 6.8 目标识别开关 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} UiRequestAdjustRecognitionSwitch;

/* 7.1.1 视频采集输入设备参数获取 */
typedef struct {
} UiRequestGetVideoInputParameters;

/* 7.1.2 主画面观察模式切换 */
typedef struct {
    ROE_U8 mainObserveMode; // 0:白光 1:红外 2:融合
} UiRequestSwitchMainObserveMode;

/* 7.1.3 画中画观察模式切换 */
typedef struct {
    ROE_U8 pipObserveMode; // 0:白光 1:红外 2:融合
} UiRequestSwitchPipObserveMode;

/* 7.2.1 可见光设备参数获取 */
typedef struct {
} UiRequestGetVideoInputCameraParameters;

/* 7.2.2 日夜模式切换 */
typedef struct {
    ROE_U8 mode; // 0:日 1:夜
} UiRequestAdjustDayNight;

/* 7.2.3 可见光亮度调节 */
typedef struct {
    ROE_U8 brightness; // 0-100
} UiRequestAdjustCameraBrightness;

/* 7.2.4 可见光对比度调节 */
typedef struct {
    ROE_U8 contrast; // 0-100
} UiRequestAdjustCameraContrast;

/* 7.2.5 可见光饱和度调节 */
typedef struct {
    ROE_U8 saturation; // 0-100
} UiRequestAdjustCameraSaturation;

/* 7.2.6 可见光色调调节 */
typedef struct {
    ROE_U8 hue; // 0-100
} UiRequestAdjustCameraHue;

/* 7.2.7 可见光透雾开关 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} UiRequestAdjustFogSwitch;

/* 7.2.8 可见光透雾强度调节 */
typedef struct {
    ROE_U8 intensity; // 0-100
} UiRequestAdjustFogIntensity;

/* 7.2.9 可见光曝光调节 */
typedef struct {
    ROE_U8 exposureType; // 0:手动 1:自动
    ROE_U32 exposureTimeUs; // UINT32_MAX:自动；手动曝光时单位为微秒
    ROE_U8 manualIspDigitalGain; // 0-100，UINT8_MAX:自动
    ROE_U8 manualSensorDigitalGain; // 0-100，UINT8_MAX:自动
    ROE_U8 manualSensorAnalogGain; // 0-100，UINT8_MAX:自动
} UiRequestAdjustCameraExposure;

/* 7.3.1 低照度设备参数获取 */
typedef struct {
} UiRequestGetVideoInputLowLightParameters;

/* 7.4.1 红外设备参数获取 */
typedef struct {
} UiRequestGetVideoInputInfraredParameters;

/* 7.4.2 红外伪彩模式切换 */
typedef struct {
    ROE_U8 mode; // 0-7 同红外伪彩模式通知
} UiRequestAdjustInfraredPseudoColor;

/* 7.4.3 红外亮度调节 */
typedef struct {
    ROE_U8 brightness; // 0-100
} UiRequestAdjustInfraredBrightness;

/* 7.4.4 红外对比度调节 */
typedef struct {
    ROE_U8 contrast; // 0-100
} UiRequestAdjustInfraredContrast;

/* 7.4.5 红外图像增强调节 */
typedef struct {
    ROE_U8 strength; // 0-100 增强强度
} UiRequestInfraredEnhanceImage;

/* 7.4.6 红外场景模式切换 */
typedef struct {
    ROE_U8 mode; // 0:室内 1:户外
} UiRequestInfraredScenarioMode;

/* 7.4.7 红外热点追踪开关 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} UiRequestInfraredHotspotTrackingSwitch;

/* 7.5.1 远程视频设备参数获取 */
typedef struct {
} UiRequestGetVideoInputRemoteParameters;

/* 8.1.1 音频输入输出设备参数获取 */
typedef struct {
} UiRequestGetAudioParameters;

/* 9.1 拍照 */
typedef struct {
} UiRequestCaptureMediaFile;

/* 9.2 录制 */
typedef struct {
    ROE_U8 recordSwitch; // 0:关闭 1:开启
} UiRequestRecordMediaFile;

/* 9.3 获取媒体文件列表 */
typedef struct {
    ROE_S16 year; // 2025-2199
    ROE_S8 month; // 0-12
    ROE_S8 day; // 0-31
    ROE_S8 hour; // -1-23
    ROE_S8 minute; // -1-59
    ROE_S8 second; // -1-59
    ROE_U32 startIndex; // 请求起始序号，固定为0
    ROE_U8 requestCount; // 请求文件数量，最大 UI_MAX_MEDIA_FILE_NUM_ONE_PAGE
    ROE_S8 requestedFileType; //-1:全部 0:照片 1:视频 2:音频
} UiRequestGetMediaFileList;

/* 9.4 退出回放列表 */
typedef struct {
} UiRequestExitPlaybackList;

/* 9.5 媒体文件删除 */
typedef struct {
    ROE_U8 fileNameLength;
    ROE_U8 fileName[];
} UiRequestDeleteMediaFile;

/* 9.6 媒体文件播放 */
typedef struct {
    ROE_U8 fileNameLength;
    ROE_U8 fileName[];
} UiRequestPlayMediaFile;

/* 9.7 播放上相邻媒体文件 */
typedef struct {
} UiRequestPlayAdjacentMediaFile;

/* 9.8 停止媒体文件播放 */
typedef struct {
} UiRequestStopMediaFilePlay;

/* 10.1.1 USB设备参数获取 */
typedef struct {
} UiRequestGetPeripheralUsbParameters;

/* 10.2.1 网络设备参数获取 */
typedef struct {
} UiRequestGetPeripheralNetworkParameters;

/* 10.2.2 WIFI开关 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} UiRequestAdjustWifiSwitch;

/* 10.2.3 WIFI信息获取 */
typedef struct {
} UiRequestGetWifiInfo;

/* 10.3.1 可见光模组参数获取 */
typedef struct {
} UiRequestGetPeripheralCameraModuleParameters;

/* 10.4.1 低照度模组参数获取 */
typedef struct {
} UiRequestGetPeripheralLowLightModuleParameters;

/* 10.5.1 红外模组参数获取 */
typedef struct {
} UiRequestGetPeripheralInfraredModuleParameters;

/* 10.5.2 红外手动去坏点 */
typedef struct {
    ROE_U8 operationType; // 1:功能 2:光标 3:坏点
    ROE_U8 functionOperation; // 0:关闭 1:开启
    ROE_U8 cursorOperation; // 0:居中 1:上 2:下 3:左 4:右
    ROE_U8 badPixelOperation; // 0:取消 1:去除
} UiRequestInfraredManualRemoveBadPixel;

/* 10.5.3 设置红外坏点校正阈值 */
typedef struct {
    ROE_U32 threshold; // 待设置坏点值
} UiRequestInfraredSetBadPixelThreshold;

/* 10.5.4 红外坏点校正操作 */
typedef struct {
    ROE_U8 opType; // 0:清除 1:撤销 2:保存
} UiRequestInfraredBadPixelOperate;

/* 10.5.5 红外热像素修复操作 */
typedef struct {
    ROE_U8 opType; // 0:清除 1:撤销 2:保存
} UiRequestInfraredHotPixelRepair;

/* 10.5.6 红外单点非均匀性校正 */
typedef struct {
    ROE_U8 operationType; // 0:快门 1:背景 2:虚焦 3:渐晕
} UiRequestInfraredSdNuc;

/* 10.6.1 远程视频设备参数获取 */
typedef struct {
} UiRequestGetPeripheralRemoteVideoModuleParameters;

/* 10.7.1 电子罗盘参数获取 */
typedef struct {
} UiRequestGetPeripheralCompassParameters;

/* 10.7.2 电子罗盘开关 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} UiRequestAdjustCompassSwitch;

/* 10.7.3 电子罗盘设置磁偏角 */
typedef struct {
    ROE_FLOAT declination; // -180.0 ~ 180.0
} UiRequestSetCompassDeclination;

/* 10.7.4 电子罗盘保存配置 */
typedef struct {
} UiRequestSaveCompassConfig;

/* 10.7.5 电子罗盘开始校准 */
typedef struct {
    ROE_U8 method;
    ROE_S16 number;
} UiRequestStartCompassCalibration;

/* 10.7.6 电子罗盘停止校准 */
typedef struct {
    ROE_U8 saveFlag;
} UiRequestStopCompassCalibration;

/* 10.8.1 卫星定位参数获取 */
typedef struct {
} UiRequestGetPeripheralGnssParameters;

/* 10.8.2 卫星定位开关 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} UiRequestAdjustGnssSwitch;

/* 10.8.3 卫星定位系统切换 */
typedef struct {
    ROE_U8 system; // 0:全部 1:联合 2:北斗 3:格林纳斯 4:GPS 5:联合+北斗 6:北斗+格林纳斯
} UiRequestAdjustGnssSystem;

/* 10.8.4 卫星定位坐标系切换 */
typedef struct {
    ROE_U8 system; // 0:WGS-84 1:CK-42 2:COMBINE
} UiRequestAdjustCoordinateSystem;

/* 10.9.1 测距机参数获取 */
typedef struct {
} UiRequestGetPeripheralRangeFinderParameters;

/* 10.9.2 测距机操作 */
typedef struct {
    ROE_S8 sw; // 0:关 1:开
    ROE_S8 rangeSwitch;
} UiRequestRangeFinderOperate;

/* 10.9.3 测距频率调节 */
typedef struct {
    ROE_U8 freq; // 0:单次 1:1Hz 5:5Hz 10:10Hz
} UiRequestAdjustRangeFrequency;

/* 10.9.4 测距时长调节 */
typedef struct {
    ROE_S8 duration; // 0:单次 10:10分钟 30:30分钟 60:1小时 -1:一直测距
} UiRequestAdjustRangeDuration;

/* 10.10.1 云台参数获取 */
typedef struct {
} UiRequestGetPeripheralPanTiltParameters;

/* 10.10.2 云台运动控制 */
typedef struct {
    ROE_U8 direction; // 0:水平 1:垂直
    ROE_U8 ctrlType; // 水平:0停止 1右 2左; 垂直:0停止 1上 2下
} UiRequestPanTiltMoveControl;

/* 10.10.3 云台运动速率调节 */
typedef struct {
    ROE_U8 direction; // 0:水平 1:垂直
    ROE_U8 ctrlType; // 速率值 (0-100)
} UiRequestPanTiltSpeedControl;

#pragma pack(pop)

#endif // ZKSL_75_6LC_UI_IPC_REQUEST_TYPES_H
