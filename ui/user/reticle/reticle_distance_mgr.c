// reticle_distance_mgr.c
// 分划板距离列表 UI 管理器
//
// 约定：
// 1. 距离顺序、默认距离索引都以下位机返回结果为准。
// 2. 本文件只负责把模型顺序显示到 UI，不再做本地二次排序。
// 3. tag_idx 表示协议距离标签索引，供三级/四级操作定位当前距离使用。

#include "reticle_distance_mgr.h"
#include "lvgl.h"
#include "ui.h"

/* 当前枪型对应的距离条目对象、数据缓存 */
static lv_obj_t * s_obj[RETICLE_MAX_DISTANCE_ITEMS];
static reticle_distance_entry_t s_entry[RETICLE_MAX_DISTANCE_ITEMS];
static uint8_t s_cnt = 0;

/* 当前逻辑选中项 / 默认距离项 */
static uint8_t s_sel = 0;
static uint8_t s_primary = 0;

/* 更新距离标签文本 */
static void set_item_text(lv_obj_t * item, int dist)
{
    lv_label_set_text_fmt(ui_comp_get_child(item, UI_COMP_DISTANCELABEL_CONTPILL_ITEMLABEL), "%d", dist);
}

/* 所有距离条目共用同一个 dots 图标；默认距离额外叠加 USER_2 样式。 */
static void set_item_primary_icon(lv_obj_t * item)
{
    lv_obj_t * icon = ui_comp_get_child(item, UI_COMP_DISTANCELABEL_IMGICON);
    lv_obj_remove_flag(icon, LV_OBJ_FLAG_HIDDEN);
}

