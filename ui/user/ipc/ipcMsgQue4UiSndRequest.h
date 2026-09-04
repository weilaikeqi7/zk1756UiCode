//
// Created by jinxing on 2026/2/11.
//

#ifndef ZKSL_75_6LC_IPCMSGQUE4UISNDREQUEST_H
#define ZKSL_75_6LC_IPCMSGQUE4UISNDREQUEST_H

#include "user/ipc/ipcMsgQue4UiTypeCommon.h"
#include "user/core/roeTypes.h"

#define UI_MSG_VERSION 0
#define UI_MAX(x, y) ((x) > (y) ? (x) : (y))
#define UI_MAX_EXTEND_STRING_NUM UI_MAX(UI_MAX_MEDIA_FILE_NUM_ONE_PAGE, UI_RETICLE_NUM)

/* Host-only descriptors. Their pointers are used while building a message
 * and are never copied to the wire. */
typedef struct {
    ROE_U8 stringNum;
    const ROE_S8 * pStringList[UI_MAX_EXTEND_STRING_NUM];
} StringData_st;

typedef struct {
    ROE_U8 version;
    ROE_U8 concreteType;
    const void * pFormatParam;
    ROE_S32 formatParamSize;
    StringData_st strData;
} ParamOfMsg4Ui_st;

#pragma pack(push, 1)

/* 3.1 注册/注销 */
typedef struct {
    ROE_U8 reg; // 0:注销 1:注册
} ReqRegister_st;

/* 3.2 退出菜单模式 */
typedef struct {
} ReqExitMenu_st;

/* 3.3 设置系统时间 */
typedef struct {
    ROE_S16 year;
    ROE_S8 month;
    ROE_S8 day;
    ROE_S8 hour;
    ROE_S8 minute;
    ROE_S8 second;
} ReqSetSystemTime_st;

/* 3.4 主画面观察模式调整 */
typedef struct {
    ROE_U8 mode; // 0:白光 1:红外 2:融合
} ReqAdjustObserveMode_st;

/* 3.4 画中画观察模式调整 */
typedef struct {
    ROE_U8 mode; // 0:白光 1:红外 2:融合
} ReqAdjustPipObserveMode_st;

/* 3.5 日夜模式切换 */
typedef struct {
    ROE_U8 mode; // 0:日 1:夜
} ReqAdjustDayNight_st;

/* 3.6 识别开关调整 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} ReqAdjustRecognitionSwitch_st;

/* 3.7 可见光亮度调整 */
typedef struct {
    ROE_U8 brightness; // 0-100
} ReqAdjustCameraBrightness_st;

/* 3.8 红外亮度调整 */
typedef struct {
    ROE_U8 brightness; // 0-100
} ReqAdjustInfraredBrightness_st;

/* 3.9 可见光对比度调整 */
typedef struct {
    ROE_U8 contrast; // 0-100
} ReqAdjustCameraContrast_st;

/* 3.10 红外对比度调整 */
typedef struct {
    ROE_U8 contrast; // 0-100
} ReqAdjustInfraredContrast_st;

/* 3.11 可见光透雾开关调整 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} ReqAdjustFogSwitch_st;

/* 3.12 可见光透雾强度调整 */
typedef struct {
    ROE_U8 intensity; // 0-100
} ReqAdjustFogIntensity_st;

/* 3.13 电子罗盘开关调整 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} ReqAdjustCompassSwitch_st;

/* 3.14 电子罗盘开始校准 */
typedef struct {
    ROE_U8 method;
    ROE_S16 number;
} ReqStartCompassCalibration_st;

/* 3.15 电子罗盘停止校准 */
typedef struct {
    ROE_U8 ifsave;
} ReqStopCompassCalibration_st;

/* 3.16 电子罗盘设置磁偏角 */
typedef struct {
    ROE_FLOAT declination; // -180.0 ~ 180.0
} ReqSetCompassDeclination_st;

/* 3.17 电子罗盘保存配置 */
typedef struct {
} ReqSaveCompassConfig_st;

