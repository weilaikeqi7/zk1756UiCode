#ifndef UI_FOCUS_MANAGER_H
#define UI_FOCUS_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include "lvgl.h"

/* Rebuild the shared keypad focus group from a screen-local object list. */
bool ui_focus_group_set(lv_obj_t * const * objects, uint32_t count);
bool ui_focus_group_add(lv_obj_t * object);
void ui_focus_group_clear(void);
bool ui_focus_group_focus(lv_obj_t * object);
bool ui_focus_group_next(void);
bool ui_focus_group_prev(void);

#endif
