// reticle_feature_dialog.c
// 分划板弹框与层级切换逻辑

#include "reticle_feature_internal.h"

static void dialog_owner_mark_open(lv_obj_t * owner)
{
    s_dialog_owner = owner;
    s_dialog_owner_had_user1 = false;
    if(!owner) return;

    s_dialog_owner_had_user1 = lv_obj_has_state(owner, LV_STATE_USER_1);
    if(!s_dialog_owner_had_user1) {
        lv_obj_add_state(owner, LV_STATE_USER_1);
    }
}

static void dialog_owner_mark_close(void)
{
    if(s_dialog_owner) {
        if(!s_dialog_owner_had_user1) {
            lv_obj_clear_state(s_dialog_owner, LV_STATE_USER_1);
        }
    }
    s_dialog_owner = NULL;
    s_dialog_owner_had_user1 = false;
}

lv_obj_t * dialog_ok(lv_obj_t * dlg)
{
    return ui_comp_get_child(dlg, UI_COMP_DIALOGEG_DIALOGOK);
}

lv_obj_t * dialog_cancel(lv_obj_t * dlg)
{
    return ui_comp_get_child(dlg, UI_COMP_DIALOGEG_DIALOGCANCEL);
}

lv_obj_t * dialog_text_label(lv_obj_t * dlg)
{
    return ui_comp_get_child(dlg, UI_COMP_DIALOGEG_DIALOGTEXT_LABEL);
}

lv_obj_t * dialog_ok_label(lv_obj_t * dlg)
{
    return ui_comp_get_child(dlg, UI_COMP_DIALOGEG_DIALOGOK_LABEL);
}

lv_obj_t * dialog_cancel_label(lv_obj_t * dlg)
{
    return ui_comp_get_child(dlg, UI_COMP_DIALOGEG_DIALOGCANCEL_LABEL);
}

void dialog_close(lv_obj_t * dlg)
{
    lv_obj_add_flag(dlg, LV_OBJ_FLAG_HIDDEN);
    s_dlg_kind = DLG_NONE;

    /* 弹框关闭：恢复触发控件的 USER_1 标记 */
    dialog_owner_mark_close();

    // 恢复焦点
    if(s_restore_focus) {
        /*
         * 弹框可能在任意层级打开（2/3/4级）。
         * 恢复焦点时按当前可见的菜单层级重建 group，确保焦点回到触发控件。
         */
        if(!lv_obj_has_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN)) {
            focus_level4_calibration();
        } else if(!lv_obj_has_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN)) {
            focus_level3_distance();
        } else if(!lv_obj_has_flag(ui_contmenureticle, LV_OBJ_FLAG_HIDDEN)) {
            focus_level2_reticle();
        } else {
            focus_page2_main_only();
        }

        lv_group_focus_obj(s_restore_focus);
        s_restore_focus = NULL;
    }
}

void dialog_open(lv_obj_t * dlg, dlg_kind_t kind, lv_obj_t * restore_focus)
{
    s_dlg_kind = kind;
    s_restore_focus = restore_focus;

    /* 弹框打开：把触发控件临时置为 USER_1（用于样式高亮/提示正在操作） */
    dialog_owner_mark_open(restore_focus);

    lv_obj_remove_flag(dlg, LV_OBJ_FLAG_HIDDEN);

    // 焦点组切换到弹框按钮
    lv_group_remove_all_objs(keypad_group);
    lv_group_add_obj(keypad_group, dialog_ok(dlg));
    lv_group_add_obj(keypad_group, dialog_cancel(dlg));
    lv_group_focus_obj(dialog_ok(dlg));
}

void ensure_zero_dialog(void)
{
    if(s_dlg_zero) return;

    // 把 dialog 放在 MainPage 上层（不依赖 SquareLine 生成对象）
    s_dlg_zero = ui_dialogeg_create(ui_MainPage);
    lv_obj_center(s_dlg_zero);
    lv_obj_add_flag(s_dlg_zero, LV_OBJ_FLAG_HIDDEN);

    // 设置默认文案（可按需改中文/英文）
    lv_label_set_text(dialog_text_label(s_dlg_zero), "Zero Action?");
    lv_label_set_text(dialog_ok_label(s_dlg_zero), "Clear");
    lv_label_set_text(dialog_cancel_label(s_dlg_zero), "Reset");
}

