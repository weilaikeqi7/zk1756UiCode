// reticle_types.h
// 分划板相关基础类型定义
//
// 约定：
// 1. reticle_gun_cfg_t.items[] 的顺序，直接使用底层返回的最终顺序。
// 2. default_idx 表示“默认距离在当前列表中的索引”。
// 3. tag_idx 仍保留为协议标签索引，便于查询/修改/校准时定位同一条距离标签。

#ifndef RETICLE_TYPES_H
#define RETICLE_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#ifndef RETICLE_MAX_DISTANCE_ITEMS
#define RETICLE_MAX_DISTANCE_ITEMS 20
#endif

#define RETICLE_GUN_COUNT 20
#define RETICLE_STYLE_COUNT 255
#define RETICLE_COLOR_COUNT 255

typedef struct {
    int16_t abs_x;
    int16_t abs_y;
    int16_t rel_x;
    int16_t rel_y;
} reticle_zero_pos_t;

typedef struct {
    /* 协议里的距离标签身份（0-based）。
     * 注意：它不是当前排序后在 UI 里的显示位置。
     * 三级/四级菜单、默认距离、3.65/3.66/3.67/3.68 都应围绕这个身份工作。 */
    uint8_t tag_idx;
    uint16_t dist;
    reticle_zero_pos_t zero;
} reticle_distance_entry_t;

typedef struct {
    uint8_t style;        /* 1-based */
    uint8_t color;        /* 1-based */
    /* 当前默认距离的“协议标签索引”(0-based)，不是当前排序后在 UI 里的显示位置 */
    uint8_t default_idx;
    uint8_t count;
    reticle_distance_entry_t items[RETICLE_MAX_DISTANCE_ITEMS];
} reticle_gun_cfg_t;

typedef struct {
    uint8_t version;
    uint8_t gun_count;
    uint8_t style_count;
    uint8_t color_count;
    bool visible;
    bool rotate;
    bool ballistic;
    uint8_t cur_gun;      /* UI 内部 0-based */
    uint8_t default_gun;  /* UI 内部 0-based */
    reticle_gun_cfg_t guns[RETICLE_GUN_COUNT];
} reticle_cfg_t;

#endif
