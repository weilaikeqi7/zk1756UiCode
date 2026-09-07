//
// Created by jinxing on 2026/1/8.
//

#include "menu_event_registry.h"
#include "menu_event_internal.h"
#include "reticle_model.h"

#include <stdbool.h>

static UiRequestSetCompassDeclination s_declination_request;

static float calculate_declination_value(void)
{
    int integer_part = magnetic.num1 * 100 + magnetic.num2 * 10 + magnetic.num3;
    int fractional_part = magnetic.num4 * 10 + magnetic.num5;
    float value = (float)integer_part + (float)fractional_part / 100.0f;

    if(magnetic.symbol == '-') value = -value;
    if(magnetic.num1 == 0 && magnetic.num2 == 0 && magnetic.num3 == 0 && magnetic.num4 == 0 &&
       magnetic.num5 == 0) {
        value = 0.0f;
    }
    return value;
}

static void send_declination_update(void)
{
    magnetic.value = calculate_declination_value();
    s_declination_request.declination = magnetic.value;
    UiIpcSendSetCompassDeclinationRequest(global_parameters.sendMsgQueId, &s_declination_request);
}

static void set_digit_arrows_hidden(lv_obj_t * parent, bool hidden)
{
    lv_obj_t * up_arrow = ui_comp_get_child(parent, UI_COMP_NUM_IMAGEUP);
    lv_obj_t * down_arrow = ui_comp_get_child(parent, UI_COMP_NUM_IMAGEDOWN);

    if(up_arrow != NULL) {
        if(hidden) lv_obj_add_flag(up_arrow, LV_OBJ_FLAG_HIDDEN);
        else lv_obj_remove_flag(up_arrow, LV_OBJ_FLAG_HIDDEN);
    }
    if(down_arrow != NULL) {
        if(hidden) lv_obj_add_flag(down_arrow, LV_OBJ_FLAG_HIDDEN);
        else lv_obj_remove_flag(down_arrow, LV_OBJ_FLAG_HIDDEN);
    }
}

static void handle_declination_digit_event(lv_event_t * event,
                                           int * digit,
                                           bool is_sign_digit)
{
    if(event == NULL) return;
    if(lv_event_get_code(event) != LV_EVENT_KEY) return;

    lv_obj_t * parent = lv_event_get_user_data(event);
    if(parent == NULL) return;

    lv_obj_t * edit_target = ui_comp_get_child(parent, UI_COMP_NUM_PANELNUM);
    lv_obj_t * value_label = ui_comp_get_child(parent, UI_COMP_NUM_PANELNUM_LABEL);
    if(edit_target == NULL || value_label == NULL) return;

    uint32_t key = lv_indev_get_key(lv_indev_active());
    bool editing = lv_obj_has_state(edit_target, LV_STATE_USER_1);

    switch(key) {
    case LV_KEY_UP:
        if(!editing) {
            ui_focus_group_next();
        } else if(is_sign_digit) {
            magnetic.symbol = (magnetic.symbol == '+') ? '-' : '+';
            lv_label_set_text_fmt(value_label, "%c", magnetic.symbol);
            send_declination_update();
        } else {
            *digit = (*digit + 1) % 10;
            lv_label_set_text_fmt(value_label, "%d", *digit);
            send_declination_update();
        }
        break;
    case LV_KEY_DOWN:
        if(!editing) {
            ui_focus_group_prev();
        } else if(is_sign_digit) {
            magnetic.symbol = (magnetic.symbol == '+') ? '-' : '+';
            lv_label_set_text_fmt(value_label, "%c", magnetic.symbol);
            send_declination_update();
        } else {
            *digit = (*digit + 9) % 10;
            lv_label_set_text_fmt(value_label, "%d", *digit);
            send_declination_update();
        }
        break;
    case LV_KEY_ENTER:
        lv_obj_set_state(edit_target, LV_STATE_USER_1, !editing);
        set_digit_arrows_hidden(parent, editing);
        break;
    case LV_KEY_ESC:
        lv_obj_set_state(edit_target, LV_STATE_USER_1, false);
        hidden_menu_page3_item2_item2();
        restore_declination();
        break;
    default:
        break;
    }
}

void ui_event_num1(lv_event_t * event)
{
    handle_declination_digit_event(event, NULL, true);
}

void ui_event_num2(lv_event_t * event)
{
    handle_declination_digit_event(event, &magnetic.num1, false);
}

void ui_event_num3(lv_event_t * event)
{
    handle_declination_digit_event(event, &magnetic.num2, false);
}

void ui_event_num4(lv_event_t * event)
{
    handle_declination_digit_event(event, &magnetic.num3, false);
}

void ui_event_num5(lv_event_t * event)
{
    handle_declination_digit_event(event, &magnetic.num4, false);
}

void ui_event_num6(lv_event_t * event)
{
    handle_declination_digit_event(event, &magnetic.num5, false);
}
