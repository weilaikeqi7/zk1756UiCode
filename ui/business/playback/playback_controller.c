//
// Created by jinxing on 2026/1/14.
//

#include "playback_controller.h"
#include "lvgl/lvgl.h"
#include <math.h>
#include <string.h>
#include "playback_internal.h"
#include "ui_focus_manager.h"

FindDateTime findDateTime;
PlayListState playlist_state;
int cur_focus_index = 0;

static void clear_media_list_items(uint32_t media_count)
{
    ui_focus_group_clear();

    if(media_count > UI_MAX_MEDIA_FILE_NUM_ONE_PAGE) {
        media_count = UI_MAX_MEDIA_FILE_NUM_ONE_PAGE;
    }
    for(uint32_t i = PLAYLIST_MEDIA_FIRST_INDEX;
        i < PLAYLIST_MEDIA_FIRST_INDEX + media_count;
        i++) {
        if(ui_PlayList[i] != NULL) {
            lv_obj_delete(ui_PlayList[i]);
            ui_PlayList[i] = NULL;
        }
    }
    playlist_state.current_play_list = 0;
}

static bool playback_controls_ready(void)
{
    if(keypad_group == NULL || ui_List_Container == NULL || ui_BTN4 == NULL || ui_BTN5 == NULL ||
       ui_BTN6 == NULL || ui_PlayBar == NULL) {
        return false;
    }

    for(uint32_t i = 0; i < 9U; i++) {
        if(ui_PlayList[i] == NULL || !lv_obj_is_valid(ui_PlayList[i])) return false;
    }
    return true;
}

static void add_playback_event(lv_obj_t * object, lv_event_cb_t callback, void * user_data)
{
    if(object == NULL || !lv_obj_is_valid(object) || callback == NULL) return;
    lv_obj_add_event_cb(object, callback, LV_EVENT_ALL, user_data);
}

void play_list_focus_index(uint32_t index)
{
    if(keypad_group == NULL || index >= playlist_state.current_items || ui_PlayList[index] == NULL ||
       !lv_obj_is_valid(ui_PlayList[index])) {
        return;
    }

    playlist_state.current_index = index;
    ui_focus_group_focus(ui_PlayList[index]);
}

void play_list_focus_relative(int step)
{
    const uint32_t item_count = playlist_state.current_items;
    if(item_count == 0U || step == 0) return;

    int64_t index = (int64_t)playlist_state.current_index;
    const int64_t count = (int64_t)item_count;
    index = (index + step) % count;
    if(index < 0) index += count;

    for(uint32_t i = 0; i < item_count; i++) {
        uint32_t candidate = (uint32_t)index;
        if(ui_PlayList[candidate] != NULL) {
            play_list_focus_index(candidate);
            return;
        }
        index = (index + (step > 0 ? 1 : -1)) % count;
        if(index < 0) index += count;
    }
}

void play_media_list_request_init(UiRequestGetMediaFileList * request, ROE_U32 startIndex)
{
    if(request == NULL) return;

    memset(request, 0, sizeof(*request));
    request->requestedFileType = -1;
    request->year = 2024;
    request->month = 0;
    request->day = 0;
    request->hour = -1;
    request->minute = -1;
    request->second = -1;
    request->startIndex = startIndex;
    request->requestCount = UI_MAX_MEDIA_FILE_NUM_ONE_PAGE;

    if(playlist_state.find_type != 1) return;

    if(findDateTime.year == 2024) return;
    request->year = findDateTime.year;
    if(findDateTime.month == 0) return;
    request->month = findDateTime.month;
    if(findDateTime.day == 0) return;
    request->day = findDateTime.day;
    if(findDateTime.hour == -1) return;
    request->hour = findDateTime.hour;
    if(findDateTime.minute == -1) return;
    request->minute = findDateTime.minute;
}

