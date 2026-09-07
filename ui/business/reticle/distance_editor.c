//
// Created by jinxing on 2026/2/3.
//

#include "distance_editor.h"
#include "ui.h"
#include "ui_focus_manager.h"
#include "lv_port_indev.h"

static bool s_inited = false;
static bool s_opened = false;

/* 记录弹窗初始坐标（SquareLine 默认位置）：Add Distance 需要保持该位置 */
static bool s_pos_inited = false;
static lv_coord_t s_init_x = 0;
static lv_coord_t s_init_y = 0;

/* 触发弹窗的控件：弹窗期间临时加 LV_STATE_USER_1，关闭时恢复 */
static lv_obj_t * s_owner_obj = NULL;
static bool s_owner_had_user1 = false;

static distance_editor_ok_cb_t s_ok_cb = NULL;
static void * s_ok_user = NULL;
static distance_editor_cancel_cb_t s_cancel_cb = NULL;
static void * s_cancel_user = NULL;
static distance_editor_restore_cb_t s_restore_cb = NULL;
static void * s_restore_user = NULL;

static int s_d1 = 0, s_d2 = 0, s_d3 = 0, s_d4 = 0;

static lv_obj_t * distance_child(int child_id)
{
    if(ui_editdistance == NULL) return NULL;
    return ui_comp_get_child(ui_editdistance, child_id);
}

static int clamp_0_9999(int v)
{
    if(v < 0) return 0;
    if(v > 9999) return 9999;
    return v;
}

static void set_digits_from_value(int v)
{
    v = clamp_0_9999(v);
    s_d1 = (v / 1000) % 10;
    s_d2 = (v / 100) % 10;
    s_d3 = (v / 10) % 10;
    s_d4 = v % 10;
}

static int get_value_from_digits(void)
{
    return s_d1 * 1000 + s_d2 * 100 + s_d3 * 10 + s_d4;
}

static void refresh_digit_labels(void)
{
    if(ui_editdistance == NULL) return;

    const uint8_t values[] = {s_d1, s_d2, s_d3, s_d4};
    const int label_ids[] = {
        UI_COMP_DISTANCE_VALUE1_PANELNUM_LABEL,
        UI_COMP_DISTANCE_VALUE2_PANELNUM_LABEL,
        UI_COMP_DISTANCE_VALUE3_PANELNUM_LABEL,
        UI_COMP_DISTANCE_VALUE4_PANELNUM_LABEL,
    };
    for(uint32_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        lv_obj_t * label = ui_comp_get_child(ui_editdistance, label_ids[i]);
        if(label != NULL) lv_label_set_text_fmt(label, "%d", values[i]);
    }
}

static void hide_all_arrows(void)
{
    if(ui_editdistance == NULL) return;

    const int arrow_ids[] = {
        UI_COMP_DISTANCE_VALUE1_IMAGEUP, UI_COMP_DISTANCE_VALUE1_IMAGEDOWN,
        UI_COMP_DISTANCE_VALUE2_IMAGEUP, UI_COMP_DISTANCE_VALUE2_IMAGEDOWN,
        UI_COMP_DISTANCE_VALUE3_IMAGEUP, UI_COMP_DISTANCE_VALUE3_IMAGEDOWN,
        UI_COMP_DISTANCE_VALUE4_IMAGEUP, UI_COMP_DISTANCE_VALUE4_IMAGEDOWN,
    };
    for(uint32_t i = 0; i < sizeof(arrow_ids) / sizeof(arrow_ids[0]); i++) {
        lv_obj_t * arrow = ui_comp_get_child(ui_editdistance, arrow_ids[i]);
        if(arrow != NULL) lv_obj_add_flag(arrow, LV_OBJ_FLAG_HIDDEN);
    }
}

/** 弹窗打开后，把 group 的焦点对象切换到弹窗内部 */
static void focus_to_popup(void)
{
    if(ui_editdistance == NULL) return;

    lv_obj_t * objects[] = {
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE1_PANELNUM),
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE2_PANELNUM),
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE3_PANELNUM),
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_VALUE4_PANELNUM),
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_DISTANCEOK),
        ui_comp_get_child(ui_editdistance, UI_COMP_DISTANCE_DISTANCECANCEL),
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(objects[0]);
}

static void close_internal(bool call_cancel)
{
    if(!s_opened) return;
    s_opened = false;

    if(ui_editdistance != NULL) {
        lv_obj_add_flag(ui_editdistance, LV_OBJ_FLAG_HIDDEN);
    }

    /* 关闭弹窗时恢复触发控件的 USER_1 高亮 */
    if(s_owner_obj) {
        if(!s_owner_had_user1) {
            lv_obj_clear_state(s_owner_obj, LV_STATE_USER_1);
        }
        s_owner_obj = NULL;
        s_owner_had_user1 = false;
    }

    if(call_cancel && s_cancel_cb) s_cancel_cb(s_cancel_user);
    if(s_restore_cb) s_restore_cb(s_restore_user);

    s_ok_cb = NULL;
    s_ok_user = NULL;
    s_cancel_cb = NULL;
    s_cancel_user = NULL;
    s_restore_cb = NULL;
    s_restore_user = NULL;
}

