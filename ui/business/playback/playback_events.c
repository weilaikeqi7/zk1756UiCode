//
// Created by jinxing on 2026/1/14.
//

#include "playback_controller.h"
#include "playback_internal.h"

void ui_event_PlayList_1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            play_list_focus_relative(1);
            break;
        case LV_KEY_DOWN:
            play_list_focus_relative(-1);
            break;
        case LV_KEY_ENTER: {
            UiRequestGetMediaFileList getMediaFileList;
            playlist_state.req_type = 1;
            playlist_state.current_page_index = 1;
            playlist_state.find_type = 2;
            play_media_list_request_init(&getMediaFileList, 0);
            UiIpcSendGetMediaFileListRequest(global_parameters.sendMsgQueId, &getMediaFileList);
            cur_focus_index = FOCUS_ALL;
            break;
        }
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_PlayList_1_5(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                play_list_focus_relative(1);
            } else {
                switch(playlist_state.current_index) {
                case 1: {
                    findDateTime.year += 1;
                    if(findDateTime.year > 2199) {
                        findDateTime.year = 2199;
                    }
                    lv_label_set_text_fmt(ui_PlayList[1], "%d", findDateTime.year);
                }
                break;
                case 2: {
                    findDateTime.month += 1;
                    if(findDateTime.month > 12) {
                        findDateTime.month = 0;
                    }
                    if(findDateTime.month == 0) {
                        lv_label_set_text(ui_PlayList[2], "All");
                    } else {
                        if(findDateTime.month < 10) {
                            lv_label_set_text_fmt(ui_PlayList[2], "0%d", findDateTime.month);
                        } else {
                            lv_label_set_text_fmt(ui_PlayList[2], "%d", findDateTime.month);
                        }
                    }
                }
                break;
                case 3: {
                    findDateTime.day += 1;
                    // 获取当前年月对应的最大天数
                    int8_t max_day = get_days_in_month(findDateTime.year, findDateTime.month);
                    if(findDateTime.day > max_day) {
                        // 使用当月最大天数替换固定的31
                        findDateTime.day = 0;
                    }
                    if(findDateTime.day == 0) {
                        lv_label_set_text(ui_PlayList[3], "All");
                    } else {
                        if(findDateTime.day < 10) {
                            lv_label_set_text_fmt(ui_PlayList[3], "0%d", findDateTime.day);
                        } else {
                            lv_label_set_text_fmt(ui_PlayList[3], "%d", findDateTime.day);
                        }
                    }
                }
                break;
                case 4: {
                    findDateTime.hour += 1;
                    if(findDateTime.hour > 23) {
                        findDateTime.hour = -1;
                    }
                    if(findDateTime.hour == -1) {
                        lv_label_set_text(ui_PlayList[4], "All");
                    } else {
                        if(findDateTime.hour < 10) {
                            lv_label_set_text_fmt(ui_PlayList[4], "0%d", findDateTime.hour);
                        } else {
                            lv_label_set_text_fmt(ui_PlayList[4], "%d", findDateTime.hour);
                        }
                    }
                }
                break;
                case 5: {
                    findDateTime.minute += 1;
                    if(findDateTime.minute > 59) {
                        findDateTime.minute = -1;
                    }
                    if(findDateTime.minute == -1) {
                        lv_label_set_text(ui_PlayList[5], "All");
                    } else {
                        if(findDateTime.minute < 10) {
                            lv_label_set_text_fmt(ui_PlayList[5], "0%d", findDateTime.minute);
                        } else {
                            lv_label_set_text_fmt(ui_PlayList[5], "%d", findDateTime.minute);
                        }
                    }
                }
                break;
                default:
                    break;
                }
            }
            break;
        case LV_KEY_DOWN:
            if(!lv_obj_has_state(obj, LV_STATE_USER_1)) {
                play_list_focus_relative(-1);
            } else {
                switch(playlist_state.current_index) {
                case 1: {
                    findDateTime.year -= 1;
                    if(findDateTime.year < 2024) {
                        findDateTime.year = 2024;
                    }
                    if(findDateTime.year == 2024) {
                        lv_label_set_text(ui_PlayList[1], "All");
                    } else {
                        lv_label_set_text_fmt(ui_PlayList[1], "%d", findDateTime.year);
                    }
                }
                break;
                case 2: {
                    findDateTime.month -= 1;
                    if(findDateTime.month < 0) {
                        findDateTime.month = 12;
                    }
                    if(findDateTime.month == 0) {
                        lv_label_set_text(ui_PlayList[2], "All");
                    } else {
                        if(findDateTime.month < 10) {
                            lv_label_set_text_fmt(ui_PlayList[2], "0%d", findDateTime.month);
                        } else {
                            lv_label_set_text_fmt(ui_PlayList[2], "%d", findDateTime.month);
                        }
                    }
                }
                break;
                case 3: {
                    findDateTime.day -= 1;
                    // 获取当前年月对应的最大天数
                    int8_t max_day = get_days_in_month(findDateTime.year, findDateTime.month);
                    if(findDateTime.day < 0) {
                        findDateTime.day = max_day; // 使用当月最大天数替换固定的31
                    }
                    if(findDateTime.day == 0) {
                        lv_label_set_text(ui_PlayList[3], "All");
                    } else {
                        if(findDateTime.day < 10) {
                            lv_label_set_text_fmt(ui_PlayList[3], "0%d", findDateTime.day);
                        } else {
                            lv_label_set_text_fmt(ui_PlayList[3], "%d", findDateTime.day);
                        }
                    }
                }
                break;
                case 4: {
                    findDateTime.hour -= 1;
                    if(findDateTime.hour < -1) {
                        findDateTime.hour = 23;
                    }
                    if(findDateTime.hour == -1) {
                        lv_label_set_text(ui_PlayList[4], "All");
                    } else {
                        if(findDateTime.hour < 10) {
                            lv_label_set_text_fmt(ui_PlayList[4], "0%d", findDateTime.hour);
                        } else {
                            lv_label_set_text_fmt(ui_PlayList[4], "%d", findDateTime.hour);
                        }
                    }
                }
                break;
                case 5: {
                    findDateTime.minute -= 1;
                    if(findDateTime.minute < -1) {
                        findDateTime.minute = 59;
                    }
                    if(findDateTime.minute == -1) {
                        lv_label_set_text(ui_PlayList[5], "All");
                    } else {
                        if(findDateTime.minute < 10) {
                            lv_label_set_text_fmt(ui_PlayList[5], "0%d", findDateTime.minute);
                        } else {
                            lv_label_set_text_fmt(ui_PlayList[5], "%d", findDateTime.minute);
                        }
                    }
                }
                break;
                default:
                    break;
                }
            }
            break;
        case LV_KEY_ENTER:
            if(lv_obj_has_state(obj, LV_STATE_USER_1)) {
                lv_obj_set_state(obj, LV_STATE_USER_1, false);
                lv_obj_t * parent = lv_obj_get_parent(ui_PlayList[playlist_state.current_index]);
                lv_obj_add_flag(ui_comp_get_child(parent, UI_COMP_DATEITEM_ADD), LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(ui_comp_get_child(parent, UI_COMP_DATEITEM_SUB), LV_OBJ_FLAG_HIDDEN);
            } else {
                lv_obj_set_state(obj, LV_STATE_USER_1, true);
                lv_obj_t * parent = lv_obj_get_parent(ui_PlayList[playlist_state.current_index]);
                lv_obj_remove_flag(ui_comp_get_child(parent, UI_COMP_DATEITEM_ADD), LV_OBJ_FLAG_HIDDEN);
                lv_obj_remove_flag(ui_comp_get_child(parent, UI_COMP_DATEITEM_SUB), LV_OBJ_FLAG_HIDDEN);
            }
            break;
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_PlayList_6(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            play_list_focus_relative(1);
            break;
        case LV_KEY_DOWN:
            play_list_focus_relative(-1);
            break;
        case LV_KEY_ENTER: {
            UiRequestGetMediaFileList getMediaFileList;
            playlist_state.req_type = 1;
            playlist_state.current_page_index = 1;
            playlist_state.find_type = 1;
            play_media_list_request_init(&getMediaFileList, 0);
            UiIpcSendGetMediaFileListRequest(global_parameters.sendMsgQueId, &getMediaFileList);
            cur_focus_index = FOCUS_FIND;
            break;
        }
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}