/* 3.18 卫星定位开关调整 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} ReqAdjustGnssSwitch_st;

/* 3.19 卫星定位系统调整 */
typedef struct {
    ROE_U8 system; // 0:全部 1:联合 2:北斗 3:格林纳斯 4:GPS 5:联合+北斗 6:北斗+格林纳斯
} ReqAdjustGnssSystem_st;

/* 3.20 大地坐标系统调整 */
typedef struct {
    ROE_U8 system; // 0:WGS-84 1:CK-42 2:COMBINE
} ReqAdjustCoordinateSystem_st;

/* 3.21 恢复出厂设置 */
typedef struct {
} ReqRestoreFactory_st;

/* 3.22 磁盘格式化 */
typedef struct {
} ReqFormatDisk_st;

/* 3.23 WIFI开关调整 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} ReqAdjustWifiSwitch_st;

/* 3.24 WIFI信息获取 */
typedef struct {
} ReqGetWifiInfo_st;

/* 3.25 版本信息获取 */
typedef struct {
} ReqGetAppVersion_st;

/* 3.26 红外伪彩模式调整 */
typedef struct {
    ROE_U8 mode; // 0-7 同红外伪彩模式通知
} ReqAdjustInfraredPseudoColor_st;

/* 3.27 获取媒体文件列表 */
typedef struct {
    ROE_S16 year; // 2025-2199
    ROE_S8 month; // 0-12
    ROE_S8 day; // 0-31
    ROE_S8 hour; // -1-23
    ROE_S8 minute; // -1-59
    ROE_S8 second; // -1-59
    ROE_U32 startIndex; // 请求起始序号，固定为0
    ROE_U8 reqCount; // 请求文件数量，最大 UI_MAX_MEDIA_FILE_NUM_ONE_PAGE
    ROE_S8 reqFileType; //-1:全部 0:照片 1:视频 2:音频
} ReqGetMediaFileList_st;

/* 3.28 媒体文件列表翻页 */
typedef struct {
    ROE_U32 startIndex; // 请求起始序号
    ROE_U8 reqCount; // 请求文件数量，最大 UI_MAX_MEDIA_FILE_NUM_ONE_PAGE
    ROE_S8 reqFileType; //-1:全部 0:照片 1:视频 2:音频
} ReqGetMediaFileListPage_st;

/* 3.29 媒体文件删除 */

/* 3.30 媒体文件播放 */

/* 3.31 播放上一个/下一个媒体文件 */
typedef struct {
} ReqPlayPriorOrNextMediaFile_st;

/* 3.32 退出媒体文件播放 */
typedef struct {
} ReqExitMediaPlay_st;

/* 3.33 测距机开关调整 */
typedef struct {
    ROE_S8 sw; // 0:关 1:开
    ROE_S8 range_sw;
} ReqAdjustRangefinderSwitch_st;

/* 3.34 测距频率调整 */
typedef struct {
    ROE_U8 freq; // 0:单次 1:1Hz 5:5Hz 10:10Hz
} ReqAdjustRangeFrequency_st;

/* 3.35 测距时长调整 */
typedef struct {
    ROE_S8 duration; // 0:单次 10:10分钟 30:30分钟 60:1小时 -1:一直测距
} ReqAdjustRangeDuration_st;

/* 3.36 画中画开关调整 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} ReqAdjustPipSwitch_st;

/* 3.37 扩展显示开关调整 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} ReqAdjustExtendDisplaySwitch_st;

/* 3.38 OLED显示亮度调整 */
typedef struct {
    ROE_U8 brightness; // 0-100
} ReqAdjustOledBrightness_st;

/* 3.39 OLED显示对比度调整 */
typedef struct {
    ROE_U8 contrast; // 0-100
} ReqAdjustOledContrast_st;

/* 3.40 视频变倍调整 */
typedef struct {
    ROE_U8 direction; // 0:反向 1:正向
} ReqAdjustVideoZoom_st;

/* 3.41 关机 */
typedef struct {
} ReqShutdown_st;

/* 3.42 退出对话框 */
typedef struct {
} ReqExitDialogBox_st;

/* 3.43 退出回放列表 */
typedef struct {
} ReqExitPlaybackList_st;

