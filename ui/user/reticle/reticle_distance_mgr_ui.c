// reticle_distance_mgr_ui.c
#include "reticle_distance_mgr.h"
#include "ui.h"
#include "mainpage_event_handle.h"

void reticle_distance_mgr_refresh_calibration_ui(uint8_t idx)
{
    reticle_distance_entry_t * e = reticle_distance_mgr_entry(idx);
    if(!e) return;
    reticle_zero_pos_t * z = &e->zero;

    lv_label_set_text_fmt(
        ui_comp_get_child(ui_calibrationrow1, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
        "%d",
        (int)z->rel_x);
    lv_label_set_text_fmt(
        ui_comp_get_child(ui_calibrationrow2, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
        "%d",
        (int)z->rel_y);
    lv_label_set_text_fmt(
        ui_comp_get_child(ui_calibrationrow4, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
        "%.*f",
        g_zoom.precision,
        g_zoom.zoomValue);

    lv_obj_t * sw = ui_comp_get_child(ui_calibrationrow5, UI_COMP_ROWSWITCH_CONTPILL_SWITCH);
    if(g_freeze_switch) {
        lv_obj_add_state(sw, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(sw, LV_STATE_CHECKED);
    }
    lv_obj_send_event(sw, LV_EVENT_VALUE_CHANGED, NULL);
}

void reticle_distance_mgr_refresh_calib_x_ui(uint8_t idx)
{
    reticle_distance_entry_t * e = reticle_distance_mgr_entry(idx);
    if(!e) return;
    reticle_zero_pos_t * z = &e->zero;
    lv_label_set_text_fmt(
        ui_comp_get_child(ui_calibrationrow1, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
        "%d",
        (int)z->rel_x);
}

void reticle_distance_mgr_refresh_calib_y_ui(uint8_t idx)
{
    reticle_distance_entry_t * e = reticle_distance_mgr_entry(idx);
    if(!e) return;
    reticle_zero_pos_t * z = &e->zero;
    lv_label_set_text_fmt(
        ui_comp_get_child(ui_calibrationrow2, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
        "%d",
        (int)z->rel_y);
}

void reticle_distance_mgr_refresh_calib_zoom_ui(uint8_t idx)
{
    LV_UNUSED(idx);

    lv_label_set_text_fmt(
        ui_comp_get_child(ui_calibrationrow4, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
        "%.*f",
        g_zoom.precision,
        g_zoom.zoomValue);
}

void reticle_distance_mgr_refresh_calib_freeze_ui(uint8_t idx)
{
    LV_UNUSED(idx);

    lv_obj_t * sw = ui_comp_get_child(ui_calibrationrow5, UI_COMP_ROWSWITCH_CONTPILL_SWITCH);
    if(g_freeze_switch) {
        lv_obj_add_state(sw, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(sw, LV_STATE_CHECKED);
    }
    lv_obj_send_event(sw, LV_EVENT_VALUE_CHANGED, NULL);
}