void show_level2(void)
{
    lv_obj_remove_flag(ui_contmenureticle, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);

    clear_reticle_edit_states();

    // 进入二级菜单：先刷新全局开关(只在这里/初始化刷)，再刷新当前枪型相关配置
    load_global_cfg_to_ui();
    load_gun_cfg_to_ui();

    focus_level2_reticle();

    // 进入二级菜单时：距离条目不处于编辑态
    set_selected_distance_editing(false);

    if(reticle_distance_mgr_count() > 0) {
        reticle_gun_cfg_t * gc = reticle_model_cur_gun_cfg();
        reticle_feature_set_active_distance_tag(gc->default_idx);
        reticle_distance_mgr_set_selected_by_tag(gc->default_idx);
    }
    lv_group_focus_obj(ui_reticlerow1);
}

void show_level3(void)
{
    lv_obj_remove_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);

    clear_reticle_edit_states();
    focus_level3_distance();
    // 进入三级菜单：围绕当前活动距离标签工作
    reticle_feature_sync_selected_to_active_tag();
    set_selected_distance_editing(true);
    lv_group_focus_obj(ui_distancerow1);
}

void show_level4(void)
{
    send_move_req(0);
    /* 需求变更：进入四级菜单时，隐藏前面三个菜单（主菜单/二级/三级），仅显示四级 */
    lv_obj_add_flag(ui_contpage2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenureticle, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);

    lv_obj_remove_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);

    clear_reticle_edit_states();
    reticle_feature_sync_selected_to_active_tag();
    uint8_t idx = reticle_distance_mgr_get_selected();
    reticle_distance_mgr_refresh_calibration_ui(idx);
    // 四级菜单属于距离校准编辑过程：保持距离条目 USER_1
    set_selected_distance_editing(true);

    focus_level4_calibration();
    lv_group_focus_obj(ui_calibrationrow1);
}

void set_selected_distance_editing(bool en)
{
    reticle_feature_sync_selected_to_active_tag();
    lv_obj_t * item = reticle_distance_mgr_obj(reticle_distance_mgr_get_selected());
    if(!item) return;

    if(en)
        lv_obj_add_state(item, LV_STATE_USER_1);
    else
        lv_obj_clear_state(item, LV_STATE_USER_1);
}

void ev_dialog_button(lv_event_t * e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;

    lv_obj_t * btn = lv_event_get_target(e);
    uint32_t key = lv_indev_get_key(lv_indev_active());

    lv_obj_t * dlg = NULL;
    if(s_dlg_kind == DLG_SAVE_ROW)
        dlg = ui_savereticle;
    else if(s_dlg_kind == DLG_EXIT_PROMPT)
        dlg = ui_savechanges;
    else if(s_dlg_kind == DLG_ZERO_ACTION)
        dlg = s_dlg_zero;
    else
        return;

    if(key == LV_KEY_UP) {
        lv_group_focus_next(keypad_group);
        return;
    }
    if(key == LV_KEY_DOWN) {
        lv_group_focus_prev(keypad_group);
        return;
    }

    if(key == LV_KEY_ESC) {
        dialog_close(dlg);
        return;
    }

    if(key != LV_KEY_ENTER) return;

    bool is_ok = (btn == dialog_ok(dlg));

    if(s_dlg_kind == DLG_SAVE_ROW) {
        if(is_ok) {
            s_save_pending = SAVE_PENDING_ROW;
            SendMsg4UiWeaponSaveConfigReq(global_parameters.sendMsgQueId);
        }
        dialog_close(dlg);
        return;
    }

    if(s_dlg_kind == DLG_EXIT_PROMPT) {
        if(is_ok) {
            s_save_pending = SAVE_PENDING_EXIT;
            SendMsg4UiWeaponSaveConfigReq(global_parameters.sendMsgQueId);
            dialog_close(dlg);
            return;
        }
        dialog_close(dlg);
        reticle_feature_clear_user_dirty();
        clear_reticle_edit_states();
        hide_all_submenus();
        s_opened = false;
        focus_page2_main_only();
        return;
    }

    if(s_dlg_kind == DLG_ZERO_ACTION) {
        if(is_ok)
            do_zero_clear();
        else
            do_zero_reset();
        dialog_close(dlg);
        return;
    }
}

