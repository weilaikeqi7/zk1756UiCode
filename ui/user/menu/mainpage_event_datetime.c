//
// Created by jinxing on 2026/1/8.
//

#include "mainpage_event_handle.h"
#include "mainpage_event_internal.h"
#include "ipcMsgQue4UiSndRequest.h"
#include "reticle_model.h"

/* 辅助函数：闰年 & 当月天数 */
int is_leap_year(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int days_in_month(int y, int m)
{
    static const int dim[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(m < 1 || m > 12) return 31;
    if(m == 2 && is_leap_year(y)) return 29;
    return dim[m];
}

static void set_system(void)
{
    ReqSetSystemTime_st setSystemTime;
    setSystemTime.year = date.year;
    setSystemTime.month = date.month;
    setSystemTime.day = date.day;
    setSystemTime.hour = tim.hour;
    setSystemTime.minute = tim.min;
    setSystemTime.second = tim.sec;
    SendMsg4UiTimeReq(global_parameters.sendMsgQueId, &setSystemTime);
}

void ui_event_rowitemyear(lv_event_t * e)
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
            } else {
                date.year++;
                if(date.year > 2099)
                    date.year = 2026;
                /* 修正 day */
                int dim = days_in_month(date.year, date.month);
                if(date.day > dim)
                    date.day = dim;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemyear, UI_COMP_ROWITEM1_LABEL), "%d", date.year);
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemday, UI_COMP_ROWITEM1_LABEL), "%d", date.day);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                date.year--;
                if(date.year < 2026)
                    date.year = 2099;
                int dim = days_in_month(date.year, date.month);
                if(date.day > dim)
                    date.day = dim;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemyear, UI_COMP_ROWITEM1_LABEL), "%d", date.year);
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemday, UI_COMP_ROWITEM1_LABEL), "%d", date.day);
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
            hidden_menu_page3_itme6_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemmonth(lv_event_t * e)
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
            } else {
                date.month++;
                if(date.month > 12)
                    date.month = 1;
                int dim = days_in_month(date.year, date.month);
                if(date.day > dim)
                    date.day = dim;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemmonth, UI_COMP_ROWITEM1_LABEL), "%d", date.month);
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemday, UI_COMP_ROWITEM1_LABEL), "%d", date.day);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                date.month--;
                if(date.month < 1)
                    date.month = 12;
                int dim = days_in_month(date.year, date.month);
                if(date.day > dim)
                    date.day = dim;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemmonth, UI_COMP_ROWITEM1_LABEL), "%d", date.month);
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemday, UI_COMP_ROWITEM1_LABEL), "%d", date.day);
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
            hidden_menu_page3_itme6_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemday(lv_event_t * e)
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
            } else {
                int dim = days_in_month(date.year, date.month);
                date.day++;
                if(date.day > dim)
                    date.day = 1;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemday, UI_COMP_ROWITEM1_LABEL), "%d", date.day);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                int dim = days_in_month(date.year, date.month);
                date.day--;
                if(date.day < 1)
                    date.day = dim;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemday, UI_COMP_ROWITEM1_LABEL), "%d", date.day);
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
            hidden_menu_page3_itme6_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemback(lv_event_t * e)
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
            set_system();
            hidden_menu_page3_itme6_item1();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item1();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemhour(lv_event_t * e)
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
            } else {
                tim.hour++;
                if(tim.hour > 23)
                    tim.hour = 0;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemhour, UI_COMP_ROWITEM1_LABEL), "%02d", tim.hour);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                tim.hour--;
                if(tim.hour < 0)
                    tim.hour = 23;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemhour, UI_COMP_ROWITEM1_LABEL), "%02d", tim.hour);
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
            hidden_menu_page3_itme6_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemmin(lv_event_t * e)
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
            } else {
                tim.min++;
                if(tim.min > 59)
                    tim.min = 0;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemmin, UI_COMP_ROWITEM1_LABEL), "%02d", tim.min);
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_group_focus_prev(keypad_group);
            } else {
                tim.min--;
                if(tim.min < 0)
                    tim.min = 59;
                lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemmin, UI_COMP_ROWITEM1_LABEL), "%02d", tim.min);
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
            hidden_menu_page3_itme6_item2();
            break;
        default:
            break;
        }
    }
}

void ui_event_rowitemtimeback(lv_event_t * e)
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
            set_system();
            hidden_menu_page3_itme6_item2();
            break;
        case LV_KEY_ESC:
            lv_obj_set_state(obj, LV_STATE_USER_1, false);
            hidden_menu_page3_itme6_item2();
            break;
        default:
            break;
        }
    }
}






