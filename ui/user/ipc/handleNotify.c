//
// Created by jinxing on 2026/3/2.
//

#include "ui.h"
#include "handleNotify.h"

#include "ipcMsgQue4UiRcvNotify.h"
#include "reticle_model.h"
#include "reticle_feature.h"
#include "mainpage_event_handle.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

static lv_timer_t * self_timer = NULL;

static void
self_timer_cb(lv_timer_t * timer)
{
    (void)timer;
    lv_disp_load_scr(ui_MainPage);
    if(self_timer != NULL) {
        lv_timer_delete(self_timer);
        self_timer = NULL;
    }
}

// 函数：将米 (Meter) 转换为码 (Yard)
ROE_S32 handleMagneticDeclinationNotify(ROE_U8 * msgData)
{
    NotifyMagneticDeclination_st * magneticDecLination = (NotifyMagneticDeclination_st *)msgData;
    magnetic.value = magneticDecLination->magneticDeclination;
    float v = magnetic.value;
    float absVal = (v < 0) ? -v : v;
    magnetic.symbol = (v < 0) ? '-' : '+';
    magnetic.num1 = (int)(absVal / 100) % 10;
    magnetic.num2 = (int)(absVal / 10) % 10;
    magnetic.num3 = (int)absVal % 10;
    magnetic.num4 = (int)(absVal * 10) % 10;
    magnetic.num5 = (int)(absVal * 100) % 10;
    lv_label_set_text_fmt(ui_comp_get_child(ui_num1, UI_COMP_NUM_PANELNUM_LABEL), "%c", magnetic.symbol);
    lv_label_set_text_fmt(ui_comp_get_child(ui_num2, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num1);
    lv_label_set_text_fmt(ui_comp_get_child(ui_num3, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num2);
    lv_label_set_text_fmt(ui_comp_get_child(ui_num4, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num3);
    lv_label_set_text_fmt(ui_comp_get_child(ui_num5, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num4);
    lv_label_set_text_fmt(ui_comp_get_child(ui_num6, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num5);
    return ROE_SUCCESS;
}

ROE_S32 handleObserveModeNotify(ROE_U8 * msgData)
{
    NotifyObserveMode_st * observeMode = (NotifyObserveMode_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handlePeripheralSelfTest(ROE_U8 * msgData)
{
    NotifySelfCheck_st * selfCheck = (NotifySelfCheck_st *)msgData;
    int sum = 0;
    LV_LOG_USER("selfCheck->selfCheckState = %d", selfCheck->selfCheckState);
    for(int i = 0; i < SELF_ITEM_NUM; i++) {
        lv_label_set_text(ui_self_item_label[i], self_info[selfCheck->selfItem[i]]);
        LV_LOG_USER("selfCheck->selfItem[%d] = %d", i, selfCheck->selfItem[i]);
        if(selfCheck->selfItem[i] == 2) {
            lv_obj_set_style_text_color(ui_self_item_label[i], lv_color_hex(0xFF3B30), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    if(selfCheck->selfCheckState == 1) {
        for(int i = 0; i < SELF_ITEM_NUM; i++) {
            sum += selfCheck->selfItem[i];
        }

        if(sum == 7) {
            self_timer = lv_timer_create(self_timer_cb, 1000, NULL);
        } else {
            popup_stack_push(&g_popup_stack, &g_popup_self);
        }
        if(selfCheck->selfItem[2] == 1) {
            lv_obj_set_style_image_recolor_opa(ui_imgsd, LV_OPA_100, LV_PART_MAIN);
        } else {
            lv_obj_set_style_image_recolor_opa(ui_imgsd, LV_OPA_0, LV_PART_MAIN);
        }
    }
    return ROE_SUCCESS;
}

ROE_S32 handleCompassData(ROE_U8 * msgData)
{
    NotifyCompass_st * compass = (NotifyCompass_st *)msgData;
    ui_attitude_scale_update(compass->yaw, compass->roll, compass->pitch);
    return ROE_SUCCESS;
}

ROE_S32 handleGpsData(ROE_U8 * msgData)
{
    NotifyGps_st * gps = (NotifyGps_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleSdVccVolNotify(ROE_U8 * msgData)
{
    NotifyPower_st * sdVccVol = (NotifyPower_st *)msgData;
    lv_label_set_text_fmt(ui_labelsd, "%.1fG", sdVccVol->sdAvailableGB);

    if(sdVccVol->batteryPercent >= 75) {
        lv_image_set_src(ui_imgbattery, IMAGES_PATH "Battery4.png");
    } else if(sdVccVol->batteryPercent >= 50) {
        lv_image_set_src(ui_imgbattery, IMAGES_PATH "Battery3.png");
    } else if(sdVccVol->batteryPercent >= 25) {
        lv_image_set_src(ui_imgbattery, IMAGES_PATH "Battery2.png");
    } else {
        lv_image_set_src(ui_imgbattery, IMAGES_PATH "Battery1.png");
    }
    return ROE_SUCCESS;
}

ROE_S32 handleCompassCalibrationNotify(ROE_U8 * msgData)
{
    NotifyCompassScore_st * compassScore = (NotifyCompassScore_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleDialogBoxNotify(ROE_U8 * msgData)
{
    NotifyDialog_st * dialog = (NotifyDialog_st *)msgData;
    LV_LOG_USER("dialog->dialogType:%d, dialog->option:%d", dialog->dialogType, dialog->option);
    if(dialog->dialogType == 0) {
        if(dialog->option == 0) {
            if(&g_popup_self == popup_stack_get_top(&g_popup_stack)) {
                lv_disp_load_scr(ui_MainPage);
            }
            popup_stack_pop(&g_popup_stack);
            if(popup_stack_depth(&g_popup_stack) == 0) {
                SendMsg4UiExitDialogBoxReq(global_parameters.sendMsgQueId);
            }
        } else if(dialog->option == 1) {
            int depth = popup_stack_depth(&g_popup_stack);
            for(int i = 0; i < depth; i++) {
                if(&g_popup_self == popup_stack_get_top(&g_popup_stack)) {
                    lv_disp_load_scr(ui_MainPage);
                }
                popup_stack_pop(&g_popup_stack);
            }
            SendMsg4UiExitDialogBoxReq(global_parameters.sendMsgQueId);
        }
    } else if(dialog->dialogType == 2) {
        popup_stack_push(&g_popup_stack, &g_popup_poweroff);
    }
    return ROE_SUCCESS;
}

ROE_S32 handleMenuNotify(ROE_U8 * msgData)
{
    NotifyMenuMode_st * menu = (NotifyMenuMode_st *)msgData;
    LV_LOG_USER("menu->action:%d, menu->option:%d", menu->action, menu->option);
    if(menu->action == 0) {
        if(menu->option == 0) {
            g_my_keypad_btn_points[3] = 1;
        } else if(menu->option == 1) {
            hidden_all_menu();
        }
    } else if(menu->action == 1) {
        show_menu_page1();
    }
    return ROE_SUCCESS;
}

ROE_S32 handleKeyEventNotify(ROE_U8 * msgData)
{
    NotifyMenuKey_st * menuKey = (NotifyMenuKey_st *)msgData;
    if(menuKey->inMenu == 1) {
        // LV_LOG_USER("menuKey->keyCode:%d, menuKey->keyEvent:%d", menuKey->keyCode, menuKey->keyEvent);
        switch(menuKey->keyCode) {
        case 0:
            g_my_keypad_btn_points[2] = 1;
            break;
        case 1:
            g_my_keypad_btn_points[0] = 1;
            break;
        case 4:
            g_my_keypad_btn_points[1] = 1;
            break;
        default:
            break;
        }
    }
    return ROE_SUCCESS;
}

ROE_S32 handleResourcePathNotify(ROE_U8 * msgData)
{
    NotifyPath_st * path = (NotifyPath_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleReticleOverallInfoNotify(ROE_U8 * msgData)
{
    NotifyReticleInfo_st * reticleInfo = (NotifyReticleInfo_st *)msgData;
    LV_LOG_USER(
        "[RETICLE][NTF][2.18 overall] gunCount=%u styleCount=%u colorCount=%u display=%u rotate=%u ballistic=%u curGun=%u maxDist=%u defaultDistIndex=%u defaultDist=%u",
        (unsigned)reticleInfo->weaponTypeCount,
        (unsigned)reticleInfo->reticleTypeCount,
        (unsigned)reticleInfo->colorCount,
        (unsigned)reticleInfo->displaySwitch,
        (unsigned)reticleInfo->rotateSwitch,
        (unsigned)reticleInfo->ballisticSwitch,
        (unsigned)reticleInfo->currentWeaponIndex,
        (unsigned)reticleInfo->maxDistanceCount,
        (unsigned)reticleInfo->defaultDistanceIndex,
        (unsigned)reticleInfo->defaultDistance);
    reticle_cfg_t * cfg = reticle_model_cfg();
    if(!cfg) return ROE_FAILURE;

    cfg->gun_count = reticleInfo->weaponTypeCount ? reticleInfo->weaponTypeCount : 1;
    cfg->style_count = reticleInfo->reticleTypeCount ? reticleInfo->reticleTypeCount : 1;
    cfg->color_count = reticleInfo->colorCount ? reticleInfo->colorCount : 1;
    cfg->visible = !!reticleInfo->displaySwitch;
    cfg->rotate = !!reticleInfo->rotateSwitch;
    cfg->ballistic = !!reticleInfo->ballisticSwitch;
    ui_set_rowswitch_checked(ui_rowballistic, cfg->ballistic);
    cfg->cur_gun = (reticleInfo->currentWeaponIndex > 0) ? (uint8_t)(reticleInfo->currentWeaponIndex - 1) : 0;
    lv_label_set_text_fmt(ui_imggun, "G%d", cfg->cur_gun + 1);
    reticle_gun_cfg_t * gc = &cfg->guns[cfg->cur_gun];
    if(reticleInfo->defaultDistanceIndex > 0)
        gc->default_idx = (uint8_t)(reticleInfo->defaultDistanceIndex - 1);
    else
        gc->default_idx = 0;

    if(gc->count == 0) gc->count = 1;
    if(gc->default_idx >= RETICLE_MAX_DISTANCE_ITEMS) gc->default_idx = 0;
    if(gc->default_idx >= gc->count) gc->count = (uint8_t)(gc->default_idx + 1);
    if(gc->count > RETICLE_MAX_DISTANCE_ITEMS) gc->count = RETICLE_MAX_DISTANCE_ITEMS;

    gc->items[gc->default_idx].tag_idx = gc->default_idx;
    gc->items[gc->default_idx].dist = reticleInfo->defaultDistance;
    lv_label_set_text_fmt(ui_labeldistance, "%d", gc->items[gc->default_idx].dist);
    /* 2.18 只更新概览模型，不在通知后立刻查询 3.62/3.66。 */
    return ROE_SUCCESS;
}

ROE_S32 handlePanTiltHorizontalAngleNotify(ROE_U8 * msgData)
{
    NotifyGimbalYaw_st * gimbalYaw = (NotifyGimbalYaw_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handlePanTiltVerticalAngleNotify(ROE_U8 * msgData)
{
    NotifyGimbalPitch_st * gimbalPitch = (NotifyGimbalPitch_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handlePanTiltHorizontalRunningStatusNotify(ROE_U8 * msgData)
{
    NotifyGimbalYawState_st * gimbalYawState = (NotifyGimbalYawState_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handlePanTiltVerticalRunningStatusNotify(ROE_U8 * msgData)
{
    NotifyGimbalPitchState_st * gimbalPitchState = (NotifyGimbalPitchState_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handlePeripheralsAbilityNotify(ROE_U8 * msgData)
{
    NotifyDeviceCapability_st * deviceCapability = (NotifyDeviceCapability_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleInfraredBadPixelThresholdNotify(ROE_U8 * msgData)
{
    NotifyBadPixelThreshold_st * badPixelThreshold = (NotifyBadPixelThreshold_st *)msgData;
    g_app.bad_point.threshold = badPixelThreshold->defaultValue;
    g_app.bad_point.threshold_max = badPixelThreshold->maxValue;
    g_app.bad_point.threshold_min = badPixelThreshold->minValue;
    LV_LOG_USER("threshold:%d, threshold_max:%d, threshold_min:%d",
                g_app.bad_point.threshold,
                g_app.bad_point.threshold_max,
                g_app.bad_point.threshold_min);
    return ROE_SUCCESS;
}

ROE_S32 handleInfraredBadPixelNumNotify(ROE_U8 * msgData)
{
    NotifyBadPixelCount_st * badPixelNum = (NotifyBadPixelCount_st *)msgData;
    g_app.bad_point.bpnum = badPixelNum->badPixelCount;
    lv_label_set_text_fmt(
        ui_comp_get_child(ui_bad_pixel_item1, UI_COMP_MCITEM_MCP2P1L2),
        "%u",
        g_app.bad_point.bpnum);
    LV_LOG_USER("bpnum:%d", g_app.bad_point.bpnum);
    return ROE_SUCCESS;
}

ROE_S32 handleInitConfigNotify(ROE_U8 * msgData)
{
    NotifyInitConfig_st * initConfig = (NotifyInitConfig_st *)msgData;
    g_app.ui.language_item.index = initConfig->language;
    return ROE_SUCCESS;
}

ROE_S32 handleBatteryInfoNotify(ROE_U8 * msgData)
{
    NotifyBattery_st * batteryInfo = (NotifyBattery_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleRtCtlPanTiltInfoNotify(ROE_U8 * msgData)
{
    NotifyGimbalControl_st * gimbalControl = (NotifyGimbalControl_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleOledStatusInfoNotify(ROE_U8 * msgData)
{
    NotifyOled_st * oledStatus = (NotifyOled_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleInfraredHotPixelRepairedCorrectedValueNotify(ROE_U8 * msgData)
{
    NotifyHotPixelFix_st * hotPixelFix = (NotifyHotPixelFix_st *)msgData;
    return ROE_SUCCESS;
}

ROE_S32 handleReticleInfoUpdatingNotify(ROE_U8 * msgData)
{
    NotifyReticleUpdate_st * reticleUpdate = (NotifyReticleUpdate_st *)msgData;
    DividingPlates_st * dividingPlatesinfo[UI_MAX_DIVIDING_PLATES_NUM];

    ROE_S8 conut = reticleUpdate->num;
    ROE_U8 * dataPtr = reticleUpdate->dividingPlatesData;
    char * imageName[3] = {"/run/reticleUi0.bmp", "/run/reticleUi1.bmp", "/run/reticleUi2.bmp"};
    char name[256];

    if(conut > UI_MAX_DIVIDING_PLATES_NUM) {
        conut = UI_MAX_DIVIDING_PLATES_NUM;
    }

    for(ROE_S8 i = 0; i < conut; i++) {
        dividingPlatesinfo[i] = (DividingPlates_st *)dataPtr;
        dataPtr += sizeof(DividingPlates_st) + dividingPlatesinfo[i]->nameLen;

        // LV_LOG_USER(
        //     "state:%d, width:%d, height:%d, displayX:%d, displayY:%d, cuttingX:%d, cuttingY:%d, cuttingWidth:%d, cuttingHeight:%d, nameLen:%d, name:%s",
        //     dividingPlatesinfo[i]->state,
        //     dividingPlatesinfo[i]->width,
        //     dividingPlatesinfo[i]->height,
        //     dividingPlatesinfo[i]->displayX,
        //     dividingPlatesinfo[i]->displayY,
        //     dividingPlatesinfo[i]->cuttingX,
        //     dividingPlatesinfo[i]->cuttingY,
        //     dividingPlatesinfo[i]->cuttingWidth,
        //     dividingPlatesinfo[i]->cuttingHeight,
        //     dividingPlatesinfo[i]->nameLen,
        //     dividingPlatesinfo[i]->name);

        if(g_app.playPageFlag == 0) {
            if(dividingPlatesinfo[i]->state == 1) {
                lv_obj_remove_flag(ui_dividing_contimage[i], LV_OBJ_FLAG_HIDDEN);
                g_app.reticle_state[i] = dividingPlatesinfo[i]->state;
            } else if(dividingPlatesinfo[i]->state == 0) {
                lv_obj_add_flag(ui_dividing_contimage[i], LV_OBJ_FLAG_HIDDEN);
                g_app.reticle_state[i] = dividingPlatesinfo[i]->state;
                continue;
            } else {
                continue;
            }
        }
        lv_obj_set_width(ui_dividing_contimage[i], dividingPlatesinfo[i]->cuttingWidth);
        lv_obj_set_height(ui_dividing_contimage[i], dividingPlatesinfo[i]->cuttingHeight);
        lv_obj_set_pos(ui_dividing_contimage[i],
                       dividingPlatesinfo[i]->displayX + dividingPlatesinfo[i]->cuttingX,
                       dividingPlatesinfo[i]->displayY + dividingPlatesinfo[i]->cuttingY);
        lv_obj_set_pos(ui_dividing_image[i],
                       -dividingPlatesinfo[i]->cuttingX,
                       -dividingPlatesinfo[i]->cuttingY);
        rename((char *)dividingPlatesinfo[i]->name, imageName[i]);
        lv_memset(name, 0, 256);
        sprintf(name, "A:%s", imageName[i]);
        lv_image_set_src(ui_dividing_image[i], name);
        lv_obj_update_layout(ui_dividing_contimage[i]);
    }

    return ROE_SUCCESS;
}