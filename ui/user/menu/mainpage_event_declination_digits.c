//
// Created by jinxing on 2026/1/8.
//

#include "mainpage_event_handle.h"
#include "mainpage_event_internal.h"
#include "reticle_model.h"

static ReqSetCompassDeclination_st setCompassDeclination;

void ui_event_num1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * Papa_obj = lv_event_get_user_data(e);
    lv_obj_t * child_obj = ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                magnetic.symbol = (magnetic.symbol == '+') ? '-' : '+';
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL), "%c", magnetic.symbol);
                int integer = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
                int frac = magnetic.num4 * 10 + magnetic.num5;
                float v = (float)integer + (float)frac / 100.0f;
                if(magnetic.symbol == '-') {
                    v = -v;
                }
                if(magnetic.num1 == 0 && magnetic.num2 == 0 && magnetic.num3 == 0 && magnetic.num4 == 0 && magnetic.num5
                   ==
                   0) {
                    v = 0.00f;
                }
                magnetic.value = v;
                setCompassDeclination.declination = magnetic.value;
                SendMsg4UiSetCompassDeclinationReq(global_parameters.sendMsgQueId, &setCompassDeclination);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                magnetic.symbol = (magnetic.symbol == '+') ? '-' : '+';
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL), "%c", magnetic.symbol);
                int integer = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
                int frac = magnetic.num4 * 10 + magnetic.num5;
                float v = (float)integer + (float)frac / 100.0f;
                if(magnetic.symbol == '-') {
                    v = -v;
                }
                if(magnetic.num1 == 0 && magnetic.num2 == 0 && magnetic.num3 == 0 && magnetic.num4 == 0 && magnetic.num5
                   ==
                   0) {
                    v = 0.00f;
                }
                magnetic.value = v;
                setCompassDeclination.declination = magnetic.value;
                SendMsg4UiSetCompassDeclinationReq(global_parameters.sendMsgQueId, &setCompassDeclination);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, true);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2_item2();
            restore_declination();
            break;
        default:
            break;
        }
    }
}

void ui_event_num2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * Papa_obj = lv_event_get_user_data(e);
    lv_obj_t * child_obj = ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                magnetic.num1++;
                if(magnetic.num1 > 9) {
                    magnetic.num1 = 0;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num1);
                int integer = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
                int frac = magnetic.num4 * 10 + magnetic.num5;
                float v = (float)integer + (float)frac / 100.0f;
                if(magnetic.symbol == '-') {
                    v = -v;
                }
                if(magnetic.num1 == 0 && magnetic.num2 == 0 && magnetic.num3 == 0 && magnetic.num4 == 0 && magnetic.num5
                   ==
                   0) {
                    v = 0.00f;
                }
                magnetic.value = v;
                setCompassDeclination.declination = magnetic.value;
                SendMsg4UiSetCompassDeclinationReq(global_parameters.sendMsgQueId, &setCompassDeclination);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                magnetic.num1--;
                if(magnetic.num1 < 0) {
                    magnetic.num1 = 9;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num1);
                int integer = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
                int frac = magnetic.num4 * 10 + magnetic.num5;
                float v = (float)integer + (float)frac / 100.0f;
                if(magnetic.symbol == '-') {
                    v = -v;
                }
                if(magnetic.num1 == 0 && magnetic.num2 == 0 && magnetic.num3 == 0 && magnetic.num4 == 0 && magnetic.num5
                   ==
                   0) {
                    v = 0.00f;
                }
                magnetic.value = v;
                setCompassDeclination.declination = magnetic.value;
                SendMsg4UiSetCompassDeclinationReq(global_parameters.sendMsgQueId, &setCompassDeclination);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, true);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2_item2();
            restore_declination();
            break;
        default:
            break;
        }
    }
}

void ui_event_num3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * Papa_obj = lv_event_get_user_data(e);
    lv_obj_t * child_obj = ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                magnetic.num2++;
                if(magnetic.num2 > 9) {
                    magnetic.num2 = 0;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num2);
                int integer = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
                int frac = magnetic.num4 * 10 + magnetic.num5;
                float v = (float)integer + (float)frac / 100.0f;
                if(magnetic.symbol == '-') {
                    v = -v;
                }
                if(magnetic.num1 == 0 && magnetic.num2 == 0 && magnetic.num3 == 0 && magnetic.num4 == 0 && magnetic.num5
                   ==
                   0) {
                    v = 0.00f;
                }
                magnetic.value = v;
                setCompassDeclination.declination = magnetic.value;
                SendMsg4UiSetCompassDeclinationReq(global_parameters.sendMsgQueId, &setCompassDeclination);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                magnetic.num2--;
                if(magnetic.num2 < 0) {
                    magnetic.num2 = 9;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num2);
                int integer = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
                int frac = magnetic.num4 * 10 + magnetic.num5;
                float v = (float)integer + (float)frac / 100.0f;
                if(magnetic.symbol == '-') {
                    v = -v;
                }
                if(magnetic.num1 == 0 && magnetic.num2 == 0 && magnetic.num3 == 0 && magnetic.num4 == 0 && magnetic.num5
                   ==
                   0) {
                    v = 0.00f;
                }
                magnetic.value = v;
                setCompassDeclination.declination = magnetic.value;
                SendMsg4UiSetCompassDeclinationReq(global_parameters.sendMsgQueId, &setCompassDeclination);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, true);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2_item2();
            restore_declination();
            break;
        default:
            break;
        }
    }
}