static void ok_internal(void)
{
    int v = get_value_from_digits();
    if(s_ok_cb) s_ok_cb(v, s_ok_user);
    close_internal(false);
}

/**
 * 四位数字单元的按键处理：
 * - 非编辑态：UP/DOWN 用于焦点移动
 * - 编辑态：UP/DOWN 修改数字
 * - ENTER：切换编辑态（并显示/隐藏上下箭头）
 */
static void digit_key_handler(lv_obj_t * panelnum, lv_obj_t * img_up, lv_obj_t * img_down, int * digit, lv_event_t * e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;

    uint32_t key = lv_indev_get_key(lv_indev_active());
    if(panelnum == NULL || digit == NULL) return;
    bool editing = lv_obj_has_state(panelnum, LV_STATE_USER_1);

    switch(key) {
    case LV_KEY_UP:
        if(!editing) ui_focus_group_next();
        else {
            (*digit) = (*digit + 1) % 10;
            refresh_digit_labels();
        }
        break;

    case LV_KEY_DOWN:
        if(!editing) ui_focus_group_prev();
        else {
            (*digit) = (*digit + 9) % 10;
            refresh_digit_labels();
        }
        break;

    case LV_KEY_ENTER:
        if(editing) {
            lv_obj_clear_state(panelnum, LV_STATE_USER_1);
            if(img_up != NULL) lv_obj_add_flag(img_up, LV_OBJ_FLAG_HIDDEN);
            if(img_down != NULL) lv_obj_add_flag(img_down, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_add_state(panelnum, LV_STATE_USER_1);
            if(img_up != NULL) lv_obj_remove_flag(img_up, LV_OBJ_FLAG_HIDDEN);
            if(img_down != NULL) lv_obj_remove_flag(img_down, LV_OBJ_FLAG_HIDDEN);
        }
        break;

    case LV_KEY_ESC:
        close_internal(true);
        break;

    default:
        break;
    }
}

static void ev_digit1(lv_event_t * e)
{
    digit_key_handler(
        distance_child(UI_COMP_DISTANCE_VALUE1_PANELNUM),
        distance_child(UI_COMP_DISTANCE_VALUE1_IMAGEUP),
        distance_child(UI_COMP_DISTANCE_VALUE1_IMAGEDOWN),
        &s_d1,
        e
        );
}

static void ev_digit2(lv_event_t * e)
{
    digit_key_handler(
        distance_child(UI_COMP_DISTANCE_VALUE2_PANELNUM),
        distance_child(UI_COMP_DISTANCE_VALUE2_IMAGEUP),
        distance_child(UI_COMP_DISTANCE_VALUE2_IMAGEDOWN),
        &s_d2,
        e
        );
}

static void ev_digit3(lv_event_t * e)
{
    digit_key_handler(
        distance_child(UI_COMP_DISTANCE_VALUE3_PANELNUM),
        distance_child(UI_COMP_DISTANCE_VALUE3_IMAGEUP),
        distance_child(UI_COMP_DISTANCE_VALUE3_IMAGEDOWN),
        &s_d3,
        e
        );
}

static void ev_digit4(lv_event_t * e)
{
    digit_key_handler(
        distance_child(UI_COMP_DISTANCE_VALUE4_PANELNUM),
        distance_child(UI_COMP_DISTANCE_VALUE4_IMAGEUP),
        distance_child(UI_COMP_DISTANCE_VALUE4_IMAGEDOWN),
        &s_d4,
        e
        );
}

static void ev_ok(lv_event_t * e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    if(key == LV_KEY_ENTER) ok_internal();
    else if(key == LV_KEY_ESC) close_internal(true);
    else if(key == LV_KEY_UP) ui_focus_group_next();
    else if(key == LV_KEY_DOWN) ui_focus_group_prev();
}

static void ev_cancel(lv_event_t * e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    if(key == LV_KEY_ENTER || key == LV_KEY_ESC) close_internal(true);
    else if(key == LV_KEY_UP) ui_focus_group_next();
    else if(key == LV_KEY_DOWN) ui_focus_group_prev();
}

void distance_editor_init(void)
{
    if(s_inited) return;

    if(ui_editdistance == NULL) {
        LV_LOG_ERROR("distance editor root object is unavailable");
        return;
    }
    s_inited = true;
    lv_obj_add_flag(ui_editdistance, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * digit1 = distance_child(UI_COMP_DISTANCE_VALUE1_PANELNUM);
    lv_obj_t * digit2 = distance_child(UI_COMP_DISTANCE_VALUE2_PANELNUM);
    lv_obj_t * digit3 = distance_child(UI_COMP_DISTANCE_VALUE3_PANELNUM);
    lv_obj_t * digit4 = distance_child(UI_COMP_DISTANCE_VALUE4_PANELNUM);
    lv_obj_t * ok = distance_child(UI_COMP_DISTANCE_DISTANCEOK);
    lv_obj_t * cancel = distance_child(UI_COMP_DISTANCE_DISTANCECANCEL);

    if(digit1 != NULL) lv_obj_add_event_cb(digit1, ev_digit1, LV_EVENT_ALL, NULL);
    if(digit2 != NULL) lv_obj_add_event_cb(digit2, ev_digit2, LV_EVENT_ALL, NULL);
    if(digit3 != NULL) lv_obj_add_event_cb(digit3, ev_digit3, LV_EVENT_ALL, NULL);
    if(digit4 != NULL) lv_obj_add_event_cb(digit4, ev_digit4, LV_EVENT_ALL, NULL);
    if(ok != NULL) lv_obj_add_event_cb(ok, ev_ok, LV_EVENT_ALL, NULL);
    if(cancel != NULL) lv_obj_add_event_cb(cancel, ev_cancel, LV_EVENT_ALL, NULL);

    hide_all_arrows();
}

void distance_editor_open_ex(int initial_value,
                             lv_obj_t * owner_obj,
                             bool align_right,
                             distance_editor_ok_cb_t ok_cb,
                             void * ok_user,
                             distance_editor_cancel_cb_t cancel_cb,
                             void * cancel_user,
                             distance_editor_restore_cb_t restore_cb,
                             void * restore_user)
{
    distance_editor_init();
    if(!s_inited) return;

    s_ok_cb = ok_cb;
    s_ok_user = ok_user;
    s_cancel_cb = cancel_cb;
    s_cancel_user = cancel_user;
    s_restore_cb = restore_cb;
    s_restore_user = restore_user;

    /* 记录 SquareLine 默认坐标（只记录一次） */
    if(!s_pos_inited) {
        s_init_x = lv_obj_get_x(ui_editdistance);
        s_init_y = lv_obj_get_y(ui_editdistance);
        s_pos_inited = true;
    }

    /* 标记触发控件高亮（弹窗期间） */
    s_owner_obj = owner_obj;
    s_owner_had_user1 = false;
    if(s_owner_obj) {
        s_owner_had_user1 = lv_obj_has_state(s_owner_obj, LV_STATE_USER_1);
        lv_obj_add_state(s_owner_obj, LV_STATE_USER_1);
    }

    set_digits_from_value(initial_value);
    refresh_digit_labels();

    // 清除四位的编辑态
    if(distance_child(UI_COMP_DISTANCE_VALUE1_PANELNUM) != NULL)
        lv_obj_clear_state(distance_child(UI_COMP_DISTANCE_VALUE1_PANELNUM), LV_STATE_USER_1);
    if(distance_child(UI_COMP_DISTANCE_VALUE2_PANELNUM) != NULL)
        lv_obj_clear_state(distance_child(UI_COMP_DISTANCE_VALUE2_PANELNUM), LV_STATE_USER_1);
    if(distance_child(UI_COMP_DISTANCE_VALUE3_PANELNUM) != NULL)
        lv_obj_clear_state(distance_child(UI_COMP_DISTANCE_VALUE3_PANELNUM), LV_STATE_USER_1);
    if(distance_child(UI_COMP_DISTANCE_VALUE4_PANELNUM) != NULL)
        lv_obj_clear_state(distance_child(UI_COMP_DISTANCE_VALUE4_PANELNUM), LV_STATE_USER_1);
    hide_all_arrows();

    lv_obj_remove_flag(ui_editdistance, LV_OBJ_FLAG_HIDDEN);

    /* 位置策略：
     * - Add Distance：保持 SquareLine 默认位置（避免挡住右侧刻度/其它 UI）
     * - Modify Distance：靠右显示，避免挡住左侧菜单列
     */
    if(align_right) {
        // lv_obj_t *parent = lv_obj_get_parent(ui_editdistance);
        // if (parent) {
        //     lv_coord_t pw = lv_obj_get_width(parent);
        //     lv_coord_t w  = lv_obj_get_width(ui_editdistance);
        //     lv_coord_t x  = pw - w - 20;
        //     if (x < 0) x = 0;
        //     lv_obj_set_pos(ui_editdistance, x, 40);
        //     lv_obj_set_pos(ui_editdistance, x + 180, s_init_y);
        // }
        lv_obj_set_pos(ui_editdistance, s_init_x + 190, s_init_y);
    } else {
        lv_obj_set_pos(ui_editdistance, s_init_x, s_init_y);
    }
    s_opened = true;

    focus_to_popup();
}

void distance_editor_open(int initial_value,
                          distance_editor_ok_cb_t ok_cb,
                          void * ok_user,
                          distance_editor_cancel_cb_t cancel_cb,
                          void * cancel_user,
                          distance_editor_restore_cb_t restore_cb,
                          void * restore_user)
{
    /* 兼容旧接口：默认按 Add Distance 的策略（不右移、无 owner 高亮） */
    distance_editor_open_ex(initial_value,
                            NULL,
                            false,
                            ok_cb,
                            ok_user,
                            cancel_cb,
                            cancel_user,
                            restore_cb,
                            restore_user);
}

bool distance_editor_is_open(void)
{
    return s_opened;
}

void distance_editor_close(void)
{
    close_internal(false);
}
