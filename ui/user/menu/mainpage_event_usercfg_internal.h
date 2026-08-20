#ifndef ZKSL_75_6LC_MAINPAGE_EVENT_USERCFG_INTERNAL_H
#define ZKSL_75_6LC_MAINPAGE_EVENT_USERCFG_INTERNAL_H

#include "mainpage_event_handle.h"

void ui_rowswitch_set_checked(lv_obj_t * row, ROE_U8 checked);
int standby_timeout_sec_to_ui_min(ROE_U16 sec);
ROE_U16 ui_min_to_standby_timeout_sec(int min);
void send_user_common_config_partial(ROE_S8 showDateTime,
                                     ROE_S16 standbyTimeout,
                                     ROE_S16 shutdownTimeout,
                                     ROE_S8 distanceUnit,
                                     ROE_U8 saveFlag);
void send_user_media_config_partial(ROE_S8 burstCount,
                                    ROE_S16 maxRecordDuration,
                                    ROE_S8 recoilPreRecordSwitch,
                                    ROE_S16 recoilPreRecordDuration,
                                    ROE_S8 micSwitch,
                                    ROE_U8 saveFlag);

#endif
