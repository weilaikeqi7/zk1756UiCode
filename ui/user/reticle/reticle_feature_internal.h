#ifndef RETICLE_FEATURE_INTERNAL_H
#define RETICLE_FEATURE_INTERNAL_H

#include "distance_editor.h"
#include "mainpage_event_handle.h"
#include "reticle_distance_mgr.h"
#include "reticle_feature.h"
#include "reticle_model.h"
#include "ui.h"

/* 保存对话框来源 */
typedef enum {
    SAVE_PENDING_NONE = 0,
    SAVE_PENDING_ROW,
    SAVE_PENDING_EXIT,
} save_pending_t;

/* 分划板内部弹框类型 */
typedef enum {
    DLG_NONE = 0,
    DLG_SAVE_ROW,
    DLG_EXIT_PROMPT,
    DLG_ZERO_ACTION,
} dlg_kind_t;

/* 分划板内部状态 */
extern bool s_opened;
extern save_pending_t s_save_pending;
extern uint8_t s_dist_page;
extern dlg_kind_t s_dlg_kind;
extern lv_obj_t * s_restore_focus;
extern lv_obj_t * s_dialog_owner;
extern bool s_dialog_owner_had_user1;
extern uint8_t s_modify_old_idx;
extern bool s_user_dirty;
extern uint8_t s_active_dist_tag_idx;

/* 索引转换：UI 内部 0-based，协议 1-based */
ROE_U8 ui_idx_to_proto(uint8_t idx0);

uint8_t proto_idx_to_ui(ROE_U8 idx1);

/* 分页工具 */
uint8_t dist_pages(uint8_t dist_cnt);

void dist_page_range(uint8_t page, uint8_t dist_cnt, uint8_t * start, uint8_t * show_n);

void level2_set_fixed_rows_hidden(bool hide);

/* 菜单可见性 / 焦点 */
void hide_all_submenus(void);

void focus_page2_main_only(void);

void focus_level3_distance(void);

void focus_level4_calibration(void);

void clear_reticle_edit_states(void);

/* UI 刷新 */
void ui_set_rowlabel_value(lv_obj_t * rowlabel, const char * fmt, int v);

void sync_distance_mgr_to_model(void);

void load_global_cfg_to_ui(void);

void load_gun_cfg_to_ui(void);

/* 协议请求发送 */
void send_reticle_common_req(int show, int rotate, int ballistic, int saveFlag);

void send_query_current_gun(void);

void send_query_selected_distance(void);

void send_move_req(ROE_S8 moveDir);

void send_zero_req(ROE_U8 zeroType);

/* 对话框工具 */
lv_obj_t * dialog_ok(lv_obj_t * dlg);

lv_obj_t * dialog_cancel(lv_obj_t * dlg);

lv_obj_t * dialog_text_label(lv_obj_t * dlg);

lv_obj_t * dialog_ok_label(lv_obj_t * dlg);

lv_obj_t * dialog_cancel_label(lv_obj_t * dlg);

void dialog_open(lv_obj_t * dlg, dlg_kind_t kind, lv_obj_t * restore_focus);

void ensure_zero_dialog(void);

/* 层级切换 */
void show_level2(void);

void show_level4(void);

void set_selected_distance_editing(bool en);

/* 事件入口 */
void ev_distance_item(lv_event_t * e);

void restore_to_level2(void * user);

void on_add_distance_ok(int v, void * user);

void on_modify_ok(int new_val, void * user);

void on_modify_cancel(void * user);

void ev_level2_common_nav(lv_event_t * e);

void ev_visible(lv_event_t * e);

void ev_rotate(lv_event_t * e);

void ev_gun_type(lv_event_t * e);

void ev_style(lv_event_t * e);

void ev_color(lv_event_t * e);

void do_reticle_reset(void);

void ev_reset(lv_event_t * e);

void ev_add_distance(lv_event_t * e);

void ev_save(lv_event_t * e);

void ev_level3(lv_event_t * e);

void do_zero_clear(void);

void do_zero_reset(void);

void ev_level4(lv_event_t * e);

void ev_dialog_button(lv_event_t * e);


#endif
