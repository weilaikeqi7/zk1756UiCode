//
// Created by jinxing on 2026/1/14.
//

#include "font.h"

#include "lvgl/lvgl.h"

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

static int g_fonts_initialized;

static lv_font_t * create_font(const char * path, const char * file_name, uint16_t size)
{
    char font_path[1024];

    if(path == NULL || file_name == NULL) {
        LV_LOG_WARN("[FONT][DROP] invalid font path");
        return NULL;
    }

    int written = snprintf(font_path, sizeof(font_path), "%s%s", path, file_name);
    if(written < 0 || (size_t)written >= sizeof(font_path)) {
        LV_LOG_ERROR("[FONT][DROP] font path is too long: %s%s", path, file_name);
        return NULL;
    }

    lv_font_t * font = lv_freetype_font_create(font_path,
                                                LV_FREETYPE_FONT_RENDER_MODE_BITMAP,
                                                size,
                                                LV_FREETYPE_FONT_STYLE_NORMAL);
    if(font == NULL) {
        LV_LOG_WARN("[FONT][DROP] failed to load: %s", font_path);
    }
    return font;
}

void ui_font_init(void)
{
    if(g_fonts_initialized) return;

    const char * path = app_args.fonts_path;
    ui_font_WebnarItalic24 = create_font(path, "Webnar-Italic.ttf", 24);
    ui_font_WebnarItalic32 = create_font(path, "Webnar-Italic.ttf", 32);
    ui_font_WebnarMedium15 = create_font(path, "Webnar-Medium.ttf", 15);
    ui_font_WebnarMedium18 = create_font(path, "Webnar-Medium.ttf", 18);
    ui_font_WebnarRegular13 = create_font(path, "Webnar-Regular.ttf", 13);
    ui_font_WebnarRegular15 = create_font(path, "Webnar-Regular.ttf", 15);
    ui_font_WebnarRegular18 = create_font(path, "Webnar-Regular.ttf", 18);
    ui_font_WebnarRegular20 = create_font(path, "Webnar-Regular.ttf", 20);
    ui_font_WebnarRegular24 = create_font(path, "Webnar-Regular.ttf", 24);
    ui_font_WebnarSemiBold12 = create_font(path, "Webnar-SemiBold.ttf", 12);
    ui_font_WebnarSemiBold18 = create_font(path, "Webnar-SemiBold.ttf", 18);
    ui_font_WebnarSemiBold24 = create_font(path, "Webnar-SemiBold.ttf", 24);
    g_fonts_initialized = 1;
}

void ui_font_deinit(void)
{
#define DELETE_FONT(font) \
    do { \
        if((font) != NULL) { \
            lv_freetype_font_delete(font); \
            (font) = NULL; \
        } \
    } while(0)

    DELETE_FONT(ui_font_WebnarItalic24);
    DELETE_FONT(ui_font_WebnarItalic32);
    DELETE_FONT(ui_font_WebnarMedium15);
    DELETE_FONT(ui_font_WebnarMedium18);
    DELETE_FONT(ui_font_WebnarRegular13);
    DELETE_FONT(ui_font_WebnarRegular15);
    DELETE_FONT(ui_font_WebnarRegular18);
    DELETE_FONT(ui_font_WebnarRegular20);
    DELETE_FONT(ui_font_WebnarRegular24);
    DELETE_FONT(ui_font_WebnarSemiBold12);
    DELETE_FONT(ui_font_WebnarSemiBold18);
    DELETE_FONT(ui_font_WebnarSemiBold24);

#undef DELETE_FONT
    g_fonts_initialized = 0;
}
