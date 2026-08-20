#ifndef ZKSL_75_6LC_MAINPAGE_EVENT_INTERNAL_H
#define ZKSL_75_6LC_MAINPAGE_EVENT_INTERNAL_H

#include "mainpage_event_handle.h"

void ui_apply_user_common_config(void);

void ui_apply_user_media_config(void);

void usercfg_set_show_datetime(ROE_U8 show);

void usercfg_set_shutdown_timeout_sec(ROE_U16 sec);

void usermedia_set_burst_count(ROE_U8 count);

void usermedia_set_max_record_duration_sec(ROE_U16 sec);

void usermedia_set_recoil_pre_record_duration_sec(ROE_U16 sec);

void switch_distance_label_unit(lv_obj_t * label, target_unit_t target_unit);

void restore_declination(void);

void ui_event_rowlrf(lv_event_t * e);

void ui_event_rowreticle(lv_event_t * e);

void ui_event_rowballistic(lv_event_t * e);

void ui_event_rowstandby(lv_event_t * e);

void ui_event_rowcompasscalibration(lv_event_t * e);

void ui_event_rowdeadpixel(lv_event_t * e);

void ui_event_rowstatusbar(lv_event_t * e);

void ui_event_rowdeletefile(lv_event_t * e);

void ui_event_rowsetting(lv_event_t * e);

void ui_event_menu1row4(lv_event_t * e);

void ui_event_rowmic(lv_event_t * e);

void ui_event_rowrav(lv_event_t * e);

void ui_event_rowswitch1(lv_event_t * e);

void ui_event_rowitem1(lv_event_t * e);

void ui_event_rowimagemode(lv_event_t * e);

void ui_event_rowbrightness(lv_event_t * e);

void ui_event_rowcontrast(lv_event_t * e);

void ui_event_rowsharpness(lv_event_t * e);

void ui_event_rowexpansion(lv_event_t * e);

void ui_event_rowpip(lv_event_t * e);

void ui_event_menu1row1(lv_event_t * e);

void ui_event_menu1row2(lv_event_t * e);

void ui_event_menu1row3(lv_event_t * e);

void ui_event_menu1row5(lv_event_t * e);

void ui_event_rowitem21(lv_event_t * e);

void ui_event_rowitem22(lv_event_t * e);

void ui_event_rowitem23(lv_event_t * e);

void ui_event_rowitem24(lv_event_t * e);

void ui_event_rowitem25(lv_event_t * e);

void ui_event_rowitem26(lv_event_t * e);

void ui_event_rowitem27(lv_event_t * e);

void ui_event_rowitem28(lv_event_t * e);

void ui_event_rowitem29(lv_event_t * e);

void ui_event_rowwifi(lv_event_t * e);

void ui_event_rowtilt(lv_event_t * e);

void ui_event_rowcompass(lv_event_t * e);

void ui_event_rowitem2(lv_event_t * e);

void ui_event_rowitem3(lv_event_t * e);

void ui_event_rowitem4(lv_event_t * e);

void ui_event_rowitem5(lv_event_t * e);

void ui_event_num1(lv_event_t * e);

void ui_event_num2(lv_event_t * e);

void ui_event_num3(lv_event_t * e);

void ui_event_num4(lv_event_t * e);

void ui_event_num5(lv_event_t * e);

void ui_event_num6(lv_event_t * e);

void ui_event_rowitemOK(lv_event_t * e);

void ui_event_rowitemCANCEL(lv_event_t * e);

void ui_event_settingrow1(lv_event_t * e);

void ui_event_settingrow2(lv_event_t * e);

void ui_event_settingrow3(lv_event_t * e);

void ui_event_settingrow4(lv_event_t * e);

void ui_event_settingrow5(lv_event_t * e);

void ui_event_settingrow6(lv_event_t * e);

int is_leap_year(int y);

int days_in_month(int y, int m);

void ui_event_rowitemyear(lv_event_t * e);

void ui_event_rowitemmonth(lv_event_t * e);

void ui_event_rowitemday(lv_event_t * e);

void ui_event_rowitemback(lv_event_t * e);

void ui_event_rowitemhour(lv_event_t * e);

void ui_event_rowitemmin(lv_event_t * e);

void ui_event_rowitemtimeback(lv_event_t * e);

void ui_event_resetOK(lv_event_t * e);

void ui_event_resetCANCEL(lv_event_t * e);

void ui_event_infoOK(lv_event_t * e);

void ui_event_DialogFormattingSdOk(lv_event_t * e);

void ui_event_DialogFormattingSdCancel(lv_event_t * e);

void ui_event_powerOffOK(lv_event_t * e);

void ui_event_powerOffCancel(lv_event_t * e);

void ui_event_bad_pixel(lv_event_t * e);

void ui_event_pixel_return(lv_event_t * e);

void ui_event_pixel_item2(lv_event_t * e);

void ui_event_pixel_item3(lv_event_t * e);

void ui_event_pixel_item4(lv_event_t * e);

void ui_event_pixel_item5(lv_event_t * e);

void ui_event_pixel_item6(lv_event_t * e);

void ui_event_CompassStart(lv_event_t * e);

void ui_event_CompassCancel(lv_event_t * e);

void ui_event_DialogPixelClearOk(lv_event_t * e);

void ui_event_DialogPixelClearCancel(lv_event_t * e);

void show_menu_page3_itme6_item6(void);

void hidden_menu_page3_itme6_item6(void);

#endif