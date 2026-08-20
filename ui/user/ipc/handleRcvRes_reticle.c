// handleRcvRes_reticle.c
// 分划板相关请求响应处理
//
// 当前原则：
// 1. 距离列表顺序、默认距离索引都直接信底层返回值。
// 2. UI 不再二次排序，也不再按旧值推导默认索引。
// 3. 3.66 查询/新增/删除/修改统一围绕“协议距离标签索引”工作。

#include "ipcMsgQue4UiRcvRes.h"
#include "handleRcvRes.h"
#include "reticle_model.h"
#include "reticle_distance_mgr.h"
#include "reticle_feature.h"
#include "play_handle.h"
#include "lvgl.h"

static void format_dist_array_u16(char * buf, size_t buf_size, ROE_U8 count, const ROE_U16 * dists)
{
    if(!buf || buf_size == 0U) return;

    int pos = lv_snprintf(buf, buf_size, "count=%u dists=[", (unsigned)count);
    if(pos < 0) {
        buf[0] = '\0';
        return;
    }

    if(pos >= (int)buf_size) pos = (int)buf_size - 1;

    for(ROE_U8 i = 0; i < count && i < 20 && pos > -1 && pos < (int)buf_size - 2; i++) {
        int n = lv_snprintf(buf + pos, buf_size - (size_t)pos, "%s%u", (i == 0U) ? "" : ",", (unsigned)dists[i]);
        if(n < 0) break;
        if(n >= (int)(buf_size - (size_t)pos)) {
            pos = (int)buf_size - 1;
            break;
        }
        pos += n;
    }

    if(pos < 0) pos = 0;
    lv_snprintf(buf + pos, buf_size - (size_t)pos, "]");
}

static inline uint8_t proto_idx_to_ui(ROE_U8 idx1)
{
    return idx1 > 0 ? (uint8_t)(idx1 - 1) : 0;
}

static reticle_distance_entry_t * get_dist_entry(reticle_gun_cfg_t * gc, ROE_U8 proto_dist_idx)
{
    uint8_t idx = proto_idx_to_ui(proto_dist_idx);
    if(idx >= RETICLE_MAX_DISTANCE_ITEMS) return NULL;
    if(idx >= gc->count) gc->count = (uint8_t)(idx + 1);
    gc->items[idx].tag_idx = idx;
    return &gc->items[idx];
}

/* 用底层返回的完整距离列表直接覆盖当前枪型模型。
 * 注意：这里不做本地排序，顺序完全信底层。
 * zero 信息只保留同一索引标签的旧值；当前操作标签的 zero 会在具体响应里再覆盖。 */
static void sync_dist_list(reticle_gun_cfg_t * gc, ROE_U8 count, const ROE_U16 * dists)
{
    /* 协议里的 shootDistances[] 顺序按“标签索引”返回，不是 UI 排序后的显示顺序。
     * 模型层必须按标签索引(0..count-1)保存；显示排序交给 distance_mgr。 */
    if(count > RETICLE_MAX_DISTANCE_ITEMS) count = RETICLE_MAX_DISTANCE_ITEMS;

    reticle_distance_entry_t old_items[RETICLE_MAX_DISTANCE_ITEMS];
    ROE_U8 old_count = gc->count;
    for(ROE_U8 i = 0; i < old_count && i < RETICLE_MAX_DISTANCE_ITEMS; i++) {
        old_items[i] = gc->items[i];
    }

    gc->count = count;
    for(ROE_U8 i = 0; i < count; i++) {
        gc->items[i].tag_idx = i;
        gc->items[i].dist = dists[i];
        if(i < old_count) {
            gc->items[i].zero = old_items[i].zero; /* 同一标签索引的零位信息保留 */
        } else {
            gc->items[i].zero.abs_x = 0;
            gc->items[i].zero.abs_y = 0;
            gc->items[i].zero.rel_x = 0;
            gc->items[i].zero.rel_y = 0;
        }
    }
}

/* 3.66 的 opDistValue 在当前主控实现里并不总是可靠，
 * 尤其是 Modify/Query 后，整表 shootDistances[] 已经更新，
 * 但 opDistValue 可能还是旧值。
 *
 * 这里统一优先按“当前协议标签索引 op_tag 对应的整表值”取距离；
 * 只有整表不存在对应项时，才退回使用 result->distValue。
 */
