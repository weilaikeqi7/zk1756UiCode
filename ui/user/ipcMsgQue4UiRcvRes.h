//
// Created by jinxing on 2026/2/11.
//

#ifndef ZKSL_75_6LC_IPCMSGQUE4UIRCVRES_H
#define ZKSL_75_6LC_IPCMSGQUE4UIRCVRES_H

#include "roeTypes.h"
#include "msg.h"
#include "ipcMsgQue4UiTypeCommon.h"

#pragma pack(push, 1)

/* 3.1 注册/注销 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspRegister_st;

/* 3.2 退出菜单模式 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspExitMenu_st;

/* 3.3 设置系统时间 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspSetSystemTime_st;

/* 3.4 观察模式调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustObserveMode_st;

/* 3.5 日夜模式切换 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustDayNight_st;

/* 3.6 识别开关调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustRecognitionSwitch_st;

/* 3.7 可见光亮度调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustCameraBrightness_st;

/* 3.8 红外亮度调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustInfraredBrightness_st;

/* 3.9 可见光对比度调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustCameraContrast_st;

/* 3.10 红外对比度调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustInfraredContrast_st;

/* 3.11 可见光透雾开关调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustFogSwitch_st;

/* 3.12 可见光透雾强度调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustFogIntensity_st;

/* 3.13 电子罗盘开关调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustCompassSwitch_st;

/* 3.14 电子罗盘开始校准 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspStartCompassCalibration_st;

/* 3.15 电子罗盘停止校准 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspStopCompassCalibration_st;

/* 3.16 电子罗盘设置磁偏角 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspSetCompassDeclination_st;

/* 3.17 电子罗盘保存配置 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspSaveCompassConfig_st;

/* 3.18 卫星定位开关调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustGnssSwitch_st;

/* 3.19 卫星定位系统调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustGnssSystem_st;

/* 3.20 大地坐标系统调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustCoordinateSystem_st;

/* 3.21 恢复出厂设置 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspRestoreFactory_st;

/* 3.22 磁盘格式化 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspFormatDisk_st;

/* 3.23 WIFI开关调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustWifiSwitch_st;

/* 3.24 WIFI信息获取 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspGetWifiInfo_st;

/* 3.25 版本信息获取 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 verLen; // 版本字符串长度
    ROE_U8 version[]; // 版本字符序列
} RspGetAppVersion_st;

/* 3.26 红外伪彩模式调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustInfraredPseudoColor_st;

/* 3.27 获取媒体文件列表 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U32 totalCount; // 符合条件的总文件数量
    ROE_U8 fileCount; // 本次返回文件实际数量 (0-15)
    /* 后面紧跟 fileCount 个媒体文件信息，每个信息为变长结构 MediaFileInfo_st */
    ROE_U8 fileData[];
} RspGetMediaFileList_st;

/* 辅助结构：媒体文件信息（用于解析 RspGetMediaFileList_st/fileData） */
typedef struct {
    ROE_U8 type; // 0:照片 1:视频 2:音频
    ROE_S64 size;
    ROE_S32 duration;
    ROE_U32 createTime;
    ROE_U8 nameLen;
    ROE_U8 name[]; // 文件名，长度为nameLen
} MediaFileInfo_st;

/* 3.28 媒体文件列表翻页 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 fileCount; // 本次返回文件实际数量 (0-15)
    /* 后面紧跟 fileCount 个媒体文件信息 */
    ROE_U8 fileData[];
} RspGetMediaFileListPage_st;

/* 3.29 媒体文件删除 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 fileCount; // 本次返回文件实际数量 (0-15)
    /* 后面紧跟 fileCount 个媒体文件信息 */
    ROE_U8 fileData[];
} RspDelMediaFile_st;

