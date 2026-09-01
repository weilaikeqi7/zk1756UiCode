#ifndef __UI_SELF__
#define __UI_SELF__

#define SELF_ITEM_NUM   7
#include "lvgl/lvgl.h"
#include "popup_stack.h"

extern lv_obj_t * ui_self;
extern lv_obj_t * ui_self_count;
extern lv_obj_t * ui_label_title;
extern lv_obj_t * ui_self_item_cont;
extern lv_obj_t * ui_self_item[SELF_ITEM_NUM];
extern lv_obj_t * ui_self_item_label[SELF_ITEM_NUM];
extern char * self_info[];
extern lv_obj_t * ui_self_button_label;
extern popup_desc_t g_popup_self;

extern void ui_self_screen_init(void);

extern void ui_self_screen_destroy(void);

#endif