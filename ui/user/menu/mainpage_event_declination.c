//
// Created by jinxing on 2026/1/8.
//

#include "mainpage_event_handle.h"
#include "mainpage_event_internal.h"
#include "ipcMsgQue4UiSndRequest.h"
#include "reticle_model.h"

static ReqInfraredBadPixelOperate_st infraredBadPixelOperate;

void ui_event_rowitem2(lv_event_t * e)
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
            hidden_menu_page3_item1();
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

void ui_event_rowitem3(lv_event_t * e)
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
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_item2_tiem1();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem4(lv_event_t * e)
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
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_item2_item2();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitem5(lv_event_t * e)
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
            hidden_menu_page3_item2();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_bad_pixel(lv_event_t * e)
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
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_itme3_itme1();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item3();
            break;
        default:
            break;
        }
    }
}

void ui_event_pixel_return(lv_event_t * e)
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
            hidden_menu_page3_item3();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_item3();
            break;
        default:
            break;
        }
    }
}

void ui_event_pixel_item2(lv_event_t * e)
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
                g_app.bad_point.threshold += 1;
                if(g_app.bad_point.threshold > g_app.bad_point.threshold_max) {
                    g_app.bad_point.threshold = g_app.bad_point.threshold_max;
                }
                lv_label_set_text_fmt(
                    ui_comp_get_child(obj, UI_COMP_MCITEM_MCP2P1L2),
                    "%u",
                    g_app.bad_point.threshold);
                ReqInfraredSetBadPixelThreshold_st threshold_st;
                threshold_st.threshold = g_app.bad_point.threshold;
                SendMsg4UiInfraredSetBadPixelThresholdReq(global_parameters.sendMsgQueId, &threshold_st);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                g_app.bad_point.threshold -= 1;
                if(g_app.bad_point.threshold < g_app.bad_point.threshold_min) {
                    g_app.bad_point.threshold = g_app.bad_point.threshold_min;
                }
                lv_label_set_text_fmt(
                    ui_comp_get_child(obj, UI_COMP_MCITEM_MCP2P1L2),
                    "%u",
                    g_app.bad_point.threshold);
                ReqInfraredSetBadPixelThreshold_st threshold_st;
                threshold_st.threshold = g_app.bad_point.threshold;
                SendMsg4UiInfraredSetBadPixelThresholdReq(global_parameters.sendMsgQueId, &threshold_st);
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
            hidden_menu_page3_itme3_itme1();
            break;
        default:
            break;
        }
    }
}

void ui_event_pixel_item3(lv_event_t * e)
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
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
            }
            show_menu_page3_item3_itme1_itme3();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme3_itme1();
            break;
        default:
            break;
        }
    }
}

void ui_event_DialogPixelClearOk(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            lv_group_focus_next(keypad_group);
            break;
        case LV_KEY_DOWN:
            lv_group_focus_prev(keypad_group);
            break;
        case LV_KEY_ENTER:
            infraredBadPixelOperate.opType = 0;
            SendMsg4UiInfraredBadPixelOperateReq(global_parameters.sendMsgQueId, &infraredBadPixelOperate);
            hidden_menu_page3_item3_itme1_itme3();
            break;
        case LV_KEY_ESC:
            hidden_menu_page3_item3_itme1_itme3();
            break;
        default:
            break;
        }
    }
}

void ui_event_DialogPixelClearCancel(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            lv_group_focus_next(keypad_group);
            break;
        case LV_KEY_DOWN:
            lv_group_focus_prev(keypad_group);
            break;
        case LV_KEY_ENTER:
            hidden_menu_page3_item3_itme1_itme3();
            break;
        case LV_KEY_ESC:
            hidden_menu_page3_item3_itme1_itme3();
            break;
        default:
            break;
        }
    }
}

void ui_event_pixel_item4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            lv_group_focus_next(keypad_group);
            break;
        case LV_KEY_DOWN:
            lv_group_focus_prev(keypad_group);
            break;
        case LV_KEY_ENTER:
            infraredBadPixelOperate.opType = 1;
            SendMsg4UiInfraredBadPixelOperateReq(global_parameters.sendMsgQueId, &infraredBadPixelOperate);
            break;
        case LV_KEY_ESC:
            hidden_menu_page3_itme3_itme1();
            break;
        default:
            break;
        }
    }
}

