// reticle_feature_level2.c
// 分划板二级菜单事件处理

#include "reticle_feature_internal.h"

uint8_t s_modify_old_idx = 0;

void ev_distance_item(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    int idx = reticle_distance_mgr_find_idx_by_obj(obj);
    if(idx < 0) return;

    if(code == LV_EVENT_FOCUSED) {
        reticle_distance_mgr_set_selected((uint8_t)idx);
        lv_label_set_text(ui_lbltitle4, "Distance");
        return;
    }

    if(code != LV_EVENT_KEY) return;

    uint32_t key = lv_indev_get_key(lv_indev_active());

    /*
     * 需求：UP 向后(下一个)，DOWN 向前(上一个)
     * 同时：当距离条目位于“页边界”时，需要触发真正翻页。
     * 因此这里复用二级通用导航函数 ev_level2_common_nav()，
     * 避免只在固定行上能翻页、而距离条目上不能翻页导致“1-10循环”。
     */
    if(key == LV_KEY_UP || key == LV_KEY_DOWN) {
        ev_level2_common_nav(e);
    } else if(key == LV_KEY_ENTER) {
        reticle_distance_mgr_set_selected((uint8_t)idx);
        reticle_feature_set_active_distance_tag(reticle_distance_mgr_get_selected_tag());
        reticle_feature_wait_show_level3_on_dist_rsp(true);
        send_query_selected_distance();
    } else if(key == LV_KEY_ESC) {
        reticle_feature_close();
        lv_obj_clear_state(ui_rowreticle, LV_STATE_USER_1);
    }
}

void restore_to_level2(void * user)
{
    (void)user;
    // 回到二级：确保距离条目不处于编辑态
    set_selected_distance_editing(false);
    focus_level2_reticle();
    // 需求：Add Distance 确认/取消后，焦点仍停留在“添加距离”这一行
    lv_group_focus_obj(ui_reticlerow7);
}

void on_add_distance_ok(int v, void * user)
{
    (void)user;

    ReqWeaponOperateShootDist_st req = {
        .videoChannel = 0,
        .weaponIndex = ui_idx_to_proto(reticle_model_get_cur_gun()),
        .distIndex = 0,
        .distValue = (ROE_U16)v,
        .opType = 1,
        .syncMoveReticle = 0,
    };
    reticle_feature_note_dist_op(req.opType);
    SendMsg4UiWeaponOperateShootDistReq(global_parameters.sendMsgQueId, &req);
    restore_to_level2(NULL);
}

void on_modify_ok(int new_val, void * user)
{
    (void)user;

    ReqWeaponOperateShootDist_st req = {
        .videoChannel = 0,
        .weaponIndex = ui_idx_to_proto(reticle_model_get_cur_gun()),
        .distIndex = ui_idx_to_proto(reticle_feature_get_active_distance_tag()),
        .distValue = (ROE_U16)new_val,
        .opType = 3,
        .syncMoveReticle = 0,
    };
    reticle_feature_note_dist_op(req.opType);
    SendMsg4UiWeaponOperateShootDistReq(global_parameters.sendMsgQueId, &req);

    lv_obj_add_flag(ui_contmenudistance, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenucalibration, LV_OBJ_FLAG_HIDDEN);
    set_selected_distance_editing(false);
    focus_level2_reticle();
}

void on_modify_cancel(void * user)
{
    (void)user;
    focus_level3_distance();
    lv_group_focus_obj(ui_distancerow3);
}

