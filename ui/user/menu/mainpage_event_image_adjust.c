//
// Created by jinxing on 2026/1/8.
//

#include "reticle_feature.h"
#include "mainpage_event_handle.h"
#include "mainpage_event_internal.h"
#include <string.h>
#include "ipcMsgQue4UiSndRequest.h"
#include "mainpage_event_usercfg_internal.h"
#include "reticle_model.h"

static ReqAdjustInfraredPseudoColor_st infraredPseudoColor;

void ui_event_rowbrightness(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);
    ReqAdjustInfraredBrightness_st infaredBrightness;
    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Brightness");
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
                Brightness += 1;
                if(Brightness > 10) {
                    Brightness = 0;
                }
                lv_label_set_text_fmt(
                    ui_comp_get_child(ui_rowbrightness, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                    "%d",
                    Brightness);
                infaredBrightness.brightness = (uint8_t)(Brightness * 10);
                SendMsg4UiInfraredBrightnessReq(global_parameters.sendMsgQueId, &infaredBrightness);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                Brightness -= 1;
                if(Brightness < 0) {
                    Brightness = 10;
                }
                lv_label_set_text_fmt(
                    ui_comp_get_child(ui_rowbrightness, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                    "%d",
                    Brightness);
                infaredBrightness.brightness = (uint8_t)(Brightness * 10);
                SendMsg4UiInfraredBrightnessReq(global_parameters.sendMsgQueId, &infaredBrightness);
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
            hidden_menu_page1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowcontrast(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);
    ReqAdjustInfraredContrast_st infraredContrast;

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Contrast");
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
                Contrast += 1;
                if(Contrast > 10) {
                    Contrast = 0;
                }
                lv_label_set_text_fmt(
                    ui_comp_get_child(ui_rowcontrast, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                    "%d",
                    Contrast);
                infraredContrast.contrast = (uint8_t)(Contrast * 10);
                SendMsg4UiInfraredContrastReq(global_parameters.sendMsgQueId, &infraredContrast);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                Contrast -= 1;
                if(Contrast < 0) {
                    Contrast = 10;
                }
                lv_label_set_text_fmt(
                    ui_comp_get_child(ui_rowcontrast, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                    "%d",
                    Contrast);
                infraredContrast.contrast = (uint8_t)(Contrast * 10);
                SendMsg4UiInfraredContrastReq(global_parameters.sendMsgQueId, &infraredContrast);
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
            hidden_menu_page1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowsharpness(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);
    ReqInfraredEnhanceImage_st infraredEnhanceImage;

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Sharpness");
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
                Sharpness += 1;
                if(Sharpness > 10) {
                    Sharpness = 0;
                }
                lv_label_set_text_fmt(
                    ui_comp_get_child(ui_rowsharpness, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                    "%d",
                    Sharpness);
                infraredEnhanceImage.strength = (uint8_t)(Sharpness * 10);
                SendMsg4UiInfraredEnhanceImageReq(global_parameters.sendMsgQueId, &infraredEnhanceImage);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                Sharpness -= 1;
                if(Sharpness < 0) {
                    Sharpness = 10;
                }
                lv_label_set_text_fmt(
                    ui_comp_get_child(ui_rowsharpness, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                    "%d",
                    Sharpness);
                infraredEnhanceImage.strength = (uint8_t)(Sharpness * 10);
                SendMsg4UiInfraredEnhanceImageReq(global_parameters.sendMsgQueId, &infraredEnhanceImage);
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
            hidden_menu_page1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowexpansion(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "Extend");
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
            ReqAdjustExtendDisplaySwitch_st sw;
            ui_rowswitch_set_checked(obj, next_on);
            sw.sw = next_on;
            SendMsg4UiExtendDisplaySwitchReq(global_parameters.sendMsgQueId, &sw);
            break;
        }
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowpip(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);
    ReqAdjustPipSwitch_st pipSwitch;
    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle, "PIP");
    }
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_add_flag(ui_contpage1, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
                lv_group_remove_all_objs(keypad_group);
                show_menu_page2();
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
                pipSwitch.sw = 0;
                SendMsg4UiPipSwitchReq(global_parameters.sendMsgQueId, &pipSwitch);
            } else {
                lv_obj_set_state(ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH), LV_STATE_CHECKED, true);
                lv_obj_send_event(
                    ui_comp_get_child(obj, UI_COMP_ROWSWITCH_CONTPILL_SWITCH),
                    LV_EVENT_VALUE_CHANGED,
                    NULL);
                pipSwitch.sw = 1;
                SendMsg4UiPipSwitchReq(global_parameters.sendMsgQueId, &pipSwitch);
            }
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