//
// Created by jinxing on 2026/1/8.
//

#include "mainpage_event_handle.h"
#include "mainpage_event_internal.h"
#include "ipcMsgQue4UiSndRequest.h"
#include "reticle_model.h"

#include "mainpage_event_usercfg_internal.h"

void ui_event_menu1row4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle2, "Unit");
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                DistanceUnit.index = (DistanceUnit.index + 1) % DistanceUnit.count;
                userCommonConfig.distanceUnit = (ROE_U8)DistanceUnit.index;

                lv_label_set_text(ui_comp_get_child(ui_menu1row4, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  DistanceUnit.des[DistanceUnit.index]);
                switch_distance_label_unit(ui_distancelabel, (target_unit_t)DistanceUnit.index);
                switch_distance_label_unit(ui_tempdistancelabel, (target_unit_t)DistanceUnit.index);
                send_user_common_config_partial(-1, -1, -1, (ROE_S8)userCommonConfig.distanceUnit, 1);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                DistanceUnit.index = (DistanceUnit.index - 1 + DistanceUnit.count) % DistanceUnit.count;
                userCommonConfig.distanceUnit = (ROE_U8)DistanceUnit.index;

                lv_label_set_text(ui_comp_get_child(ui_menu1row4, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  DistanceUnit.des[DistanceUnit.index]);
                switch_distance_label_unit(ui_distancelabel, (target_unit_t)DistanceUnit.index);
                switch_distance_label_unit(ui_tempdistancelabel, (target_unit_t)DistanceUnit.index);
                send_user_common_config_partial(-1, -1, -1, (ROE_S8)userCommonConfig.distanceUnit, 1);
            }
            break;
        case LV_KEY_ENTER:
            lv_obj_set_state(obj, LV_STATE_USER_1, !lv_obj_has_state(obj, LV_STATE_USER_1));
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

void ui_event_rowmic(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Microphone");
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
        case LV_KEY_ENTER: {
            ROE_U8 next_on =
                lv_obj_has_state(ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED) ? 0 : 1;
            send_user_media_config_partial(-1, -1, -1, -1, (ROE_S8)next_on, 1);
            break;
        }
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowrav(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "RAV Recording");
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_add_flag(ui_contpage2, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
                lv_group_remove_all_objs(keypad_group);
                show_menu_page3();
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            }
            break;
        case LV_KEY_ENTER: {
            ROE_U8 next_on =
                lv_obj_has_state(ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED) ? 0 : 1;
            send_user_media_config_partial(-1, -1, (ROE_S8)next_on, -1, -1, 1);
            break;
        }
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowswitch1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

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
        case LV_KEY_ENTER: {
            ROE_U8 next_on =
                lv_obj_has_state(ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED)
                    ? OFF
                    : ON;
            g_standby_switch = next_on;
            ui_rowswitch_set_checked(obj, next_on);
            userCommonConfig.standbyTimeout = (next_on == ON) ? ui_min_to_standby_timeout_sec(StandbyTime) : 0;
            send_user_common_config_partial(-1, (ROE_S16)userCommonConfig.standbyTimeout, -1, -1, 1);
            break;
        }
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                int rem;
                if(StandbyTime <= 0) {
                    StandbyTime = 1;
                } else {
                    rem = StandbyTime % 5;
                    if(rem == 0) {
                        StandbyTime += 5;
                    } else {
                        StandbyTime += (5 - rem);
                    }
                    if(StandbyTime > 60) {
                        StandbyTime = 1;
                    }
                }
                lv_label_set_text_fmt(
                    ui_comp_get_child(ui_rowitem1, UI_COMP_ROWITEM1_LABEL),
                    "%d minutes",
                    StandbyTime);
                if(g_standby_switch == ON) {
                    userCommonConfig.standbyTimeout = ui_min_to_standby_timeout_sec(StandbyTime);
                    send_user_common_config_partial(-1, (ROE_S16)userCommonConfig.standbyTimeout, -1, -1, 1);
                }
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                if(StandbyTime == 1) {
                    StandbyTime = 60;
                } else if(StandbyTime % 5 != 0) {
                    StandbyTime = (StandbyTime / 5) * 5;
                    if(StandbyTime == 0)
                        StandbyTime = 1;
                } else {
                    if(StandbyTime == 5) {
                        StandbyTime = 1;
                    } else {
                        StandbyTime -= 5;
                    }
                }
                if(StandbyTime < 1) {
                    StandbyTime = 60;
                }
                lv_label_set_text_fmt(
                    ui_comp_get_child(ui_rowitem1, UI_COMP_ROWITEM1_LABEL),
                    "%d minutes",
                    StandbyTime);
                if(g_standby_switch == ON) {
                    userCommonConfig.standbyTimeout = ui_min_to_standby_timeout_sec(StandbyTime);
                    send_user_common_config_partial(-1, (ROE_S16)userCommonConfig.standbyTimeout, -1, -1, 1);
                }
            }
            break;
        case LV_KEY_ENTER:
            lv_obj_set_state(obj, LV_STATE_USER_1, !lv_obj_has_state(obj, LV_STATE_USER_1));
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item1();
            break;
        default:
            break;
        }
    }
}