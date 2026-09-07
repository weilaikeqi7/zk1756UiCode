//
// Created by jinxing on 2026/1/5.
//

#include "menu_visibility.h"

#include "ui/business/reticle/distance_editor.h"
#include "ui_ipc_request_sender.h"
#include "reticle_feature.h"
#include "ui_focus_manager.h"

void show_menu_page1(void)
{
    lv_obj_remove_flag(ui_contpage1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
    if(g_app.video.tilt == ON)
        lv_obj_add_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {
        ui_rowlrf, ui_rowimagemode, ui_rowbrightness, ui_rowcontrast,
        ui_rowsharpness, ui_rowexpansion, ui_rowpip,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void hidden_menu_page1(void)
{
    lv_obj_add_flag(ui_contpage1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
    ui_focus_group_clear();
    if(g_app.video.tilt == ON)
        lv_obj_remove_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);
    UiIpcSendExitMenuRequest(global_parameters.sendMsgQueId);
}

void show_menu_page1_item1(void)
{
    lv_obj_remove_flag(ui_contmenu2, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {ui_menu1row1, ui_menu1row2, ui_menu1row3, ui_menu1row4, ui_menu1row5};
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void hidden_menu_page1_item1(void)
{
    lv_obj_add_flag(ui_contmenu2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowlrf, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {
        ui_rowlrf, ui_rowimagemode, ui_rowbrightness, ui_rowcontrast,
        ui_rowsharpness, ui_rowexpansion, ui_rowpip,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void show_menu_page1_item2(void)
{
    lv_obj_remove_flag(ui_contitem2, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {
        ui_rowitem21, ui_rowitem22, ui_rowitem23, ui_rowitem24, ui_rowitem25,
        ui_rowitem26, ui_rowitem27, ui_rowitem28, ui_rowitem29,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void hidden_menu_page1_item2(void)
{
    lv_obj_add_flag(ui_contitem2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowimagemode, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {
        ui_rowlrf, ui_rowimagemode, ui_rowbrightness, ui_rowcontrast,
        ui_rowsharpness, ui_rowexpansion, ui_rowpip,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));

    ui_focus_group_focus(ui_rowimagemode);
}

void show_menu_page2(void)
{
    lv_obj_remove_flag(ui_contpage2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
    if(g_app.video.tilt == ON)
        lv_obj_add_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {
        ui_rowwifi, ui_rowtilt, ui_rowcompass, ui_rowreticle,
        ui_rowballistic, ui_rowmic, ui_rowrav,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void hidden_menu_page2(void)
{
    lv_obj_add_flag(ui_contpage2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
    ui_focus_group_clear();
    if(g_app.video.tilt == ON)
        lv_obj_remove_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);
    UiIpcSendExitMenuRequest(global_parameters.sendMsgQueId);
}

void show_menu_page3(void)
{
    lv_obj_remove_flag(ui_contpage3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
    if(g_app.video.tilt == ON)
        lv_obj_add_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {
        ui_rowstandby, ui_rowcompasscalibration, ui_rowdeadpixel,
        ui_rowstatusbar, ui_rowdeletefile, ui_rowsetting,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void hidden_menu_page3(void)
{
    lv_obj_add_flag(ui_contpage3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
    ui_focus_group_clear();
    if(g_app.video.tilt == ON)
        lv_obj_remove_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);
    UiIpcSendExitMenuRequest(global_parameters.sendMsgQueId);
}

void show_menu_page3_item1(void)
{
    lv_obj_remove_flag(ui_page3item1, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {ui_rowswitch1, ui_rowitem1, ui_rowitem2};
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void hidden_menu_page3_item1(void)
{
    lv_obj_add_flag(ui_page3item1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowstandby, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {
        ui_rowstandby, ui_rowcompasscalibration, ui_rowdeadpixel,
        ui_rowstatusbar, ui_rowdeletefile, ui_rowsetting,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void show_menu_page3_item2(void)
{
    lv_obj_remove_flag(ui_page3item2, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {ui_rowitem3, ui_rowitem4, ui_rowitem5};
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void hidden_menu_page3_item2(void)
{
    lv_obj_add_flag(ui_page3item2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowcompasscalibration, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {
        ui_rowstandby, ui_rowcompasscalibration, ui_rowdeadpixel,
        ui_rowstatusbar, ui_rowdeletefile, ui_rowsetting,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(ui_rowcompasscalibration);
}

void show_menu_page3_item3(void)
{
    lv_obj_remove_flag(ui_dead_pixels_cont, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {ui_bad_pixel, ui_pixel_return};
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void hidden_menu_page3_item3(void)
{
    lv_obj_add_flag(ui_dead_pixels_cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowdeadpixel, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {
        ui_rowstandby, ui_rowcompasscalibration, ui_rowdeadpixel,
        ui_rowstatusbar, ui_rowdeletefile, ui_rowsetting,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(ui_rowdeadpixel);
}

void hidden_all_menu(void)
{
    if(g_app.video.tilt == ON)
        lv_obj_remove_flag(ui_controll, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_lbltitle, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contpage1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contpage2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contpage3, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_contmenu2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowlrf, LV_STATE_USER_1, false);
    lv_obj_set_state(ui_rowimagemode, LV_STATE_USER_1, false);
    lv_obj_set_state(ui_rowbrightness, LV_STATE_USER_1, false);
    lv_obj_set_state(ui_rowcontrast, LV_STATE_USER_1, false);
    lv_obj_set_state(ui_rowsharpness, LV_STATE_USER_1, false);
    lv_obj_set_state(ui_menu1row4, LV_STATE_USER_1, false);
    lv_obj_add_flag(ui_contitem2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowreticle, LV_STATE_USER_1, false);
    dialog_close(ui_savereticle);
    dialog_close(ui_savechanges);
    dialog_close(s_dlg_zero);
    distance_editor_close();
    reticle_feature_clear_user_dirty();
    reticle_feature_close();
    lv_obj_add_flag(ui_page3item1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowstandby, LV_STATE_USER_1, false);
    lv_obj_add_flag(ui_page3item2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowcompasscalibration, LV_STATE_USER_1, false);
    lv_obj_add_flag(ui_dead_pixels_cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowdeadpixel, LV_STATE_USER_1, false);
    lv_obj_add_flag(ui_DialogPixelClear, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_bad_pixel_item3, LV_STATE_USER_1, false);
    lv_obj_add_flag(ui_contmenusetting, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowsetting, LV_STATE_USER_1, false);
    lv_obj_set_state(ui_rowitem1, LV_STATE_USER_1, false);
    lv_obj_add_flag(ui_DialogCompass, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowitem3, LV_STATE_USER_1, false);
    lv_obj_add_flag(ui_numInput, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowitem4, LV_STATE_USER_1, false);
    lv_obj_set_state(ui_comp_get_child(ui_num1, UI_COMP_NUM_PANELNUM), LV_STATE_USER_1, false);
    lv_obj_set_state(ui_comp_get_child(ui_num2, UI_COMP_NUM_PANELNUM), LV_STATE_USER_1, false);
    lv_obj_set_state(ui_comp_get_child(ui_num3, UI_COMP_NUM_PANELNUM), LV_STATE_USER_1, false);
    lv_obj_set_state(ui_comp_get_child(ui_num4, UI_COMP_NUM_PANELNUM), LV_STATE_USER_1, false);
    lv_obj_set_state(ui_comp_get_child(ui_num5, UI_COMP_NUM_PANELNUM), LV_STATE_USER_1, false);
    lv_obj_set_state(ui_comp_get_child(ui_num6, UI_COMP_NUM_PANELNUM), LV_STATE_USER_1, false);
    lv_obj_add_flag(ui_comp_get_child(ui_num1, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_num1, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_num2, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_num2, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_num3, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_num3, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_num4, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_num4, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_num5, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_num5, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_num6, UI_COMP_NUM_IMAGEUP), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_comp_get_child(ui_num6, UI_COMP_NUM_IMAGEDOWN), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_bad_pixel_cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_bad_pixel, LV_STATE_USER_1, false);
    lv_obj_set_state(ui_bad_pixel_item2, LV_STATE_USER_1, false);
    lv_obj_add_flag(ui_contdate, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_settingrow1, LV_STATE_USER_1, false);
    lv_obj_add_flag(ui_conttime, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_settingrow2, LV_STATE_USER_1, false);
    lv_obj_set_state(ui_settingrow3, LV_STATE_USER_1, false);
    lv_obj_add_flag(ui_DialogReset, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_settingrow4, LV_STATE_USER_1, false);
    lv_obj_add_flag(ui_DialogInfo, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_settingrow5, LV_STATE_USER_1, false);
    lv_obj_add_flag(ui_DialogFormattingSd, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_settingrow6, LV_STATE_USER_1, false);
    lv_obj_set_state(ui_rowitemyear, LV_STATE_USER_1, false);
    lv_obj_set_state(ui_rowitemmonth, LV_STATE_USER_1, false);
    lv_obj_set_state(ui_rowitemday, LV_STATE_USER_1, false);
    lv_obj_set_state(ui_rowitemhour, LV_STATE_USER_1, false);
    lv_obj_set_state(ui_rowitemmin, LV_STATE_USER_1, false);
    ui_focus_group_clear();
    UiIpcSendExitMenuRequest(global_parameters.sendMsgQueId);
}
