// reticle_model.c
// 分划板模型层：保存当前枪型、距离列表、默认距离和 zero 数据。

#include "reticle_model.h"
#include <string.h>

static reticle_cfg_t s_cfg;
static bool s_dirty = false;

static void normalize_cfg(reticle_cfg_t * cfg)
{
    if(cfg == NULL) return;

    if(cfg->gun_count == 0U || cfg->gun_count > RETICLE_GUN_COUNT) {
        cfg->gun_count = RETICLE_GUN_COUNT;
    }
    if(cfg->style_count == 0U) cfg->style_count = 1U;
    if(cfg->color_count == 0U) cfg->color_count = 1U;
    if(cfg->cur_gun >= RETICLE_GUN_COUNT) cfg->cur_gun = 0U;
    if(cfg->default_gun >= RETICLE_GUN_COUNT) cfg->default_gun = 0U;

    for(uint8_t i = 0; i < RETICLE_GUN_COUNT; i++) {
        reticle_gun_cfg_t * gun = &cfg->guns[i];
        if(gun->style == 0U) gun->style = 1U;
        if(gun->color == 0U) gun->color = 1U;
        if(gun->count > RETICLE_MAX_DISTANCE_ITEMS) {
            gun->count = RETICLE_MAX_DISTANCE_ITEMS;
        }
        if(gun->count == 0U) {
            gun->default_idx = 0U;
        } else if(gun->default_idx >= gun->count) {
            gun->default_idx = 0U;
        }
        for(uint8_t item = 0; item < gun->count; item++) {
            if(gun->items[item].tag_idx >= RETICLE_MAX_DISTANCE_ITEMS) {
                gun->items[item].tag_idx = item;
            }
        }
    }
}

// 给每个枪型设置默认值：
// - 全局 visible/rotate 默认关闭 (false)
// - style=S1, color=C1
// - 默认 1 条距离=100（若你希望“默认无100”，可把 count=0 并不初始化 items）
static void set_defaults(reticle_cfg_t * cfg)
{
    memset(cfg, 0, sizeof(*cfg));
    cfg->version = 1;
    cfg->gun_count = 1;
    cfg->style_count = 1;
    cfg->color_count = 1;
    cfg->cur_gun = 0;
    cfg->default_gun = 0;
    cfg->visible = false;
    cfg->rotate = false;
    cfg->ballistic = false;

    for (uint8_t g = 0; g < RETICLE_GUN_COUNT; g++) {
        reticle_gun_cfg_t *gc = &cfg->guns[g];
        gc->style = 1;
        gc->color = 1;
        gc->count = 1;
        gc->default_idx = 0;
        gc->items[0].tag_idx = 0;
        gc->items[0].dist = 100;
        gc->items[0].zero.abs_x = 0;
        gc->items[0].zero.abs_y = 0;
        gc->items[0].zero.rel_x = 0;
        gc->items[0].zero.rel_y = 0;
    }
}


void reticle_model_init(void) {
    reticle_cfg_t tmp;
    if (reticle_model_nv_load(&tmp)) {
        s_cfg = tmp;
        normalize_cfg(&s_cfg);
    } else {
        set_defaults(&s_cfg);
    }
    s_dirty = false;
}

void reticle_model_mark_dirty(void) { s_dirty = true; }
void reticle_model_clear_dirty(void) { s_dirty = false; }
bool reticle_model_is_dirty(void) { return s_dirty; }

reticle_cfg_t *reticle_model_cfg(void) { return &s_cfg; }

uint8_t reticle_model_get_cur_gun(void) { return s_cfg.cur_gun; }

void reticle_model_set_cur_gun(uint8_t idx) {
    if (idx >= RETICLE_GUN_COUNT) idx = 0;
    s_cfg.cur_gun = idx;
}

reticle_gun_cfg_t *reticle_model_cur_gun_cfg(void) {
    return &s_cfg.guns[s_cfg.cur_gun];
}

// ---------------- NV 占位 ----------------
// 你需要在这里对接 Flash/NVS。
// 返回 true 表示加载/保存成功，false 表示失败（则用默认值）。
bool reticle_model_nv_load(reticle_cfg_t *out) {
    (void) out;
    return false;
}

bool reticle_model_nv_save(const reticle_cfg_t *in) {
    (void) in;
    return true;
}