void ev_level2_common_nav(lv_event_t * e)
{
    if(lv_event_get_code(e) != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    /* 需求：UP 向后(下一个)，DOWN 向前(上一个)
     * 另外：当距离条目超过 2 条时，二级菜单需要“分页”，
     * - UP 在当前页最后一条距离上 -> 翻到下一页
     * - DOWN 在当前页第一条距离上 -> 翻到上一页
     */
    if(key == LV_KEY_UP || key == LV_KEY_DOWN) {
        {
            uint8_t cnt = reticle_distance_mgr_count();
            uint8_t pages = dist_pages(cnt);
            if(pages > 1) {
                lv_obj_t * focused = lv_group_get_focused(keypad_group);

                uint8_t start = 0, show_n = 0;
                dist_page_range(s_dist_page, cnt, &start, &show_n);

                lv_obj_t * first_it = (show_n > 0) ? reticle_distance_mgr_obj(start) : NULL;
                lv_obj_t * last_it = (show_n > 0) ? reticle_distance_mgr_obj((uint8_t)(start + show_n - 1)) : NULL;

                /* ====== 循环翻页：最后一页最后一条 UP -> 回到第一页显示开关；第一页显示开关 DOWN -> 跳到最后一页最后一条 ====== */
                if(pages > 1) {
                    /* 计算最后一页的最后一条距离对象 */
                    uint8_t lstart = 0, lshow = 0;
                    dist_page_range((uint8_t)(pages - 1), cnt, &lstart, &lshow);
                    lv_obj_t * last_page_last =
                        (lshow > 0) ? reticle_distance_mgr_obj((uint8_t)(lstart + lshow - 1)) : NULL;

                    /* UP=向后：在“最后一页最后一条距离”上再按 UP -> 回到第一页并聚焦显示开关 */
                    if(key == LV_KEY_UP && last_page_last && focused == last_page_last) {
                        s_dist_page = 0;
                        focus_level2_reticle();
                        lv_group_focus_obj(ui_reticlerow1);
                        return;
                    }

                    /* DOWN=向前：在“第一页显示开关”上再按 DOWN -> 跳到最后一页并聚焦最后一条距离 */
                    if(key == LV_KEY_DOWN && focused == ui_reticlerow1 && last_page_last) {
                        s_dist_page = (uint8_t)(pages - 1);
                        focus_level2_reticle();
                        /* 进入最后一页后，聚焦最后一条距离 */
                        lv_group_focus_obj(last_page_last);
                        return;
                    }
                }

                /* UP=向后：在本页最后一条距离上再按 UP -> 下一页 */
                if(key == LV_KEY_UP && last_it && focused == last_it) {
                    if((uint8_t)(s_dist_page + 1) < pages) {
                        s_dist_page++;
                        focus_level2_reticle();

                        uint8_t nstart = 0, nshow = 0;
                        dist_page_range(s_dist_page, cnt, &nstart, &nshow);
                        if(nshow > 0) lv_group_focus_obj(reticle_distance_mgr_obj(nstart));
                        return;
                    }
                }

                /* DOWN=向前：在本页第一条距离上再按 DOWN -> 上一页 */
                if(key == LV_KEY_DOWN && first_it && focused == first_it) {
                    if(s_dist_page > 0) {
                        s_dist_page--;
                        focus_level2_reticle();

                        uint8_t pstart = 0, pshow = 0;
                        dist_page_range(s_dist_page, cnt, &pstart, &pshow);
                        if(pshow > 0)
                            lv_group_focus_obj(reticle_distance_mgr_obj((uint8_t)(pstart + pshow - 1)));
                        else {
                            /* 回到第一页但没有距离时，落在 Save */
                            if(s_dist_page == 0) lv_group_focus_obj(ui_reticlerow8);
                        }
                        return;
                    }
                }
            }
        }

        /* 默认焦点移动 */
        if(key == LV_KEY_UP)
            lv_group_focus_next(keypad_group);
        else
            lv_group_focus_prev(keypad_group);
        return;
    }

    if(key == LV_KEY_ESC) {
        reticle_feature_close();
        lv_obj_clear_state(ui_rowreticle, LV_STATE_USER_1);
        return;
    }
}

// 显示开关（rowswitch）
void ev_visible(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle4, "Display switch");
    }

    if(event_code != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    if(key == LV_KEY_ENTER) {
        reticle_cfg_t * cfg = reticle_model_cfg();
        send_reticle_common_req(cfg->visible ? 0 : 1, -1, -1, 0);
    } else {
        ev_level2_common_nav(e);
    }
}

// 旋转开关（rowswitch）
void ev_rotate(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle4, "Rotary switch");
    }

    if(event_code != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    if(key == LV_KEY_ENTER) {
        reticle_cfg_t * cfg = reticle_model_cfg();
        send_reticle_common_req(-1, cfg->rotate ? 0 : 1, -1, 0);
    } else {
        ev_level2_common_nav(e);
    }
}

// Gun Type（rowlabel）：ENTER 进入编辑态，UP/DOWN 切换 G1~G10，ENTER 退出编辑态并加载对应枪型
void ev_gun_type(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle4, "Gun Type");
    }

    if(event_code != LV_EVENT_KEY) return;

    uint32_t key = lv_indev_get_key(lv_indev_active());
    bool editing = lv_obj_has_state(ui_reticlerow3, LV_STATE_USER_1);

    if(key == LV_KEY_ENTER) {
        if(editing)
            lv_obj_clear_state(ui_reticlerow3, LV_STATE_USER_1);
        else
            lv_obj_add_state(ui_reticlerow3, LV_STATE_USER_1);
        return;
    }

    if(editing && (key == LV_KEY_UP || key == LV_KEY_DOWN)) {
        reticle_cfg_t * cfg = reticle_model_cfg();
        uint8_t total = cfg->gun_count ? cfg->gun_count : RETICLE_GUN_COUNT;
        uint8_t g = reticle_model_get_cur_gun();
        if(key == LV_KEY_UP)
            g = (uint8_t)((g + 1) % total);
        else
            g = (uint8_t)((g + total - 1) % total);

        ReqWeaponMarkConfigOperate_st req = {
            .videoChannel = 0,
            .weaponIndex = ui_idx_to_proto(g),
            .opType = 1,
        };
        reticle_feature_note_weapon_mark_op(req.opType);
        SendMsg4UiWeaponMarkConfigOperateReq(global_parameters.sendMsgQueId, &req);
        return;
    }

    ev_level2_common_nav(e);
}

