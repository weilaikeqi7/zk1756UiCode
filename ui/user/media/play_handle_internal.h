#ifndef ZKSL_75_6LC_PLAY_HANDLE_INTERNAL_H
#define ZKSL_75_6LC_PLAY_HANDLE_INTERNAL_H

#include "play_handle.h"

extern int cur_focus_index;
extern lv_obj_t * ui_focus_temp[30];

void ui_event_play_or_del(lv_event_t * e);
void ui_event_video_play(lv_event_t * e);

#endif
