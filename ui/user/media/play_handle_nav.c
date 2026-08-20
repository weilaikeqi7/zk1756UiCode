//
// Created by jinxing on 2026/1/14.
//

#include "play_handle.h"
#include "play_handle_internal.h"

void ui_event_PlayList_7(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            playlist_state.current_index = (playlist_state.current_index + 1) % playlist_state.current_items;
            lv_group_focus_obj(ui_PlayList[playlist_state.current_index]);
            break;
        case LV_KEY_DOWN:
            playlist_state.current_index =
                (playlist_state.current_index - 1 + playlist_state.current_items) % playlist_state.current_items;
            lv_group_focus_obj(ui_PlayList[playlist_state.current_index]);
            break;
        case LV_KEY_ENTER:
            lv_obj_set_style_border_color(ui_PlayList[7], lv_color_hex(0x37F6FA), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(ui_PlayList[7], 255, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_obj_set_style_border_color(ui_PlayList[8], lv_color_hex(0x708383), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(ui_PlayList[8], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            playlist_state.current_item_mode = PLAY_MODE;
            break;
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_PlayList_8(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            playlist_state.current_index = (playlist_state.current_index + 1) % playlist_state.current_items;
            lv_group_focus_obj(ui_PlayList[playlist_state.current_index]);
            break;
        case LV_KEY_DOWN:
            playlist_state.current_index =
                (playlist_state.current_index - 1 + playlist_state.current_items) % playlist_state.current_items;
            lv_group_focus_obj(ui_PlayList[playlist_state.current_index]);
            break;
        case LV_KEY_ENTER:
            lv_obj_set_style_border_color(ui_PlayList[8], lv_color_hex(0x37F6FA), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(ui_PlayList[8], 255, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_obj_set_style_border_color(ui_PlayList[7], lv_color_hex(0x708383), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(ui_PlayList[7], 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            playlist_state.current_item_mode = DEL_MODE;
            break;
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_PlayList_back(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            playlist_state.current_index = (playlist_state.current_index + 1) % playlist_state.current_items;
            lv_group_focus_obj(ui_PlayList[playlist_state.current_index]);
            break;
        case LV_KEY_DOWN:
            playlist_state.current_index =
                (playlist_state.current_index - 1 + playlist_state.current_items) % playlist_state.current_items;
            lv_group_focus_obj(ui_PlayList[playlist_state.current_index]);
            break;
        case LV_KEY_ENTER:
            hidden_play_page();
            SendMsg4UiExitPlaybackListReq(global_parameters.sendMsgQueId);
            break;
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_PlayList_prev(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            playlist_state.current_index = (playlist_state.current_index + 1) % playlist_state.current_items;
            lv_group_focus_obj(ui_PlayList[playlist_state.current_index]);
            break;
        case LV_KEY_DOWN:
            playlist_state.current_index =
                (playlist_state.current_index - 1 + playlist_state.current_items) % playlist_state.current_items;
            lv_group_focus_obj(ui_PlayList[playlist_state.current_index]);
            break;
        case LV_KEY_ENTER:
            playlist_state.req_type = 2;
            if(playlist_state.current_page_index > 1) {
                ReqGetMediaFileList_st getMediaFileList;
                getMediaFileList.reqFileType = -1;
                if(playlist_state.find_type == 1) {
                    getMediaFileList.year = 2024;
                    getMediaFileList.month = 0;
                    getMediaFileList.day = 0;
                    getMediaFileList.hour = -1;
                    getMediaFileList.minute = -1;
                    getMediaFileList.second = -1;
                    if(findDateTime.year == 2024) {
                    } else if(findDateTime.month == 0) {
                        getMediaFileList.year = findDateTime.year;
                    } else if(findDateTime.day == 0) {
                        getMediaFileList.year = findDateTime.year;
                        getMediaFileList.month = findDateTime.month;
                    } else if(findDateTime.hour == -1) {
                        getMediaFileList.year = findDateTime.year;
                        getMediaFileList.month = findDateTime.month;
                        getMediaFileList.day = findDateTime.day;
                    } else if(findDateTime.minute == -1) {
                        getMediaFileList.year = findDateTime.year;
                        getMediaFileList.month = findDateTime.month;
                        getMediaFileList.day = findDateTime.day;
                        getMediaFileList.hour = findDateTime.hour;
                    } else {
                        getMediaFileList.year = findDateTime.year;
                        getMediaFileList.month = findDateTime.month;
                        getMediaFileList.day = findDateTime.day;
                        getMediaFileList.hour = findDateTime.hour;
                        getMediaFileList.minute = findDateTime.minute;
                    }
                } else if(playlist_state.find_type == 2) {
                    getMediaFileList.year = 2024;
                    getMediaFileList.month = 0;
                    getMediaFileList.day = 0;
                    getMediaFileList.hour = -1;
                    getMediaFileList.minute = -1;
                    getMediaFileList.second = -1;
                }
                getMediaFileList.startIndex = (playlist_state.current_page_index - 1) * UI_MAX_MEDIA_FILE_NUM_ONE_PAGE -
                                              UI_MAX_MEDIA_FILE_NUM_ONE_PAGE;
                getMediaFileList.reqCount = 10;
                SendMsg4UiGetMediaFileListReq(global_parameters.sendMsgQueId, &getMediaFileList);
                cur_focus_index = FOCUS_PREV;
            }
            break;
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_PlayList_next(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());
        switch(key) {
        case LV_KEY_UP:
            playlist_state.current_index = (playlist_state.current_index + 1) % playlist_state.current_items;
            lv_group_focus_obj(ui_PlayList[playlist_state.current_index]);
            break;
        case LV_KEY_DOWN:
            playlist_state.current_index =
                (playlist_state.current_index - 1 + playlist_state.current_items) % playlist_state.current_items;
            lv_group_focus_obj(ui_PlayList[playlist_state.current_index]);
            break;
        case LV_KEY_ENTER:
            playlist_state.req_type = 3;
            if(playlist_state.current_page_index < (int32_t)playlist_state.total_page_index) {
                ReqGetMediaFileList_st getMediaFileList;
                getMediaFileList.reqFileType = -1;
                if(playlist_state.find_type == 1) {
                    getMediaFileList.year = 2024;
                    getMediaFileList.month = 0;
                    getMediaFileList.day = 0;
                    getMediaFileList.hour = -1;
                    getMediaFileList.minute = -1;
                    getMediaFileList.second = -1;
                    if(findDateTime.year == 2024) {
                    } else if(findDateTime.month == 0) {
                        getMediaFileList.year = findDateTime.year;
                    } else if(findDateTime.day == 0) {
                        getMediaFileList.year = findDateTime.year;
                        getMediaFileList.month = findDateTime.month;
                    } else if(findDateTime.hour == -1) {
                        getMediaFileList.year = findDateTime.year;
                        getMediaFileList.month = findDateTime.month;
                        getMediaFileList.day = findDateTime.day;
                    } else if(findDateTime.minute == -1) {
                        getMediaFileList.year = findDateTime.year;
                        getMediaFileList.month = findDateTime.month;
                        getMediaFileList.day = findDateTime.day;
                        getMediaFileList.hour = findDateTime.hour;
                    } else {
                        getMediaFileList.year = findDateTime.year;
                        getMediaFileList.month = findDateTime.month;
                        getMediaFileList.day = findDateTime.day;
                        getMediaFileList.hour = findDateTime.hour;
                        getMediaFileList.minute = findDateTime.minute;
                    }
                } else if(playlist_state.find_type == 2) {
                    getMediaFileList.year = 2024;
                    getMediaFileList.month = 0;
                    getMediaFileList.day = 0;
                    getMediaFileList.hour = -1;
                    getMediaFileList.minute = -1;
                    getMediaFileList.second = -1;
                }
                getMediaFileList.startIndex = playlist_state.current_page_index * UI_MAX_MEDIA_FILE_NUM_ONE_PAGE;
                //LV_LOG_USER("fileNo %d", FileList.fileNo);
                getMediaFileList.reqCount = 10;
                SendMsg4UiGetMediaFileListReq(global_parameters.sendMsgQueId, &getMediaFileList);
                cur_focus_index = FOCUS_NEXT;
            }
            break;
        case LV_KEY_ESC:
            break;
        default:
            break;
        }
    }
}

void ui_event_play_or_del(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = *((uint32_t *)lv_event_get_param(e));

        switch(key) {
        case LV_KEY_UP:
            playlist_state.current_index = (playlist_state.current_index + 1) % playlist_state.current_items;
            lv_group_focus_obj(ui_PlayList[playlist_state.current_index]);
            break;
        case LV_KEY_DOWN:
            playlist_state.current_index =
                (playlist_state.current_index - 1 + playlist_state.current_items) % playlist_state.current_items;
            lv_group_focus_obj(ui_PlayList[playlist_state.current_index]);
            break;
        case LV_KEY_ENTER:
            if(playlist_state.current_item_mode == PLAY_MODE) {
                char tempBuff[256];
                sprintf(tempBuff,
                        "%s",
                        lv_label_get_text(
                            ui_comp_get_child(ui_PlayList[playlist_state.current_index], UI_COMP_LISTITEM_1)));
                SendMsg4UiPlayMediaFileReq(global_parameters.sendMsgQueId, (ROE_S8 *)tempBuff);
            } else {
                char tempBuff[256];
                sprintf(tempBuff,
                        "%s",
                        lv_label_get_text(
                            ui_comp_get_child(ui_PlayList[playlist_state.current_index], UI_COMP_LISTITEM_1)));
                SendMsg4UiDelMediaFileReq(global_parameters.sendMsgQueId, (ROE_S8 *)tempBuff);
                cur_focus_index = FOCUS_DEL;
            }
            break;
        default:
            break;
        }
    }
}

void ui_event_video_play(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_KEY) {
        uint32_t key = lv_indev_get_key(lv_indev_active());

        switch(key) {
        case LV_KEY_UP:
            SendMsg4UiPlayPriorOrNextMediaFileReq(global_parameters.sendMsgQueId, 1);
            break;
        case LV_KEY_DOWN:
            SendMsg4UiPlayPriorOrNextMediaFileReq(global_parameters.sendMsgQueId, 0);
            break;
        case LV_KEY_ENTER:
            SendMsg4UiExitMediaPlayReq(global_parameters.sendMsgQueId);
            break;
        default:
            break;
        }
    }
}