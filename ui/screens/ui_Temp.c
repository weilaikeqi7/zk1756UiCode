//
// Created by Administrator on 2026/4/20.
//

#include "../ui.h"

lv_obj_t * ui_Temp = NULL;
lv_obj_t * ui_tempcontdistance = NULL;
lv_obj_t * ui_tempdistancelabel = NULL;

void ui_Temp_screen_init(void)
{
    ui_Temp = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_Temp, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    ui_object_set_themeable_style_property(ui_Temp,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_BG_COLOR,
                                           _ui_theme_color_transparent);
    ui_object_set_themeable_style_property(ui_Temp,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_transparent);

    ui_tempcontdistance = ui_paneleg_create(ui_Temp);
    lv_obj_set_width(ui_tempcontdistance, 120);
    lv_obj_set_height(ui_tempcontdistance, 40);
    lv_obj_set_x(ui_tempcontdistance, -20);
    lv_obj_set_y(ui_tempcontdistance, 40);
    lv_obj_set_align(ui_tempcontdistance, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_tempcontdistance, LV_OBJ_FLAG_HIDDEN); /// Flags

    ui_tempdistancelabel = lv_label_create(ui_tempcontdistance);
    lv_obj_set_width(ui_tempdistancelabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_height(ui_tempdistancelabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_tempdistancelabel, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_tempdistancelabel, "----M");
    ui_object_set_themeable_style_property(ui_tempdistancelabel,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Text);
    ui_object_set_themeable_style_property(ui_tempdistancelabel,
                                           LV_PART_MAIN | LV_STATE_DEFAULT,
                                           LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Text);
    lv_obj_set_style_text_font(ui_tempdistancelabel, ui_font_WebnarRegular24, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_move_to_index(ui_tempdistancelabel, 0);
}

void ui_Temp_screen_destroy(void)
{
    if(ui_Temp)
        lv_obj_del(ui_Temp);

    // NULL screen variables
    ui_Temp = NULL;
    ui_tempcontdistance = NULL;
    ui_tempdistancelabel = NULL;
}