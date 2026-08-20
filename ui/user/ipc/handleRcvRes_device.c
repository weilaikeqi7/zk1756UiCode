//
// Created by jinxing on 2026/3/2.
//

#include "ipcMsgQue4UiRcvRes.h"
#include "handleRcvRes.h"
#include "play_handle.h"

ROE_S32 handleParseAdjustRangeFinderSwitchStatusMsg(ROE_U8 * msgData)
{
    RspAdjustRangefinderSwitch_st * result = (RspAdjustRangefinderSwitch_st *)msgData;
    /* 处理测距机开关调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustRangeFrequencyMsg(ROE_U8 * msgData)
{
    RspAdjustRangeFrequency_st * result = (RspAdjustRangeFrequency_st *)msgData;
    /* 处理测距频率调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustRangeTimeDurationMsg(ROE_U8 * msgData)
{
    RspAdjustRangeDuration_st * result = (RspAdjustRangeDuration_st *)msgData;
    /* 处理测距时长调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustPipSwitchStatusMsg(ROE_U8 * msgData)
{
    RspAdjustPipSwitch_st * result = (RspAdjustPipSwitch_st *)msgData;
    /* 处理画中画开关调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustExtendDisplaySwitchStatusMsg(ROE_U8 * msgData)
{
    RspAdjustExtendDisplaySwitch_st * result = (RspAdjustExtendDisplaySwitch_st *)msgData;
    /* 处理扩展显示开关调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustOledBrightnessMsg(ROE_U8 * msgData)
{
    RspAdjustOledBrightness_st * result = (RspAdjustOledBrightness_st *)msgData;
    /* 处理 OLED 显示亮度调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustOledContrastMsg(ROE_U8 * msgData)
{
    RspAdjustOledContrast_st * result = (RspAdjustOledContrast_st *)msgData;
    /* 处理 OLED 显示对比度调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustVideoZoomMsg(ROE_U8 * msgData)
{
    RspAdjustVideoZoom_st * result = (RspAdjustVideoZoom_st *)msgData;
    /* 处理视频变倍调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseShutdownMsg(ROE_U8 * msgData)
{
    RspShutdown_st * result = (RspShutdown_st *)msgData;
    /* 处理关机结果 */
    if(result->result == 0) {
        popup_stack_pop(&g_popup_stack);
    }
    return ROE_SUCCESS;
}

ROE_S32 handleParseExitDialogBoxMsg(ROE_U8 * msgData)
{
    RspExitDialogBox_st * result = (RspExitDialogBox_st *)msgData;
    /* 处理退出对话框结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseExitPlaybackMediaListMsg(ROE_U8 * msgData)
{
    RspExitPlaybackList_st * result = (RspExitPlaybackList_st *)msgData;
    /* 处理退出回放列表结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParsePanTiltMovingControlMsg(ROE_U8 * msgData)
{
    RspPanTiltMoveControl_st * result = (RspPanTiltMoveControl_st *)msgData;
    /* 处理云台运动状态控制结果 */
    // direction: 0 水平 1 垂直
    // ctrlType: 控制类型
    // result: 0 成功 非 0 失败
    return ROE_SUCCESS;
}

ROE_S32 handleParsePanTiltMovingSpeedControlMsg(ROE_U8 * msgData)
{
    RspPanTiltSpeedControl_st * result = (RspPanTiltSpeedControl_st *)msgData;
    /* 处理云台运动速率控制结果 */
    // direction: 方向
    // ctrlType: 控制类型
    // result: 0 成功 非 0 失败
    return ROE_SUCCESS;
}

ROE_S32 handleParseInfraredSetBadPixelThresholdMsg(ROE_U8 * msgData)
{
    RspInfraredSetBadPixelThreshold_st * result = (RspInfraredSetBadPixelThreshold_st *)msgData;
    /* 处理红外坏点校正阈值调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseInfraredBadPixelOperateMsg(ROE_U8 * msgData)
{
    RspInfraredBadPixelOperate_st * result = (RspInfraredBadPixelOperate_st *)msgData;
    /* 处理红外坏点校正操作结果 */
    // opType: 操作类型（回显）
    return ROE_SUCCESS;
}

ROE_S32 handleParseSaveLanguageConfigMsg(ROE_U8 * msgData)
{
    RspSaveLanguageConfig_st * result = (RspSaveLanguageConfig_st *)msgData;
    /* 处理保存当前语言配置结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseInfraredHotPixelRepairOperateMsg(ROE_U8 * msgData)
{
    RspInfraredHotPixelRepair_st * result = (RspInfraredHotPixelRepair_st *)msgData;
    /* 处理红外热像素修复操作结果 */
    // opType: 操作类型（回显）
    return ROE_SUCCESS;
}

ROE_S32 handleParseInfraredSwitchHotspotTrackingMsg(ROE_U8 * msgData)
{
    RspInfraredHotspotTrackingSwitch_st * result = (RspInfraredHotspotTrackingSwitch_st *)msgData;
    /* 处理红外热点追踪开关调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseInfraredAdjustScenarioModeMsg(ROE_U8 * msgData)
{
    RspInfraredScenarioMode_st * result = (RspInfraredScenarioMode_st *)msgData;
    /* 处理红外场景模式调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseInfraredEnhanceImageMsg(ROE_U8 * msgData)
{
    RspInfraredEnhanceImage_st * result = (RspInfraredEnhanceImage_st *)msgData;
    /* 处理红外图像增强调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustCameraSaturationMsg(ROE_U8 * msgData)
{
    RspAdjustCameraSaturation_st * result = (RspAdjustCameraSaturation_st *)msgData;
    /* 处理可见光饱和度调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseAdjustCameraHueMsg(ROE_U8 * msgData)
{
    RspAdjustCameraHue_st * result = (RspAdjustCameraHue_st *)msgData;
    /* 处理可见光色调调整结果 */
    return ROE_SUCCESS;
}

ROE_S32 handleParseFreezeVideoInputMsg(ROE_U8 * msgData)
{
    RspFreezeVideoInput_st * result = (RspFreezeVideoInput_st *)msgData;
    /* 处理视频输入画面冻结结果 */
    return ROE_SUCCESS;
}