/* 3.44 云台运动状态控制 */
typedef struct {
    ROE_U8 direction; // 0:水平 1:垂直
    ROE_U8 ctrlType; // 水平:0停止 1右 2左; 垂直:0停止 1上 2下
} ReqPanTiltMoveControl_st;

/* 3.45 云台运动速率控制 */
typedef struct {
    ROE_U8 direction; // 0:水平 1:垂直
    ROE_U8 ctrlType; // 速率值 (0-100)
} ReqPanTiltSpeedControl_st;

/* 3.46 红外坏点校正阈值调整 */
typedef struct {
    ROE_U32 threshold; // 待设置坏点值
} ReqInfraredSetBadPixelThreshold_st;

/* 3.47 红外坏点校正操作 */
typedef struct {
    ROE_U8 opType; // 0:清除 1:撤销 2:保存
} ReqInfraredBadPixelOperate_st;

/* 3.48 保存当前语言配置 */
typedef struct {
    ROE_U8 langType; // 0-255 UI自己对应
} ReqSaveLanguageConfig_st;

/* 3.49 红外热像素修复操作 */
typedef struct {
    ROE_U8 opType; // 0:清除 1:撤销 2:保存
} ReqInfraredHotPixelRepair_st;

/* 3.50 红外热点追踪开关调整 */
typedef struct {
    ROE_U8 sw; // 0:关 1:开
} ReqInfraredHotspotTrackingSwitch_st;

/* 3.51 红外场景模式调整 */
typedef struct {
    ROE_U8 mode; // 0:室内 1:户外
} ReqInfraredScenarioMode_st;

/* 3.52 红外图像增强调整 */
typedef struct {
    ROE_U8 strength; // 0-100 增强强度
} ReqInfraredEnhanceImage_st;

/* 3.53 可见光饱和度调整 */
typedef struct {
    ROE_U8 saturation; // 0-100
} ReqAdjustCameraSaturation_st;

/* 3.54 可见光色调调整 */
typedef struct {
    ROE_U8 hue; // 0-100
} ReqAdjustCameraHue_st;

/* 3.55 视频输入画面冻结 */
typedef struct {
    ROE_U8 freeze; // 0:解冻 1:冻结
} ReqFreezeVideoInput_st;

/* 3.57 用户通用配置获取 */
typedef struct {
} ReqGetUserCommonConfig_st;

/* 3.58 用户通用配置修改 */
typedef struct {
    ROE_U8 saveFlag; // 0不保存 1保存
    ROE_S8 showDateTime; // -1不修改 0隐藏 1显示
    ROE_S16 standbyTimeout; // -1不修改 0永不待机 单位秒
    ROE_S16 shutdownTimeout; // -1不修改 0永不关机 单位秒
    ROE_S8 distanceUnit; // -1不修改 0米 1码
    ROE_S8 batteryLevel;
} ReqSetUserCommonConfig_st;

/* 3.59 用户媒体配置获取 */
typedef struct {
} ReqGetUserMediaConfig_st;

/* 3.60 用户媒体配置修改 */
typedef struct {
    ROE_U8 saveFlag; // 0不保存 1保存
    ROE_S8 burstCount; // -1不修改 0单拍 单位张
    ROE_S16 maxRecordDuration; // -1不修改 0无限制 单位秒
    ROE_S8 recoilPreRecordSwitch; // -1不修改 0关 1开
    ROE_S16 recoilPreRecordDuration; // -1不修改 0不录制 单位秒
    ROE_S8 micSwitch; // -1不修改 0关 1开
} ReqSetUserMediaConfig_st;

/* 3.61 分划板通用配置修改 */
typedef struct {
    ROE_U8 saveFlag; // 0不保存 1保存
    ROE_S8 showReticle; // -1不修改 0关 1开
    ROE_S8 rotateReticle; // -1不修改 0关 1开
    ROE_S8 brightnessBall;
    ROE_S8 ballisticSolve; // -1不修改 0关 1开
} ReqSetReticleCommonConfig_st;

/* 3.62 武器型号配置操作 */
typedef struct {
    ROE_U8 videoChannel; // 0主画面 1画中画
    ROE_U8 weaponIndex; // 武器型号索引 1-最大索引
    ROE_U8 opType; // 0查询 1设置当前武器型号 2重置武器配置
} ReqWeaponMarkConfigOperate_st;

