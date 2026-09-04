//
// Created by jinxing on 2026/3/12.
//

#include "popup_stack.h"
#include <string.h>

static bool popup_obj_valid(lv_obj_t * obj)
{
    return (obj != NULL) && lv_obj_is_valid(obj);
}

void popup_stack_init(popup_stack_t * stack, lv_indev_t * indev)
{
    if(!stack) return;

    memset(stack, 0, sizeof(*stack));
    stack->indev = indev;
}

void popup_stack_deinit(popup_stack_t * stack)
{
    if(!stack) return;

    popup_stack_pop_all(stack);
    stack->indev = NULL;
}

uint16_t popup_stack_depth(const popup_stack_t * stack)
{
    return stack ? stack->top : 0;
}

popup_desc_t * popup_stack_get_top(const popup_stack_t * stack)
{
    if(!stack || stack->top == 0) return NULL;
    return stack->layers[stack->top - 1].popup;
}

bool popup_stack_push(popup_stack_t * stack, popup_desc_t * popup)
{
    if(!stack || !stack->indev || !popup) return false;
    if(!popup->root || !popup->group) return false;
    if(stack->top >= POPUP_STACK_MAX) return false;
    if(!popup_obj_valid(popup->root)) return false;

    for(uint16_t i = 0; i < stack->top; i++) {
        if(stack->layers[i].popup == popup) return false;
    }

    popup_layer_t * layer = &stack->layers[stack->top];
    memset(layer, 0, sizeof(*layer));

    lv_group_t * cur_group = lv_indev_get_group(stack->indev);

    layer->prev_group = cur_group;
    layer->prev_focused = cur_group ? lv_group_get_focused(cur_group) : NULL;
    layer->prev_editing = cur_group ? lv_group_get_editing(cur_group) : false;
    layer->popup = popup;

    /* 冻结上一层焦点，防止误切换 */
    if(cur_group) {
        lv_group_focus_freeze(cur_group, true);
    }

    /* 显示当前弹窗 */
    lv_obj_remove_flag(popup->root, LV_OBJ_FLAG_HIDDEN);

    /* keypad 切到当前栈顶 group */
    lv_indev_set_group(stack->indev, popup->group);

    /* 默认用导航态 */
    lv_group_set_editing(popup->group, false);

    if(popup->default_focus && popup_obj_valid(popup->default_focus)) {
        lv_group_focus_obj(popup->default_focus);
    }

    stack->top++;
    return true;
}

bool popup_stack_pop(popup_stack_t * stack)
{
    if(!stack || !stack->indev || stack->top == 0) return false;

    popup_layer_t * layer = &stack->layers[stack->top - 1];
    popup_desc_t * popup = layer->popup;

    /* 隐藏当前弹窗 */
    if(popup && popup_obj_valid(popup->root)) {
        lv_obj_add_flag(popup->root, LV_OBJ_FLAG_HIDDEN);
    }

    /* 切回上一层 group */
    lv_indev_set_group(stack->indev, layer->prev_group);

    if(layer->prev_group) {
        lv_group_focus_freeze(layer->prev_group, false);
        lv_group_set_editing(layer->prev_group, layer->prev_editing);

        if(layer->prev_focused && popup_obj_valid(layer->prev_focused)) {
            lv_group_focus_obj(layer->prev_focused);
        }
    }

    memset(layer, 0, sizeof(*layer));
    stack->top--;
    return true;
}

void popup_stack_pop_all(popup_stack_t * stack)
{
    if(!stack) return;

    while(stack->top > 0) {
        if(!popup_stack_pop(stack)) {
            break;
        }
    }
}
