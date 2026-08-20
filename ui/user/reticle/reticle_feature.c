// reticle_feature.c
// 分划板主流程：分页、焦点、菜单显示/隐藏、协议请求发送
#include "reticle_feature_internal.h"

/* ===================== 状态/dirty ===================== */
bool s_opened = false;
save_pending_t s_save_pending = SAVE_PENDING_NONE;
uint8_t s_dist_page = 0;
bool s_user_dirty = false;
static uint8_t s_last_weapon_mark_op = 0xFF;
static uint8_t s_last_dist_op = 0xFF;
static bool s_wait_show_level3_after_dist_rsp = false;
/* 当前活动距离标签（协议 0-based 索引）。
 * 从二级进入三级/四级后，后续默认距离 / 坐标操作都围绕这条标签进行。 */
uint8_t s_active_dist_tag_idx = 0;

/* ===================== dialog 管理 ===================== */
dlg_kind_t s_dlg_kind = DLG_NONE;
lv_obj_t * s_restore_focus = NULL;
lv_obj_t * s_dlg_zero = NULL;
lv_obj_t * s_dialog_owner = NULL;
bool s_dialog_owner_had_user1 = false;

/* 分页规则（真实翻页）：
 * - Page0：显示 8 个固定项 + 最多 2 条距离（保证第一页总计<=10）
 * - Page1..：仅显示距离条目，每页最多 10 条（例如第二页剩 6 条，就显示 6 条）
 */
#define RETICLE_DIST_FIRST_PAGE 2
#define RETICLE_DIST_OTHER_PAGE 10


ROE_U8 ui_idx_to_proto(uint8_t idx0)
{
    return (ROE_U8)(idx0 + 1);
}

uint8_t proto_idx_to_ui(ROE_U8 idx1)
{
    return idx1 > 0 ? (uint8_t)(idx1 - 1) : 0;
}


/*
 * 当前版本的分划板功能完全走协议驱动：
 * - 开关/样式/颜色/距离/默认距离 都以下位机返回的最终状态为准
 * - UI 只负责显示模型，不再本地直接下发“假状态”
 * 因此这里不再保留早期的 hw_reticle_* 占位接口。
 */

/* 根据距离条目下标计算所在页：第一页 2 条，后续页每页 10 条。 */
static uint8_t dist_page_from_idx(uint8_t idx)
{
    if(idx < RETICLE_DIST_FIRST_PAGE) return 0;
    return (uint8_t)(1 + ((idx - RETICLE_DIST_FIRST_PAGE) / RETICLE_DIST_OTHER_PAGE));
}

static bool obj_is_level2_fixed_row(lv_obj_t * obj)
{
    return obj == ui_reticlerow1 || obj == ui_reticlerow2 || obj == ui_reticlerow3 || obj == ui_reticlerow4 ||
           obj == ui_reticlerow5 || obj == ui_reticlerow6 || obj == ui_reticlerow7 || obj == ui_reticlerow8;
}

static bool obj_is_level3_row(lv_obj_t * obj)
{
    return obj == ui_distancerow1 || obj == ui_distancerow2 || obj == ui_distancerow3 || obj == ui_distancerow4;
}

static bool obj_is_level4_row(lv_obj_t * obj)
{
    return obj == ui_calibrationrow1 || obj == ui_calibrationrow2 || obj == ui_calibrationrow3 ||
           obj == ui_calibrationrow4 || obj == ui_calibrationrow5;
}

/* 清理分划板相关 USER_1 编辑态。
 * USER_1 只表示“当前正在编辑的业务对象”，不等同于普通焦点。 */
void clear_reticle_edit_states(void)
{
    lv_obj_t * rows[] = {ui_reticlerow3, ui_reticlerow4, ui_reticlerow5, ui_reticlerow7, ui_reticlerow8,
                         ui_distancerow1, ui_distancerow3, ui_calibrationrow1, ui_calibrationrow2, ui_calibrationrow3,
                         ui_calibrationrow4};

    for(uint8_t i = 0; i < sizeof(rows) / sizeof(rows[0]); i++) {
        if(rows[i])
            lv_obj_clear_state(rows[i], LV_STATE_USER_1);
    }

    for(uint8_t i = 0; i < reticle_distance_mgr_count(); i++) {
        lv_obj_t * obj = reticle_distance_mgr_obj(i);
        if(obj)
            lv_obj_clear_state(obj, LV_STATE_USER_1);
    }
}

