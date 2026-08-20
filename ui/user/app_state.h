#ifndef ZKSL_75_6LC_APP_STATE_H
#define ZKSL_75_6LC_APP_STATE_H

#include "user/roeTypes.h"
#include "ipcMsgQue4UiTypeCommon.h"

#pragma pack(push, 1)

typedef struct {
    const char * des[10];
    int count;
    int index;
} app_item_t;

typedef struct {
    int symbol;
    int num1;
    int num2;
    int num3;
    int num4;
    int num5;
    float value;
} app_magnetic_t;

typedef struct {
    ROE_S16 year;
    ROE_S8 month;
    ROE_S8 day;
} app_date_t;

typedef struct {
    ROE_S8 hour;
    ROE_S8 min;
    ROE_S8 sec;
} app_time_t;

typedef struct {
    ROE_FLOAT zoomValue;
    ROE_U8 precision;
} app_zoom_t;

typedef struct {
    ROE_S8 all;
    ROE_S8 datetime;
} app_osd_t;

typedef struct {
    ROE_S8 wifi;
    ROE_S8 bluetooth;
} app_device_switch_t;

typedef struct {
    ROE_U8 showDateTime;
    ROE_U16 standbyTimeout;
    ROE_U16 shutdownTimeout;
    ROE_U8 distanceUnit;
} app_user_common_config_t;

typedef struct {
    ROE_U8 burstCount;
    ROE_U16 maxRecordDuration;
    ROE_U8 recoilPreRecordSwitch;
    ROE_U16 recoilPreRecordDuration;
    ROE_U8 micSwitch;
} app_user_media_config_t;

typedef struct {
    app_zoom_t zoom;
    app_osd_t osd;
    app_device_switch_t dev_switch;
    ROE_U8 freeze_on;
    ROE_U8 rangefinder_on;
    ROE_U8 mode;
    ROE_U8 tilt;
    ROE_U8 compass;
} app_video_state_t;

typedef struct {
    int brightness;
    int contrast;
    int sharpness;
    ROE_U8 standby_switch;
    int standby_time_min;
    app_item_t distance_unit_item;
    app_item_t language_item;
} app_ui_cache_t;

typedef struct {
    ROE_U32 bpnum;
    ROE_U32 threshold_min;
    ROE_U32 threshold;
    ROE_U32 threshold_max;
} app_badpoint_t;

typedef struct {
    app_magnetic_t mag_state;
    app_date_t date_state;
    app_time_t time_state;
    app_video_state_t video;
    app_user_common_config_t user_common;
    app_user_media_config_t user_media;
    app_ui_cache_t ui;
    app_badpoint_t bad_point;
    ROE_U8 reticle_state[UI_MAX_DIVIDING_PLATES_NUM];
    ROE_U8 playPageFlag;
} app_state_t;

#pragma pack(pop)

extern app_state_t g_app;

void app_state_init_defaults(void);
#endif
