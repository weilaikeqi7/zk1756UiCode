//
// Created by jinxing on 2026/1/14.
//

#ifndef ZKSL_75_6LC_PLAY_HANDLE_H
#define ZKSL_75_6LC_PLAY_HANDLE_H

#include "ipcMsgQue4UiRcvRes.h"
#include "ui.h"

#pragma pack(push, 1)

enum mode { PLAY_MODE, DEL_MODE };

typedef struct {
    uint32_t current_items;     // 当前播放项数目
    uint32_t current_index;     // 当前播放项索引
    uint32_t current_play_list; // 当前播放列表
    uint8_t current_item_mode;  // 当前播放项模式
    int32_t total_items;        //总数量
    uint32_t total_page_index;
    int32_t current_page_index;
    uint8_t req_type;  //当前请求类型
    uint8_t find_type; //当前搜索类型
} PlayListState;

typedef struct {
    int16_t year;
    int8_t month;
    int8_t day;
    int8_t hour;
    int8_t minute;
} FindDateTime;

typedef enum { FOCUS_ALL, FOCUS_FIND, FOCUS_PREV, FOCUS_NEXT, FOCUS_DEL } focus_item;

#pragma pack(pop)

void ui_event_PlayList_1(lv_event_t * e);
void ui_event_PlayList_1_5(lv_event_t * e);
void ui_event_PlayList_6(lv_event_t * e);
void ui_event_PlayList_7(lv_event_t * e);
void ui_event_PlayList_8(lv_event_t * e);
void ui_event_PlayList_back(lv_event_t * e);
void ui_event_PlayList_prev(lv_event_t * e);
void ui_event_PlayList_next(lv_event_t * e);
void show_play_page(void);
void hidden_play_page(void);
void play_event_init(void);
void play_list_display(RspGetMediaFileList_st * fileList, MediaFileInfo_st ** fileInfo);
int8_t get_days_in_month(int year, int month);
extern PlayListState playlist_state;
extern FindDateTime findDateTime;
#endif //ZKSL_75_6LC_PLAY_HANDLE_H