static ROE_U16 pick_dist_from_rsp(ROE_U8 count, const ROE_U16 * dists, uint8_t op_tag, ROE_U16 fallback)
{
    if(dists && op_tag < count && op_tag < RETICLE_MAX_DISTANCE_ITEMS) {
        return dists[op_tag];
    }
    return fallback;
}

static void
apply_zero_to_entry(reticle_distance_entry_t * e, ROE_U16 dist, ROE_S16 absX, ROE_S16 absY, ROE_S16 relX, ROE_S16 relY)
{
    if(!e) return;
    e->dist = dist;
    e->zero.abs_x = absX;
    e->zero.abs_y = absY;
    e->zero.rel_x = relX;
    e->zero.rel_y = relY;
}

ROE_S32 handleParseSetReticleCommonConfigMsg(ROE_U8 * msgData)
{
    RspSetReticleCommonConfig_st * result = (RspSetReticleCommonConfig_st *)msgData;
    LV_LOG_USER("[RETICLE][RSP][3.61 common] result=%u show=%u rotate=%u ballistic=%u",
                (unsigned)result->result,
                (unsigned)result->currentShowReticle,
                (unsigned)result->currentRotateReticle,
                (unsigned)result->currentBallisticSolve);
    if(result->result != 0) return ROE_FAILURE;
    reticle_cfg_t * cfg = reticle_model_cfg();
    cfg->visible = !!result->currentShowReticle;
    cfg->rotate = !!result->currentRotateReticle;
    cfg->ballistic = !!result->currentBallisticSolve;
    ui_set_rowswitch_checked(ui_rowballistic, cfg->ballistic);

    reticle_feature_mark_user_dirty();
    reticle_feature_reload_from_model();
    return ROE_SUCCESS;
}

ROE_S32 handleParseWeaponMarkConfigOperateMsg(ROE_U8 * msgData)
{
    RspWeaponMarkConfigOperate_st * result = (RspWeaponMarkConfigOperate_st *)msgData;
    char dist_buf[160];
    format_dist_array_u16(dist_buf, sizeof(dist_buf), result->shootDistanceCount, result->shootDistances);
    LV_LOG_USER(
        "[RETICLE][RSP][3.62 weaponCfg] result=%u video=%u weapon=%u defaultWeapon=%u style=%u color=%u defaultDistIndex=%u %s",
        (unsigned)result->result,
        (unsigned)result->videoChannel,
        (unsigned)result->weaponIndex,
        (unsigned)result->defaultWeaponIndex,
        (unsigned)result->reticleTypeIndex,
        (unsigned)result->reticleColorIndex,
        (unsigned)result->defaultDistIndex,
        dist_buf);
    if(result->result != 0) return ROE_FAILURE;
    if(result->videoChannel != 0) return ROE_SUCCESS;

    reticle_cfg_t * cfg = reticle_model_cfg();
    cfg->default_gun = proto_idx_to_ui(result->defaultWeaponIndex);
    cfg->cur_gun = proto_idx_to_ui(result->weaponIndex);

    reticle_gun_cfg_t * gc = &cfg->guns[cfg->cur_gun];
    gc->style = result->reticleTypeIndex;
    gc->color = result->reticleColorIndex;
    gc->default_idx = proto_idx_to_ui(result->defaultDistIndex);
    sync_dist_list(gc, result->shootDistanceCount, result->shootDistances);

    reticle_feature_set_active_distance_tag(gc->default_idx);
    reticle_feature_reload_from_model();
    if(reticle_distance_mgr_count() > 0) {
        reticle_distance_mgr_set_selected_by_tag(gc->default_idx);
    }

    if(reticle_feature_consume_weapon_mark_op() != 0) {
        reticle_feature_mark_user_dirty();
    }

    if(reticle_feature_is_open()) {
        bool menu_hidden = lv_obj_has_flag(ui_contmenureticle, LV_OBJ_FLAG_HIDDEN);
        if(menu_hidden) {
            reticle_feature_show_menu_after_query();
        }
    }
    return ROE_SUCCESS;
}