/* 3.30 媒体文件播放 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspPlayMediaFile_st;

/* 3.31 播放上一个/下一个媒体文件 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspPlayPriorOrNextMediaFile_st;

/* 3.32 退出媒体文件播放 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspExitMediaPlay_st;

/* 3.33 测距机开关调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustRangefinderSwitch_st;

/* 3.34 测距频率调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustRangeFrequency_st;

/* 3.35 测距时长调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustRangeDuration_st;

/* 3.36 画中画开关调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustPipSwitch_st;

/* 3.37 扩展显示开关调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustExtendDisplaySwitch_st;

/* 3.38 OLED显示亮度调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustOledBrightness_st;

/* 3.39 OLED显示对比度调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustOledContrast_st;

/* 3.40 视频变倍调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustVideoZoom_st;

/* 3.41 关机 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspShutdown_st;

/* 3.42 退出对话框 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspExitDialogBox_st;

/* 3.43 退出回放列表 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspExitPlaybackList_st;

/* 3.44 云台运动状态控制 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 direction; // 0:水平 1:垂直
    ROE_U8 ctrlType; // 同请求
    ROE_U8 result; // 0成功 非0失败
} RspPanTiltMoveControl_st;

/* 3.45 云台运动速率控制 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 direction;
    ROE_U8 ctrlType;
    ROE_U8 result;
} RspPanTiltSpeedControl_st;

/* 3.46 红外坏点校正阈值调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspInfraredSetBadPixelThreshold_st;

/* 3.47 红外坏点校正操作 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 opType; // 操作类型（回显）
} RspInfraredBadPixelOperate_st;

/* 3.48 保存当前语言配置 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspSaveLanguageConfig_st;

/* 3.49 红外热像素修复操作 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 opType; // 操作类型（回显）
} RspInfraredHotPixelRepair_st;

/* 3.50 红外热点追踪开关调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspInfraredHotspotTrackingSwitch_st;

/* 3.51 红外场景模式调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspInfraredScenarioMode_st;

/* 3.52 红外图像增强调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspInfraredEnhanceImage_st;

/* 3.53 可见光饱和度调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustCameraSaturation_st;

/* 3.54 可见光色调调整 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspAdjustCameraHue_st;

/* 3.55 视频输入画面冻结 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspFreezeVideoInput_st;

/* 3.56 测距 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_S8 result; // 0成功 -1测距机未开 -2正在测距时开始/未停止 -3操作失败
} RspSwitchRange_st;

/* 3.57 用户通用配置获取 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 showDateTime; // 0隐藏 1显示
    ROE_U16 standbyTimeout; // 待机时长，0永不待机，单位秒
    ROE_U16 shutdownTimeout; // 关机时长，0永不关机，单位秒
    ROE_U8 distanceUnit; // 0米 1码
} RspGetUserCommonConfig_st;

/* 3.58 用户通用配置修改 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 showDateTime; // 当前值
    ROE_U16 standbyTimeout;
    ROE_U16 shutdownTimeout;
    ROE_U8 distanceUnit;
} RspSetUserCommonConfig_st;

/* 3.59 用户媒体配置获取 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 burstCount; // 连拍数量，0单拍
    ROE_U16 maxRecordDuration; // 单个文件最大录制时长，0无限制
    ROE_U8 recoilPreRecordSwitch; // 后坐力激活视频预录开关，0关 1开
    ROE_U16 recoilPreRecordDuration; // 后坐力激活视频预录时长，0不录制
    ROE_U8 micSwitch; // 麦克风开关，0关 1开
} RspGetUserMediaConfig_st;

/* 3.60 用户媒体配置修改 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 burstCount;
    ROE_U16 maxRecordDuration;
    ROE_U8 recoilPreRecordSwitch;
    ROE_U16 recoilPreRecordDuration;
    ROE_U8 micSwitch;
} RspSetUserMediaConfig_st;

/* 3.61 分划板通用配置修改 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 currentShowReticle;
    ROE_U8 currentRotateReticle;
    ROE_U8 currentBallisticSolve;
} RspSetReticleCommonConfig_st;

/* 3.62 武器型号配置操作 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 videoChannel;
    ROE_U8 defaultWeaponIndex; // 默认武器型号
    ROE_U8 weaponIndex; // 当前武器型号
    ROE_U8 reticleTypeIndex; // 分划板类型索引
    ROE_U8 reticleColorIndex; // 分划板颜色索引
    ROE_U8 shootDistanceCount; // 射击距离数量 1-20
    ROE_U8 defaultDistIndex; // 默认射击距离索引
    ROE_U16 shootDistances[20]; // 射击距离值，有效数量为 shootDistanceCount
} RspWeaponMarkConfigOperate_st;

/* 3.63 武器分划板类型设置 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 reticleTypeIndex;
} RspWeaponSetReticleStyle_st;

/* 3.64 武器分划板颜色设置 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 reticleColorIndex;
} RspWeaponSetReticleColor_st;

/* 3.65 武器默认射击距离设置 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 defaultDistIndex;
    ROE_U16 defaultDist;
    ROE_S16 defaultAbsX;
    ROE_S16 defaultAbsY;
    ROE_S16 defaultRelX;
    ROE_S16 defaultRelY;
} RspWeaponSetDefaultShootDist_st;

/* 3.66 武器射击距离操作 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 distIndex; // 操作后有效的射击距离索引
    ROE_U16 distValue;
    ROE_S16 absX;
    ROE_S16 absY;
    ROE_S16 relX;
    ROE_S16 relY;
    ROE_U8 shootDistanceCount; // 当前射击距离数量
    ROE_U8 defaultDistIndex; // 当前默认射击距离索引
    ROE_U16 shootDistances[20]; // 所有射击距离值
} RspWeaponOperateShootDist_st;

/* 3.67 武器射击位置设置 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 distIndex;
    ROE_U16 distValue;
    ROE_S16 absX;
    ROE_S16 absY;
    ROE_S16 relX;
    ROE_S16 relY;
} RspWeaponSetShootPosition_st;

/* 3.68 武器射击零位设置 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
    ROE_U8 videoChannel;
    ROE_U8 weaponIndex;
    ROE_U8 distIndex;
    ROE_U16 distValue;
    ROE_S16 absX;
    ROE_S16 absY;
    ROE_S16 relX;
    ROE_S16 relY;
} RspWeaponSetShootZero_st;

/* 3.69 武器配置保存 */
typedef struct {
    MsgQueHeader4Ui_st head;
    ROE_U8 result;
} RspWeaponSaveConfig_st;

#pragma pack(pop)

ROE_S32 ParseResMsg(ROE_SL msgType, RoeIpcMsgQueRawData_st * rawData);
#endif //ZKSL_75_6LC_IPCMSGQUE4UIRCVRES_H
