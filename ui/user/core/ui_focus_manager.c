#include "ui_focus_manager.h"

#include "lv_port_indev.h"

void ui_focus_group_clear(void)
{
    if(keypad_group != NULL) {
        lv_group_remove_all_objs(keypad_group);
    }
}

bool ui_focus_group_add(lv_obj_t * object)
{
    if(keypad_group == NULL || object == NULL || !lv_obj_is_valid(object)) return false;

    lv_group_add_obj(keypad_group, object);
    return true;
}

bool ui_focus_group_set(lv_obj_t * const * objects, uint32_t count)
{
    if(keypad_group == NULL) return false;

    ui_focus_group_clear();
    if(objects == NULL) return true;

    bool success = true;
    for(uint32_t i = 0; i < count; i++) {
        if(!ui_focus_group_add(objects[i])) success = false;
    }
    return success;
}

bool ui_focus_group_focus(lv_obj_t * object)
{
    if(keypad_group == NULL || object == NULL || !lv_obj_is_valid(object)) return false;

    lv_group_focus_obj(object);
    return true;
}

bool ui_focus_group_next(void)
{
    if(keypad_group == NULL) return false;

    lv_group_focus_next(keypad_group);
    return true;
}

bool ui_focus_group_prev(void)
{
    if(keypad_group == NULL) return false;

    lv_group_focus_prev(keypad_group);
    return true;
}
