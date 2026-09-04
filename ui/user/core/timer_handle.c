//
// Created by jinxing on 2026/1/30.
//

#include "timer_handle.h"

DateTime datatime;
lv_timer_t * timer_datetime = NULL;

/* 从系统获取本地年月日并写入传入的 Date 指针（若为 NULL 则不操作） */
void datetime_get_local(DateTime * d)
{
    if(!d) return;
    time_t t = time(NULL);
    struct tm tm_now;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm_now, &t);
#else
    localtime_r(&t, &tm_now);
#endif
    d->year = tm_now.tm_year + 1900;
    d->month = tm_now.tm_mon + 1;
    d->day = tm_now.tm_mday;
    d->hour = tm_now.tm_hour;
    d->min = tm_now.tm_min;
    d->sec = tm_now.tm_sec;
}

void datetime_timer_event(lv_timer_t * timer)
{
    (void)timer; // 未使用参数
    datetime_get_local(&datatime);
    if(ui_labeldate == NULL || ui_labeltime == NULL || ui_settingrow1 == NULL || ui_settingrow2 == NULL) {
        return;
    }

    lv_label_set_text_fmt(ui_labeldate, "%02d/%02d/%02d", datatime.year, datatime.month, datatime.day);
    lv_label_set_text_fmt(ui_labeltime, "%02d:%02d", datatime.hour, datatime.min);
    lv_label_set_text_fmt(ui_comp_get_child(ui_settingrow1, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                          "%04d/%02d/%02d",
                          datatime.year,
                          datatime.month,
                          datatime.day);
    lv_label_set_text_fmt(ui_comp_get_child(ui_settingrow2, UI_COMP_ROWLABEL_CONTPILL1_ITEMLABEL1),
                          "%02d:%02d",
                          datatime.hour,
                          datatime.min);
}

void timer_init(void)
{
    timer_deinit();
    timer_datetime = lv_timer_create(datetime_timer_event, 1000, NULL);
    if(timer_datetime != NULL) {
        lv_timer_ready(timer_datetime);
    }
}

void timer_deinit(void)
{
    if(timer_datetime != NULL) {
        lv_timer_delete(timer_datetime);
        timer_datetime = NULL;
    }
}