void ui_event_pixel_item5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            lv_group_focus_next(keypad_group);
            break;
        case LV_KEY_DOWN:
            lv_group_focus_prev(keypad_group);
            break;
        case LV_KEY_ENTER:
            infraredBadPixelOperate.opType = 2;
            SendMsg4UiInfraredBadPixelOperateReq(global_parameters.sendMsgQueId, &infraredBadPixelOperate);
            break;
        case LV_KEY_ESC:
            hidden_menu_page3_itme3_itme1();
            break;
        default:
            break;
        }
    }
}

void ui_event_pixel_item6(lv_event_t * e)
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
            hidden_menu_page3_itme3_itme1();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme3_itme1();
            break;
        default:
            break;
        }
    }
}

static int state1 = 0;
static int state2 = 0;

void ui_event_CompassStart(lv_event_t * e)
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
            lv_group_focus_next(keypad_group);
            break;
        case LV_KEY_DOWN:
            lv_group_focus_prev(keypad_group);
            break;
        case LV_KEY_ENTER:
            if(state1 == 1 && state2 == 0) {
                state1 = 0;
                ReqStopCompassCalibration_st compassCalibration;
                compassCalibration.ifsave = 0;
                SendMsg4UiStopCompassCalibrationReq(global_parameters.sendMsgQueId, &compassCalibration);
                lv_label_set_text(ui_comp_get_child(ui_DialogCompass, UI_COMP_DIALOGEG_DIALOGTEXT_LABEL),
                                  "Confirm saving the result?");
                lv_label_set_text(ui_comp_get_child(obj, UI_COMP_ROWITEM_LABEL), "Ok");
                state2 = 1;
            } else if(state1 == 0 && state2 == 0) {
                state1 = 1;
                ReqStartCompassCalibration_st compassCalibration;
                compassCalibration.method = 0;
                compassCalibration.number = -1;
                SendMsg4UiStartCompassCalibrationReq(global_parameters.sendMsgQueId, &compassCalibration);
                lv_label_set_text(ui_comp_get_child(obj, UI_COMP_ROWITEM_LABEL), "Stop");
            } else if(state1 == 0 && state2 == 1) {
                state2 = 0;
                ReqStopCompassCalibration_st compassCalibration;
                compassCalibration.ifsave = 1;
                SendMsg4UiStopCompassCalibrationReq(global_parameters.sendMsgQueId, &compassCalibration);
                lv_label_set_text(ui_comp_get_child(ui_DialogCompass, UI_COMP_DIALOGEG_DIALOGOK_LABEL),
                                  "Start");
                lv_label_set_text(ui_comp_get_child(ui_DialogCompass, UI_COMP_DIALOGEG_DIALOGTEXT_LABEL),
                                  "Rotate 360° around the three \naxes(X, Y, Z) for three times each.");
                hidden_menu_page3_item2_tiem1();
            }
            break;
        case LV_KEY_ESC:
            hidden_menu_page3_item2_tiem1();
            break;
        default:
            break;
        }
    }
}

void ui_event_CompassCancel(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_FOCUSED) {
    }
    if(event_code == LV_EVENT_DEFOCUSED) {
    }

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            lv_group_focus_next(keypad_group);
            break;
        case LV_KEY_DOWN:
            lv_group_focus_prev(keypad_group);
            break;
        case LV_KEY_ENTER: {
            if(state1 == 1) {
                ReqStopCompassCalibration_st compassCalibration;
                compassCalibration.ifsave = 0;
                SendMsg4UiStopCompassCalibrationReq(global_parameters.sendMsgQueId, &compassCalibration);
            }
            lv_label_set_text(ui_comp_get_child(ui_DialogCompass, UI_COMP_DIALOGEG_DIALOGOK_LABEL),
                              "Start");
            lv_label_set_text(ui_comp_get_child(ui_DialogCompass, UI_COMP_DIALOGEG_DIALOGTEXT_LABEL),
                              "Rotate 360° around the three \naxes(X, Y, Z) for three times each.");
            hidden_menu_page3_item2_tiem1();
            state1 = 0;
            state2 = 0;
            break;
        }
        case LV_KEY_ESC:
            hidden_menu_page3_item2_tiem1();
            break;
        default:
            break;
        }
    }
}