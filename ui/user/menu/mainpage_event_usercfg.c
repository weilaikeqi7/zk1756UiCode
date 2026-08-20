//
// Created by jinxing on 2026/1/8.
//

#include "reticle_feature.h"
#include "mainpage_event_handle.h"
#include "mainpage_event_internal.h"
#include <stdlib.h>
#include <string.h>
#include "handleNotify.h"
#include "ipcMsgQue4UiSndRequest.h"
#include "reticle_model.h"

void ui_rowswitch_set_checked(lv_obj_t * row, ROE_U8 checked)
{
    if(row == NULL) return;

    lv_obj_t * sw = ui_comp_get_child(row, UI_COMP_ROWSWITCH_CONTPILL_SWITCH);
    if(sw == NULL) return;

    if(checked) {
        lv_obj_add_state(sw, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(sw, LV_STATE_CHECKED);
    }

    lv_obj_send_event(sw, LV_EVENT_VALUE_CHANGED, NULL);
}

int standby_timeout_sec_to_ui_min(ROE_U16 sec)
{
    if(sec == 0) {
        return (StandbyTime > 0) ? StandbyTime : 5;
    }

    {
        int min = (sec + 59) / 60;
        if(min < 1) min = 1;
        if(min > 60) min = 60;
        return min;
    }
}

ROE_U16 ui_min_to_standby_timeout_sec(int min)
{
    if(min <= 0) min = 1;
    return (ROE_U16)(min * 60);
}

void send_user_common_config_partial(ROE_S8 showDateTime,
                                     ROE_S16 standbyTimeout,
                                     ROE_S16 shutdownTimeout,
                                     ROE_S8 distanceUnit,
                                     ROE_U8 saveFlag)
{
    ReqSetUserCommonConfig_st req;

    req.saveFlag = saveFlag;
    req.showDateTime = showDateTime;
    req.standbyTimeout = standbyTimeout;
    req.shutdownTimeout = shutdownTimeout;
    req.distanceUnit = distanceUnit;

    SendMsg4UiSetUserCommonConfigReq(global_parameters.sendMsgQueId, &req);
}

void send_user_media_config_partial(ROE_S8 burstCount,
                                    ROE_S16 maxRecordDuration,
                                    ROE_S8 recoilPreRecordSwitch,
                                    ROE_S16 recoilPreRecordDuration,
                                    ROE_S8 micSwitch,
                                    ROE_U8 saveFlag)
{
    ReqSetUserMediaConfig_st req;

    req.saveFlag = saveFlag;
    req.burstCount = burstCount;
    req.maxRecordDuration = maxRecordDuration;
    req.recoilPreRecordSwitch = recoilPreRecordSwitch;
    req.recoilPreRecordDuration = recoilPreRecordDuration;
    req.micSwitch = micSwitch;

    SendMsg4UiSetUserMediaConfigReq(global_parameters.sendMsgQueId, &req);
}

void ui_apply_user_common_config(void)
{
    DistanceUnit.index = (userCommonConfig.distanceUnit < DistanceUnit.count) ? userCommonConfig.distanceUnit : 0;

    g_osd.datetime = userCommonConfig.showDateTime;

    if(userCommonConfig.showDateTime) {
        if(ui_contitemdate) lv_obj_remove_flag(ui_contitemdate, LV_OBJ_FLAG_HIDDEN);
        if(ui_contitemtime) lv_obj_remove_flag(ui_contitemtime, LV_OBJ_FLAG_HIDDEN);
    } else {
        if(ui_contitemdate) lv_obj_add_flag(ui_contitemdate, LV_OBJ_FLAG_HIDDEN);
        if(ui_contitemtime) lv_obj_add_flag(ui_contitemtime, LV_OBJ_FLAG_HIDDEN);
    }

    if(ui_menu1row4) {
        lv_label_set_text(ui_comp_get_child(ui_menu1row4, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                          DistanceUnit.des[DistanceUnit.index]);
    }

    if(ui_distancelabel) {
        switch_distance_label_unit(ui_distancelabel, (target_unit_t)DistanceUnit.index);
    }
    if(ui_tempdistancelabel) {
        switch_distance_label_unit(ui_tempdistancelabel, (target_unit_t)DistanceUnit.index);
    }

    g_standby_switch = (userCommonConfig.standbyTimeout == 0) ? OFF : ON;
    StandbyTime = standby_timeout_sec_to_ui_min(userCommonConfig.standbyTimeout);

    if(ui_rowswitch1) {
        ui_rowswitch_set_checked(ui_rowswitch1, g_standby_switch);
    }

    if(ui_rowitem1) {
        lv_label_set_text_fmt(ui_comp_get_child(ui_rowitem1, UI_COMP_ROWITEM1_LABEL),
                              "%d minutes",
                              StandbyTime);
    }
}

void ui_apply_user_media_config(void)
{
    if(ui_rowmic) {
        ui_rowswitch_set_checked(ui_rowmic, userMediaConfig.micSwitch);
    }

    if(ui_rowrav) {
        ui_rowswitch_set_checked(ui_rowrav, userMediaConfig.recoilPreRecordSwitch);
    }
}

void usercfg_set_show_datetime(ROE_U8 show)
{
    userCommonConfig.showDateTime = show ? 1 : 0;
    send_user_common_config_partial((ROE_S8)userCommonConfig.showDateTime, -1, -1, -1, 1);
}

void usercfg_set_shutdown_timeout_sec(ROE_U16 sec)
{
    userCommonConfig.shutdownTimeout = sec;
    send_user_common_config_partial(-1, -1, (ROE_S16)userCommonConfig.shutdownTimeout, -1, 1);
}

void usermedia_set_burst_count(ROE_U8 count)
{
    userMediaConfig.burstCount = count;
    send_user_media_config_partial((ROE_S8)userMediaConfig.burstCount, -1, -1, -1, -1, 1);
}

void usermedia_set_max_record_duration_sec(ROE_U16 sec)
{
    userMediaConfig.maxRecordDuration = sec;
    send_user_media_config_partial(-1, (ROE_S16)userMediaConfig.maxRecordDuration, -1, -1, -1, 1);
}

void usermedia_set_recoil_pre_record_duration_sec(ROE_U16 sec)
{
    userMediaConfig.recoilPreRecordDuration = sec;
    send_user_media_config_partial(-1, -1, -1, (ROE_S16)userMediaConfig.recoilPreRecordDuration, -1, 1);
}

void switch_distance_label_unit(lv_obj_t * label, target_unit_t target_unit)
{
    if(label == NULL) return;

    // 1. 获取当前标签文本
    const char * current_text = lv_label_get_text(label);
    if(current_text == NULL || strlen(current_text) == 0) return;

    // 2. 判断是否为无数据状态 ("----Y" 或 "----M")
    if(strstr(current_text, "----") != NULL) {
        if(target_unit == TARGET_UNIT_METER) {
            lv_label_set_text(label, "----M");
        } else {
            lv_label_set_text(label, "----Y");
        }
        return; // 处理完毕，直接返回
    }

    // 3. 处理有数据的情况
    int len = strlen(current_text);
    char current_unit_char = current_text[len - 1]; // 获取最后一个字符 (M 或 Y)

    // 提取当前数值 (atof 会自动停止在非数字字符处，比如 'Y' 或 'M')
    double current_val = atof(current_text);
    double new_val = current_val;

    // 4. 执行转换逻辑
    if(current_unit_char == 'Y' && target_unit == TARGET_UNIT_METER) {
        // 码转米
        new_val = current_val * METERS_PER_YARD;
        lv_label_set_text_fmt(label, "%.1fM", new_val); // 保留1位小数
    } else if(current_unit_char == 'M' && target_unit == TARGET_UNIT_YARD) {
        // 米转码
        new_val = current_val * YARDS_PER_METER;
        lv_label_set_text_fmt(label, "%.1fY", new_val); // 保留1位小数
    }
    // 如果当前单位和目标单位相同，则不需要做任何处理
}

void restore_declination(void)
{
    float v = magnetic.value;
    float absVal = (v < 0) ? -v : v;
    magnetic.symbol = (v < 0) ? '-' : '+';
    magnetic.num1 = (int)(absVal / 100) % 10;
    magnetic.num2 = (int)(absVal / 10) % 10;
    magnetic.num3 = (int)absVal % 10;
    magnetic.num4 = (int)(absVal * 10) % 10;
    magnetic.num5 = (int)(absVal * 100) % 10;
}