/* 3.63 武器分划板类型设置 */
typedef struct {
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 reticleTypeIndex; // 分划板类型索引 1-最大索引
} ReqWeaponSetReticleStyle_st;

/* 3.64 武器分划板颜色设置 */
typedef struct {
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 reticleColorIndex; // 分划板颜色索引 1-最大索引
} ReqWeaponSetReticleColor_st;

/* 5.1.4 武器分划板亮度设置 */
typedef struct {
    ROE_U8 brightness; //分划板亮度 0-100
} ReqWeaponSetBrightness_st;

/* 3.65 武器默认射击距离设置 */
typedef struct {
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 defaultDistIndex; // 默认射击距离索引 1-最大索引
} ReqWeaponSetDefaultShootDist_st;

/* 3.66 武器射击距离操作 */
typedef struct {
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 distIndex; // 射击距离索引，新增时忽略
    ROE_U16 distValue; // 对应射击距离，查询/删除时忽略
    ROE_U8 opType; // 0查询 1新增 2删除 3修改
    ROE_U8 syncMoveReticle; // 0不移动 1移动
} ReqWeaponOperateShootDist_st;

/* 3.67 武器射击位置设置 */
typedef struct {
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 distIndex; // 射击距离索引
    ROE_S8 moveDir; // 0上 1下 2左 3右
} ReqWeaponSetShootPosition_st;

/* 3.68 武器射击零位设置 */
typedef struct {
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 distIndex; // 射击距离索引
    ROE_U8 zeroType; // 0相对 1绝对
} ReqWeaponSetShootZero_st;

/* 3.69 武器配置保存 */
typedef struct {
} ReqWeaponSaveConfig_st;

/* Header-only protocol requests. The common header is added by SendMsg4UiReq. */
typedef struct {
} ReqGetVideoOutputPara_st;

typedef struct {
} ReqGetVideoInputPara_st;

typedef struct {
} ReqGetVideoInputCameraPara_st;

typedef struct {
} ReqGetVideoInputLowLightPara_st;

typedef struct {
} ReqGetVideoInputInfraredPara_st;

typedef struct {
} ReqGetVideoInputRemotePara_st;

typedef struct {
    ROE_U8 exposureType; // 0:手动 1:自动
    ROE_U32 exposureTimeUs; // UINT32_MAX:自动；手动曝光时单位为微秒
    ROE_U8 manualIspDigitalGain; // 0-100，UINT8_MAX:自动
    ROE_U8 manualSensorDigitalGain; // 0-100，UINT8_MAX:自动
    ROE_U8 manualSensorAnalogGain; // 0-100，UINT8_MAX:自动
} ReqAdjustCameraExposure_st;

typedef struct {
} ReqGetAudioPara_st;

typedef struct {
} ReqCaptureMediaFile_st;

typedef struct {
    ROE_U8 recordSwitch; // 0:关闭 1:开启
} ReqRecordMediaFile_st;

typedef struct {
} ReqGetPeripheralUsbPara_st;

typedef struct {
} ReqGetPeripheralNetworkPara_st;

typedef struct {
} ReqGetPeripheralCameraModulePara_st;

typedef struct {
} ReqGetPeripheralLowLightModulePara_st;

typedef struct {
} ReqGetPeripheralInfraredModulePara_st;

typedef struct {
} ReqGetPeripheralRemotedVideoModulePara_st;

typedef struct {
} ReqGetPeripheralCompassPara_st;

typedef struct {
} ReqGetPeripheralGnssPara_st;

typedef struct {
} ReqGetPeripheralRangeFinderPara_st;

typedef struct {
} ReqGetPeripheralPanTiltPara_st;

typedef struct {
    ROE_U8 operationType; // 1:功能 2:光标 3:坏点
    ROE_U8 functionOperation; // 0:关闭 1:开启
    ROE_U8 cursorOperation; // 0:居中 1:上 2:下 3:左 4:右
    ROE_U8 badPixelOperation; // 0:取消 1:去除
} ReqInfraredManualRemoveBadPixel_st;

