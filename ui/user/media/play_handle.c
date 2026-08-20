//
// Created by jinxing on 2026/1/14.
//

#include "play_handle.h"
#include <math.h>
#include "play_handle_internal.h"

FindDateTime findDateTime;
PlayListState playlist_state;
int cur_focus_index = 0;

lv_obj_t * ui_focus_temp[30];

void show_play_page(void)
{
    ReqGetMediaFileList_st getMediaFileList;
    time_t rawtime;
    struct tm * timeinfo;

    getMediaFileList.reqFileType = -1;
    getMediaFileList.year = 2024;
    getMediaFileList.month = 0;
    getMediaFileList.day = 0;
    getMediaFileList.hour = -1;
    getMediaFileList.minute = -1;
    getMediaFileList.second = -1;
    getMediaFileList.startIndex = 0;
    getMediaFileList.reqCount = 10;
    playlist_state.req_type = 1;
    playlist_state.current_page_index = 1;
    playlist_state.find_type = 2;
    SendMsg4UiGetMediaFileListReq(global_parameters.sendMsgQueId, &getMediaFileList);

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    findDateTime.year = timeinfo->tm_year + 1900;
    findDateTime.month = timeinfo->tm_mon + 1;
    findDateTime.day = timeinfo->tm_mday;
    findDateTime.hour = timeinfo->tm_hour;
    findDateTime.minute = timeinfo->tm_min;

    lv_label_set_text_fmt(ui_PlayList[1], "%d", findDateTime.year);
    lv_label_set_text_fmt(ui_PlayList[2], "%02d", findDateTime.month);
    lv_label_set_text_fmt(ui_PlayList[3], "%02d", findDateTime.day);
    lv_label_set_text_fmt(ui_PlayList[4], "%02d", findDateTime.hour);
    lv_label_set_text_fmt(ui_PlayList[5], "%02d", findDateTime.minute);

    lv_obj_set_style_border_color(ui_PlayList[7], lv_color_hex(0x37F6FA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PlayList[7], 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_border_color(ui_PlayList[8], lv_color_hex(0x708383), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PlayList[8], 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PlayList[9 + playlist_state.current_play_list] = ui_BTN4;
    ui_PlayList[9 + playlist_state.current_play_list + 1] = ui_BTN5;
    ui_PlayList[9 + playlist_state.current_play_list + 2] = ui_BTN6;

    playlist_state.current_items = 9 + playlist_state.current_play_list + 3;
    lv_group_remove_all_objs(keypad_group);
    for(uint32_t i = 0; i < playlist_state.current_items; i++) {
        lv_group_add_obj(keypad_group, ui_PlayList[i]);
    }

    cur_focus_index = FOCUS_ALL;
    playlist_state.current_index = 0;
    playlist_state.current_item_mode = PLAY_MODE;
    g_app.playPageFlag = 1;
    for(uint32_t i = 0; i < UI_MAX_DIVIDING_PLATES_NUM; i++) {
        if(g_app.reticle_state[i] == 1) {
            lv_obj_add_flag(ui_dividing_contimage[i], LV_OBJ_FLAG_HIDDEN);
        }
    }
    lv_screen_load(ui_ScrFileMgr);
}

void hidden_play_page(void)
{
    ui_focus_temp[0] = ui_rowstandby;
    ui_focus_temp[1] = ui_rowcompasscalibration;
    ui_focus_temp[2] = ui_rowdeadpixel;
    ui_focus_temp[3] = ui_rowstatusbar;
    ui_focus_temp[4] = ui_rowdeletefile;
    ui_focus_temp[5] = ui_rowsetting;

    lv_group_remove_all_objs(keypad_group);

    for(int i = 0; i < 6; i++) {
        lv_group_add_obj(keypad_group, ui_focus_temp[i]);
    }
    lv_group_focus_obj(ui_focus_temp[4]);
    g_app.playPageFlag = 0;
    for(uint32_t i = 0; i < UI_MAX_DIVIDING_PLATES_NUM; i++) {
        if(g_app.reticle_state[i] == 1) {
            lv_obj_remove_flag(ui_dividing_contimage[i], LV_OBJ_FLAG_HIDDEN);
        }
    }

    lv_screen_load(ui_MainPage);
}


int8_t get_days_in_month(int year, int month)
{
    switch(month) {
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2: {
        // 判断闰年：能被4整除但不能被100整除，或能被400整除
        if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return 29;
        }
        return 28;
    }
    default:
        return 31;
    }
}

void play_list_display(RspGetMediaFileList_st * fileList, MediaFileInfo_st ** fileInfo)
{
    if(fileList->fileCount > UI_MAX_MEDIA_FILE_NUM_ONE_PAGE) {
        return;
    }
    if(playlist_state.current_play_list > 0) {
        for(uint32_t i = 9; i < playlist_state.current_play_list + 9; i++) {
            lv_obj_delete(ui_PlayList[i]);
            ui_PlayList[i] = NULL;
        }
        playlist_state.current_play_list = 0;
    }
    LV_LOG_USER("fileList->fileCount:%d, fileList->totalCount:%d", fileList->fileCount, fileList->totalCount);
    for(int i = 9; i < fileList->fileCount + 9; i++) {
        LV_LOG_USER("%d %lld %d %d %s",
                    fileInfo[i - 9]->type,
                    fileInfo[i - 9]->size,
                    fileInfo[i - 9]->duration,
                    fileInfo[i - 9]->createTime,
                    fileInfo[i - 9]->name);
        char buf[256] = {0};
        ui_PlayList[i] = ui_listItem_create(ui_List_Container);
        lv_label_set_text(ui_comp_get_child(ui_PlayList[i], UI_COMP_LISTITEM_1), (const char *)fileInfo[i - 9]->name);
        int64_t bytes = fileInfo[i - 9]->size;
        const char * units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB"};
        int uint_index = 0;
        double value = (double)bytes;
        while(uint_index < 6 && fabs(value) >= 1024.0) {
            value /= 1024.0;
            uint_index++;
        }
        lv_label_set_text_fmt(
            ui_comp_get_child(ui_PlayList[i], UI_COMP_LISTITEM_2),
            "%.2f%s",
            value,
            units[uint_index]);
        uint32_t hours = fileInfo[i - 9]->duration / 3600;
        uint32_t mins = (fileInfo[i - 9]->duration % 3600) / 60;
        uint32_t secs = fileInfo[i - 9]->duration % 60;
        lv_label_set_text_fmt(
            ui_comp_get_child(ui_PlayList[i], UI_COMP_LISTITEM_3),
            "%02d:%02d:%02d",
            hours,
            mins,
            secs);
        time_t fileTime = fileInfo[i - 9]->createTime;
        struct tm * pTmInfo = localtime(&fileTime);
        strftime(buf, 256, "%Y-%m-%d %H:%M:%S", pTmInfo);
        lv_label_set_text_fmt(ui_comp_get_child(ui_PlayList[i], UI_COMP_LISTITEM_4), "%s", buf);
    }
    playlist_state.total_page_index = fileList->totalCount;
    if(playlist_state.total_page_index % UI_MAX_MEDIA_FILE_NUM_ONE_PAGE == 0) {
        playlist_state.total_page_index /= UI_MAX_MEDIA_FILE_NUM_ONE_PAGE;
    } else {
        playlist_state.total_page_index /= UI_MAX_MEDIA_FILE_NUM_ONE_PAGE;
        playlist_state.total_page_index += 1;
    }

    if(playlist_state.req_type == 2) {
        playlist_state.current_page_index--;
    } else if(playlist_state.req_type == 3) {
        playlist_state.current_page_index++;
    }
    if(fileList->fileCount == 0) {
        playlist_state.current_page_index = 0;
    }

    lv_label_set_text_fmt(ui_comp_get_child(ui_BTN7, UI_COMP_BTN_BTNL),
                          "%d/%d",
                          playlist_state.current_page_index,
                          playlist_state.total_page_index);
    ui_PlayList[fileList->fileCount + 9] = ui_BTN4;
    ui_PlayList[fileList->fileCount + 9 + 1] = ui_BTN5;
    ui_PlayList[fileList->fileCount + 9 + 2] = ui_BTN6;

    playlist_state.current_play_list = fileList->fileCount;
    playlist_state.current_items = 9 + playlist_state.current_play_list + 3;
    playlist_state.current_index = 0;
    lv_group_remove_all_objs(keypad_group);
    for(uint32_t i = 0; i < playlist_state.current_items; i++) {
        lv_group_add_obj(keypad_group, ui_PlayList[i]);
    }
    LV_LOG_USER("playlist_state.current_items:%d", playlist_state.current_items);
    for(uint32_t i = 9; i < playlist_state.current_items - 3; i++) {
        lv_obj_add_event_cb(ui_PlayList[i], ui_event_play_or_del, LV_EVENT_ALL, NULL);
    }

    if(cur_focus_index == FOCUS_ALL) {
        playlist_state.current_index = 0;
        lv_group_focus_obj(ui_PlayList[0]);
    } else if(cur_focus_index == FOCUS_FIND) {
        playlist_state.current_index = 6;
        lv_group_focus_obj(ui_PlayList[6]);
    } else if(cur_focus_index == FOCUS_PREV) {
        playlist_state.current_index = fileList->fileCount + 9 + 1;
        lv_group_focus_obj(ui_PlayList[fileList->fileCount + 9 + 1]);
    } else if(cur_focus_index == FOCUS_NEXT) {
        playlist_state.current_index = fileList->fileCount + 9 + 2;
        lv_group_focus_obj(ui_PlayList[fileList->fileCount + 9 + 2]);
    } else if(cur_focus_index == FOCUS_DEL) {
        playlist_state.current_index = 9;
        lv_group_focus_obj(ui_PlayList[9]);
    }
}

void play_event_init(void)
{
    ui_PlayList[0] = ui_BTN;
    ui_PlayList[1] = ui_comp_get_child(ui_year, UI_COMP_DATEITEM_NUM);
    ui_PlayList[2] = ui_comp_get_child(ui_month, UI_COMP_DATEITEM_NUM);
    ui_PlayList[3] = ui_comp_get_child(ui_day, UI_COMP_DATEITEM_NUM);
    ui_PlayList[4] = ui_comp_get_child(ui_hour, UI_COMP_DATEITEM_NUM);
    ui_PlayList[5] = ui_comp_get_child(ui_min, UI_COMP_DATEITEM_NUM);
    ui_PlayList[6] = ui_BTN1;
    ui_PlayList[7] = ui_BTN2;
    ui_PlayList[8] = ui_BTN3;

    lv_obj_add_event_cb(ui_PlayList[0], ui_event_PlayList_1, LV_EVENT_ALL, ui_PlayList[0]);
    for(int i = 1; i < 6; i++) {
        lv_obj_add_event_cb(ui_PlayList[i], ui_event_PlayList_1_5, LV_EVENT_ALL, ui_PlayList[i]);
    }

    lv_obj_add_event_cb(ui_PlayList[6], ui_event_PlayList_6, LV_EVENT_ALL, ui_PlayList[6]);
    lv_obj_add_event_cb(ui_PlayList[7], ui_event_PlayList_7, LV_EVENT_ALL, ui_PlayList[7]);
    lv_obj_add_event_cb(ui_PlayList[8], ui_event_PlayList_8, LV_EVENT_ALL, ui_PlayList[8]);
    lv_obj_add_event_cb(ui_BTN4, ui_event_PlayList_back, LV_EVENT_ALL, ui_BTN4);
    lv_obj_add_event_cb(ui_BTN5, ui_event_PlayList_prev, LV_EVENT_ALL, ui_BTN5);
    lv_obj_add_event_cb(ui_BTN6, ui_event_PlayList_next, LV_EVENT_ALL, ui_BTN6);
    lv_obj_add_event_cb(ui_PlayBar, ui_event_video_play, LV_EVENT_ALL, ui_PlayBar);
}