#include "lvgl/lvgl.h"
#include "lvgl/src/drivers/sdl/lv_sdl_mouse.h"
#include "lvgl/src/drivers/sdl/lv_sdl_window.h"
#include "ui/ui.h"
#include "ui/user/core/app_state.h"

#include <stdint.h>

#define SIMULATOR_WIDTH  1280
#define SIMULATOR_HEIGHT 1024

GlobalParameters global_parameters = {
    .sendMsgQueId = -1,
    .recvMsgQueId = -1,
    .ipc_ready = 1,
    .g_quit = 0,
};

AppArgs app_args = {
    .language_index = 0,
    .self_pass_index = 0,
    .sendKey = 2027,
    .recvKey = 2026,
    .set_w_res = SIMULATOR_WIDTH,
    .set_h_res = SIMULATOR_HEIGHT,
    .fonts_path = UI_SIMULATOR_FONT_PATH,
};

typedef struct {
    const char * label;
    uint8_t key_index;
} SimulatorKey;

static const SimulatorKey simulator_keys[] = {
    {"UP", 0U},
    {"ENTER", 1U},
    {"DOWN", 2U},
    {"ESC", 3U},
};

static void simulator_key_clicked(lv_event_t * event)
{
    const SimulatorKey * key = lv_event_get_user_data(event);
    if(key == NULL) return;

    /* Linux creates this focus list after the menu notification arrives. The
     * standalone simulator creates the equivalent initial menu locally. */
    if(keypad_group != NULL && lv_group_get_obj_count(keypad_group) == 0U) {
        show_menu_page1();
    }

    lv_port_indev_simulate_key(key->key_index);
}

static void create_simulator_key_buttons(void)
{
    lv_obj_t * panel = lv_obj_create(lv_layer_top());
    lv_obj_set_size(panel, LV_SIZE_CONTENT, 58);
    lv_obj_align(panel, LV_ALIGN_BOTTOM_MID, 0, -8);
    lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_all(panel, 6, LV_PART_MAIN);
    lv_obj_set_style_pad_column(panel, 6, LV_PART_MAIN);
    lv_obj_set_style_radius(panel, 6, LV_PART_MAIN);
    lv_obj_set_style_bg_color(panel, lv_color_hex(0x24272B), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(panel, LV_OPA_90, LV_PART_MAIN);
    lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);

    for(uint32_t i = 0; i < sizeof(simulator_keys) / sizeof(simulator_keys[0]); ++i) {
        lv_obj_t * button = lv_button_create(panel);
        lv_obj_set_size(button, i == 1U ? 92 : 72, 42);
        lv_obj_set_style_radius(button, 4, LV_PART_MAIN);
        lv_obj_add_event_cb(button, simulator_key_clicked, LV_EVENT_PRESSED, (void *)&simulator_keys[i]);

        lv_obj_t * label = lv_label_create(button);
        lv_label_set_text(label, simulator_keys[i].label);
        lv_obj_center(label);
    }
}

int main(void)
{
    app_state_init_defaults();
    lv_init();

    lv_display_t * display = lv_sdl_window_create(app_args.set_w_res, app_args.set_h_res);
    if(display == NULL) return 1;

    lv_sdl_window_set_title(display, "ZK1756 UI Simulator");
    lv_sdl_mouse_create();

    ui_init();
    create_simulator_key_buttons();

    for(;;) {
        uint32_t delay_ms = lv_timer_handler();
        if(delay_ms < 1U) delay_ms = 1U;
        if(delay_ms > 20U) delay_ms = 20U;
        lv_delay_ms(delay_ms);
    }
}