ROE_S32 handleParseWeaponSetReticleStyleMsg(ROE_U8 * msgData)
{
    RspWeaponSetReticleStyle_st * result = (RspWeaponSetReticleStyle_st *)msgData;
    LV_LOG_USER("[RETICLE][RSP][3.63 style] result=%u video=%u weapon=%u style=%u",
                (unsigned)result->result,
                (unsigned)result->videoChannel,
                (unsigned)result->weaponIndex,
                (unsigned)result->reticleTypeIndex);
    if(result->result != 0 || result->videoChannel != 0) return ROE_FAILURE;

    reticle_cfg_t * cfg = reticle_model_cfg();
    uint8_t gun = proto_idx_to_ui(result->weaponIndex);
    if(gun >= RETICLE_GUN_COUNT) return ROE_FAILURE;
    cfg->guns[gun].style = result->reticleTypeIndex;
    reticle_feature_mark_user_dirty();
    reticle_feature_reload_from_model();
    return ROE_SUCCESS;
}

ROE_S32 handleParseWeaponSetReticleColorMsg(ROE_U8 * msgData)
{
    RspWeaponSetReticleColor_st * result = (RspWeaponSetReticleColor_st *)msgData;
    LV_LOG_USER("[RETICLE][RSP][3.64 color] result=%u video=%u weapon=%u color=%u",
                (unsigned)result->result,
                (unsigned)result->videoChannel,
                (unsigned)result->weaponIndex,
                (unsigned)result->reticleColorIndex);
    if(result->result != 0 || result->videoChannel != 0) return ROE_FAILURE;

    reticle_cfg_t * cfg = reticle_model_cfg();
    uint8_t gun = proto_idx_to_ui(result->weaponIndex);
    if(gun >= RETICLE_GUN_COUNT) return ROE_FAILURE;
    cfg->guns[gun].color = result->reticleColorIndex;
    reticle_feature_mark_user_dirty();
    reticle_feature_reload_from_model();
    return ROE_SUCCESS;
}

/* 处理 3.65：设置优先距离。
 * 默认索引以下位机返回的 defaultDistIndex 为准。 */
ROE_S32 handleParseWeaponSetDefaultShootDistanceMsg(ROE_U8 * msgData)
{
    RspWeaponSetDefaultShootDist_st * result = (RspWeaponSetDefaultShootDist_st *)msgData;
    LV_LOG_USER(
        "[RETICLE][RSP][3.65 defaultDist] result=%u video=%u weapon=%u distIndex=%u distValue=%u abs=(%d,%d) rel=(%d,%d)",
        (unsigned)result->result,
        (unsigned)result->videoChannel,
        (unsigned)result->weaponIndex,
        (unsigned)result->defaultDistIndex,
        (unsigned)result->defaultDist,
        (int)result->defaultAbsX,
        (int)result->defaultAbsY,
        (int)result->defaultRelX,
        (int)result->defaultRelY);
    if(result->result != 0 || result->videoChannel != 0) return ROE_FAILURE;

    reticle_cfg_t * cfg = reticle_model_cfg();
    uint8_t gun = proto_idx_to_ui(result->weaponIndex);
    if(gun >= RETICLE_GUN_COUNT) return ROE_FAILURE;

    reticle_gun_cfg_t * gc = &cfg->guns[gun];

    /* 设置优先距离按协议标签索引生效。 */
    gc->default_idx = proto_idx_to_ui(result->defaultDistIndex);

    reticle_distance_entry_t * e = get_dist_entry(gc, result->defaultDistIndex);
    apply_zero_to_entry(
        e,
        result->defaultDist,
        result->defaultAbsX,
        result->defaultAbsY,
        result->defaultRelX,
        result->defaultRelY);

    reticle_feature_reload_from_model();
    /* 当前活动标签不应被“设置优先距离”操作改掉；只刷新 USER_2 标记。 */
    reticle_feature_sync_selected_to_active_tag();
    reticle_feature_mark_user_dirty();
    reticle_feature_refresh_calibration_from_model();
    return ROE_SUCCESS;
}

/* 处理 3.66：距离查询 / 新增 / 删除 / 修改。
 * shootDistances[] 已经是下位机最终顺序，UI 直接使用。 */
