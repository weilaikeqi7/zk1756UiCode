//
// Created by jinxing on 2026/1/8.
//

#include "mainpage_event_handle.h"
#include "mainpage_event_internal.h"
#include <stdlib.h>
#include <string.h>
#include "play_handle.h"
#include "reticle_model.h"

void ui_event_rowcompasscalibration(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Compass Calibration");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_item2();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowdeadpixel(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Dead Pixel Repair");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_itme3_itme1();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowstatusbar(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Status Bar");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                lv_obj_set_state(ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, false);
                lv_obj_send_event(
                    ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                    LV_EVENT_VALUE_CHANGED,
                    NULL);
                lv_obj_add_flag(ui_contstatusbar, LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_set_state(ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(
                    ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                    LV_EVENT_VALUE_CHANGED,
                    NULL);
                lv_obj_remove_flag(ui_contstatusbar, LV_OBJ_FLAG_HIDDEN);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowdeletefile(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Playback");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            show_play_page();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowsetting(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Setting");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_add_flag(ui_contpage3, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
                lv_group_remove_all_objs(keypad_group);
                show_menu_page1();
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_item6();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3();
            break;
        default:
            break;
        }
    }
}
