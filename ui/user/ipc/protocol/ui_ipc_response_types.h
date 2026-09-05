//
// Created by jinxing on 2026/2/11.
//

#ifndef ZKSL_75_6LC_UI_IPC_RESPONSE_TYPES_H
#define ZKSL_75_6LC_UI_IPC_RESPONSE_TYPES_H

#include "user/core/roeTypes.h"
#include "user/ipc/protocol/ui_ipc_protocol.h"

/* Wire-format response payloads. Keep field order and widths aligned with
 * the IPC protocol. */
#pragma pack(push, 1)

/* 4.1.1 注册/注销 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseRegister;

/* 4.1.2 关机 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseShutdown;

/* 4.1.3 版本信息获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 versionLength; // 版本字符串长度
    ROE_U8 version[]; // 版本字符序列
} UiResponseGetAppVersion;

/* 4.1.4 系统时间设置 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseSetSystemTime;

/* 4.1.5 磁盘格式化 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseFormatDisk;

/* 4.2.1 恢复出厂设置 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseRestoreFactory;

/* 4.2.2 保存语言配置 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseSaveLanguageConfig;

/* 4.2.3 用户通用配置获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 showDateTime; // 0隐藏 1显示
    ROE_U16 standbyTimeout; // 待机时长，0永不待机，单位秒
    ROE_U16 shutdownTimeout; // 关机时长，0永不关机，单位秒
    ROE_U8 distanceUnit; // 0米 1码
    ROE_U8 batteryLevel; //0 图标 1百分比
} UiResponseGetUserCommonConfig;

/* 4.2.4 用户通用配置修改 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 showDateTime; // 当前值
    ROE_U16 standbyTimeout;
    ROE_U16 shutdownTimeout;
    ROE_U8 distanceUnit;
    ROE_U8 batteryLevel;
} UiResponseSetUserCommonConfig;

/* 4.2.5 用户媒体配置获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 burstCount; // 连拍数量，0单拍
    ROE_U16 maxRecordDuration; // 单个文件最大录制时长，0无限制
    ROE_U8 recoilPreRecordSwitch; // 后坐力激活视频预录开关，0关 1开
    ROE_U16 recoilPreRecordDuration; // 后坐力激活视频预录时长，0不录制
    ROE_U8 micSwitch; // 麦克风开关，0关 1开
} UiResponseGetUserMediaConfig;

/* 4.2.6 用户媒体配置修改 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 burstCount;
    ROE_U16 maxRecordDuration;
    ROE_U8 recoilPreRecordSwitch;
    ROE_U16 recoilPreRecordDuration;
    ROE_U8 micSwitch;
} UiResponseSetUserMediaConfig;

/* 4.3.1 退出菜单模式 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseExitMenu;

/* 4.3.2 退出对话框 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseExitDialogBox;

/* 5.1.1 分划板通用配置修改 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 currentShowReticle;
    ROE_U8 currentRotateReticle;
    ROE_U8 currentBrightnessBall;
    ROE_U8 currentBallisticSolve;
} UiResponseSetReticleCommonConfig;

/* 5.1.2 武器分划板类型设置 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 reticleTypeIndex;
} UiResponseWeaponSetReticleStyle;

/* 5.1.3 武器分划板颜色设置 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 reticleColorIndex;
} UiResponseWeaponSetReticleColor;

/* 5.1.4 武器分划板亮度调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseWeaponSetReticleBrightness;

/* 5.1.5 武器配置保存 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseWeaponSaveConfig;

/* 5.1.6 武器型号配置操作 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 videoChannel;
    ROE_U8 defaultWeaponIndex; // 默认武器型号
    ROE_U8 weaponIndex; // 当前武器型号
    ROE_U8 reticleTypeIndex; // 分划板类型索引
    ROE_U8 reticleColorIndex; // 分划板颜色索引
    ROE_U8 shootDistanceCount; // 射击距离数量 1-20
    ROE_U8 defaultDistanceIndex; // 默认射击距离索引
    ROE_U16 shootDistances[20]; // 射击距离值，有效数量为 shootDistanceCount
} UiResponseWeaponMarkConfigOperate;

/* 5.1.7 武器默认射击距离设置 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 defaultDistanceIndex;
    ROE_U16 defaultDistance;
    ROE_S16 defaultAbsX;
    ROE_S16 defaultAbsY;
    ROE_S16 defaultRelX;
    ROE_S16 defaultRelY;
} UiResponseWeaponSetDefaultShootDistance;

/* 5.1.8 武器射击距离操作 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 distanceIndex; // 操作后有效的射击距离索引
    ROE_U16 distanceValue;
    ROE_S16 absX;
    ROE_S16 absY;
    ROE_S16 relX;
    ROE_S16 relY;
    ROE_U8 shootDistanceCount; // 当前射击距离数量
    ROE_U8 defaultDistanceIndex; // 当前默认射击距离索引
    ROE_U16 shootDistances[20]; // 所有射击距离值
} UiResponseWeaponOperateShootDistance;

/* 5.1.9 武器射击位置设置 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 distanceIndex;
    ROE_U16 distanceValue;
    ROE_S16 absX;
    ROE_S16 absY;
    ROE_S16 relX;
    ROE_S16 relY;
} UiResponseWeaponSetShootPosition;

/* 5.1.10 武器射击零位设置 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 distanceIndex;
    ROE_U16 distanceValue;
    ROE_S16 absX;
    ROE_S16 absY;
    ROE_S16 relX;
    ROE_S16 relY;
} UiResponseWeaponSetShootZero;

/* 6.1 视频输出显示设备参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseGetVideoOutputParameters;

/* 6.2 主显示亮度调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustMainDisplayBrightness;

/* 6.3 主显示对比度调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustMainDisplayContrast;

/* 6.4 扩展显示开关 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustExtendDisplaySwitch;

/* 6.5 画中画开关 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustPipSwitch;

/* 6.6 视频变倍 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustVideoZoom;

/* 6.7 视频画面冻结 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseFreezeVideoInput;

/* 6.8 目标识别开关 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustRecognitionSwitch;

/* 7.1.1 视频采集输入设备参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseGetVideoInputParameters;

/* 7.1.2 主画面观察模式切换 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseSwitchMainObserveMode;

/* 7.1.3 画中画观察模式切换 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseSwitchPipObserveMode;

/* 7.2.1 可见光设备参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U32 minExposureTimeUs;
    ROE_U32 maxExposureTimeUs;
} UiResponseGetVideoInputCameraParameters;

/* 7.2.2 日夜模式切换 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustDayNight;

/* 7.2.3 可见光亮度调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustCameraBrightness;

/* 7.2.4 可见光对比度调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustCameraContrast;

/* 7.2.5 可见光饱和度调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustCameraSaturation;

/* 7.2.6 可见光色调调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustCameraHue;

/* 7.2.7 可见光透雾开关 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustFogSwitch;

/* 7.2.8 可见光透雾强度调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustFogIntensity;

/* 7.2.9 可见光曝光调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustCameraExposure;

/* 7.3.1 低照度设备参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseGetVideoInputLowLightParameters;

/* 7.4.1 红外设备参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 pseudoColorCount;
} UiResponseGetVideoInputInfraredParameters;

/* 7.4.2 红外伪彩模式切换 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustInfraredPseudoColor;

/* 7.4.3 红外亮度调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustInfraredBrightness;

/* 7.4.4 红外对比度调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustInfraredContrast;

/* 7.4.5 红外图像增强调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseInfraredEnhanceImage;

/* 7.4.6 红外场景模式切换 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseInfraredScenarioMode;

/* 7.4.7 红外热点追踪开关 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseInfraredHotspotTrackingSwitch;

/* 7.5.1 远程视频设备参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 pseudoColorCount;
} UiResponseGetVideoInputRemoteParameters;

/* 8.1.1 音频输入输出设备参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseGetAudioParameters;

/* 9.1 拍照 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseCaptureMediaFile;

/* 9.2 录制 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 recordSwitch;
    ROE_U8 result;
} UiResponseRecordMediaFile;

/* 9.3 获取媒体文件列表 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U32 totalCount; // 符合条件的总文件数量
    ROE_U8 fileCount; // 本次返回文件实际数量 (0-UI_MAX_MEDIA_FILE_NUM_ONE_PAGE)
    /* 后面紧跟 fileCount 个媒体文件信息，每个信息为变长结构 UiMediaFileInfo */
    ROE_U8 fileData[];
} UiResponseGetMediaFileList;

