//
// Created by jinxing on 2026/1/8.
//

#ifndef ZKSL_75_6LC_EVENT_HANDLE_H
#define ZKSL_75_6LC_EVENT_HANDLE_H

#include "ui/foundation/types.h"
#include "ui.h"
#include "ui/foundation/roeTypes.h"
#include "ui/foundation/app_state.h"


#pragma pack(push, 1)

typedef enum { TARGET_UNIT_METER = 0, TARGET_UNIT_YARD } target_unit_t;

typedef app_item_t Item;
typedef app_magnetic_t Magnetic;
typedef app_date_t Date;
typedef app_time_t Time;
#pragma pack(pop)

void add_event_of_menu(void);

int is_leap_year(int y);
int days_in_month(int y, int m);

void switch_distance_label_unit(lv_obj_t * label, target_unit_t target_unit);

void ui_apply_user_common_config(void);
void ui_apply_user_media_config(void);

void usercfg_set_show_datetime(ROE_U8 show);
void usercfg_set_shutdown_timeout_sec(ROE_U16 sec);
void usermedia_set_burst_count(ROE_U8 count);
void usermedia_set_max_record_duration_sec(ROE_U16 sec);
void usermedia_set_recoil_pre_record_duration_sec(ROE_U16 sec);

#define DistanceUnit         (g_app.ui.distance_unit_item)
#define Brightness           (g_app.ui.brightness)
#define Contrast             (g_app.ui.contrast)
#define Sharpness            (g_app.ui.sharpness)
#define g_standby_switch     (g_app.ui.standby_switch)
#define StandbyTime          (g_app.ui.standby_time_min)

#define magnetic             (g_app.mag_state)
#define date                 (g_app.date_state)
#define tim                  (g_app.time_state)
#define Language             (g_app.ui.language_item)

#define g_rangefinder_switch (g_app.video.rangefinder_on)
#define g_freeze_switch      (g_app.video.freeze_on)
#define g_zoom               (g_app.video.zoom)
#define g_osd                (g_app.video.osd)
#define g_device_switch      (g_app.video.dev_switch)
#define g_mode               (g_app.video.mode)
#define g_tilt               (g_app.video.tilt)
#define g_compass            (g_app.video.compass)

#define userCommonConfig     (g_app.user_common)
#define userMediaConfig      (g_app.user_media)

#endif //ZKSL_75_6LC_EVENT_HANDLE_H
