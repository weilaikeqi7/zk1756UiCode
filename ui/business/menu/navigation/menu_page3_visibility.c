//
// Created by jinxing on 2026/1/5.
//

#include "menu_visibility.h"
#include "ui_focus_manager.h"

void show_menu_page3_item2_item2(void)
{
    lv_label_set_text_fmt(ui_comp_get_child(ui_num1, UI_COMP_NUM_PANELNUM_LABEL), "%c", magnetic.symbol);
    lv_label_set_text_fmt(ui_comp_get_child(ui_num2, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num1);
    lv_label_set_text_fmt(ui_comp_get_child(ui_num3, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num2);
    lv_label_set_text_fmt(ui_comp_get_child(ui_num4, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num3);
    lv_label_set_text_fmt(ui_comp_get_child(ui_num5, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num4);
    lv_label_set_text_fmt(ui_comp_get_child(ui_num6, UI_COMP_NUM_PANELNUM_LABEL), "%d", magnetic.num5);

    lv_obj_remove_flag(ui_numInput, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {
        ui_comp_get_child(ui_num1, UI_COMP_NUM_PANELNUM),
        ui_comp_get_child(ui_num2, UI_COMP_NUM_PANELNUM),
        ui_comp_get_child(ui_num3, UI_COMP_NUM_PANELNUM),
        ui_comp_get_child(ui_num4, UI_COMP_NUM_PANELNUM),
        ui_comp_get_child(ui_num5, UI_COMP_NUM_PANELNUM),
        ui_comp_get_child(ui_num6, UI_COMP_NUM_PANELNUM),
        ui_rowitemOK,
        ui_rowitemCANCEL,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void hidden_menu_page3_item2_item2(void)
{
    lv_obj_add_flag(ui_numInput, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowitem4, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {ui_rowitem3, ui_rowitem4, ui_rowitem5};
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(ui_rowitem4);
}

void show_menu_page3_item6(void)
{
    lv_obj_remove_flag(ui_contmenusetting, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {
        ui_settingrow1, ui_settingrow2, ui_settingrow3,
        ui_settingrow4, ui_settingrow6, ui_settingrow5,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void hidden_menu_page3_item6(void)
{
    lv_obj_add_flag(ui_contmenusetting, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowsetting, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {
        ui_rowstandby, ui_rowcompasscalibration, ui_rowdeadpixel,
        ui_rowstatusbar, ui_rowdeletefile, ui_rowsetting,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(ui_rowsetting);
}

void show_menu_page3_item6_item1(void)
{
    lv_obj_remove_flag(ui_contdate, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {
        ui_rowitemyear, ui_rowitemmonth, ui_rowitemday, ui_rowitemdateback,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    date.year = (ROE_S16)datatime.year;
    date.month = (ROE_S8)datatime.month;
    date.day = (ROE_S8)datatime.day;
    tim.hour = (ROE_S8)datatime.hour;
    tim.min = (ROE_S8)datatime.min;
    tim.sec = (ROE_S8)0;
    lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemyear, UI_COMP_ROWITEM1_LABEL), "%d", date.year);
    lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemmonth, UI_COMP_ROWITEM1_LABEL), "%d", date.month);
    lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemday, UI_COMP_ROWITEM1_LABEL), "%d", date.day);
}

void hidden_menu_page3_item6_item1(void)
{
    lv_obj_add_flag(ui_contdate, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_settingrow1, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {
        ui_settingrow1, ui_settingrow2, ui_settingrow3,
        ui_settingrow4, ui_settingrow6, ui_settingrow5,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void show_menu_page3_item6_item2(void)
{
    lv_obj_remove_flag(ui_conttime, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {ui_rowitemhour, ui_rowitemmin, ui_rowitemtimeback};
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    date.year = (ROE_S16)datatime.year;
    date.month = (ROE_S8)datatime.month;
    date.day = (ROE_S8)datatime.day;
    tim.hour = (ROE_S8)datatime.hour;
    tim.min = (ROE_S8)datatime.min;
    tim.sec = (ROE_S8)0;
    lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemhour, UI_COMP_ROWITEM1_LABEL), "%02d", tim.hour);
    lv_label_set_text_fmt(ui_comp_get_child(ui_rowitemmin, UI_COMP_ROWITEM1_LABEL), "%02d", tim.min);
}

void hidden_menu_page3_item6_item2(void)
{
    lv_obj_add_flag(ui_conttime, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_settingrow2, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {
        ui_settingrow1, ui_settingrow2, ui_settingrow3,
        ui_settingrow4, ui_settingrow6, ui_settingrow5,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(ui_settingrow2);
}

void show_menu_page3_item6_item4(void)
{
    lv_obj_remove_flag(ui_DialogReset, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {ui_resetOK, ui_resetCANCEL};
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(ui_resetCANCEL);
}

void hidden_menu_page3_item6_item4(void)
{
    lv_obj_add_flag(ui_DialogReset, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_settingrow4, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {
        ui_settingrow1, ui_settingrow2, ui_settingrow3,
        ui_settingrow4, ui_settingrow6, ui_settingrow5,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(ui_settingrow4);
}

void show_menu_page3_item6_item5(void)
{
    lv_obj_remove_flag(ui_DialogInfo, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {ui_infoOK};
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void hidden_menu_page3_item6_item5(void)
{
    lv_obj_add_flag(ui_DialogInfo, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_settingrow5, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {
        ui_settingrow1, ui_settingrow2, ui_settingrow3,
        ui_settingrow4, ui_settingrow6, ui_settingrow5,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(ui_settingrow5);
}

void show_menu_page3_item6_item6(void)
{
    lv_obj_remove_flag(ui_DialogFormattingSd, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {
        ui_comp_get_child(ui_DialogFormattingSd, UI_COMP_DIALOGEG_DIALOGOK),
        ui_comp_get_child(ui_DialogFormattingSd, UI_COMP_DIALOGEG_DIALOGCANCEL),
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(objects[1]);
}

void hidden_menu_page3_item6_item6(void)
{
    lv_obj_add_flag(ui_DialogFormattingSd, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_settingrow6, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {
        ui_settingrow1, ui_settingrow2, ui_settingrow3,
        ui_settingrow4, ui_settingrow6, ui_settingrow5,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(ui_settingrow6);
}

void show_menu_page3_item3_item1(void)
{
    lv_obj_remove_flag(ui_bad_pixel_cont, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {
        ui_bad_pixel_item2, ui_bad_pixel_item3, ui_bad_pixel_item4,
        ui_bad_pixel_item5, ui_bad_pixel_item6,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    lv_label_set_text_fmt(ui_comp_get_child(ui_bad_pixel_item2, UI_COMP_MCITEM_MCP2P1L2),
                          "%u",
                          g_app.bad_point.threshold);
    lv_label_set_text_fmt(ui_comp_get_child(ui_bad_pixel_item1, UI_COMP_MCITEM_MCP2P1L2), "%u", g_app.bad_point.bpnum);
}

void hidden_menu_page3_item3_item1(void)
{
    lv_obj_add_flag(ui_bad_pixel_cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowdeadpixel, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {
        ui_rowstandby, ui_rowcompasscalibration, ui_rowdeadpixel,
        ui_rowstatusbar, ui_rowdeletefile, ui_rowsetting,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(ui_rowdeadpixel);
}

void show_menu_page3_item2_item1(void)
{
    lv_obj_remove_flag(ui_DialogCompass, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {
        ui_comp_get_child(ui_DialogCompass, UI_COMP_DIALOGEG_DIALOGOK),
        ui_comp_get_child(ui_DialogCompass, UI_COMP_DIALOGEG_DIALOGCANCEL),
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void hidden_menu_page3_item2_item1(void)
{
    lv_obj_add_flag(ui_DialogCompass, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_rowitem3, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {ui_rowitem3, ui_rowitem4, ui_rowitem5};
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(ui_rowitem3);
}

void show_menu_page3_item3_item1_item3(void)
{
    lv_obj_remove_flag(ui_DialogPixelClear, LV_OBJ_FLAG_HIDDEN);

    lv_obj_t * objects[] = {
        ui_comp_get_child(ui_DialogPixelClear, UI_COMP_DIALOGEG_DIALOGOK),
        ui_comp_get_child(ui_DialogPixelClear, UI_COMP_DIALOGEG_DIALOGCANCEL),
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
}

void hidden_menu_page3_item3_item1_item3(void)
{
    lv_obj_add_flag(ui_DialogPixelClear, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_state(ui_bad_pixel_item3, LV_STATE_USER_1, false);

    lv_obj_t * objects[] = {
        ui_bad_pixel_item2, ui_bad_pixel_item3, ui_bad_pixel_item4,
        ui_bad_pixel_item5, ui_bad_pixel_item6,
    };
    ui_focus_group_set(objects, sizeof(objects) / sizeof(objects[0]));
    ui_focus_group_focus(ui_bad_pixel_item3);
}
