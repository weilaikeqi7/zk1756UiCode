//
// Created by jinxing on 2026/3/12.
//

#ifndef ZKSL_75_6LC_POPUP_STACK_H
#define ZKSL_75_6LC_POPUP_STACK_H

#ifdef __cplusplus
extern "C" {



#endif

#include "lvgl.h"
#include <stdbool.h>
#include <stdint.h>

#ifndef POPUP_STACK_MAX
#define POPUP_STACK_MAX 8
#endif

/* 预创建弹窗描述 */
typedef struct {
    lv_obj_t * root; /* 弹窗根对象，预创建 */
    lv_group_t * group; /* 该弹窗自己的输入组，预创建 */
    lv_obj_t * default_focus; /* 显示该弹窗时默认焦点 */
} popup_desc_t;

/* 栈中保存的“上一层输入现场” */
typedef struct {
    lv_group_t * prev_group;
    lv_obj_t * prev_focused;
    bool prev_editing;
    popup_desc_t * popup;
} popup_layer_t;

/* 弹窗栈 */
typedef struct {
    lv_indev_t * indev;
    popup_layer_t layers[POPUP_STACK_MAX];
    uint16_t top;
} popup_stack_t;

/* 初始化 */
void popup_stack_init(popup_stack_t * stack, lv_indev_t * indev);

/* 栈深 */
uint16_t popup_stack_depth(const popup_stack_t * stack);

/* 显示一层预创建弹窗 */
bool popup_stack_push(popup_stack_t * stack, popup_desc_t * popup);

/* 隐藏最上层弹窗 */
bool popup_stack_pop(popup_stack_t * stack);

/* 隐藏所有弹窗 */
void popup_stack_pop_all(popup_stack_t * stack);

/* 获取当前栈顶弹窗 */
popup_desc_t * popup_stack_get_top(const popup_stack_t * stack);

#ifdef __cplusplus
}
#endif

#endif //ZKSL_75_6LC_POPUP_STACK_H