ROE_S32 handleParseWeaponOperateShootDistanceMsg(ROE_U8 * msgData)
{
    RspWeaponOperateShootDist_st * result = (RspWeaponOperateShootDist_st *)msgData;
    char dist_buf[160];
    format_dist_array_u16(dist_buf, sizeof(dist_buf), result->shootDistanceCount, result->shootDistances);
    LV_LOG_USER(
        "[RETICLE][RSP][3.66 distOp] result=%u video=%u weapon=%u opDistIndex=%u opDistValue=%u defaultDistIndex=%u abs=(%d,%d) rel=(%d,%d) %s",
        (unsigned)result->result,
        (unsigned)result->videoChannel,
        (unsigned)result->weaponIndex,
        (unsigned)result->distIndex,
        (unsigned)result->distValue,
        (unsigned)result->defaultDistIndex,
        (int)result->absX,
        (int)result->absY,
        (int)result->relX,
        (int)result->relY,
        dist_buf);
    if(result->result != 0 || result->videoChannel != 0) return ROE_FAILURE;

    reticle_cfg_t * cfg = reticle_model_cfg();
    uint8_t gun = proto_idx_to_ui(result->weaponIndex);
    if(gun >= RETICLE_GUN_COUNT) return ROE_FAILURE;

    reticle_gun_cfg_t * gc = &cfg->guns[gun];
    uint8_t dist_op = reticle_feature_consume_dist_op();

    uint8_t op_tag = proto_idx_to_ui(result->distIndex);

    if(dist_op == 0) {
        /* 查询当前活动距离标签详情：不改列表 / 默认 / 焦点。
         * 当前距离值优先信整表 shootDistances[op_tag]。 */
        ROE_U16 cur_dist = pick_dist_from_rsp(result->shootDistanceCount,
                                              result->shootDistances,
                                              op_tag,
                                              result->distValue);
        reticle_distance_entry_t * e = get_dist_entry(gc, result->distIndex);
        if(e) {
            apply_zero_to_entry(e, cur_dist, result->absX, result->absY, result->relX, result->relY);
        }
        /* 同步刷新距离管理器缓存，否则四级界面会继续显示旧的 rel_x/rel_y。 */
        reticle_distance_entry_t * de = reticle_distance_mgr_entry_by_tag(op_tag);
        if(de) {
            apply_zero_to_entry(de, cur_dist, result->absX, result->absY, result->relX, result->relY);
        }

        reticle_feature_set_active_distance_tag(op_tag);
        reticle_feature_refresh_calibration_from_model();
        if(reticle_feature_is_open() && reticle_feature_consume_wait_show_level3_on_dist_rsp()) {
            show_level3();
        }
        return ROE_SUCCESS;
    }

    /* 默认标签按协议返回的 defaultDistIndex 生效，它表示“标签身份”，不是当前排序位置。 */
    gc->default_idx = proto_idx_to_ui(result->defaultDistIndex);

    if(dist_op == 1) {
        /* Add：列表直接以返回的 shootDistances[] 为准，不再使用 opDistValue 回填。 */
        sync_dist_list(gc, result->shootDistanceCount, result->shootDistances);
        reticle_feature_reload_from_model();
        reticle_feature_mark_user_dirty();
        focus_level2_reticle();
        lv_group_focus_obj(ui_reticlerow7);
        return ROE_SUCCESS;
    }

    if(dist_op == 2) {
        /* Delete：按返回的剩余列表重建；若删掉当前活动标签，则回退到默认标签。 */
        sync_dist_list(gc, result->shootDistanceCount, result->shootDistances);
        if(reticle_feature_get_active_distance_tag() == op_tag)
            reticle_feature_set_active_distance_tag(gc->default_idx);
        reticle_feature_reload_from_model();
        reticle_feature_mark_user_dirty();
        reticle_feature_focus_selected_distance_level2();
        return ROE_SUCCESS;
    }

    if(dist_op == 3) {
        /* Modify：
         * 1) 列表整体以 shootDistances[] 为准
         * 2) 当前被修改标签的 zero 再按本次响应覆盖
         * 3) 焦点和页码按活动标签恢复 */
        sync_dist_list(gc, result->shootDistanceCount, result->shootDistances);
        ROE_U16 cur_dist = pick_dist_from_rsp(result->shootDistanceCount,
                                              result->shootDistances,
                                              op_tag,
                                              result->distValue);
        reticle_distance_entry_t * e = get_dist_entry(gc, result->distIndex);
        if(e) apply_zero_to_entry(e, cur_dist, result->absX, result->absY, result->relX, result->relY);
        reticle_feature_set_active_distance_tag(op_tag);
        reticle_feature_reload_from_model();
        reticle_feature_mark_user_dirty();
        reticle_feature_sync_selected_to_active_tag();
        reticle_feature_focus_selected_distance_level2();
        reticle_feature_refresh_calibration_from_model();
        return ROE_SUCCESS;
    }

    return ROE_SUCCESS;
}