void show_play_page(void)
{
    UiRequestGetMediaFileList getMediaFileList;
    time_t rawtime;
    struct tm * timeinfo;

    if(!playback_controls_ready()) {
        LV_LOG_ERROR("[MEDIA][INIT] playlist controls are not initialized");
        return;
    }

    playlist_state.req_type = 1;
    playlist_state.current_page_index = 1;
    playlist_state.find_type = 2;
    play_media_list_request_init(&getMediaFileList, 0);
    UiIpcSendGetMediaFileListRequest(global_parameters.sendMsgQueId, &getMediaFileList);

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if(timeinfo == NULL) {
        LV_LOG_ERROR("[MEDIA][INIT] failed to get local time");
        return;
    }
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

    ui_PlayList[PLAYLIST_MEDIA_FIRST_INDEX + playlist_state.current_play_list] = ui_BTN4;
    ui_PlayList[PLAYLIST_MEDIA_FIRST_INDEX + playlist_state.current_play_list + 1] = ui_BTN5;
    ui_PlayList[PLAYLIST_MEDIA_FIRST_INDEX + playlist_state.current_play_list + 2] = ui_BTN6;

    playlist_state.current_items = PLAYLIST_MEDIA_FIRST_INDEX + playlist_state.current_play_list +
                                   PLAYLIST_ACTION_ITEM_COUNT;
    ui_focus_group_set(ui_PlayList, playlist_state.current_items);

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
    lv_obj_t * objects[] = {
        ui_rowstandby, ui_rowcompasscalibration, ui_rowdeadpixel,
        ui_rowstatusbar, ui_rowdeletefile, ui_rowsetting,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(ui_rowdeletefile);
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

void play_list_display(UiResponseGetMediaFileList * fileList, UiMediaFileInfo ** fileInfo)
{
    if(fileList == NULL || fileInfo == NULL || ui_List_Container == NULL || keypad_group == NULL ||
       ui_BTN4 == NULL || ui_BTN5 == NULL || ui_BTN6 == NULL) {
        LV_LOG_ERROR("[MEDIA][UI][DROP] playlist objects are not initialized");
        return;
    }
    if(fileList->fileCount > UI_MAX_MEDIA_FILE_NUM_ONE_PAGE) {
        LV_LOG_WARN("[MEDIA][UI][DROP] invalid file count:%u", (unsigned)fileList->fileCount);
        return;
    }
    for(ROE_U8 i = 0; i < fileList->fileCount; i++) {
        if(fileInfo[i] == NULL) {
            LV_LOG_WARN("[MEDIA][UI][DROP] null file info index:%u", (unsigned)i);
            return;
        }
    }

    clear_media_list_items(playlist_state.current_play_list);
    LV_LOG_USER("fileList->fileCount:%d, fileList->totalCount:%d", fileList->fileCount, fileList->totalCount);
    for(uint32_t i = PLAYLIST_MEDIA_FIRST_INDEX;
        i < (uint32_t)fileList->fileCount + PLAYLIST_MEDIA_FIRST_INDEX;
        i++) {
        char fileName[256] = {0};
        ROE_SIZE nameLength = fileInfo[i - PLAYLIST_MEDIA_FIRST_INDEX]->nameLength;
        if(nameLength >= sizeof(fileName)) {
            nameLength = sizeof(fileName) - 1U;
        }
        memcpy(fileName, fileInfo[i - PLAYLIST_MEDIA_FIRST_INDEX]->name, nameLength);
        fileName[nameLength] = '\0';
        LV_LOG_USER("%d %lld %d %d %s",
                    fileInfo[i - PLAYLIST_MEDIA_FIRST_INDEX]->type,
                    fileInfo[i - PLAYLIST_MEDIA_FIRST_INDEX]->size,
                    fileInfo[i - PLAYLIST_MEDIA_FIRST_INDEX]->duration,
                    fileInfo[i - PLAYLIST_MEDIA_FIRST_INDEX]->createTime,
                    fileName);
        char buf[256] = {0};
        ui_PlayList[i] = ui_listItem_create(ui_List_Container);
        if(ui_PlayList[i] == NULL) {
            LV_LOG_ERROR("[MEDIA][UI][DROP] create playlist item failed index:%u",
                         (unsigned)(i - PLAYLIST_MEDIA_FIRST_INDEX));
            clear_media_list_items((uint32_t)(i - PLAYLIST_MEDIA_FIRST_INDEX + 1));
            return;
        }
        lv_obj_t * nameLabel = ui_comp_get_child(ui_PlayList[i], UI_COMP_LISTITEM_1);
        lv_obj_t * sizeLabel = ui_comp_get_child(ui_PlayList[i], UI_COMP_LISTITEM_2);
        lv_obj_t * durationLabel = ui_comp_get_child(ui_PlayList[i], UI_COMP_LISTITEM_3);
        lv_obj_t * dateLabel = ui_comp_get_child(ui_PlayList[i], UI_COMP_LISTITEM_4);
        if(nameLabel == NULL || sizeLabel == NULL || durationLabel == NULL || dateLabel == NULL) {
            LV_LOG_ERROR("[MEDIA][UI][DROP] playlist item children missing index:%u",
                         (unsigned)(i - PLAYLIST_MEDIA_FIRST_INDEX));
            clear_media_list_items((uint32_t)(i - PLAYLIST_MEDIA_FIRST_INDEX + 1));
            return;
        }
        lv_label_set_text(nameLabel, fileName);
        int64_t bytes = fileInfo[i - PLAYLIST_MEDIA_FIRST_INDEX]->size;
        const char * units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB"};
        int uint_index = 0;
        double value = (double)bytes;
        while(uint_index < 6 && fabs(value) >= 1024.0) {
            value /= 1024.0;
            uint_index++;
        }
        lv_label_set_text_fmt(sizeLabel, "%.2f%s", value, units[uint_index]);
        int32_t duration = fileInfo[i - PLAYLIST_MEDIA_FIRST_INDEX]->duration;
        if(duration < 0) duration = 0;
        uint32_t hours = (uint32_t)duration / 3600U;
        uint32_t mins = ((uint32_t)duration % 3600U) / 60U;
        uint32_t secs = (uint32_t)duration % 60U;
        lv_label_set_text_fmt(durationLabel, "%02d:%02d:%02d", hours, mins, secs);
        time_t fileTime = fileInfo[i - PLAYLIST_MEDIA_FIRST_INDEX]->createTime;
        struct tm * pTmInfo = localtime(&fileTime);
        if(pTmInfo != NULL) {
            strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", pTmInfo);
        } else {
            lv_snprintf(buf, sizeof(buf), "----");
        }
        lv_label_set_text_fmt(dateLabel, "%s", buf);
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

    if(ui_BTN7 != NULL) {
        lv_obj_t * pageLabel = ui_comp_get_child(ui_BTN7, UI_COMP_BTN_BTNL);
        if(pageLabel != NULL) {
            lv_label_set_text_fmt(pageLabel,
                                  "%d/%d",
                                  playlist_state.current_page_index,
                                  playlist_state.total_page_index);
        }
    }
    ui_PlayList[fileList->fileCount + PLAYLIST_MEDIA_FIRST_INDEX] = ui_BTN4;
    ui_PlayList[fileList->fileCount + PLAYLIST_MEDIA_FIRST_INDEX + 1] = ui_BTN5;
    ui_PlayList[fileList->fileCount + PLAYLIST_MEDIA_FIRST_INDEX + 2] = ui_BTN6;

    playlist_state.current_play_list = fileList->fileCount;
    playlist_state.current_items = PLAYLIST_MEDIA_FIRST_INDEX + playlist_state.current_play_list + PLAYLIST_ACTION_ITEM_COUNT;
    playlist_state.current_index = 0;
    ui_focus_group_set(ui_PlayList, playlist_state.current_items);
    LV_LOG_USER("playlist_state.current_items:%d", playlist_state.current_items);
    for(uint32_t i = PLAYLIST_MEDIA_FIRST_INDEX;
        i < playlist_state.current_items - PLAYLIST_ACTION_ITEM_COUNT;
        i++) {
        if(ui_PlayList[i] != NULL) {
            add_playback_event(ui_PlayList[i], ui_event_play_or_del, NULL);
        }
    }

    if(cur_focus_index == FOCUS_ALL) {
        play_list_focus_index(0);
    } else if(cur_focus_index == FOCUS_FIND) {
        play_list_focus_index(6);
    } else if(cur_focus_index == FOCUS_PREV) {
        play_list_focus_index(fileList->fileCount + PLAYLIST_MEDIA_FIRST_INDEX + 1);
    } else if(cur_focus_index == FOCUS_NEXT) {
        play_list_focus_index(fileList->fileCount + PLAYLIST_MEDIA_FIRST_INDEX + 2);
    } else if(cur_focus_index == FOCUS_DEL) {
        play_list_focus_index(PLAYLIST_MEDIA_FIRST_INDEX);
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

    add_playback_event(ui_PlayList[0], ui_event_PlayList_1, ui_PlayList[0]);
    for(int i = 1; i < 6; i++) {
        add_playback_event(ui_PlayList[i], ui_event_PlayList_1_5, ui_PlayList[i]);
    }

    add_playback_event(ui_PlayList[6], ui_event_PlayList_6, ui_PlayList[6]);
    add_playback_event(ui_PlayList[7], ui_event_PlayList_7, ui_PlayList[7]);
    add_playback_event(ui_PlayList[8], ui_event_PlayList_8, ui_PlayList[8]);
    add_playback_event(ui_BTN4, ui_event_PlayList_back, ui_BTN4);
    add_playback_event(ui_BTN5, ui_event_PlayList_prev, ui_BTN5);
    add_playback_event(ui_BTN6, ui_event_PlayList_next, ui_BTN6);
    add_playback_event(ui_PlayBar, ui_event_video_play, ui_PlayBar);
}