typedef struct {
    ROE_U8 operationType; // 0:快门 1:背景 2:虚焦 3:渐晕
} ReqInfraredSdNuc_st;

#pragma pack(pop)

ROE_S32 SendMsg4UiRegisterReq(ROE_S32 msgQueId, ReqRegister_st * registerType);

ROE_S32 SendMsg4UiExitMenuReq(ROE_S32 msgQueId);

ROE_S32 SendMsg4UiTimeReq(ROE_S32 msgQueId, ReqSetSystemTime_st * setTime);

ROE_S32 SendMsg4UiObserveModeReq(ROE_S32 msgQueId, ReqAdjustObserveMode_st * setObserveMode);

ROE_S32 SendMsg4UiPipObserveModeReq(ROE_S32 msgQueId, ReqAdjustPipObserveMode_st * setObserveMode);

ROE_S32 SendMsg4UiDayNightReq(ROE_S32 msgQueId, ReqAdjustDayNight_st * setDayNight);

ROE_S32 SendMsg4UiRecognitionSwitchReq(ROE_S32 msgQueId, ReqAdjustRecognitionSwitch_st * setRecognitionSwitch);

ROE_S32 SendMsg4UiCameraBrightnessReq(ROE_S32 msgQueId, ReqAdjustCameraBrightness_st * cameraBrightness);

ROE_S32 SendMsg4UiInfraredBrightnessReq(ROE_S32 msgQueId, ReqAdjustInfraredBrightness_st * infraredBrightness);

ROE_S32 SendMsg4UiCameraContrastReq(ROE_S32 msgQueId, ReqAdjustCameraContrast_st * cameraContrast);

ROE_S32 SendMsg4UiInfraredContrastReq(ROE_S32 msgQueId, ReqAdjustInfraredContrast_st * infraredContrast);

ROE_S32 SendMsg4UiFogSwitchReq(ROE_S32 msgQueId, ReqAdjustFogSwitch_st * fogSwitch);

ROE_S32 SendMsg4UiFogIntensityReq(ROE_S32 msgQueId, ReqAdjustFogIntensity_st * fogIntensity);

ROE_S32 SendMsg4UiCompassSwitchReq(ROE_S32 msgQueId, ReqAdjustCompassSwitch_st * compassSwitch);

ROE_S32 SendMsg4UiStartCompassCalibrationReq(ROE_S32 msgQueId, ReqStartCompassCalibration_st * compassCalibration);

ROE_S32 SendMsg4UiStopCompassCalibrationReq(ROE_S32 msgQueId, ReqStopCompassCalibration_st * compassCalibration);

ROE_S32 SendMsg4UiSetCompassDeclinationReq(ROE_S32 msgQueId, ReqSetCompassDeclination_st * setCompassDeclination);

ROE_S32 SendMsg4UiSaveCompassConfigReq(ROE_S32 msgQueId);

ROE_S32 SendMsg4UiGnssSwitchReq(ROE_S32 msgQueId, ReqAdjustGnssSwitch_st * gnssSwitch);

ROE_S32 SendMsg4UiGnssSystemReq(ROE_S32 msgQueId, ReqAdjustGnssSystem_st * gnssSystem);

ROE_S32 SendMsg4UiCoordinateSystemReq(ROE_S32 msgQueId, ReqAdjustCoordinateSystem_st * coordinateSystem);

ROE_S32 SendMsg4UiRestoreFactoryReq(ROE_S32 msgQueId);

ROE_S32 SendMsg4UiFormatDiskReq(ROE_S32 msgQueId);

ROE_S32 SendMsg4UiWifiSwitchReq(ROE_S32 msgQueId, ReqAdjustWifiSwitch_st * wifiSwitch);

ROE_S32 SendMsg4UiGetWifiInfoReq(ROE_S32 msgQueId);

ROE_S32 SendMsg4UiGetAppVersionReq(ROE_S32 msgQueId);

ROE_S32 SendMsg4UiInfraredPseudoColorReq(ROE_S32 msgQueId, ReqAdjustInfraredPseudoColor_st * infraredPseudoColor);

