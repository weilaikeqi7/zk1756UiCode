// reticle_feature_level34.c
// 分划板三级 / 四级菜单事件处理

#include "reticle_feature_internal.h"

void ev_level3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        if(obj == ui_distancerow1) {
            lv_label_set_text(ui_lbltitle5, "Zeroing profile");
        }
        if(obj == ui_distancerow2) {
            lv_label_set_text(ui_lbltitle5, "Set Primacy Distance");
        }
        if(obj == ui_distancerow3) {
            lv_label_set_text(ui_lbltitle5, "Modify Distance");
        }
        if(obj == ui_distancerow4) {
            lv_label_set_text(ui_lbltitle5, "Delete Distance");
        }
    }

    if(event_code != LV_EVENT_KEY) return;

    uint32_t key = lv_indev_get_key(lv_indev_active());
    /* 需求：UP 向后(下一个)，DOWN 向前(上一个) */
    if(key == LV_KEY_UP) {
        lv_group_focus_next(keypad_group);
        return;
    }
    if(key == LV_KEY_DOWN) {
        lv_group_focus_prev(keypad_group);
        return;
    }

    if(key == LV_KEY_ESC) {
        // 返回二级
        clear_reticle_edit_states();
        lv_obj_add_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);
        // 退出距离编辑：清除距离条目 USER_1（若为优先距离则保留 USER_2）
        set_selected_distance_editing(false);
        focus_level2_reticle();
        if(reticle_distance_mgr_count() > 0)
            lv_group_focus_obj(reticle_distance_mgr_obj(reticle_distance_mgr_get_selected()));
        else
            lv_group_focus_obj(ui_reticlerow7);
        return;
    }

    if(key != LV_KEY_ENTER) return;

    reticle_feature_sync_selected_to_active_tag();
    uint8_t sel = reticle_distance_mgr_get_selected();
    reticle_distance_entry_t * en = reticle_distance_mgr_entry_by_tag(reticle_feature_get_active_distance_tag());
    if(!en) en = reticle_distance_mgr_entry(sel);
    if(!en) return;

    if(obj == ui_distancerow1) {
        show_level4();
        return;
    }

    if(obj == ui_distancerow2) {
        ReqWeaponSetDefaultShootDist_st req = {
            .videoChannel = 0,
            .weaponIndex = ui_idx_to_proto(reticle_model_get_cur_gun()),
            .defaultDistIndex = ui_idx_to_proto(reticle_feature_get_active_distance_tag()),
        };
        SendMsg4UiWeaponSetDefaltShootDistReq(global_parameters.sendMsgQueId, &req);
        return;
    }

    if(obj == ui_distancerow3) {
        s_modify_old_idx = sel;
        /* Modify Distance：弹窗靠右显示；弹窗期间高亮 Modify Distance 行 */
        distance_editor_open_ex(
            (int)en->dist,
            ui_distancerow3,
            true,
            on_modify_ok,
            NULL,
            on_modify_cancel,
            NULL,
            NULL,
            NULL);
        return;
    }

    if(obj == ui_distancerow4) {
        ReqWeaponOperateShootDist_st req = {
            .videoChannel = 0,
            .weaponIndex = ui_idx_to_proto(reticle_model_get_cur_gun()),
            .distIndex = ui_idx_to_proto(reticle_feature_get_active_distance_tag()),
            .distValue = 0,
            .opType = 2,
            .syncMoveReticle = 0,
        };
        reticle_feature_note_dist_op(req.opType);
        SendMsg4UiWeaponOperateShootDistReq(global_parameters.sendMsgQueId, &req);

        lv_obj_add_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);
        set_selected_distance_editing(false);
        focus_level2_reticle();
        return;
    }
}

void do_zero_clear(void)
{
    send_zero_req(0);
}

void do_zero_reset(void)
{
    send_zero_req(1);
}

