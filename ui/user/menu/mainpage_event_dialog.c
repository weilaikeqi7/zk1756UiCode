//
// Created by jinxing on 2026/1/8.
//

#include "mainpage_event_handle.h"
#include "mainpage_event_internal.h"
#include "ipcMsgQue4UiSndRequest.h"
#include "reticle_model.h"

void ui_event_resetOK(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
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
            hidden_menu_page3_itme6_item4();
            SendMsg4UiRestoreFactoryReq(global_parameters.sendMsgQueId);
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item4();
            break;
        default:
            break;
        }
    }
}

void ui_event_resetCANCEL(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
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
            hidden_menu_page3_itme6_item4();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item4();
            break;
        default:
            break;
        }
    }
}

void ui_event_infoOK(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
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
            hidden_menu_page3_itme6_item5();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item5();
            break;
        default:
            break;
        }
    }
}

void ui_event_DialogFormattingSdOk(lv_event_t * e)
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
        case LV_KEY_ENTER:
            hidden_menu_page3_itme6_item6();
            SendMsg4UiFormatDiskReq(global_parameters.sendMsgQueId);
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item6();
            break;
        default:
            break;
        }
    }
}

void ui_event_DialogFormattingSdCancel(lv_event_t * e)
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
        case LV_KEY_ENTER:
            hidden_menu_page3_itme6_item6();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item6();
            break;
        default:
            break;
        }
    }
}

void ui_event_powerOffOK(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            lv_group_focus_next(g_popup_poweroff.group);
            break;
        case LV_KEY_DOWN:
            lv_group_focus_prev(g_popup_poweroff.group);
            break;
        case LV_KEY_ENTER:
            SendMsg4UiShutdownReq(global_parameters.sendMsgQueId);
            popup_stack_pop(&g_popup_stack);
            SendMsg4UiExitDialogBoxReq(global_parameters.sendMsgQueId);
            break;
        case LV_KEY_ESC:
            popup_stack_pop(&g_popup_stack);
            SendMsg4UiExitDialogBoxReq(global_parameters.sendMsgQueId);
            break;
        default:
            break;
        }
    }
}

void ui_event_powerOffCancel(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            lv_group_focus_next(g_popup_poweroff.group);
            break;
        case LV_KEY_DOWN:
            lv_group_focus_prev(g_popup_poweroff.group);
            break;
        case LV_KEY_ENTER:
            popup_stack_pop(&g_popup_stack);
            SendMsg4UiExitDialogBoxReq(global_parameters.sendMsgQueId);
            break;
        case LV_KEY_ESC:
            popup_stack_pop(&g_popup_stack);
            SendMsg4UiExitDialogBoxReq(global_parameters.sendMsgQueId);
            break;
        default:
            break;
        }
    }
}