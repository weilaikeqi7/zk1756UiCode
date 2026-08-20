#ifndef RETICLE_FEATURE_H
#define RETICLE_FEATURE_H

#include <stdbool.h>
#include <stdint.h>
#include "lvgl.h"

/* 分划板功能入口
 *
 * 当前实现约定：
 * 1. 二级菜单负责显示开关 / 旋转 / 枪型 / 样式 / 颜色 / Reset / Add / Save + 距离标签。
 * 2. 三级菜单负责当前距离标签的“校准 / 设为优先 / 修改 / 删除”。
 * 3. 四级菜单负责当前距离标签的 X/Y/Zero/Zoom/Freeze。
 * 4. 距离列表顺序、默认距离索引都直接信底层返回值，UI 不再二次排序。
 */
extern lv_obj_t * s_dlg_zero;

void reticle_feature_init(void);

void reticle_feature_bind_events(void);

void reticle_feature_open(void);

void reticle_feature_close(void);

bool reticle_feature_is_open(void);

/* 记录最近一次武器配置 / 距离操作请求类型，
 * 便于在响应阶段区分“查询 / 新增 / 修改 / 删除”。 */
void reticle_feature_note_weapon_mark_op(uint8_t op_type);

uint8_t reticle_feature_consume_weapon_mark_op(void);

void reticle_feature_note_dist_op(uint8_t op_type);

uint8_t reticle_feature_consume_dist_op(void);

/* 让二级菜单焦点落到某个距离标签 */
void reticle_feature_focus_distance_level2(uint8_t idx);

void reticle_feature_focus_selected_distance_level2(void);

/* dirty 管理：是否需要退出时提示保存 */
void reticle_feature_mark_user_dirty(void);

void reticle_feature_clear_user_dirty(void);

bool reticle_feature_has_user_dirty(void);

/* 小工具 */
void ui_set_rowswitch_checked(lv_obj_t * rowswitch, bool checked);

/* 按模型重建分划板 UI */
void reticle_feature_reload_from_model(void);

void reticle_feature_show_menu_after_query(void);

void reticle_feature_refresh_calibration_from_model(void);

/* 进入三级前先发 3.66 查询，等响应到了再显示三级 */
void reticle_feature_wait_show_level3_on_dist_rsp(bool en);

bool reticle_feature_consume_wait_show_level3_on_dist_rsp(void);

/* 保存完成后的统一收口 */
void reticle_feature_on_save_result(bool ok);

/* 菜单层级切换 */
void show_level3(void);

void focus_level2_reticle(void);

/* 当前活动距离标签（协议 0-based 索引） */
void reticle_feature_set_active_distance_tag(uint8_t tag_idx);

uint8_t reticle_feature_get_active_distance_tag(void);

void reticle_feature_sync_selected_to_active_tag(void);

void dialog_close(lv_obj_t * dlg);
#endif