ROE_S32 handleParseWeaponSetShootPositionMsg(ROE_U8 * msgData)
{
    RspWeaponSetShootPosition_st * result = (RspWeaponSetShootPosition_st *)msgData;
    LV_LOG_USER(
        "[RETICLE][RSP][3.67 shootPos] result=%u video=%u weapon=%u distIndex=%u distValue=%u abs=(%d,%d) rel=(%d,%d)",
        (unsigned)result->result,
        (unsigned)result->videoChannel,
        (unsigned)result->weaponIndex,
        (unsigned)result->distIndex,
        (unsigned)result->distValue,
        (int)result->absX,
        (int)result->absY,
        (int)result->relX,
        (int)result->relY);
    if(result->result != 0 || result->videoChannel != 0) return ROE_FAILURE;

    reticle_cfg_t * cfg = reticle_model_cfg();
    uint8_t gun = proto_idx_to_ui(result->weaponIndex);
    if(gun >= RETICLE_GUN_COUNT) return ROE_FAILURE;

    reticle_gun_cfg_t * gc = &cfg->guns[gun];
    reticle_distance_entry_t * e = get_dist_entry(gc, result->distIndex);
    apply_zero_to_entry(e, result->distValue, result->absX, result->absY, result->relX, result->relY);
    reticle_distance_entry_t * de = reticle_distance_mgr_entry_by_tag(proto_idx_to_ui(result->distIndex));
    if(de) apply_zero_to_entry(de, result->distValue, result->absX, result->absY, result->relX, result->relY);

    reticle_feature_set_active_distance_tag(proto_idx_to_ui(result->distIndex));
    reticle_feature_sync_selected_to_active_tag();
    reticle_feature_mark_user_dirty();
    reticle_feature_refresh_calibration_from_model();
    return ROE_SUCCESS;
}

ROE_S32 handleParseWeaponSetShootZeroMsg(ROE_U8 * msgData)
{
    RspWeaponSetShootZero_st * result = (RspWeaponSetShootZero_st *)msgData;
    LV_LOG_USER(
        "[RETICLE][RSP][3.68 zero] result=%u video=%u weapon=%u distIndex=%u distValue=%u abs=(%d,%d) rel=(%d,%d)",
        (unsigned)result->result,
        (unsigned)result->videoChannel,
        (unsigned)result->weaponIndex,
        (unsigned)result->distIndex,
        (unsigned)result->distValue,
        (int)result->absX,
        (int)result->absY,
        (int)result->relX,
        (int)result->relY);
    if(result->result != 0 || result->videoChannel != 0) return ROE_FAILURE;

    reticle_cfg_t * cfg = reticle_model_cfg();
    uint8_t gun = proto_idx_to_ui(result->weaponIndex);
    if(gun >= RETICLE_GUN_COUNT) return ROE_FAILURE;

    reticle_gun_cfg_t * gc = &cfg->guns[gun];
    reticle_distance_entry_t * e = get_dist_entry(gc, result->distIndex);
    apply_zero_to_entry(e, result->distValue, result->absX, result->absY, result->relX, result->relY);
    reticle_distance_entry_t * de = reticle_distance_mgr_entry_by_tag(proto_idx_to_ui(result->distIndex));
    if(de) apply_zero_to_entry(de, result->distValue, result->absX, result->absY, result->relX, result->relY);

    reticle_feature_set_active_distance_tag(proto_idx_to_ui(result->distIndex));
    reticle_feature_sync_selected_to_active_tag();
    reticle_feature_mark_user_dirty();
    reticle_feature_refresh_calibration_from_model();
    return ROE_SUCCESS;
}

ROE_S32 handleParseWeaponSaveConfigMsg(ROE_U8 * msgData)
{
    RspWeaponSaveConfig_st * result = (RspWeaponSaveConfig_st *)msgData;
    LV_LOG_USER("[RETICLE][RSP][3.69 save] result=%u", (unsigned)result->result);
    if(result->result != 0) {
        reticle_feature_on_save_result(false);
        return ROE_FAILURE;
    }

    reticle_model_nv_save(reticle_model_cfg());
    reticle_model_clear_dirty();
    reticle_feature_on_save_result(true);
    return ROE_SUCCESS;
}