/* 9.3 获取媒体文件列表的变长媒体条目结构 */
typedef struct {
    ROE_U8 type; // 0:照片 1:视频 2:音频
    ROE_S64 size;
    ROE_S32 duration;
    ROE_U32 createTime;
    ROE_U8 nameLength;
    ROE_U8 name[]; // 文件名，长度为nameLength
} UiMediaFileInfo;

/* 9.4 退出回放列表 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseExitPlaybackList;

/* 9.5 媒体文件删除 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseDeleteMediaFile;

/* 9.6 媒体文件播放 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponsePlayMediaFile;

/* 9.7 播放上相邻媒体文件 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponsePlayAdjacentMediaFile;

/* 9.8 停止媒体文件播放 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseStopMediaFilePlay;

/* 10.1.1 USB设备参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseGetPeripheralUsbParameters;

/* 10.2.1 网络设备参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseGetPeripheralNetworkParameters;

/* 10.2.2 WIFI开关 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustWifiSwitch;

/* 10.2.3 WIFI信息获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    /* 三组长度前缀字符串依次为 SSID、KEY、流地址。 */
    ROE_U8 wifiData[];
} UiResponseGetWifiInfo;

/* 10.3.1 可见光模组参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseGetPeripheralCameraModuleParameters;

/* 10.4.1 低照度模组参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseGetPeripheralLowLightModuleParameters;

/* 10.5.1 红外模组参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 supportsManualNuc;
    ROE_U8 supportsAutoNuc;
    ROE_U8 supportsTwoPointNuc;
    ROE_U8 supportsManualBadPixelRemoval;
    ROE_U8 supportsAutoBadPixelRemoval;
    ROE_U8 supportsHotPixelRepair;
} UiResponseGetPeripheralInfraredModuleParameters;

/* 10.5.2 红外手动去坏点 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseInfraredManualRemoveBadPixel;

/* 10.5.3 设置红外坏点校正阈值 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseInfraredSetBadPixelThreshold;

/* 10.5.4 红外坏点校正操作 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 opType; // 操作类型（回显）
} UiResponseInfraredBadPixelOperate;

/* 10.5.5 红外热像素修复操作 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 opType; // 操作类型（回显）
} UiResponseInfraredHotPixelRepair;

/* 10.5.6 红外单点非均匀性校正 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseInfraredSdNuc;

/* 10.6.1 远程视频设备参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseGetPeripheralRemoteVideoModuleParameters;

/* 10.7.1 电子罗盘参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
    ROE_U8 supportsManualCalibration;
    ROE_U8 supportsCalibrationEvaluation;
    ROE_U8 supportsSampleCountDuringCalibration;
} UiResponseGetPeripheralCompassParameters;

/* 10.7.2 电子罗盘开关 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustCompassSwitch;

/* 10.7.3 电子罗盘设置磁偏角 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseSetCompassDeclination;

/* 10.7.4 电子罗盘保存配置 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseSaveCompassConfig;

/* 10.7.5 电子罗盘开始校准 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseStartCompassCalibration;

/* 10.7.6 电子罗盘停止校准 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseStopCompassCalibration;

/* 10.8.1 卫星定位参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseGetPeripheralGnssParameters;

/* 10.8.2 卫星定位开关 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustGnssSwitch;

/* 10.8.3 卫星定位系统切换 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustGnssSystem;

/* 10.8.4 卫星定位坐标系切换 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustCoordinateSystem;

/* 10.9.1 测距机参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseGetPeripheralRangeFinderParameters;

/* 10.9.2 测距机操作 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_S8 result; // 0成功 -1测距机未开 -2正在测距时开始/未停止 -3操作失败
} UiResponseRangeFinderOperate;

/* 10.9.3 测距频率调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustRangeFrequency;

/* 10.9.4 测距时长调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseAdjustRangeDuration;

/* 10.10.1 云台参数获取 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 result;
} UiResponseGetPeripheralPanTiltParameters;

/* 10.10.2 云台运动控制 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 direction; // 0:水平 1:垂直
    ROE_U8 ctrlType; // 同请求
    ROE_U8 result; // 0成功 非0失败
} UiResponsePanTiltMoveControl;

/* 10.10.3 云台运动速率调节 */
typedef struct {
    UiIpcMessageHeader header;
    ROE_U8 direction;
    ROE_U8 ctrlType;
    ROE_U8 result;
} UiResponsePanTiltSpeedControl;

#pragma pack(pop)

#endif //ZKSL_75_6LC_UI_IPC_RESPONSE_TYPES_H
