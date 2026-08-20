//
// Created by jinxing on 2026/3/2.
//

#include "ui.h"
#include "handleNotify.h"
#include "ipcMsgQue4UiRcvNotify.h"
#include "reticle_model.h"
#include "reticle_feature.h"
#include "mainpage_event_handle.h"

// 函数：将米 (Meter) 转换为码 (Yard)
float meterToYard(float meters)
{
    return meters * YARDS_PER_METER;
}

// 函数：将码 (Yard) 转换为米 (Meter)
float yardToMeter(float yards)
{
    return yards * METERS_PER_YARD;
}

static void refresh_global_zoom_ui(void)
{
    if(ui_labelzoom) {
        lv_label_set_text_fmt(ui_labelzoom, "%.*fX", g_app.video.zoom.precision, g_app.video.zoom.zoomValue);
    }

    if(ui_calibrationrow4) {
        lv_label_set_text_fmt(ui_comp_get_child(ui_calibrationrow4, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                              "%.*f",
                              g_app.video.zoom.precision,
                              g_app.video.zoom.zoomValue);
    }
}

static void refresh_global_freeze_ui(void)
{
    if(!ui_calibrationrow5) return;

    lv_obj_t * sw = ui_comp_get_child(ui_calibrationrow5, UI_COMP_ROWSWITCH_CONTPILL_SWITCH);
    if(g_freeze_switch) {
        lv_obj_add_state(sw, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(sw, LV_STATE_CHECKED);
    }
    lv_obj_send_event(sw, LV_EVENT_VALUE_CHANGED, NULL);
}

ROE_S32 handleRangeData(ROE_U8 * msgData)
{
    NotifyLaser_st * laser = (NotifyLaser_st *)msgData;
    if(laser->targetCount != 0) {
        if(g_app.ui.distance_unit_item.index == TARGET_UNIT_METER) {
            lv_label_set_text_fmt(ui_distancelabel, "%.1fM", laser->firstDistance);
            lv_label_set_text_fmt(ui_tempdistancelabel, "%.1fM", laser->firstDistance);
        } else {
            lv_label_set_text_fmt(ui_distancelabel, "%.1fY", meterToYard(laser->firstDistance));
            lv_label_set_text_fmt(ui_tempdistancelabel, "%.1fY", meterToYard(laser->firstDistance));
        }
    } else {
        if(g_app.ui.distance_unit_item.index == 0) {
            lv_label_set_text(ui_distancelabel, "----M");
            lv_label_set_text(ui_tempdistancelabel, "----M");
        } else {
            lv_label_set_text(ui_distancelabel, "----Y");
            lv_label_set_text(ui_tempdistancelabel, "----Y");
        }
    }
    return ROE_SUCCESS;
}

ROE_S32 handleRangeCountdownNotify(ROE_U8 * msgData)
{
    NotifyLaserCountDown_st * laserCountDown = (NotifyLaserCountDown_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleSnapStatusNotify(ROE_U8 * msgData)
{
    NotifyPhoto_st * photo = (NotifyPhoto_st *)msgData;
    if(photo->action == 1) {
        lv_obj_remove_flag(ui_snap, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(ui_snap, LV_OBJ_FLAG_HIDDEN);
    }
    return ROE_SUCCESS;
}

ROE_S32 handleRecordStatusNotify(ROE_U8 * msgData)
{
    static int hidden_flag = 0;
    NotifyRecord_st * record = (NotifyRecord_st *)msgData;
    if(record->countUpTime < 0) {
        lv_obj_add_flag(ui_contrecord, LV_OBJ_FLAG_HIDDEN);
        hidden_flag = 0;
    } else {
        int hours = record->countUpTime / 3600;
        int mins = record->countUpTime % 3600 / 60;
        int secs = record->countUpTime % 60;
        lv_label_set_text_fmt(ui_recordtimelabel, "%02d:%02d:%02d", hours, mins, secs);
        if(hidden_flag == 0) {
            lv_obj_remove_flag(ui_contrecord, LV_OBJ_FLAG_HIDDEN);
            hidden_flag = 1;
        }
    }
    return ROE_SUCCESS;
}

ROE_S32 handleZoomInfoNotify(ROE_U8 * msgData)
{
    NotifyZoom_st * zoom = (NotifyZoom_st *)msgData;
    g_app.video.zoom.zoomValue = zoom->zoomValue;
    g_app.video.zoom.precision = zoom->precision;
    refresh_global_zoom_ui();
    return ROE_SUCCESS;
}

ROE_S32 handleRangeFinderStatusNotify(ROE_U8 * msgData)
{
    NotifyLaserState_st * laserState = (NotifyLaserState_st *)msgData;
    if(laserState->state == 0) {
        lv_obj_set_state(ui_comp_get_child(ui_menu1row1, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
        lv_obj_send_event(
            ui_comp_get_child(ui_menu1row1, UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
            LV_EVENT_VALUE_CHANGED,
            NULL);
        lv_obj_set_state(
            ui_comp_get_child(ui_menu1row3, UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
            LV_STATE_CHECKED,
            false);
        lv_obj_send_event(
            ui_comp_get_child(ui_menu1row3, UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
            LV_EVENT_VALUE_CHANGED,
            NULL);
        lv_label_set_text(ui_comp_get_child(ui_rowlrf, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "OFF");
        g_app.video.rangefinder_on = OFF;
        lv_obj_add_flag(ui_contdistance, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_tempcontdistance, LV_OBJ_FLAG_HIDDEN);
    } else if(laserState->state == 1) {
        lv_obj_set_state(ui_comp_get_child(ui_menu1row1, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
        lv_obj_send_event(
            ui_comp_get_child(ui_menu1row1, UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
            LV_EVENT_VALUE_CHANGED,
            NULL);
        lv_label_set_text(ui_comp_get_child(ui_rowlrf, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "ON");
        g_app.video.rangefinder_on = ON;
        if(g_app.ui.distance_unit_item.index == 0) {
            lv_label_set_text(ui_distancelabel, "----M");
            lv_label_set_text(ui_tempdistancelabel, "----M");
        } else {
            lv_label_set_text(ui_distancelabel, "----Y");
            lv_label_set_text(ui_tempdistancelabel, "----Y");
        }
        lv_obj_remove_flag(ui_contdistance, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(ui_tempcontdistance, LV_OBJ_FLAG_HIDDEN);
    }
    return ROE_SUCCESS;
}

ROE_S32 handleVideoInputDeviceSwitchStatusNotify(ROE_U8 * msgData)
{
    NotifyVideoInput_st * videoInput = (NotifyVideoInput_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleVideoInputDeviceAuxiliaryLightingNotify(ROE_U8 * msgData)
{
    NotifyLight_st * light = (NotifyLight_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleVideoInputDeviceFreezingNotify(ROE_U8 * msgData)
{
    NotifyFreeze_st * freeze = (NotifyFreeze_st *)msgData;
    g_app.video.freeze_on = freeze->state;
    refresh_global_freeze_ui();

    return ROE_SUCCESS;
}

ROE_S32 handleVideoInputDeviceMirrorFlipNotify(ROE_U8 * msgData)
{
    NotifyMirror_st * mirror = (NotifyMirror_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleVideoInputDeviceRotatingNotify(ROE_U8 * msgData)
{
    NotifyRotate_st * rotate = (NotifyRotate_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleMediaFilePlayOperateNotify(ROE_U8 * msgData)
{
    NotifyMediaPlay_st * mediaPlay = (NotifyMediaPlay_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleOsdShowHideOperateNotify(ROE_U8 * msgData)
{
    NotifyOsd_st * osdShowHide = (NotifyOsd_st *)msgData;
    g_app.video.osd.all = osdShowHide->all;
    g_app.video.osd.datetime = osdShowHide->datetime;
    if(g_app.video.osd.all == 1) {
        lv_screen_load(ui_MainPage);
    } else if(g_app.video.osd.all == 0) {
        lv_screen_load(ui_Temp);
    }
    if(g_app.video.osd.datetime == 1) {
        lv_obj_remove_flag(ui_contitemdate, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_flag(ui_contitemtime, LV_OBJ_FLAG_HIDDEN);
    } else if(g_app.video.osd.datetime == 0) {
        lv_obj_add_flag(ui_contitemdate, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_contitemtime, LV_OBJ_FLAG_HIDDEN);
    }
    return ROE_SUCCESS;
}

ROE_S32 handlePeripheralsPowerStatusNotify(ROE_U8 * msgData)
{
    NotifyDeviceSwitch_st * deviceSwitch = (NotifyDeviceSwitch_st *)msgData;
    g_app.video.dev_switch.bluetooth = deviceSwitch->bluetooth;
    g_app.video.dev_switch.wifi = deviceSwitch->wifi;
    LV_LOG_USER("g_app.video.dev_switch.bluetooth:%d, g_app.video.dev_switch.wifi:%d",
                deviceSwitch->bluetooth,
                g_app.video.dev_switch.wifi);
    if(g_app.video.dev_switch.wifi == OFF) {
        lv_obj_set_state(ui_comp_get_child(ui_rowwifi, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
        lv_obj_send_event(
            ui_comp_get_child(ui_rowwifi, UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
            LV_EVENT_VALUE_CHANGED,
            NULL);
        lv_obj_set_style_image_recolor_opa(ui_imgwifi, LV_OPA_30, LV_PART_MAIN);
    } else {
        lv_obj_set_state(ui_comp_get_child(ui_rowwifi, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
        lv_obj_send_event(
            ui_comp_get_child(ui_rowwifi, UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
            LV_EVENT_VALUE_CHANGED,
            NULL);
        lv_obj_set_style_image_recolor_opa(ui_imgwifi, LV_OPA_0, LV_PART_MAIN);
    }
    return ROE_SUCCESS;
}

ROE_S32 handleInfraredPseudoColorModeNotify(ROE_U8 * msgData)
{
    NotifyPseudoColor_st * pseudoColor = (NotifyPseudoColor_st *)msgData;
    g_app.video.mode = pseudoColor->mode;
    switch(g_app.video.mode) {
    case 0:
        lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "White Hot");
        lv_image_set_src(ui_imgpolarity, IMAGES_PATH "HOT-W.png");
        break;
    case 1:
        lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "Black Hot");
        lv_image_set_src(ui_imgpolarity, IMAGES_PATH "HOT-B.png");
        break;
    case 2:
        lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "Iron Red");
        lv_image_set_src(ui_imgpolarity, IMAGES_PATH "HOT-I.png");
        break;
    case 3:
        lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "Desert Yellow");
        lv_image_set_src(ui_imgpolarity, IMAGES_PATH "HOT-Y.png");
        break;
    case 4:
        lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "Green Hot");
        lv_image_set_src(ui_imgpolarity, IMAGES_PATH "HOT-G.png");
        break;
    case 5:
        lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "Red Hot");
        lv_image_set_src(ui_imgpolarity, IMAGES_PATH "HOT-R.png");
        break;
    case 6:
        lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "Highlight");
        lv_image_set_src(ui_imgpolarity, IMAGES_PATH "HOT-H.png");
        break;
    case 7:
        lv_label_set_text(ui_comp_get_child(ui_rowimagemode, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), "Outline");
        lv_image_set_src(ui_imgpolarity, IMAGES_PATH "HOT-O.png");
        break;
    default:
        break;
    }
    return ROE_SUCCESS;
}