void ev_level4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_user_data(e);

    if(event_code == LV_EVENT_FOCUSED) {
        if(obj == ui_calibrationrow1) {
            lv_label_set_text(ui_lbltitle6, "Zero Modify(X)");
        }
        if(obj == ui_calibrationrow2) {
            lv_label_set_text(ui_lbltitle6, "Zero Modify(Y)");
        }
        if(obj == ui_calibrationrow3) {
            lv_label_set_text(ui_lbltitle6, "Zero Clear/Reset");
        }
        if(obj == ui_calibrationrow4) {
            lv_label_set_text(ui_lbltitle6, "Digtal Zoom");
        }
        if(obj == ui_calibrationrow5) {
            lv_label_set_text(ui_lbltitle6, "Freeze");
        }
    }

    if(event_code != LV_EVENT_KEY) return;

    uint32_t key = lv_indev_get_key(lv_indev_active());

    uint8_t idx = reticle_distance_mgr_get_selected();
    reticle_distance_entry_t * en = reticle_distance_mgr_entry(idx);
    if(!en) return;

    bool editing = lv_obj_has_state(obj, LV_STATE_USER_1);

    if(key == LV_KEY_ESC) {
        send_move_req(-1);
        clear_reticle_edit_states();
        lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);

        /* 退出四级：恢复前面三个菜单可见 */
        lv_obj_clear_flag(ui_contpage2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_contmenureticle, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);

        focus_level3_distance();
        set_selected_distance_editing(true);
        lv_group_focus_obj(ui_distancerow1);
        return;
    }

    if(!editing) {
        /* 需求：UP 向后(下一个)，DOWN 向前(上一个) */
        if(key == LV_KEY_UP) {
            lv_group_focus_next(keypad_group);
            return;
        }
        if(key == LV_KEY_DOWN) {
            lv_group_focus_prev(keypad_group);
            return;
        }
    }

    if(key == LV_KEY_ENTER) {
        // X/Y/Zoom：切换编辑态
        if(obj == ui_calibrationrow1 || obj == ui_calibrationrow2 || obj == ui_calibrationrow4) {
            if(editing)
                lv_obj_clear_state(obj, LV_STATE_USER_1);
            else
                lv_obj_add_state(obj, LV_STATE_USER_1);
            return;
        }

        // Zero Clear/Reset：弹框选择并确认（需求表 10/11：弹框确认后清零）
        if(obj == ui_calibrationrow3) {
            ensure_zero_dialog();
            // 文案可改为中文
            lv_label_set_text(dialog_text_label(s_dlg_zero), "Clear or Reset zero?");
            lv_label_set_text(dialog_ok_label(s_dlg_zero), "Clear");
            lv_label_set_text(dialog_cancel_label(s_dlg_zero), "Reset");
            dialog_open(s_dlg_zero, DLG_ZERO_ACTION, ui_calibrationrow3);
            return;
        }

        // Freeze：切换开关
        if(obj == ui_calibrationrow5) {
            ReqFreezeVideoInput_st req = {.freeze = g_freeze_switch ? 0 : 1};
            SendMsg4UiFreezeVideoInputReq(global_parameters.sendMsgQueId, &req);
            return;
        }
    }

    if(editing) {
        if(obj == ui_calibrationrow1) {
            if(key == LV_KEY_UP)
                send_move_req(4); /* X+ -> 右 */
            else if(key == LV_KEY_DOWN)
                send_move_req(3); /* X- -> 左 */
            return;
        }
        if(obj == ui_calibrationrow2) {
            if(key == LV_KEY_UP)
                send_move_req(1); /* Y+ -> 上 */
            else if(key == LV_KEY_DOWN)
                send_move_req(2); /* Y- -> 下 */
            return;
        }
        if(obj == ui_calibrationrow4) {
            ReqAdjustVideoZoom_st req;

            if(key == LV_KEY_UP) {
                req.direction = 1; /* 正向 */
                SendMsg4UiVideoZoomReq(global_parameters.sendMsgQueId, &req);
            } else if(key == LV_KEY_DOWN) {
                req.direction = 0; /* 反向 */
                SendMsg4UiVideoZoomReq(global_parameters.sendMsgQueId, &req);
            }
            return;
        }
    }
}