ROE_S32 SendMsg4UiGetMediaFileListReq(ROE_S32 msgQueId, ReqGetMediaFileList_st * getMediaFileList);

ROE_S32 SendMsg4UiDelMediaFileReq(ROE_S32 msgQueId, ROE_S8 * filename);

ROE_S32 SendMsg4UiPlayMediaFileReq(ROE_S32 msgQueId, ROE_S8 * filename);

ROE_S32 SendMsg4UiPlayPriorOrNextMediaFileReq(ROE_S32 msgQueId, ROE_U8 direction);

ROE_S32 SendMsg4UiExitMediaPlayReq(ROE_S32 msgQueId);

ROE_S32 SendMsg4UiRangeFinderSwitchReq(ROE_S32 msgQueId, ReqAdjustRangefinderSwitch_st * rangefinderSwitch);

ROE_S32 SendMsg4UiRangeFrequencyReq(ROE_S32 msgQueId, ReqAdjustRangeFrequency_st * rangeFrequency);

ROE_S32 SendMsg4UiRangeDurationReq(ROE_S32 msgQueId, ReqAdjustRangeDuration_st * rangeDuration);

ROE_S32 SendMsg4UiPipSwitchReq(ROE_S32 msgQueId, ReqAdjustPipSwitch_st * pipSwitch);

ROE_S32 SendMsg4UiExtendDisplaySwitchReq(ROE_S32 msgQueId, ReqAdjustExtendDisplaySwitch_st * extendDisplaySwitch);

ROE_S32 SendMsg4UiOledBrightnessReq(ROE_S32 msgQueId, ReqAdjustOledBrightness_st * oledBrightness);

ROE_S32 SendMsg4UiOledContrastReq(ROE_S32 msgQueId, ReqAdjustOledContrast_st * oledContrast);

ROE_S32 SendMsg4UiVideoZoomReq(ROE_S32 msgQueId, ReqAdjustVideoZoom_st * adjustVideoZoom);

ROE_S32 SendMsg4UiShutdownReq(ROE_S32 msgQueId);

ROE_S32 SendMsg4UiExitDialogBoxReq(ROE_S32 msgQueId);

ROE_S32 SendMsg4UiExitPlaybackListReq(ROE_S32 msgQueId);

ROE_S32 SendMsg4UiPanTiltMoveControlReq(ROE_S32 msgQueId, ReqPanTiltMoveControl_st * panTiltMoveControl);

ROE_S32 SendMsg4UiPanTiltSpeedControlReq(ROE_S32 msgQueId, ReqPanTiltSpeedControl_st * panTiltSpeedControl);

ROE_S32 SendMsg4UiInfraredSetBadPixelThresholdReq(ROE_S32 msgQueId,
                                                  ReqInfraredSetBadPixelThreshold_st * infraredSetBadPixelThreshold);

ROE_S32 SendMsg4UiInfraredBadPixelOperateReq(ROE_S32 msgQueId, ReqInfraredBadPixelOperate_st * infraredBadPixelOperate);

ROE_S32 SendMsg4UiSaveLanguageConfig(ROE_S32 msgQueId, ReqSaveLanguageConfig_st * saveLanguageConfig);

ROE_S32 SendMsg4UiInfraredHotPixelRepairReq(ROE_S32 msgQueId, ReqInfraredHotPixelRepair_st * infraredHotPixelRepair);

ROE_S32 SendMsg4UiInfraredHotspotTrackingSwitchReq(ROE_S32 msgQueId,
                                                   ReqInfraredHotspotTrackingSwitch_st * infraredHotspotTrackingSwitch);

ROE_S32 SendMsg4UiInfraredScenarioModeReq(ROE_S32 msgQueId, ReqInfraredScenarioMode_st * infraredScenarioMode);

ROE_S32 SendMsg4UiInfraredEnhanceImageReq(ROE_S32 msgQueId, ReqInfraredEnhanceImage_st * infraredEnhanceImage);

ROE_S32 SendMsg4UiCameraSaturationReq(ROE_S32 msgQueId, ReqAdjustCameraSaturation_st * cameraSaturation);