void reticle_feature_mark_user_dirty(void)
{
    s_user_dirty = true;
    reticle_model_mark_dirty();
}

void reticle_feature_clear_user_dirty(void)
{
    s_user_dirty = false;
    reticle_model_clear_dirty();
}

bool reticle_feature_has_user_dirty(void)
{
    return s_user_dirty;
}

void reticle_feature_note_weapon_mark_op(uint8_t op_type)
{
    s_last_weapon_mark_op = op_type;
}

uint8_t reticle_feature_consume_weapon_mark_op(void)
{
    uint8_t op_type = s_last_weapon_mark_op;
    s_last_weapon_mark_op = 0xFF;
    return op_type;
}

void reticle_feature_note_dist_op(uint8_t op_type)
{
    s_last_dist_op = op_type;
}

uint8_t reticle_feature_consume_dist_op(void)
{
    uint8_t op_type = s_last_dist_op;
    s_last_dist_op = 0xFF;
    return op_type;
}

void reticle_feature_wait_show_level3_on_dist_rsp(bool en)
{
    s_wait_show_level3_after_dist_rsp = en;
}

bool reticle_feature_consume_wait_show_level3_on_dist_rsp(void)
{
    bool en = s_wait_show_level3_after_dist_rsp;
    s_wait_show_level3_after_dist_rsp = false;
    return en;
}


void reticle_feature_set_active_distance_tag(uint8_t tag_idx)
{
    s_active_dist_tag_idx = tag_idx;
}

uint8_t reticle_feature_get_active_distance_tag(void)
{
    return s_active_dist_tag_idx;
}

void reticle_feature_sync_selected_to_active_tag(void)
{
    reticle_distance_mgr_set_selected_by_tag(s_active_dist_tag_idx);
}


void reticle_feature_focus_distance_level2(uint8_t idx)
{
    if(!s_opened) return;
    if(lv_obj_has_flag(ui_contmenureticle, LV_OBJ_FLAG_HIDDEN)) return;

    uint8_t cnt = reticle_distance_mgr_count();
    if(cnt == 0) {
        s_dist_page = 0;
        focus_level2_reticle();
        lv_group_focus_obj(ui_reticlerow7);
        return;
    }

    if(idx >= cnt) idx = (uint8_t)(cnt - 1);
    reticle_distance_mgr_set_selected(idx);
    s_active_dist_tag_idx = reticle_distance_mgr_get_selected_tag();
    s_dist_page = dist_page_from_idx(idx);

    focus_level2_reticle();
    lv_obj_t * obj = reticle_distance_mgr_obj(idx);
    if(obj) lv_group_focus_obj(obj);
}

void reticle_feature_focus_selected_distance_level2(void)
{
    reticle_feature_focus_distance_level2(reticle_distance_mgr_get_selected());
}

uint8_t dist_pages(uint8_t dist_cnt)
{
    if(dist_cnt <= RETICLE_DIST_FIRST_PAGE) return 1;
    uint8_t remain = (uint8_t)(dist_cnt - RETICLE_DIST_FIRST_PAGE);
    uint8_t p = (uint8_t)((remain + RETICLE_DIST_OTHER_PAGE - 1) / RETICLE_DIST_OTHER_PAGE);
    return (uint8_t)(1 + (p ? p : 1));
}

void dist_page_range(uint8_t page, uint8_t dist_cnt, uint8_t * start, uint8_t * show_n)
{
    if(page == 0) {
        *start = 0;
        *show_n = (dist_cnt < RETICLE_DIST_FIRST_PAGE) ? dist_cnt : RETICLE_DIST_FIRST_PAGE;
        return;
    }
    uint8_t s = (uint8_t)(RETICLE_DIST_FIRST_PAGE + (page - 1) * RETICLE_DIST_OTHER_PAGE);
    *start = s;
    if(s >= dist_cnt) {
        *show_n = 0;
        return;
    }
    uint8_t left = (uint8_t)(dist_cnt - s);
    *show_n = (left < RETICLE_DIST_OTHER_PAGE) ? left : RETICLE_DIST_OTHER_PAGE;
}

