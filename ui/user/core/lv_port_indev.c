/**
 * @file lv_port_indev_template.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev.h"

#include <string.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void keypad_init(void);

static void keypad_read(lv_indev_t * indev, lv_indev_data_t * data);

static uint32_t keypad_get_key(void);

/**********************
 *  STATIC VARIABLES
 **********************/

lv_indev_t * indev_keypad;
static uint32_t g_last_key;

/**********************
 *      MACROS
 **********************/
uint8_t g_my_keypad_btn_points[4];
lv_group_t * keypad_group;
/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    if(indev_keypad != NULL || keypad_group != NULL) {
        lv_port_indev_deinit();
    }
    memset(g_my_keypad_btn_points, 0, sizeof(g_my_keypad_btn_points));
    g_last_key = 0;

    /*------------------
     * Keypad
     * -----------------*/

    /*Initialize your keypad or keyboard if you have*/
    keypad_init();

    keypad_group = lv_group_create();
    /*Register a keypad input device*/
    indev_keypad = lv_indev_create();
    lv_indev_set_type(indev_keypad, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev_keypad, keypad_read);
    lv_indev_set_group(indev_keypad, keypad_group);
    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     *add objects to the group with `lv_group_add_obj(group, obj)`
     *and assign this input device to group to navigate in it:
     *`lv_indev_set_group(indev_keypad, group);`*/
}

void lv_port_indev_deinit(void)
{
    if(indev_keypad != NULL) {
        lv_indev_set_group(indev_keypad, NULL);
        lv_indev_delete(indev_keypad);
        indev_keypad = NULL;
    }

    if(keypad_group != NULL) {
        lv_group_delete(keypad_group);
        keypad_group = NULL;
    }

    memset(g_my_keypad_btn_points, 0, sizeof(g_my_keypad_btn_points));
    g_last_key = 0;
}

void lv_port_indev_simulate_key(uint8_t key_index)
{
    if(key_index < 4U) {
        g_my_keypad_btn_points[key_index] = 1U;
        if(indev_keypad != NULL) {
            lv_timer_t * read_timer = lv_indev_get_read_timer(indev_keypad);
            if(read_timer != NULL) lv_timer_ready(read_timer);
        }
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Keypad
 * -----------------*/

/*Initialize your keypad*/
static void keypad_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the mouse*/
static void keypad_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
    (void)indev_drv;

    /*Get whether the a key is pressed and save the pressed key*/
    uint32_t act_key = keypad_get_key();
    if(act_key != 0) {
        data->state = LV_INDEV_STATE_PRESSED;

        /*Translate the keys to LVGL control characters according to your key definitions*/
        switch(act_key) {
        case 1:
            act_key = LV_KEY_UP;
            break;
        case 2:
            act_key = LV_KEY_ENTER;
            break;
        case 3:
            act_key = LV_KEY_DOWN;
            break;
        case 4:
            act_key = LV_KEY_ESC;
            break;
        default:
            break;
        }

        g_last_key = act_key;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }

    data->key = g_last_key;
}

/*Get the currently being pressed key.  0 if no key is pressed*/
static uint32_t keypad_get_key(void)
{
    /*Your code comes here*/
    for(uint8_t i = 0; i < 4; i++) {
        if(g_my_keypad_btn_points[i]) {
            g_my_keypad_btn_points[i] = 0;
            return i + 1;
        }
    }
    return 0;
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