// Style（rowlabel）：ENTER编辑态，UP/DOWN 切 S1~S10，实时生效并置dirty
void ev_style(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle4, "Reticle Style");
    }
    if(event_code != LV_EVENT_KEY) return;

    uint32_t key = lv_indev_get_key(lv_indev_active());
    bool editing = lv_obj_has_state(ui_reticlerow4, LV_STATE_USER_1);
    if(key == LV_KEY_ENTER) {
        if(editing)
            lv_obj_clear_state(ui_reticlerow4, LV_STATE_USER_1);
        else
            lv_obj_add_state(ui_reticlerow4, LV_STATE_USER_1);
        return;
    }

    if(editing && (key == LV_KEY_UP || key == LV_KEY_DOWN)) {
        reticle_cfg_t * cfg = reticle_model_cfg();
        reticle_gun_cfg_t * gc = reticle_model_cur_gun_cfg();
        uint8_t maxc = cfg->style_count ? cfg->style_count : RETICLE_STYLE_COUNT;
        uint8_t sidx = gc->style;
        if(key == LV_KEY_UP)
            sidx = (uint8_t)(sidx % maxc + 1);
        else
            sidx = (uint8_t)((sidx + maxc - 2) % maxc + 1);

        ReqWeaponSetReticleStyle_st req = {
            .videoChannel = 0,
            .weaponIndex = ui_idx_to_proto(reticle_model_get_cur_gun()),
            .reticleTypeIndex = sidx,
        };
        SendMsg4UiWeaponSetReticleStyleReq(global_parameters.sendMsgQueId, &req);
        return;
    }

    ev_level2_common_nav(e);
}

// Color（rowlabel）：ENTER编辑态，UP/DOWN 切 C1~C10，实时生效并置dirty
void ev_color(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle4, "Reticle Color");
    }
    if(event_code != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    bool editing = lv_obj_has_state(ui_reticlerow5, LV_STATE_USER_1);

    if(key == LV_KEY_ENTER) {
        if(editing)
            lv_obj_clear_state(ui_reticlerow5, LV_STATE_USER_1);
        else
            lv_obj_add_state(ui_reticlerow5, LV_STATE_USER_1);
        return;
    }

    if(editing && (key == LV_KEY_UP || key == LV_KEY_DOWN)) {
        reticle_cfg_t * cfg = reticle_model_cfg();
        reticle_gun_cfg_t * gc = reticle_model_cur_gun_cfg();
        uint8_t maxc = cfg->color_count ? cfg->color_count : RETICLE_COLOR_COUNT;
        uint8_t cidx = gc->color;
        if(key == LV_KEY_UP)
            cidx = (uint8_t)(cidx % maxc + 1);
        else
            cidx = (uint8_t)((cidx + maxc - 2) % maxc + 1);

        ReqWeaponSetReticleColor_st req = {
            .videoChannel = 0,
            .weaponIndex = ui_idx_to_proto(reticle_model_get_cur_gun()),
            .reticleColorIndex = cidx,
        };
        SendMsg4UiWeaponSetReticleColorReq(global_parameters.sendMsgQueId, &req);
        return;
    }

    ev_level2_common_nav(e);
}

// Reset：仅保留一条距离=100，且零位重置到中心点；同时 style/color 重置为 S1/C1（可按你产品修改）
void do_reticle_reset(void)
{
    ReqWeaponMarkConfigOperate_st req = {
        .videoChannel = 0,
        .weaponIndex = ui_idx_to_proto(reticle_model_get_cur_gun()),
        .opType = 2,
    };
    reticle_feature_note_weapon_mark_op(req.opType);
    SendMsg4UiWeaponMarkConfigOperateReq(global_parameters.sendMsgQueId, &req);
}

void ev_reset(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle4, "Reticle Reset");
    }
    if(event_code != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());

    if(key == LV_KEY_ENTER)
        do_reticle_reset();
    else
        ev_level2_common_nav(e);
}

// Add Distance（rowenter）
void ev_add_distance(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle4, "Add Distance");
    }
    if(event_code != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());
    if(key == LV_KEY_ENTER) {
        /* Add Distance：弹窗保持 SquareLine 默认位置；弹窗期间高亮 Add Distance 行 */
        distance_editor_open_ex(
            100,
            ui_reticlerow7,
            false,
            on_add_distance_ok,
            NULL,
            NULL,
            NULL,
            restore_to_level2,
            NULL);
    } else {
        ev_level2_common_nav(e);
    }
}

// Save（rowlabel）：弹 ui_savereticle
void ev_save(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_FOCUSED) {
        lv_label_set_text(ui_lbltitle4, "Save");
    }
    if(event_code != LV_EVENT_KEY) return;
    uint32_t key = lv_indev_get_key(lv_indev_active());
    if(key == LV_KEY_ENTER) {
        dialog_open(ui_savereticle, DLG_SAVE_ROW, ui_reticlerow8);
    } else {
        ev_level2_common_nav(e);
    }
}