void level2_set_fixed_rows_hidden(bool hide)
{
    lv_obj_t * rows[] = {ui_reticlerow1,
                         ui_reticlerow2,
                         ui_reticlerow3,
                         ui_reticlerow4,
                         ui_reticlerow5,
                         ui_reticlerow6,
                         ui_reticlerow7,
                         ui_reticlerow8};
    for(uint8_t i = 0; i < sizeof(rows) / sizeof(rows[0]); i++) {
        if(hide)
            lv_obj_add_flag(rows[i], LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_clear_flag(rows[i], LV_OBJ_FLAG_HIDDEN);
    }
}

static void apply_level2_page_visibility_only(void)
{
    uint8_t cnt = reticle_distance_mgr_count();
    uint8_t pages = dist_pages(cnt);
    if(pages == 0) pages = 1;
    if(s_dist_page >= pages) s_dist_page = (uint8_t)(pages - 1);

    uint8_t start = 0, show_n = 0;
    dist_page_range(s_dist_page, cnt, &start, &show_n);
    if(s_dist_page == 0)
        level2_set_fixed_rows_hidden(false);
    else
        level2_set_fixed_rows_hidden(true);
    reticle_distance_mgr_set_visible_range(start, show_n);
}

void hide_all_submenus(void)
{
    lv_obj_add_flag(ui_contmenureticle, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);
}

void focus_page2_main_only(void)
{
    lv_group_remove_all_objs(keypad_group);
    lv_group_add_obj(keypad_group, ui_rowwifi);
    lv_group_add_obj(keypad_group, ui_rowtilt);
    lv_group_add_obj(keypad_group, ui_rowcompass);
    lv_group_add_obj(keypad_group, ui_rowreticle);
    lv_group_add_obj(keypad_group, ui_rowballistic);
    lv_group_add_obj(keypad_group, ui_rowmic);
    lv_group_add_obj(keypad_group, ui_rowrav);
    lv_group_focus_obj(ui_rowreticle);
}

void focus_level2_reticle(void)
{
    /* 注意：该函数只负责重建 group，不强制设置焦点（由调用方决定） */
    lv_group_remove_all_objs(keypad_group);

    /* 需求变更：显示开关(Show) 与底下选项无关。
     * 即使 Show=OFF，也允许操作下面所有选项。
     * 因此：不再根据 cfg->visible 禁用/隐藏后续行和距离条目。
     */
    uint8_t cnt = reticle_distance_mgr_count();
    uint8_t pages = dist_pages(cnt);
    if(pages == 0) pages = 1;
    if(s_dist_page >= pages) s_dist_page = (uint8_t)(pages - 1);

    uint8_t start = 0, show_n = 0;
    dist_page_range(s_dist_page, cnt, &start, &show_n);

    /* Page0 显示固定 8 项；Page1.. 仅显示距离 */
    if(s_dist_page == 0) {
        level2_set_fixed_rows_hidden(false);

        lv_group_add_obj(keypad_group, ui_reticlerow1);
        lv_group_add_obj(keypad_group, ui_reticlerow2);
        lv_group_add_obj(keypad_group, ui_reticlerow3);
        lv_group_add_obj(keypad_group, ui_reticlerow4);
        lv_group_add_obj(keypad_group, ui_reticlerow5);
        lv_group_add_obj(keypad_group, ui_reticlerow6);
        lv_group_add_obj(keypad_group, ui_reticlerow7);
        lv_group_add_obj(keypad_group, ui_reticlerow8);
    } else {
        level2_set_fixed_rows_hidden(true);
    }

    /* 仅显示本页距离条目（隐藏其余距离） */
    reticle_distance_mgr_set_visible_range(start, show_n);
    for(uint8_t i = 0; i < show_n; i++) {
        lv_group_add_obj(keypad_group, reticle_distance_mgr_obj((uint8_t)(start + i)));
    }

    /* 切页/重载后二级距离区域回到顶部，避免最后一条偶发被滚出可视区。 */
    lv_obj_update_layout(ui_contpagereticle);
    lv_obj_scroll_to_y(ui_contpagereticle, 0, LV_ANIM_OFF);
}

void focus_level3_distance(void)
{
    lv_group_remove_all_objs(keypad_group);
    lv_group_add_obj(keypad_group, ui_distancerow1); // Calibration Setting
    lv_group_add_obj(keypad_group, ui_distancerow2); // Set Primacy Distance
    lv_group_add_obj(keypad_group, ui_distancerow3); // Modify Distance
    lv_group_add_obj(keypad_group, ui_distancerow4); // Delete Distance
}

void focus_level4_calibration(void)
{
    lv_group_remove_all_objs(keypad_group);
    lv_group_add_obj(keypad_group, ui_calibrationrow1); // X
    lv_group_add_obj(keypad_group, ui_calibrationrow2); // Y
    lv_group_add_obj(keypad_group, ui_calibrationrow3); // Zero Clear/Reset (合并)
    lv_group_add_obj(keypad_group, ui_calibrationrow4); // Zoom
    lv_group_add_obj(keypad_group, ui_calibrationrow5); // Freeze
}

void ui_set_rowlabel_value(lv_obj_t * rowlabel, const char * fmt, int v)
{
    lv_label_set_text_fmt(ui_comp_get_child(rowlabel, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1), fmt, v);
}

void ui_set_rowswitch_checked(lv_obj_t * rowswitch, bool checked)
{
    lv_obj_t * sw = ui_comp_get_child(rowswitch, UI_COMP_ROWSWITCH_CONTPILL_SWITCH);
    if(checked) {
        lv_obj_add_state(sw, LV_STATE_CHECKED);
        lv_obj_send_event(sw, LV_EVENT_VALUE_CHANGED, NULL);
    } else {
        lv_obj_clear_state(sw, LV_STATE_CHECKED);
        lv_obj_send_event(sw, LV_EVENT_VALUE_CHANGED, NULL);
    }
}

/* 把当前距离管理器里的顺序/默认项同步回模型。
 * 现在底层已经负责排序和默认索引更新，这个同步更多用于退出菜单前兜底保存当前 UI 状态。 */
void sync_distance_mgr_to_model(void)
{
    reticle_gun_cfg_t * gc = reticle_model_cur_gun_cfg();
    reticle_distance_mgr_save_to_cfg(gc);
}

void load_global_cfg_to_ui(void)
{
    reticle_cfg_t * cfg = reticle_model_cfg();
    if(!cfg) return;

    ui_set_rowswitch_checked(ui_reticlerow1, cfg->visible);
    ui_set_rowswitch_checked(ui_reticlerow2, cfg->rotate);
}

/*
 * 当前枪型 UI 刷新：只刷新与枪型相关的项目（Gun/Style/Color/Distances）。
 * 注意：这里不要刷新显示/旋转开关。
 */
/* 刷新当前枪型在二级菜单里的显示：枪型 / 样式 / 颜色 / 距离列表。
 * 距离列表顺序直接使用模型当前顺序，不再本地二次排序。 */
void load_gun_cfg_to_ui(void)
{
    reticle_gun_cfg_t * gc = reticle_model_cur_gun_cfg();

    // 2级固定行：枪型相关数值
    ui_set_rowlabel_value(ui_reticlerow3, "G%d", (int)(reticle_model_get_cur_gun() + 1));
    lv_label_set_text_fmt(ui_imggun, "G%d", reticle_model_get_cur_gun() + 1);
    ui_set_rowlabel_value(ui_reticlerow4, "S%d", (int)gc->style);
    ui_set_rowlabel_value(ui_reticlerow5, "C%d", (int)gc->color);
    lv_label_set_text_fmt(ui_labeldistance, "%d", gc->items[gc->default_idx].dist);
    // 绑定距离列表
    reticle_distance_mgr_load_from_cfg(gc, ev_distance_item); // 事件回调稍后统一绑定（见 bind_events）
    reticle_distance_mgr_set_selected_by_tag(s_active_dist_tag_idx);
    // 注意：load_from_cfg 会把 primary icon、selected style 都刷好
}

void send_reticle_common_req(int show, int rotate, int ballistic, int saveFlag)
{
    ReqSetReticleCommonConfig_st req = {
        .saveFlag = (ROE_U8)saveFlag,
        .showReticle = (ROE_S8)show,
        .rotateReticle = (ROE_S8)rotate,
        .ballisticSolve = (ROE_S8)ballistic,
    };
    SendMsg4UiSetReticuleCommonConfigReq(global_parameters.sendMsgQueId, &req);
}

/* 查询当前枪型完整配置（3.62）。
 * 进入分划板菜单时先发这个请求，等响应回来后再刷新二级菜单。 */
void send_query_current_gun(void)
{
    ReqWeaponMarkConfigOperate_st req = {
        .videoChannel = 0,
        .weaponIndex = ui_idx_to_proto(reticle_model_get_cur_gun()),
        .opType = 0,
    };
    reticle_feature_note_weapon_mark_op(req.opType);
    SendMsg4UiWeaponMarkConfigOperateReq(global_parameters.sendMsgQueId, &req);
}

/* 查询当前活动距离标签详情（3.66 opType=0）。
 * 只用于进入三级前拿当前标签的校准数据，不用于重建整表。 */
void send_query_selected_distance(void)
{
    ReqWeaponOperateShootDist_st req = {
        .videoChannel = 0,
        .weaponIndex = ui_idx_to_proto(reticle_model_get_cur_gun()),
        .distIndex = ui_idx_to_proto(s_active_dist_tag_idx),
        .distValue = 0,
        .opType = 0,
        .syncMoveReticle = 0,
    };
    reticle_feature_note_dist_op(req.opType);
    SendMsg4UiWeaponOperateShootDistReq(global_parameters.sendMsgQueId, &req);
}

void send_move_req(ROE_S8 moveDir)
{
    ReqWeaponSetShootPosition_st req = {
        .videoChannel = 0,
        .weaponIndex = ui_idx_to_proto(reticle_model_get_cur_gun()),
        .distIndex = ui_idx_to_proto(s_active_dist_tag_idx),
        .moveDir = moveDir,
    };
    SendMsg4UiWeaponSetShootPositionReq(global_parameters.sendMsgQueId, &req);
}

void send_zero_req(ROE_U8 zeroType)
{
    ReqWeaponSetShootZero_st req = {
        .videoChannel = 0,
        .weaponIndex = ui_idx_to_proto(reticle_model_get_cur_gun()),
        .distIndex = ui_idx_to_proto(s_active_dist_tag_idx),
        .zeroType = zeroType,
    };
    SendMsg4UiWeaponSetShootZeroReq(global_parameters.sendMsgQueId, &req);
}

void reticle_feature_init(void)
{
    hide_all_submenus();

    // 确保弹框隐藏
    lv_obj_add_flag(ui_savereticle, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_savechanges, LV_OBJ_FLAG_HIDDEN);

    ensure_zero_dialog();

    distance_editor_init();
    reticle_distance_mgr_init();
    reticle_model_init();

    // 初次加载：先刷全局开关，再刷当前枪型配置（切枪时不会再刷新全局开关）
    clear_reticle_edit_states();
    load_global_cfg_to_ui();
    load_gun_cfg_to_ui();

    s_opened = false;
    s_user_dirty = false;
    s_active_dist_tag_idx = 0;
    s_dlg_kind = DLG_NONE;
    s_restore_focus = NULL;
}

void reticle_feature_bind_events(void)
{
    // 二级
    lv_obj_add_event_cb(ui_reticlerow1, ev_visible, LV_EVENT_ALL, ui_reticlerow1);
    lv_obj_add_event_cb(ui_reticlerow2, ev_rotate, LV_EVENT_ALL, ui_reticlerow2);
    lv_obj_add_event_cb(ui_reticlerow3, ev_gun_type, LV_EVENT_ALL, ui_reticlerow3);
    lv_obj_add_event_cb(ui_reticlerow4, ev_style, LV_EVENT_ALL, ui_reticlerow4);
    lv_obj_add_event_cb(ui_reticlerow5, ev_color, LV_EVENT_ALL, ui_reticlerow5);
    lv_obj_add_event_cb(ui_reticlerow6, ev_reset, LV_EVENT_ALL, ui_reticlerow6);
    lv_obj_add_event_cb(ui_reticlerow7, ev_add_distance, LV_EVENT_ALL, ui_reticlerow7);
    lv_obj_add_event_cb(ui_reticlerow8, ev_save, LV_EVENT_ALL, ui_reticlerow8);

    // 动态距离项（init 时已经绑定；若后续动态创建也会绑定）
    // 三级
    lv_obj_add_event_cb(ui_distancerow1, ev_level3, LV_EVENT_ALL, ui_distancerow1);
    lv_obj_add_event_cb(ui_distancerow2, ev_level3, LV_EVENT_ALL, ui_distancerow2);
    lv_obj_add_event_cb(ui_distancerow3, ev_level3, LV_EVENT_ALL, ui_distancerow3);
    lv_obj_add_event_cb(ui_distancerow4, ev_level3, LV_EVENT_ALL, ui_distancerow4);

    // 四级
    lv_obj_add_event_cb(ui_calibrationrow1, ev_level4, LV_EVENT_ALL, ui_calibrationrow1);
    lv_obj_add_event_cb(ui_calibrationrow2, ev_level4, LV_EVENT_ALL, ui_calibrationrow2);
    lv_obj_add_event_cb(ui_calibrationrow3, ev_level4, LV_EVENT_ALL, ui_calibrationrow3);
    lv_obj_add_event_cb(ui_calibrationrow4, ev_level4, LV_EVENT_ALL, ui_calibrationrow4);
    lv_obj_add_event_cb(ui_calibrationrow5, ev_level4, LV_EVENT_ALL, ui_calibrationrow5);

    // dialog：Save/Exit/Zero
    lv_obj_add_event_cb(dialog_ok(ui_savereticle), ev_dialog_button, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(dialog_cancel(ui_savereticle), ev_dialog_button, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(dialog_ok(ui_savechanges), ev_dialog_button, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(dialog_cancel(ui_savechanges), ev_dialog_button, LV_EVENT_ALL, NULL);

    if(s_dlg_zero) {
        lv_obj_add_event_cb(dialog_ok(s_dlg_zero), ev_dialog_button, LV_EVENT_ALL, NULL);
        lv_obj_add_event_cb(dialog_cancel(s_dlg_zero), ev_dialog_button, LV_EVENT_ALL, NULL);
    }
}

void reticle_feature_reload_from_model(void)
{
    if(!s_opened) return;

    bool level4_visible = !lv_obj_has_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);
    bool level3_visible = !level4_visible && !lv_obj_has_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);
    bool level2_visible = !level4_visible && !level3_visible && !
                          lv_obj_has_flag(ui_contmenureticle, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * focused = lv_group_get_focused(keypad_group);
    bool focused_had_user1 = focused ? lv_obj_has_state(focused, LV_STATE_USER_1) : false;
    int restore_dist_idx = focused ? reticle_distance_mgr_find_idx_by_obj(focused) : -1;
    uint8_t selected_idx = reticle_distance_mgr_get_selected();
    uint8_t active_tag = s_active_dist_tag_idx;

    load_global_cfg_to_ui();
    load_gun_cfg_to_ui();

    uint8_t cnt = reticle_distance_mgr_count();
    if(cnt > 0) {
        int active_idx = reticle_distance_mgr_find_idx_by_tag(active_tag);
        if(active_idx >= 0)
            reticle_distance_mgr_set_selected((uint8_t)active_idx);
        else {
            if(selected_idx >= cnt) selected_idx = (uint8_t)(cnt - 1);
            reticle_distance_mgr_set_selected(selected_idx);
            s_active_dist_tag_idx = reticle_distance_mgr_get_selected_tag();
        }
    }

    if(level4_visible) {
        /* 四级打开期间，二级背景列表也要保持当前分页隐藏状态，不能因为 reload 后全部显示出来。 */
        apply_level2_page_visibility_only();
        reticle_feature_sync_selected_to_active_tag();
        reticle_distance_mgr_refresh_calibration_ui(reticle_distance_mgr_get_selected());
        focus_level4_calibration();
        set_selected_distance_editing(true);
        if(obj_is_level4_row(focused)) {
            lv_group_focus_obj(focused);
            if(focused_had_user1) lv_obj_add_state(focused, LV_STATE_USER_1);
        } else
            lv_group_focus_obj(ui_calibrationrow1);
        return;
    }

    if(level3_visible) {
        /* 三级打开期间同样保持二级背景分页状态。 */
        apply_level2_page_visibility_only();
        reticle_feature_sync_selected_to_active_tag();
        focus_level3_distance();
        set_selected_distance_editing(true);
        if(obj_is_level3_row(focused)) {
            lv_group_focus_obj(focused);
            if(focused_had_user1) lv_obj_add_state(focused, LV_STATE_USER_1);
        } else
            lv_group_focus_obj(ui_distancerow1);
        return;
    }

    if(level2_visible) {
        if(restore_dist_idx >= 0) {
            /* 如果 reload 前焦点在某个距离标签上，reload 后必须按“活动标签身份”恢复，
             * 不能再按旧排序位置 restore_dist_idx 恢复。
             * 否则像 200->400 这种重排后，焦点会落到 300，而不是新的 400。 */
            reticle_feature_focus_selected_distance_level2();
            return;
        }

        s_dist_page = obj_is_level2_fixed_row(focused) ? 0 : s_dist_page;
        focus_level2_reticle();

        if(obj_is_level2_fixed_row(focused)) {
            lv_group_focus_obj(focused);
            if(focused_had_user1) lv_obj_add_state(focused, LV_STATE_USER_1);
        } else
            lv_group_focus_obj(ui_reticlerow1);
    }
}

void reticle_feature_refresh_calibration_from_model(void)
{
    if(!s_opened) return;
    reticle_feature_sync_selected_to_active_tag();
    reticle_distance_mgr_refresh_calibration_ui(reticle_distance_mgr_get_selected());
}

void reticle_feature_show_menu_after_query(void)
{
    if(!s_opened) return;
    if(!lv_obj_has_flag(ui_contmenureticle, LV_OBJ_FLAG_HIDDEN)) return;
    show_level2();
}

void reticle_feature_on_save_result(bool ok)
{
    if(!ok) {
        s_save_pending = SAVE_PENDING_NONE;
        return;
    }

    reticle_feature_clear_user_dirty();
    if(s_save_pending == SAVE_PENDING_EXIT) {
        hide_all_submenus();
        s_opened = false;
        focus_page2_main_only();
    }
    s_save_pending = SAVE_PENDING_NONE;
}

void reticle_feature_open(void)
{
    if(s_opened) return;
    s_opened = true;
    s_dist_page = 0;
    s_user_dirty = false;
    s_wait_show_level3_after_dist_rsp = false;

    clear_reticle_edit_states();

    /* 打开分划板时先不显示旧缓存菜单，等 3.62 返回后再显示。
     * 先发 3.62 查询，等响应回来后再显示二级菜单并刷新 UI。 */
    hide_all_submenus();
    focus_page2_main_only();

    send_query_current_gun();
}

void reticle_feature_close(void)
{
    // 弹框显示中不响应重复关闭
    if(s_dlg_kind != DLG_NONE) return;

    if(!s_opened) {
        hide_all_submenus();
        focus_page2_main_only();
        return;
    }

    s_wait_show_level3_after_dist_rsp = false;

    // 退出前把当前距离列表同步回模型
    sync_distance_mgr_to_model();

    // 退出时确保所有编辑态清理干净
    clear_reticle_edit_states();
    set_selected_distance_editing(false);

    // 需求表：返回至一级菜单时若检测到有修改则提示保存
    if(reticle_feature_has_user_dirty()) {
        dialog_open(ui_savechanges, DLG_EXIT_PROMPT, ui_rowreticle);
        return;
    }

    hide_all_submenus();
    s_opened = false;
    focus_page2_main_only();
}

bool reticle_feature_is_open(void)
{
    return s_opened;
}