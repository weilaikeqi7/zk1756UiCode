#ifndef ZKSL_75_6LC_PLAY_HANDLE_INTERNAL_H
#define ZKSL_75_6LC_PLAY_HANDLE_INTERNAL_H

#include "play_handle.h"

#define PLAYLIST_MEDIA_FIRST_INDEX 9U
#define PLAYLIST_ACTION_ITEM_COUNT 3U

extern int cur_focus_index;
extern lv_obj_t * ui_focus_temp[30];

/** Move focus inside the current playback list without indexing an empty list. */
void play_list_focus_relative(int step);
void play_list_focus_index(uint32_t index);
void play_media_list_request_init(ReqGetMediaFileList_st * request, ROE_U32 startIndex);

void ui_event_play_or_del(lv_event_t * e);
void ui_event_video_play(lv_event_t * e);

#endif
