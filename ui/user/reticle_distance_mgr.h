// reticle_distance_mgr.h
// 分划板距离列表 UI 管理器
//
// 当前版本设计原则：
// 1. 距离条目的最终顺序完全以底层返回的 cfg->items[] 顺序为准。
// 2. UI 侧不再做二次排序，也不再推导默认距离索引。
// 3. s_sel 表示当前 UI 逻辑选中项；s_primary 表示默认距离所在项。
// 4. LV_STATE_USER_2 用于给默认距离打样式标记；距离条目本身不再用 USER_1 做高亮。

#ifndef RETICLE_DISTANCE_MGR_H
#define RETICLE_DISTANCE_MGR_H

#include <stdbool.h>
#include <stdint.h>
#include "lvgl.h"
#include "reticle_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 初始化 / 清空 */
void reticle_distance_mgr_init(void);
void reticle_distance_mgr_clear_all(void);

/* 基础访问 */
uint8_t reticle_distance_mgr_count(void);
reticle_distance_entry_t * reticle_distance_mgr_entry(uint8_t idx);
reticle_distance_entry_t * reticle_distance_mgr_entry_by_tag(uint8_t tag_idx);
lv_obj_t * reticle_distance_mgr_obj(uint8_t idx);

/* 查找工具 */
int reticle_distance_mgr_find_idx_by_obj(lv_obj_t * obj);
int reticle_distance_mgr_find_idx_by_tag(uint8_t tag_idx);

/* 选中项 / 默认项 */
void reticle_distance_mgr_set_selected(uint8_t idx);
void reticle_distance_mgr_set_selected_by_tag(uint8_t tag_idx);
uint8_t reticle_distance_mgr_get_selected(void);
uint8_t reticle_distance_mgr_get_selected_tag(void);

void reticle_distance_mgr_set_primary(uint8_t idx);
uint8_t reticle_distance_mgr_get_primary(void);

/* 分页显示：只显示 [start, start + count) 这一段距离条目 */
void reticle_distance_mgr_set_visible_range(uint8_t start, uint8_t count);

/* 四级菜单局部刷新 */
void reticle_distance_mgr_refresh_calibration_ui(uint8_t idx);
void reticle_distance_mgr_refresh_calib_x_ui(uint8_t idx);
void reticle_distance_mgr_refresh_calib_y_ui(uint8_t idx);
void reticle_distance_mgr_refresh_calib_zoom_ui(uint8_t idx);
void reticle_distance_mgr_refresh_calib_freeze_ui(uint8_t idx);

/* 与模型同步：顺序直接信 cfg，不再二次排序 */
void reticle_distance_mgr_load_from_cfg(const reticle_gun_cfg_t * cfg, lv_event_cb_t item_event_cb);
void reticle_distance_mgr_save_to_cfg(reticle_gun_cfg_t * cfg);

#ifdef __cplusplus
}
#endif

#endif