ROE_S32 SendMsg4UiCameraHueReq(ROE_S32 msgQueId, ReqAdjustCameraHue_st * cameraHue);

ROE_S32 SendMsg4UiFreezeVideoInputReq(ROE_S32 msgQueId, ReqFreezeVideoInput_st * freezeVideoInput);

ROE_S32 SendMsg4UiGetUserCommonConfigReq(ROE_S32 msgQueId);

ROE_S32 SendMsg4UiSetUserCommonConfigReq(ROE_S32 msgQueId, ReqSetUserCommonConfig_st * setUserCommonConfig);

ROE_S32 SendMsg4UiGetUserMediaConfigReq(ROE_S32 msgQueId);

ROE_S32 SendMsg4UiSetUserMediaConfigReq(ROE_S32 msgQueId, ReqSetUserMediaConfig_st * setUserMediaConfig);

ROE_S32 SendMsg4UiSetReticuleCommonConfigReq(ROE_S32 msgQueId, ReqSetReticleCommonConfig_st * setReticleCommonConfig);

ROE_S32 SendMsg4UiWeaponMarkConfigOperateReq(ROE_S32 msgQueId, ReqWeaponMarkConfigOperate_st * weaponMarkConfigOperate);

ROE_S32 SendMsg4UiWeaponSetReticleStyleReq(ROE_S32 msgQueId, ReqWeaponSetReticleStyle_st * weaponSetReticleStyle);

ROE_S32 SendMsg4UiWeaponSetReticleColorReq(ROE_S32 msgQueId, ReqWeaponSetReticleColor_st * weaponSetReticleColor);

ROE_S32 SendMsg4UiWeaponSetDefaltShootDistReq(ROE_S32 msgQueId,
                                              ReqWeaponSetDefaultShootDist_st * weaponSetDefaltShootDist);

ROE_S32 SendMsg4UiWeqponSetBrightnessReq(ROE_S32 msgQueId, ReqWeaponSetBrightness_st * weaponSetBrightness);

ROE_S32 SendMsg4UiWeaponOperateShootDistReq(ROE_S32 msgQueId, ReqWeaponOperateShootDist_st * weaponSetShootDist);

ROE_S32 SendMsg4UiWeaponSetShootPositionReq(ROE_S32 msgQueId, ReqWeaponSetShootPosition_st * weaponSetShootPosition);

ROE_S32 SendMsg4UiWeaponSetShootZeroReq(ROE_S32 msgQueId, ReqWeaponSetShootZero_st * weaponSetShootZero);

ROE_S32 SendMsg4UiWeaponSaveConfigReq(ROE_S32 msgQueId);

ROE_S32 SendMsg4UiGetVideoOutputParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiGetVideoInputParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiGetVideoInputCameraParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiGetVideoInputLowLightParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiGetVideoInputInfraredParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiGetVideoInputRemoteParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiCameraExposureReq(ROE_S32 msgQueId, ReqAdjustCameraExposure_st * cameraExposure);
ROE_S32 SendMsg4UiGetAudioParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiCaptureMediaFileReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiRecordMediaFileReq(ROE_S32 msgQueId, ReqRecordMediaFile_st * recordMediaFile);
ROE_S32 SendMsg4UiGetPeripheralUsbParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiGetPeripheralNetworkParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiGetPeripheralCameraModuleParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiGetPeripheralLowLightModuleParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiGetPeripheralInfraredModuleParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiGetPeripheralRemotedVideoModuleParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiGetPeripheralCompassParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiGetPeripheralGnssParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiGetPeripheralRangeFinderParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiGetPeripheralPanTiltParaReq(ROE_S32 msgQueId);
ROE_S32 SendMsg4UiInfraredManualRemoveBadPixelReq(
    ROE_S32 msgQueId,
    ReqInfraredManualRemoveBadPixel_st * manualRemoveBadPixel);
ROE_S32 SendMsg4UiInfraredSdNucReq(ROE_S32 msgQueId, ReqInfraredSdNuc_st * infraredSdNuc);
#endif //ZKSL_75_6LC_IPCMSGQUE4UISNDREQUEST_H
