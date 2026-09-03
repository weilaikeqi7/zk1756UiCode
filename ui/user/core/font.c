//
// Created by jinxing on 2026/1/14.
//

#include "font.h"

#include <stdio.h>

lv_font_t * ui_font_WebnarItalic24;
lv_font_t * ui_font_WebnarItalic32;
lv_font_t * ui_font_WebnarMedium15;
lv_font_t * ui_font_WebnarMedium18;
lv_font_t * ui_font_WebnarRegular13;
lv_font_t * ui_font_WebnarRegular15;
lv_font_t * ui_font_WebnarRegular18;
lv_font_t * ui_font_WebnarRegular20;
lv_font_t * ui_font_WebnarRegular24;
lv_font_t * ui_font_WebnarSemiBold12;
lv_font_t * ui_font_WebnarSemiBold18;
lv_font_t * ui_font_WebnarSemiBold24;

void ui_font_init(void)
{
    char fonts_buff[1024] = {0};
    sprintf(fonts_buff, "%s%s", app_args.fonts_path, "Webnar-Italic.ttf");
    ui_font_WebnarItalic24 = lv_freetype_font_create(fonts_buff,
                                                     LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                                     24,
                                                     LV_FREETYPE_FONT_STYLE_NORMAL);
    ui_font_WebnarItalic32 = lv_freetype_font_create(fonts_buff,
                                                     LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                                     32,
                                                     LV_FREETYPE_FONT_STYLE_NORMAL);
    sprintf(fonts_buff, "%s%s", app_args.fonts_path, "Webnar-Medium.ttf");
    ui_font_WebnarMedium15 = lv_freetype_font_create(fonts_buff,
                                                     LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                                     15,
                                                     LV_FREETYPE_FONT_STYLE_NORMAL);
    ui_font_WebnarMedium18 = lv_freetype_font_create(fonts_buff,
                                                     LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                                     18,
                                                     LV_FREETYPE_FONT_STYLE_NORMAL);
    sprintf(fonts_buff, "%s%s", app_args.fonts_path, "Webnar-Regular.ttf");
    ui_font_WebnarRegular13 = lv_freetype_font_create(fonts_buff,
                                                      LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                                      13,
                                                      LV_FREETYPE_FONT_STYLE_NORMAL);
    ui_font_WebnarRegular15 = lv_freetype_font_create(fonts_buff,
                                                      LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                                      15,
                                                      LV_FREETYPE_FONT_STYLE_NORMAL);
    ui_font_WebnarRegular18 = lv_freetype_font_create(fonts_buff,
                                                      LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                                      18,
                                                      LV_FREETYPE_FONT_STYLE_NORMAL);
    ui_font_WebnarRegular20 = lv_freetype_font_create(fonts_buff,
                                                      LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                                      20,
                                                      LV_FREETYPE_FONT_STYLE_NORMAL);
    ui_font_WebnarRegular24 = lv_freetype_font_create(fonts_buff,
                                                      LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                                      24,
                                                      LV_FREETYPE_FONT_STYLE_NORMAL);
    sprintf(fonts_buff, "%s%s", app_args.fonts_path, "Webnar-SemiBold.ttf");
    ui_font_WebnarSemiBold12 = lv_freetype_font_create(fonts_buff,
                                                       LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                                       12,
                                                       LV_FREETYPE_FONT_STYLE_NORMAL);
    ui_font_WebnarSemiBold18 = lv_freetype_font_create(fonts_buff,
                                                       LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                                       18,
                                                       LV_FREETYPE_FONT_STYLE_NORMAL);
    ui_font_WebnarSemiBold24 = lv_freetype_font_create(fonts_buff,
                                                       LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                                       24,
                                                       LV_FREETYPE_FONT_STYLE_NORMAL);
}

void ui_font_deinit(void)
{
    lv_freetype_font_delete(ui_font_WebnarItalic24);
    lv_freetype_font_delete(ui_font_WebnarItalic32);
    lv_freetype_font_delete(ui_font_WebnarMedium15);
    lv_freetype_font_delete(ui_font_WebnarMedium18);
    lv_freetype_font_delete(ui_font_WebnarRegular13);
    lv_freetype_font_delete(ui_font_WebnarRegular15);
    lv_freetype_font_delete(ui_font_WebnarRegular18);
    lv_freetype_font_delete(ui_font_WebnarRegular20);
    lv_freetype_font_delete(ui_font_WebnarRegular24);
    lv_freetype_font_delete(ui_font_WebnarSemiBold12);
    lv_freetype_font_delete(ui_font_WebnarSemiBold18);
    lv_freetype_font_delete(ui_font_WebnarSemiBold24);
}
