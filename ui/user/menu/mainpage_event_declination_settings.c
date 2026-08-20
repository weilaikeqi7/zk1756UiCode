//
// Created by jinxing on 2026/1/8.
//

#include "mainpage_event_handle.h"
#include "mainpage_event_internal.h"
#include "ipcMsgQue4UiSndRequest.h"
#include "reticle_model.h"

void ui_event_rowitemOK(lv_event_t * e)
{
    ReqSetCompassDeclination_st setCompassDeclination;
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
            hidden_menu_page3_item2_item2();
            int integer = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
            int frac = magnetic.num4 * 10 + magnetic.num5;
            float v = (float)integer + (float)frac / 100.0f;
            if(magnetic.symbol == '-') {
                v = -v;
            }
            if(magnetic.num1 == 0 && magnetic.num2 == 0 && magnetic.num3 == 0 && magnetic.num4 == 0 && magnetic.num5 ==
               0) {
                v = 0.00f;
            }
            magnetic.value = v;
            setCompassDeclination.declination = magnetic.value;
            SendMsg4UiSetCompassDeclinationReq(global_parameters.sendMsgQueId, &setCompassDeclination);
            SendMsg4UiSaveCompassConfigReq(global_parameters.sendMsgQueId);
            break;
        case LV_KEY_ESC:
            hidden_menu_page3_item2_item2();
            restore_declination();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemCANCEL(lv_event_t * e)
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
            hidden_menu_page3_item2_item2();
            restore_declination();
            break;
        case LV_KEY_ESC:
            hidden_menu_page3_item2_item2();
            restore_declination();
            break;
        default:
            break;
        }
    }
}

void ui_event_settingrow1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle3, "Date");
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
            show_menu_page3_itme6_item1();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item6();
            break;
        default:
            break;
        }
    }
}

void ui_event_settingrow2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle3, "Time");
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
            show_menu_page3_itme6_item2();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item6();
            break;
        default:
            break;
        }
    }
}

void ui_event_settingrow3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);
    ReqSaveLanguageConfig_st saveLanguageConfig;

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle3, "Langauge");
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_next(keypad_group);
            } else {
                Language.index = (Language.index + 1) % Language.count;
                lv_label_set_text(ui_comp_get_child(obj, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  Language.des[Language.index]);
                saveLanguageConfig.langType = Language.index;
                SendMsg4UiSaveLanguageConfig(global_parameters.sendMsgQueId, &saveLanguageConfig);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                Language.index = (Language.index - 1 + Language.count) % Language.count;
                lv_label_set_text(ui_comp_get_child(obj, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                                  Language.des[Language.index]);
                saveLanguageConfig.langType = Language.index;
                SendMsg4UiSaveLanguageConfig(global_parameters.sendMsgQueId, &saveLanguageConfig);
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item6();
            break;
        default:
            break;
        }
    }
}

void ui_event_settingrow4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle3, "Factory Reset");
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
            show_menu_page3_itme6_item4();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item6();
            break;
        default:
            break;
        }
    }
}

void ui_event_settingrow5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle3, "System Info");
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
            SendMsg4UiGetAppVersionReq(global_parameters.sendMsgQueId);
            SendMsg4UiGetWifiInfoReq(global_parameters.sendMsgQueId);
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item6();
            break;
        default:
            break;
        }
    }
}

void ui_event_settingrow6(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle3, "Formatting SD");
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
            show_menu_page3_itme6_item6();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item6();
            break;
        default:
            break;
        }
    }
}