void ui_event_num4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * Papa_obj = lv_event_get_user_data(e);
    lv_obj_t * child_obj = ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                magnetic.num3++;
                if(magnetic.num3 > 9) {
                    magnetic.num3 = 0;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num3);
                int integer = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
                int frac = magnetic.num4 * 10 + magnetic.num5;
                float v = (float)integer + (float)frac / 100.0f;
                if(magnetic.symbol == '-') {
                    v = -v;
                }
                if(magnetic.num1 == 0 && magnetic.num2 == 0 && magnetic.num3 == 0 && magnetic.num4 == 0 && magnetic.num5
                   ==
                   0) {
                    v = 0.00f;
                }
                magnetic.value = v;
                setCompassDeclination.declination = magnetic.value;
                SendMsg4UiSetCompassDeclinationReq(global_parameters.sendMsgQueId, &setCompassDeclination);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                magnetic.num3--;
                if(magnetic.num3 < 0) {
                    magnetic.num3 = 9;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num3);
                int integer = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
                int frac = magnetic.num4 * 10 + magnetic.num5;
                float v = (float)integer + (float)frac / 100.0f;
                if(magnetic.symbol == '-') {
                    v = -v;
                }
                if(magnetic.num1 == 0 && magnetic.num2 == 0 && magnetic.num3 == 0 && magnetic.num4 == 0 && magnetic.num5
                   ==
                   0) {
                    v = 0.00f;
                }
                magnetic.value = v;
                setCompassDeclination.declination = magnetic.value;
                SendMsg4UiSetCompassDeclinationReq(global_parameters.sendMsgQueId, &setCompassDeclination);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, true);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2_item2();
            restore_declination();
            break;
        default:
            break;
        }
    }
}

void ui_event_num5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * Papa_obj = lv_event_get_user_data(e);
    lv_obj_t * child_obj = ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                magnetic.num4++;
                if(magnetic.num4 > 9) {
                    magnetic.num4 = 0;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num4);
                int integer = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
                int frac = magnetic.num4 * 10 + magnetic.num5;
                float v = (float)integer + (float)frac / 100.0f;
                if(magnetic.symbol == '-') {
                    v = -v;
                }
                if(magnetic.num1 == 0 && magnetic.num2 == 0 && magnetic.num3 == 0 && magnetic.num4 == 0 && magnetic.num5
                   ==
                   0) {
                    v = 0.00f;
                }
                magnetic.value = v;
                setCompassDeclination.declination = magnetic.value;
                SendMsg4UiSetCompassDeclinationReq(global_parameters.sendMsgQueId, &setCompassDeclination);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                magnetic.num4--;
                if(magnetic.num4 < 0) {
                    magnetic.num4 = 9;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num4);
                int integer = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
                int frac = magnetic.num4 * 10 + magnetic.num5;
                float v = (float)integer + (float)frac / 100.0f;
                if(magnetic.symbol == '-') {
                    v = -v;
                }
                if(magnetic.num1 == 0 && magnetic.num2 == 0 && magnetic.num3 == 0 && magnetic.num4 == 0 && magnetic.num5
                   ==
                   0) {
                    v = 0.00f;
                }
                magnetic.value = v;
                setCompassDeclination.declination = magnetic.value;
                SendMsg4UiSetCompassDeclinationReq(global_parameters.sendMsgQueId, &setCompassDeclination);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, true);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2_item2();
            restore_declination();
            break;
        default:
            break;
        }
    }
}

void ui_event_num6(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * Papa_obj = lv_event_get_user_data(e);
    lv_obj_t * child_obj = ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                magnetic.num5++;
                if(magnetic.num5 > 9) {
                    magnetic.num5 = 0;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num5);
                int integer = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
                int frac = magnetic.num4 * 10 + magnetic.num5;
                float v = (float)integer + (float)frac / 100.0f;
                if(magnetic.symbol == '-') {
                    v = -v;
                }
                if(magnetic.num1 == 0 && magnetic.num2 == 0 && magnetic.num3 == 0 && magnetic.num4 == 0 && magnetic.num5
                   ==
                   0) {
                    v = 0.00f;
                }
                magnetic.value = v;
                setCompassDeclination.declination = magnetic.value;
                SendMsg4UiSetCompassDeclinationReq(global_parameters.sendMsgQueId, &setCompassDeclination);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                magnetic.num5--;
                if(magnetic.num5 < 0) {
                    magnetic.num5 = 9;
                }
                lv_label_set_text_fmt(ui_comp_get_child(Papa_obj, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num5);
                int integer = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
                int frac = magnetic.num4 * 10 + magnetic.num5;
                float v = (float)integer + (float)frac / 100.0f;
                if(magnetic.symbol == '-') {
                    v = -v;
                }
                if(magnetic.num1 == 0 && magnetic.num2 == 0 && magnetic.num3 == 0 && magnetic.num4 == 0 && magnetic.num5
                   ==
                   0) {
                    v = 0.00f;
                }
                magnetic.value = v;
                setCompassDeclination.declination = magnetic.value;
                SendMsg4UiSetCompassDeclinationReq(global_parameters.sendMsgQueId, &setCompassDeclination);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(child_obj, LV_STATE_USER_1)) {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_set_state(child_obj, LV_STATE_USER_1, true);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui_comp_get_child(Papa_obj, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(child_obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2_item2();
            restore_declination();
            break;
        default:
            break;
        }
    }
}
