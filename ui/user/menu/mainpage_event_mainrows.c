//
// Created by jinxing on 2026/1/8.
//

#include "reticle_feature.h"
#include "mainpage_event_handle.h"
#include "mainpage_event_internal.h"
#include "ipcMsgQue4UiSndRequest.h"
#include "reticle_model.h"

void ui_event_rowlrf(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "LRF");
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
                lv_obj_add_flag(ui_contpage1, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
                lv_group_remove_all_objs(keypad_group);
                show_menu_page3();
                lv_group_focus_obj(ui_rowsetting);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page1_item1();
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

void ui_event_rowreticle(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Reticle");
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
            reticle_feature_open();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page2();
        default:
            break;
        }
    }
}

void ui_event_rowballistic(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Ballistic");
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
                ReqSetReticleCommonConfig_st req = {
                    .saveFlag = (ROE_U8)1,
                    .showReticle = (ROE_S8)-1,
                    .rotateReticle = (ROE_S8)-1,
                    .ballisticSolve = (ROE_S8)0,
                };
                SendMsg4UiSetReticuleCommonConfigReq(global_parameters.sendMsgQueId, &req);
            } else {
                ReqSetReticleCommonConfig_st req = {
                    .saveFlag = (ROE_U8)1,
                    .showReticle = (ROE_S8)-1,
                    .rotateReticle = (ROE_S8)-1,
                    .ballisticSolve = (ROE_S8)1,
                };
                SendMsg4UiSetReticuleCommonConfigReq(global_parameters.sendMsgQueId, &req);
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

void ui_event_rowstandby(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Standby Timer");
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
                lv_obj_add_flag(ui_contpage3, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
                lv_group_remove_all_objs(keypad_group);
                show_menu_page2();
                lv_group_focus_obj(ui_rowrav);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_item1();
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