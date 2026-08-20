//
// Created by jinxing on 2026/1/8.
//

#include "reticle_feature.h"
#include "mainpage_event_handle.h"
#include "mainpage_event_internal.h"
#include <string.h>
#include "ipcMsgQue4UiSndRequest.h"
#include "reticle_model.h"


void ui_event_rowwifi(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);
    ReqAdjustWifiSwitch_st wifi_switch;

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Wi-Fi");
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
                lv_obj_add_flag(ui_contpage2, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
                lv_group_remove_all_objs(keypad_group);
                show_menu_page1();
                lv_group_focus_obj(ui_rowpip);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                wifi_switch.sw = OFF;
                SendMsg4UiWifiSwitchReq(global_parameters.sendMsgQueId, &wifi_switch);
            } else {
                wifi_switch.sw = ON;
                SendMsg4UiWifiSwitchReq(global_parameters.sendMsgQueId, &wifi_switch);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowtilt(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Tilt");
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
                lv_obj_add_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_contpitch, LV_OBJ_FLAG_HIDDEN);
                g_tilt = OFF;
            } else {
                lv_obj_set_state(ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(
                    ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                    LV_EVENT_VALUE_CHANGED,
                    NULL);
                if(lv_obj_has_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN) == true) {
                    lv_obj_remove_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);
                }
                lv_obj_remove_flag(ui_contpitch, LV_OBJ_FLAG_HIDDEN);
                g_tilt = ON;
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowcompass(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Compass");
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
                lv_obj_add_flag(ui_contyaw, LV_OBJ_FLAG_HIDDEN);
                g_compass = OFF;
            } else {
                lv_obj_set_state(ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(
                    ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                    LV_EVENT_VALUE_CHANGED,
                    NULL);
                lv_obj_remove_flag(ui_contyaw, LV_OBJ_FLAG_HIDDEN);
                g_compass = ON;
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page2();
            break;
        default:
            break;
        }
    }
}