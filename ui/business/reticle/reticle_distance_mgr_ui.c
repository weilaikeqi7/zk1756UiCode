// reticle_distance_mgr_ui.c
#include "reticle_distance_mgr.h"
#include "ui.h"
#include "menu_event_registry.h"

static lv_obj_t * calibration_label(lv_obj_t * row)
{
    if(row == NULL) return NULL;
    return ui_comp_get_child(row, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1);
}

static lv_obj_t * calibration_freeze_switch(void)
{
    if(ui_calibrationrow5 == NULL) return NULL;
    return ui_comp_get_child(ui_calibrationrow5, UI_COMP_ROWSWITCH_CONTPILL_SWITCH);
}

void reticle_distance_mgr_refresh_calibration_ui(uint8_t idx)
{
    reticle_distance_entry_t * e = reticle_distance_mgr_entry(idx);
    if(!e) return;
    reticle_zero_pos_t * z = &e->zero;

    lv_obj_t * x_label = calibration_label(ui_calibrationrow1);
    lv_obj_t * y_label = calibration_label(ui_calibrationrow2);
    lv_obj_t * zoom_label = calibration_label(ui_calibrationrow4);
    if(x_label != NULL) lv_label_set_text_fmt(x_label, "%d", (int)z->rel_x);
    if(y_label != NULL) lv_label_set_text_fmt(y_label, "%d", (int)z->rel_y);
    if(zoom_label != NULL) {
        lv_label_set_text_fmt(zoom_label, "%.*f", g_zoom.precision, g_zoom.zoomValue);
    }

    lv_obj_t * sw = calibration_freeze_switch();
    if(sw == NULL) return;
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
    lv_obj_t * label = calibration_label(ui_calibrationrow1);
    if(label != NULL) lv_label_set_text_fmt(label, "%d", (int)z->rel_x);
}

void reticle_distance_mgr_refresh_calib_y_ui(uint8_t idx)
{
    reticle_distance_entry_t * e = reticle_distance_mgr_entry(idx);
    if(!e) return;
    reticle_zero_pos_t * z = &e->zero;
    lv_obj_t * label = calibration_label(ui_calibrationrow2);
    if(label != NULL) lv_label_set_text_fmt(label, "%d", (int)z->rel_y);
}

void reticle_distance_mgr_refresh_calib_zoom_ui(uint8_t idx)
{
    LV_UNUSED(idx);

    lv_obj_t * label = calibration_label(ui_calibrationrow4);
    if(label != NULL) {
        lv_label_set_text_fmt(label, "%.*f", g_zoom.precision, g_zoom.zoomValue);
    }
}

void reticle_distance_mgr_refresh_calib_freeze_ui(uint8_t idx)
{
    LV_UNUSED(idx);

    lv_obj_t * sw = calibration_freeze_switch();
    if(sw == NULL) return;
    if(g_freeze_switch) {
        lv_obj_add_state(sw, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(sw, LV_STATE_CHECKED);
    }
    lv_obj_send_event(sw, LV_EVENT_VALUE_CHANGED, NULL);
}
