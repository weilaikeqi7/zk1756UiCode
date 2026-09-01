#include "../ui.h"
#include <stdio.h>

lv_obj_t * ui_self = NULL;
lv_obj_t * ui_self_count = NULL;
lv_obj_t * ui_label_title = NULL;
lv_obj_t * ui_self_item_cont = NULL;
lv_obj_t * ui_self_item[SELF_ITEM_NUM];
lv_obj_t * ui_self_item_label[SELF_ITEM_NUM];
lv_obj_t * ui_self_button_label = NULL;
popup_desc_t g_popup_self;

static char * selfImgItem[] = {"selfItem1.png",
                               "selfItem2.png",
                               "selfItem3.png",
                               "selfItem4.png",
                               "selfItem5.png",
                               "selfItem6.png",
                               "selfItem7.png"};

static char * selfItem[] = {
    "Visible Light", "Infrared", "Memory Card", "WIFI", "Range Finder", "Electronic Compass", "Satellite Positioning"};

char * self_info[] = {"Self-check in progress", "Normal", "Abnormal"};

void ui_self_screen_init(void)
{
    ui_self = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(ui_self, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_self, LV_OPA_0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_self_count = ui_paneleg_create(ui_self);
    lv_obj_set_align(ui_self_count, LV_ALIGN_CENTER);
    lv_obj_set_width(ui_self_count, 650);
    lv_obj_set_height(ui_self_count, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(ui_self_count, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_self_count, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_radius(ui_self_count, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_self_count, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_self_count, lv_color_hex(0x2E2D2F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_self_count, LV_OPA_60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_self_count, lv_color_hex(0x37F6FA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_self_count, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_self_count, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_self_count, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_label_title = lv_label_create(ui_self_count);
    lv_obj_set_width(ui_label_title, lv_pct(100));
    lv_obj_set_height(ui_label_title, 40);
    lv_obj_set_style_text_color(ui_label_title, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_title, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label_title, ui_font_WebnarMedium15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_label_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_label_title, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_label_title, "Information");

    ui_self_item_cont = ui_paneleg_create(ui_self_count);
    lv_obj_set_width(ui_self_item_cont, lv_pct(100));
    lv_obj_set_flex_flow(ui_self_item_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_self_item_cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_all(ui_self_item_cont, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_self_item_cont, 24, LV_PART_MAIN | LV_STATE_DEFAULT);

    for(int i = 0; i < SELF_ITEM_NUM; i++) {
        ui_self_item[i] = ui_paneleg_create(ui_self_item_cont);
        lv_obj_set_width(ui_self_item[i], lv_pct(100));
        lv_obj_set_height(ui_self_item[i], 20);

        char buf[256] = {0};
        sprintf(buf, "%s%s", IMAGES_PATH, selfImgItem[i]);
        lv_obj_t * ui_self_image = lv_image_create(ui_self_item[i]);
        lv_image_set_src(ui_self_image, buf);
        lv_obj_set_width(ui_self_image, LV_SIZE_CONTENT); /// 1
        lv_obj_set_height(ui_self_image, LV_SIZE_CONTENT); /// 1
        lv_obj_set_align(ui_self_image, LV_ALIGN_LEFT_MID);

        lv_obj_t * ui_self_label = lv_label_create(ui_self_item[i]);
        lv_obj_set_width(ui_self_label, LV_SIZE_CONTENT); /// 1
        lv_obj_set_height(ui_self_label, lv_pct(100));
        lv_obj_set_align(ui_self_label, LV_ALIGN_LEFT_MID);
        lv_obj_set_x(ui_self_label, 28);
        lv_obj_set_style_text_color(ui_self_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_self_label, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_self_label, ui_font_WebnarMedium15, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text(ui_self_label, selfItem[i]);

        ui_self_item_label[i] = lv_label_create(ui_self_item[i]);
        lv_obj_set_width(ui_self_item_label[i], LV_SIZE_CONTENT); /// 1
        lv_obj_set_height(ui_self_item_label[i], lv_pct(100));
        lv_obj_set_align(ui_self_item_label[i], LV_ALIGN_RIGHT_MID);
        lv_obj_set_style_text_color(ui_self_item_label[i], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_self_item_label[i], LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_self_item_label[i], ui_font_WebnarMedium15, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text(ui_self_item_label[i], self_info[0]);
    }

    ui_self_button_label = lv_label_create(ui_self_count);
    lv_obj_set_width(ui_self_button_label, lv_pct(100));
    lv_obj_set_height(ui_self_button_label, 40);
    lv_obj_set_style_text_color(ui_self_button_label, lv_color_hex(0x37F6FA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_self_button_label, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_self_button_label, ui_font_WebnarMedium15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_self_button_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_self_button_label, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ui_self_button_label, "Confirm");
    lv_obj_add_flag(ui_self_button_label, LV_OBJ_FLAG_HIDDEN);

    lv_group_t * group = lv_group_create();
    lv_group_add_obj(group, ui_self_button_label);
    g_popup_self.root = ui_self_button_label;
    g_popup_self.group = group;
    g_popup_self.default_focus = ui_self_button_label;
}

void ui_self_screen_destroy(void)
{
    if(ui_self) {
        lv_obj_del(ui_self);
    }
    ui_self = NULL;
    ui_self_count = NULL;
    ui_label_title = NULL;
    ui_self_item_cont = NULL;
    for(int i = 0; i < SELF_ITEM_NUM; i++) {
        ui_self_item[i] = NULL;
        ui_self_item_label[i] = NULL;
    }
    ui_self_button_label = NULL;
}