#include "app_state.h"


app_state_t g_app = {
    .mag_state = {
        .symbol = '+',
        .num1 = 0,
        .num2 = 0,
        .num3 = 0,
        .num4 = 0,
        .num5 = 0,
        .value = 0.0f,
    },
    .date_state = {0, 0, 0},
    .time_state = {0, 0, 0},
    .video = {
        .zoom = {.zoomValue = 1.0f, .precision = 0},
        .osd = {.all = 0, .datetime = 0},
        .dev_switch = {.wifi = 0, .bluetooth = 0},
        .freeze_on = 0,
        .rangefinder_on = 0,
        .mode = 0,
        .tilt = 1,
        .compass = 1,
    },
    .user_common = {
        .showDateTime = 1,
        .standbyTimeout = 300,
        .shutdownTimeout = 0,
        .distanceUnit = 0,
    },
    .user_media = {
        .burstCount = 0,
        .maxRecordDuration = 0,
        .recoilPreRecordSwitch = 0,
        .recoilPreRecordDuration = 0,
        .micSwitch = 0,
    },
    .ui = {
        .brightness = 4,
        .contrast = 4,
        .sharpness = 4,
        .standby_switch = 0,
        .standby_time_min = 5,
        .distance_unit_item = {
            .des = {"M", "Y"},
            .count = 2,
            .index = 0,
        },
        .language_item = {
            .des = {"Chinese", "English", "Russian"},
            .count = 3,
            .index = 0,
        },
    },
    .bad_point = {
        .threshold = 0,
        .bpnum = 0,
    },
};

void app_state_init_defaults(void)
{
}