/* 创建一个距离条目对象 */
static lv_obj_t * create_item_obj(void)
{
    lv_obj_t * item = ui_distancelabel_create(ui_contpagereticle);
    lv_obj_add_flag(item, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    return item;
}

/* 二级菜单里，距离条目要始终放在 8 个固定项之后 */
static uint32_t get_distance_base_index(void)
{
    if(ui_reticlerow8) {
        return (uint32_t)lv_obj_get_index(ui_reticlerow8) + 1U;
    }
    return (uint32_t)lv_obj_get_child_cnt(ui_contpagereticle);
}

/* 按当前 s_entry/s_obj 顺序，把对象重新摆到正确位置 */
static void move_all_obj_to_match_order(void)
{
    uint32_t base = get_distance_base_index();
    for(uint8_t i = 0; i < s_cnt; i++) {
        lv_obj_move_to_index(s_obj[i], (uint32_t)(base + i));
    }
}

/* 按 s_primary 给默认距离条目补 USER_2 样式。 */
static void apply_primary_icon_state(void)
{
    for(uint8_t i = 0; i < s_cnt; i++) {
        set_item_primary_icon(s_obj[i]);
        if(i == s_primary)
            lv_obj_add_state(s_obj[i], LV_STATE_USER_2);
        else
            lv_obj_clear_state(s_obj[i], LV_STATE_USER_2);
    }
}

void reticle_distance_mgr_init(void)
{
    s_cnt = 0;
    s_sel = 0;
    s_primary = 0;
}

uint8_t reticle_distance_mgr_count(void)
{
    return s_cnt;
}

reticle_distance_entry_t * reticle_distance_mgr_entry(uint8_t idx)
{
    return (idx < s_cnt) ? &s_entry[idx] : NULL;
}

reticle_distance_entry_t * reticle_distance_mgr_entry_by_tag(uint8_t tag_idx)
{
    int idx = reticle_distance_mgr_find_idx_by_tag(tag_idx);
    return (idx >= 0) ? &s_entry[idx] : NULL;
}

lv_obj_t * reticle_distance_mgr_obj(uint8_t idx)
{
    return (idx < s_cnt) ? s_obj[idx] : NULL;
}

void reticle_distance_mgr_set_visible_range(uint8_t start, uint8_t count)
{
    /* 只显示当前页对应的距离条目，其他页隐藏。 */
    for(uint8_t i = 0; i < s_cnt; i++) {
        bool in_range = (i >= start) && (i < (uint8_t)(start + count));
        if(in_range)
            lv_obj_clear_flag(s_obj[i], LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(s_obj[i], LV_OBJ_FLAG_HIDDEN);
    }
}

int reticle_distance_mgr_find_idx_by_obj(lv_obj_t * obj)
{
    for(uint8_t i = 0; i < s_cnt; i++) {
        if(s_obj[i] == obj) return (int)i;
    }
    return -1;
}

int reticle_distance_mgr_find_idx_by_tag(uint8_t tag_idx)
{
    for(uint8_t i = 0; i < s_cnt; i++) {
        if(s_entry[i].tag_idx == tag_idx) return (int)i;
    }
    return -1;
}

void reticle_distance_mgr_set_selected(uint8_t idx)
{
    if(idx < s_cnt) {
        s_sel = idx;
    }
}

void reticle_distance_mgr_set_selected_by_tag(uint8_t tag_idx)
{
    int idx = reticle_distance_mgr_find_idx_by_tag(tag_idx);
    if(idx >= 0) {
        s_sel = (uint8_t)idx;
    }
}

uint8_t reticle_distance_mgr_get_selected(void)
{
    return s_sel;
}

uint8_t reticle_distance_mgr_get_selected_tag(void)
{
    if(s_sel >= s_cnt) return 0;
    return s_entry[s_sel].tag_idx;
}

void reticle_distance_mgr_set_primary(uint8_t idx)
{
    if(idx < s_cnt) {
        s_primary = idx;
        apply_primary_icon_state();
    }
}

uint8_t reticle_distance_mgr_get_primary(void)
{
    return s_primary;
}

void reticle_distance_mgr_clear_all(void)
{
    for(int i = (int)s_cnt - 1; i >= 0; i--) {
        lv_obj_del(s_obj[i]);
    }
    s_cnt = 0;
    s_sel = 0;
    s_primary = 0;
}

void reticle_distance_mgr_load_from_cfg(const reticle_gun_cfg_t * cfg, lv_event_cb_t item_event_cb)
{
    /* 直接按模型当前顺序加载，UI 顺序与下位机返回保持一致。 */
    reticle_distance_mgr_clear_all();
    if(!cfg) return;

    s_cnt = cfg->count;
    if(s_cnt > RETICLE_MAX_DISTANCE_ITEMS) s_cnt = RETICLE_MAX_DISTANCE_ITEMS;

    for(uint8_t i = 0; i < s_cnt; i++) {
        lv_obj_t * obj = create_item_obj();
        if(!obj) break;

        s_obj[i] = obj;
        s_entry[i] = cfg->items[i];

        /* tag_idx 未初始化时，默认按当前位置处理。 */
        if(s_entry[i].tag_idx >= RETICLE_MAX_DISTANCE_ITEMS) {
            s_entry[i].tag_idx = i;
        }

        set_item_text(obj, s_entry[i].dist);
        set_item_primary_icon(obj);

        if(item_event_cb) {
            lv_obj_add_event_cb(obj, item_event_cb, LV_EVENT_ALL, NULL);
        }
    }

    if(s_sel >= s_cnt) s_sel = (s_cnt > 0) ? (uint8_t)(s_cnt - 1) : 0;
    s_primary = (cfg->default_idx < s_cnt) ? cfg->default_idx : 0;

    move_all_obj_to_match_order();
    apply_primary_icon_state();
}

void reticle_distance_mgr_save_to_cfg(reticle_gun_cfg_t * cfg)
{
    /* 当前 UI 顺序已与下位机最终顺序一致，直接按当前顺序写回即可。 */
    if(!cfg) return;

    cfg->count = s_cnt;
    cfg->default_idx = (s_primary < s_cnt) ? s_primary : 0;

    for(uint8_t i = 0; i < RETICLE_MAX_DISTANCE_ITEMS; i++) {
        cfg->items[i].tag_idx = i;
        cfg->items[i].dist = 0;
        cfg->items[i].zero.abs_x = 0;
        cfg->items[i].zero.abs_y = 0;
        cfg->items[i].zero.rel_x = 0;
        cfg->items[i].zero.rel_y = 0;
    }

    for(uint8_t i = 0; i < s_cnt; i++) {
        cfg->items[i] = s_entry[i];
        cfg->items[i].tag_idx = i;
    }
}
