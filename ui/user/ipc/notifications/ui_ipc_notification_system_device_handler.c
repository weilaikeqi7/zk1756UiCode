//
// Created by jinxing on 2026/3/2.
//

#include "ui.h"
#include "lvgl/lvgl.h"
#include "ui_ipc_notification_handler.h"

#include "ui_ipc_notification_types.h"
#include "ui_ipc_request_sender.h"
#include "reticle_model.h"
#include "reticle_feature.h"
#include "mainpage_event_handle.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

static lv_timer_t * self_timer = NULL;

static void set_magnetic_label(lv_obj_t * component, const char * text)
{
    if(component == NULL || text == NULL) return;

    lv_obj_t * label = ui_comp_get_child(component, UI_COMP_NUM_PANELNUM_LABEL);
    if(label != NULL) {
        lv_label_set_text(label, text);
    }
}

static void
self_timer_cb(lv_timer_t * timer)
{
    (void)timer;
    if(ui_MainPage != NULL) {
        lv_disp_load_scr(ui_MainPage);
    }
    if(self_timer != NULL) {
        lv_timer_delete(self_timer);
        self_timer = NULL;
    }
}

ROE_S32 UiIpcHandleNotificationInitialMagneticDeclination(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiNotificationInitialMagneticDeclination * magneticDeclination =
        (UiNotificationInitialMagneticDeclination *)msgData;
    magnetic.value = magneticDeclination->magneticDeclination;
    float v = magnetic.value;
    float absVal = (v < 0) ? -v : v;
    magnetic.symbol = (v < 0) ? '-' : '+';
    magnetic.num1 = (int)(absVal / 100) % 10;
    magnetic.num2 = (int)(absVal / 10) % 10;
    magnetic.num3 = (int)absVal % 10;
    magnetic.num4 = (int)(absVal * 10) % 10;
    magnetic.num5 = (int)(absVal * 100) % 10;
    char text[8];
    lv_snprintf(text, sizeof(text), "%c", magnetic.symbol);
    set_magnetic_label(ui_num1, text);
    lv_snprintf(text, sizeof(text), "%d", magnetic.num1);
    set_magnetic_label(ui_num2, text);
    lv_snprintf(text, sizeof(text), "%d", magnetic.num2);
    set_magnetic_label(ui_num3, text);
    lv_snprintf(text, sizeof(text), "%d", magnetic.num3);
    set_magnetic_label(ui_num4, text);
    lv_snprintf(text, sizeof(text), "%d", magnetic.num4);
    set_magnetic_label(ui_num5, text);
    lv_snprintf(text, sizeof(text), "%d", magnetic.num5);
    set_magnetic_label(ui_num6, text);
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationObserveMode(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    LV_LOG_USER("[VIDEO][NTF] observe mode received");
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationPeripheralSelfTestInfo(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;

    UiNotificationPeripheralSelfTestInfo * selfCheck = (UiNotificationPeripheralSelfTestInfo *)msgData;
    if(ui_self == NULL || ui_self_item_label[0] == NULL) {
        LV_LOG_WARN("[SELFTEST][DROP] self-check screen is not initialized");
        return ROE_FAILURE;
    }

    int sum = 0;
    LV_LOG_USER("selfCheck->selfCheckState = %d", selfCheck->selfCheckState);
    for(int i = 0; i < SELF_ITEM_NUM; i++) {
        ROE_U8 state = selfCheck->selfItem[i];
        if(state >= 3U) {
            LV_LOG_WARN("[SELFTEST][DROP] invalid item state index:%d value:%u", i, (unsigned)state);
            state = 0;
        }
        if(ui_self_item_label[i] == NULL) continue;

        lv_label_set_text(ui_self_item_label[i], self_info[state]);
        LV_LOG_USER("selfCheck->selfItem[%d] = %d", i, selfCheck->selfItem[i]);
        if(selfCheck->selfItem[i] == 2) {
            lv_obj_set_style_text_color(ui_self_item_label[i], lv_color_hex(0xFF3B30), LV_PART_MAIN | LV_STATE_DEFAULT);
        } else {
            lv_obj_set_style_text_color(ui_self_item_label[i], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    if(selfCheck->selfCheckState == 1) {
        for(int i = 0; i < SELF_ITEM_NUM; i++) {
            sum += selfCheck->selfItem[i];
        }

        if(sum == 7) {
            if(self_timer != NULL) {
                lv_timer_delete(self_timer);
                self_timer = NULL;
            }
            self_timer = lv_timer_create(self_timer_cb, 1000, NULL);
        } else {
            if(ui_self_button_label != NULL) {
                lv_obj_remove_flag(ui_self_button_label, LV_OBJ_FLAG_HIDDEN);
            }
            if(lv_screen_active() != ui_self) {
                lv_screen_load(ui_self);
            }
            popup_stack_push(&g_popup_stack, &g_popup_self);
        }
        if(ui_imgsd != NULL) {
            if(selfCheck->selfItem[2] == 1) {
                lv_obj_set_style_image_recolor_opa(ui_imgsd, LV_OPA_100, LV_PART_MAIN);
            } else {
                lv_obj_set_style_image_recolor_opa(ui_imgsd, LV_OPA_0, LV_PART_MAIN);
            }
        }
    }
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationCompassData(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiNotificationCompassData * compass = (UiNotificationCompassData *)msgData;
    ui_attitude_scale_update(compass->yaw, compass->roll, compass->pitch);
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationGnssData(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    LV_LOG_USER("[GNSS][NTF] position update received");
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationPeripheralRealTimeInfo(ROE_U8 * msgData)
{
    if(msgData == NULL || ui_labelsd == NULL || ui_imgbattery == NULL) return ROE_FAILURE;
    UiNotificationPeripheralRealTimeInfo * realTimeInfo = (UiNotificationPeripheralRealTimeInfo *)msgData;
    lv_label_set_text_fmt(ui_labelsd, "%.1fG", realTimeInfo->sdAvailableGB);

    if(realTimeInfo->batteryPercent >= 75) {
        lv_image_set_src(ui_imgbattery, IMAGES_PATH "Battery4.png");
    } else if(realTimeInfo->batteryPercent >= 50) {
        lv_image_set_src(ui_imgbattery, IMAGES_PATH "Battery3.png");
    } else if(realTimeInfo->batteryPercent >= 25) {
        lv_image_set_src(ui_imgbattery, IMAGES_PATH "Battery2.png");
    } else {
        lv_image_set_src(ui_imgbattery, IMAGES_PATH "Battery1.png");
    }
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationCompassCalibrationScore(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    LV_LOG_USER("[COMPASS][NTF] calibration score received");
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationDialogBoxDisplay(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiNotificationDialogBoxDisplay * dialog = (UiNotificationDialogBoxDisplay *)msgData;
    LV_LOG_USER("dialog->dialogType:%d, dialog->option:%d", dialog->dialogType, dialog->option);
    if(dialog->dialogType == 0) {
        if(dialog->option == 0) {
            if(&g_popup_self == popup_stack_get_top(&g_popup_stack)) {
                lv_disp_load_scr(ui_MainPage);
            }
            popup_stack_pop(&g_popup_stack);
            if(popup_stack_depth(&g_popup_stack) == 0) {
                UiIpcSendExitDialogBoxRequest(global_parameters.sendMsgQueId);
            }
        } else if(dialog->option == 1) {
            int depth = popup_stack_depth(&g_popup_stack);
            for(int i = 0; i < depth; i++) {
                if(&g_popup_self == popup_stack_get_top(&g_popup_stack)) {
                    lv_disp_load_scr(ui_MainPage);
                }
                popup_stack_pop(&g_popup_stack);
            }
            UiIpcSendExitDialogBoxRequest(global_parameters.sendMsgQueId);
        }
    } else if(dialog->dialogType == 2) {
        popup_stack_push(&g_popup_stack, &g_popup_poweroff);
    }
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationMainMenuOperate(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiNotificationMainMenuOperate * menu = (UiNotificationMainMenuOperate *)msgData;
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

ROE_S32 UiIpcHandleNotificationKeyEventInfo(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiNotificationKeyEventInfo * menuKey = (UiNotificationKeyEventInfo *)msgData;
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

ROE_S32 UiIpcHandleNotificationResourcePathInfo(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiNotificationResourcePathInfo * path = (UiNotificationResourcePathInfo *)msgData;
    const ROE_U8 * data = path->pathData;
    char pathText[4][256] = {{0}};

    for(ROE_U8 i = 0; i < 4; i++) {
        ROE_U8 pathLen = *data++;
        ROE_SIZE copyLen = pathLen;
        if(copyLen >= sizeof(pathText[i])) {
            copyLen = sizeof(pathText[i]) - 1U;
        }
        memcpy(pathText[i], data, copyLen);
        pathText[i][copyLen] = '\0';
        data += pathLen;
    }
    LV_LOG_USER("resource paths: media=%s bitmap=%s handheld=%s calibration=%s",
                pathText[0],
                pathText[1],
                pathText[2],
                pathText[3]);
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationReticleOverallInfo(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiNotificationReticleOverallInfo * reticleInfo = (UiNotificationReticleOverallInfo *)msgData;
    LV_LOG_USER(
        "[RETICLE][NTF][2.18 overall] gunCount=%u styleCount=%u colorCount=%u display=%u rotate=%u ballistic=%u curGun=%u maxDist=%u defaultDistanceIndex=%u defaultDistance=%u",
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
    if(cfg->gun_count > RETICLE_GUN_COUNT) cfg->gun_count = RETICLE_GUN_COUNT;
    cfg->visible = !!reticleInfo->displaySwitch;
    cfg->rotate = !!reticleInfo->rotateSwitch;
    cfg->ballistic = !!reticleInfo->ballisticSwitch;
    ui_set_rowswitch_checked(ui_rowballistic, cfg->ballistic);
    cfg->cur_gun = (reticleInfo->currentWeaponIndex > 0) ? (uint8_t)(reticleInfo->currentWeaponIndex - 1) : 0;
    if(cfg->cur_gun >= RETICLE_GUN_COUNT) cfg->cur_gun = 0;
    if(ui_imggun != NULL) {
        lv_label_set_text_fmt(ui_imggun, "G%d", cfg->cur_gun + 1);
    }
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
    if(ui_labeldistance != NULL) {
        lv_label_set_text_fmt(ui_labeldistance, "%d", gc->items[gc->default_idx].dist);
    }
    /* 2.18 只更新概览模型，不在通知后立刻查询 3.62/3.66。 */
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationPanTiltHorizontalAngle(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    LV_LOG_USER("[PANTILT][NTF] horizontal angle received");
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationPanTiltVerticalAngle(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    LV_LOG_USER("[PANTILT][NTF] vertical angle received");
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationPanTiltHorizontalRunningStatus(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    LV_LOG_USER("[PANTILT][NTF] horizontal running status received");
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationPanTiltVerticalRunningStatus(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    LV_LOG_USER("[PANTILT][NTF] vertical running status received");
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationDeviceAbility(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    LV_LOG_USER("[DEVICE][NTF] capability received");
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationInfraredBadPixelThreshold(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiNotificationInfraredBadPixelThreshold * badPixelThreshold = (UiNotificationInfraredBadPixelThreshold *)msgData;
    g_app.bad_point.threshold = badPixelThreshold->defaultValue;
    g_app.bad_point.threshold_max = badPixelThreshold->maxValue;
    g_app.bad_point.threshold_min = badPixelThreshold->minValue;
    LV_LOG_USER("threshold:%d, threshold_max:%d, threshold_min:%d",
                g_app.bad_point.threshold,
                g_app.bad_point.threshold_max,
                g_app.bad_point.threshold_min);
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationInfraredBadPixelCount(ROE_U8 * msgData)
{
    if(msgData == NULL || ui_bad_pixel_item1 == NULL) return ROE_FAILURE;
    UiNotificationInfraredBadPixelCount * badPixelCount = (UiNotificationInfraredBadPixelCount *)msgData;
    g_app.bad_point.bpnum = badPixelCount->badPixelCount;
    lv_obj_t * count_label = ui_comp_get_child(ui_bad_pixel_item1, UI_COMP_MCITEM_MCP2P1L2);
    if(count_label == NULL) {
        LV_LOG_WARN("[INFRARED][NTF] bad-pixel count control is not initialized");
        return ROE_FAILURE;
    }
    lv_label_set_text_fmt(count_label, "%u", g_app.bad_point.bpnum);
    LV_LOG_USER("bpnum:%d", g_app.bad_point.bpnum);
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationDeviceInitConfig(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiNotificationDeviceInitConfig * initConfig = (UiNotificationDeviceInitConfig *)msgData;
    if(initConfig->language >= (ROE_U8)g_app.ui.language_item.count) return ROE_FAILURE;
    g_app.ui.language_item.index = initConfig->language;
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationPeripheralBatteryInfo(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    LV_LOG_USER("[DEVICE][NTF] battery status received");
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationPanTiltOperateInfo(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    LV_LOG_USER("[PANTILT][NTF] control status received");
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationMainDisplayStatus(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    LV_LOG_USER("[DISPLAY][NTF] OLED status received");
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationInfraredHotPixelRepairCorrection(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    LV_LOG_USER("[INFRARED][NTF] hot pixel correction value received");
    return ROE_SUCCESS;
}

ROE_S32 UiIpcHandleNotificationReticleInfoUpdate(ROE_U8 * msgData)
{
    if(msgData == NULL) return ROE_FAILURE;
    UiNotificationReticleInfoUpdate * reticleUpdate = (UiNotificationReticleInfoUpdate *)msgData;
    UiReticleEntry * reticleEntries[UI_MAX_DIVIDING_PLATES_NUM];

    ROE_S8 reticleCount = reticleUpdate->reticleCount;
    ROE_U8 * dataPtr = reticleUpdate->reticleData;
    const char * imageName[3] = {"/run/reticleUi0.bmp", "/run/reticleUi1.bmp", "/run/reticleUi2.bmp"};
    char name[256];
    char logName[256];

    if(reticleCount < 0) {
        LV_LOG_WARN("[RETICLE][NTF] invalid reticle count:%d", reticleCount);
        return ROE_FAILURE;
    }
    if(reticleCount > UI_MAX_DIVIDING_PLATES_NUM) {
        reticleCount = UI_MAX_DIVIDING_PLATES_NUM;
    }

    for(ROE_S8 i = 0; i < reticleCount; i++) {
        reticleEntries[i] = (UiReticleEntry *)dataPtr;
        dataPtr += sizeof(UiReticleEntry) + reticleEntries[i]->nameLength;

        ROE_SIZE logNameLen = reticleEntries[i]->nameLength;
        if(logNameLen >= sizeof(logName)) {
            logNameLen = sizeof(logName) - 1U;
        }
        memcpy(logName, reticleEntries[i]->name, logNameLen);
        logName[logNameLen] = '\0';

        LV_LOG_USER(
            "state:%d, width:%d, height:%d, displayX:%d, displayY:%d, cuttingX:%d, cuttingY:%d, cuttingWidth:%d, cuttingHeight:%d, nameLength:%d, name:%s",
            reticleEntries[i]->state,
            reticleEntries[i]->width,
            reticleEntries[i]->height,
            reticleEntries[i]->displayX,
            reticleEntries[i]->displayY,
            reticleEntries[i]->cuttingX,
            reticleEntries[i]->cuttingY,
            reticleEntries[i]->cuttingWidth,
            reticleEntries[i]->cuttingHeight,
            reticleEntries[i]->nameLength,
            logName);

        /* -1 means unchanged. Do not resize or reload its image. */
        if(reticleEntries[i]->state == -1) {
            continue;
        }
        if(reticleEntries[i]->state != 0 && reticleEntries[i]->state != 1) {
            continue;
        }

        /* Keep the latest state while the playback page is active. */
        g_app.reticle_state[i] = reticleEntries[i]->state;
        if(g_app.playPageFlag != 0) {
            continue;
        }

        if(ui_dividing_contimage[i] == NULL || ui_dividing_image[i] == NULL) {
            LV_LOG_WARN("[RETICLE][NTF] reticle controls are not initialized index:%d", i);
            continue;
        }

        if(reticleEntries[i]->state == 0) {
            lv_obj_add_flag(ui_dividing_contimage[i], LV_OBJ_FLAG_HIDDEN);
            continue;
        }

        lv_obj_remove_flag(ui_dividing_contimage[i], LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_width(ui_dividing_contimage[i], reticleEntries[i]->cuttingWidth);
        lv_obj_set_height(ui_dividing_contimage[i], reticleEntries[i]->cuttingHeight);
        lv_obj_set_pos(ui_dividing_contimage[i],
                       reticleEntries[i]->displayX + reticleEntries[i]->cuttingX,
                       reticleEntries[i]->displayY + reticleEntries[i]->cuttingY);
        lv_obj_set_pos(ui_dividing_image[i],
                       -reticleEntries[i]->cuttingX,
                       -reticleEntries[i]->cuttingY);
        char sourceName[256] = {0};
        ROE_SIZE nameLength = reticleEntries[i]->nameLength;
        if(nameLength >= sizeof(sourceName)) {
            nameLength = sizeof(sourceName) - 1U;
        }
        memcpy(sourceName, reticleEntries[i]->name, nameLength);
        sourceName[nameLength] = '\0';
        if(sourceName[0] != '\0') {
            rename(sourceName, imageName[i]);
        }
        lv_memset(name, 0, 256);
        snprintf(name, sizeof(name), "A:%s", imageName[i]);
        lv_image_set_src(ui_dividing_image[i], name);
        lv_obj_update_layout(ui_dividing_contimage[i]);
    }

    return ROE_SUCCESS;
}
