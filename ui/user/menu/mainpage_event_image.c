//
// Created by jinxing on 2026/1/8.
//

#include "reticle_feature.h"
#include "mainpage_event_handle.h"
#include "mainpage_event_internal.h"
#include <string.h>
#include "ipcMsgQue4UiSndRequest.h"
#include "reticle_model.h"

void ui_event_rowimagemode(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Image Mode");
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
            show_menu_page1_item2();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1();
            break;
        default:
            break;
        }
    }
}

void ui_event_menu1row1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);
    ReqAdjustRangefinderSwitch_st rangefinderSwitch;

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle2, "Switch");
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
                rangefinderSwitch.sw = OFF;
                rangefinderSwitch.range_sw = -1;
                SendMsg4UiRangeFinderSwitchReq(global_parameters.sendMsgQueId, &rangefinderSwitch);
            } else {
                rangefinderSwitch.sw = ON;
                rangefinderSwitch.range_sw = -1;
                SendMsg4UiRangeFinderSwitchReq(global_parameters.sendMsgQueId, &rangefinderSwitch);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_menu1row2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle2, "Single Measure");
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
            if(g_rangefinder_switch == ON) {
                ReqAdjustRangeFrequency_st rangeFrequency;
                ReqAdjustRangeDuration_st rangeDuration;
                ReqAdjustRangefinderSwitch_st rangefinderSwitch;
                rangeFrequency.freq = 0;
                rangeDuration.duration = 0;
                rangefinderSwitch.sw = -1;
                rangefinderSwitch.range_sw = 1;
                SendMsg4UiRangeFrequencyReq(global_parameters.sendMsgQueId, &rangeFrequency);
                SendMsg4UiRangeDurationReq(global_parameters.sendMsgQueId, &rangeDuration);
                SendMsg4UiRangeFinderSwitchReq(global_parameters.sendMsgQueId, &rangefinderSwitch);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_menu1row3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);
    ReqAdjustRangefinderSwitch_st rangefinderSwitch;

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle2, "Continuous Measure");
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
            if(g_rangefinder_switch == ON) {
                ReqAdjustRangeFrequency_st rangeFrequency;
                ReqAdjustRangeDuration_st rangeDuration;
                if(lv_obj_has_state(ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)) {
                    lv_obj_set_state(
                        ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                        LV_STATE_CHECKED,
                        false);
                    lv_obj_send_event(
                        ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                        LV_EVENT_VALUE_CHANGED,
                        NULL);
                    rangefinderSwitch.sw = -1;
                    rangefinderSwitch.range_sw = 0;
                    SendMsg4UiRangeFinderSwitchReq(global_parameters.sendMsgQueId, &rangefinderSwitch);
                } else {
                    lv_obj_set_state(ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                    lv_obj_send_event(
                        ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                        LV_EVENT_VALUE_CHANGED,
                        NULL);
                    rangeFrequency.freq = 1;
                    rangeDuration.duration = -1;
                    SendMsg4UiRangeFrequencyReq(global_parameters.sendMsgQueId, &rangeFrequency);
                    SendMsg4UiRangeDurationReq(global_parameters.sendMsgQueId, &rangeDuration);
                    rangefinderSwitch.sw = -1;
                    rangefinderSwitch.range_sw = 1;
                    SendMsg4UiRangeFinderSwitchReq(global_parameters.sendMsgQueId, &rangefinderSwitch);
                }
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1_item1();
            break;
        default:
            break;
        }
    }
}
