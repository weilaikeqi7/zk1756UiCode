//
// Created by jinxing on 2026/1/8.
//

#include "reticle_feature.h"
#include "mainpage_event_handle.h"
#include "mainpage_event_internal.h"

void add_event_of_menu(void)
{
    lv_obj_add_event_cb(ui_rowlrf, ui_event_rowlrf, LV_EVENT_ALL, ui_rowlrf);
    lv_obj_add_event_cb(ui_rowimagemode, ui_event_rowimagemode, LV_EVENT_ALL, ui_rowimagemode);
    lv_obj_add_event_cb(ui_rowbrightness, ui_event_rowbrightness, LV_EVENT_ALL, ui_rowbrightness);
    lv_obj_add_event_cb(ui_rowcontrast, ui_event_rowcontrast, LV_EVENT_ALL, ui_rowcontrast);
    lv_obj_add_event_cb(ui_rowsharpness, ui_event_rowsharpness, LV_EVENT_ALL, ui_rowsharpness);
    lv_obj_add_event_cb(ui_rowexpansion, ui_event_rowexpansion, LV_EVENT_ALL, ui_rowexpansion);
    lv_obj_add_event_cb(ui_rowpip, ui_event_rowpip, LV_EVENT_ALL, ui_rowpip);
    lv_obj_add_event_cb(ui_menu1row1, ui_event_menu1row1, LV_EVENT_ALL, ui_menu1row1);
    lv_obj_add_event_cb(ui_menu1row2, ui_event_menu1row2, LV_EVENT_ALL, ui_menu1row2);
    lv_obj_add_event_cb(ui_menu1row3, ui_event_menu1row3, LV_EVENT_ALL, ui_menu1row3);
    lv_obj_add_event_cb(ui_menu1row4, ui_event_menu1row4, LV_EVENT_ALL, ui_menu1row4);
    lv_obj_add_event_cb(ui_menu1row5, ui_event_menu1row5, LV_EVENT_ALL, ui_menu1row5);
    lv_obj_add_event_cb(ui_rowitem21, ui_event_rowitem21, LV_EVENT_ALL, ui_rowitem21);
    lv_obj_add_event_cb(ui_rowitem22, ui_event_rowitem22, LV_EVENT_ALL, ui_rowitem22);
    lv_obj_add_event_cb(ui_rowitem23, ui_event_rowitem23, LV_EVENT_ALL, ui_rowitem23);
    lv_obj_add_event_cb(ui_rowitem24, ui_event_rowitem24, LV_EVENT_ALL, ui_rowitem24);
    lv_obj_add_event_cb(ui_rowitem25, ui_event_rowitem25, LV_EVENT_ALL, ui_rowitem25);
    lv_obj_add_event_cb(ui_rowitem26, ui_event_rowitem26, LV_EVENT_ALL, ui_rowitem26);
    lv_obj_add_event_cb(ui_rowitem27, ui_event_rowitem27, LV_EVENT_ALL, ui_rowitem27);
    lv_obj_add_event_cb(ui_rowitem28, ui_event_rowitem28, LV_EVENT_ALL, ui_rowitem28);
    lv_obj_add_event_cb(ui_rowitem29, ui_event_rowitem29, LV_EVENT_ALL, ui_rowitem29);
    lv_obj_add_event_cb(ui_rowwifi, ui_event_rowwifi, LV_EVENT_ALL, ui_rowwifi);
    lv_obj_add_event_cb(ui_rowtilt, ui_event_rowtilt, LV_EVENT_ALL, ui_rowtilt);
    lv_obj_add_event_cb(ui_rowcompass, ui_event_rowcompass, LV_EVENT_ALL, ui_rowcompass);
    lv_obj_add_event_cb(ui_rowreticle, ui_event_rowreticle, LV_EVENT_ALL, ui_rowreticle);
    lv_obj_add_event_cb(ui_rowballistic, ui_event_rowballistic, LV_EVENT_ALL, ui_rowballistic);
    lv_obj_add_event_cb(ui_rowmic, ui_event_rowmic, LV_EVENT_ALL, ui_rowmic);
    lv_obj_add_event_cb(ui_rowrav, ui_event_rowrav, LV_EVENT_ALL, ui_rowrav);
    lv_obj_add_event_cb(ui_rowstandby, ui_event_rowstandby, LV_EVENT_ALL, ui_rowstandby);
    lv_obj_add_event_cb(
        ui_rowcompasscalibration,
        ui_event_rowcompasscalibration,
        LV_EVENT_ALL,
        ui_rowcompasscalibration);
    lv_obj_add_event_cb(ui_rowdeadpixel, ui_event_rowdeadpixel, LV_EVENT_ALL, ui_rowdeadpixel);
    lv_obj_add_event_cb(ui_rowstatusbar, ui_event_rowstatusbar, LV_EVENT_ALL, ui_rowstatusbar);
    lv_obj_add_event_cb(ui_rowdeletefile, ui_event_rowdeletefile, LV_EVENT_ALL, ui_rowdeletefile);
    lv_obj_add_event_cb(ui_rowsetting, ui_event_rowsetting, LV_EVENT_ALL, ui_rowsetting);
    lv_obj_add_event_cb(ui_rowswitch1, ui_event_rowswitch1, LV_EVENT_ALL, ui_rowswitch1);
    lv_obj_add_event_cb(ui_rowitem1, ui_event_rowitem1, LV_EVENT_ALL, ui_rowitem1);
    lv_obj_add_event_cb(ui_rowitem2, ui_event_rowitem2, LV_EVENT_ALL, ui_rowitem2);
    lv_obj_add_event_cb(ui_rowitem3, ui_event_rowitem3, LV_EVENT_ALL, ui_rowitem3);
    lv_obj_add_event_cb(ui_rowitem4, ui_event_rowitem4, LV_EVENT_ALL, ui_rowitem4);
    lv_obj_add_event_cb(ui_rowitem5, ui_event_rowitem5, LV_EVENT_ALL, ui_rowitem5);
    lv_obj_add_event_cb(ui_comp_get_child(ui_num1, UI_COMP_NUM_PANELNUM), ui_event_num1, LV_EVENT_ALL, ui_num1);
    lv_obj_add_event_cb(ui_comp_get_child(ui_num2, UI_COMP_NUM_PANELNUM), ui_event_num2, LV_EVENT_ALL, ui_num2);
    lv_obj_add_event_cb(ui_comp_get_child(ui_num3, UI_COMP_NUM_PANELNUM), ui_event_num3, LV_EVENT_ALL, ui_num3);
    lv_obj_add_event_cb(ui_comp_get_child(ui_num4, UI_COMP_NUM_PANELNUM), ui_event_num4, LV_EVENT_ALL, ui_num4);
    lv_obj_add_event_cb(ui_comp_get_child(ui_num5, UI_COMP_NUM_PANELNUM), ui_event_num5, LV_EVENT_ALL, ui_num5);
    lv_obj_add_event_cb(ui_comp_get_child(ui_num6, UI_COMP_NUM_PANELNUM), ui_event_num6, LV_EVENT_ALL, ui_num6);
    lv_obj_add_event_cb(ui_rowitemOK, ui_event_rowitemOK, LV_EVENT_ALL, ui_rowitemOK);
    lv_obj_add_event_cb(ui_rowitemCANCEL, ui_event_rowitemCANCEL, LV_EVENT_ALL, ui_rowitemCANCEL);
    lv_obj_add_event_cb(ui_settingrow1, ui_event_settingrow1, LV_EVENT_ALL, ui_settingrow1);
    lv_obj_add_event_cb(ui_settingrow2, ui_event_settingrow2, LV_EVENT_ALL, ui_settingrow2);
    lv_obj_add_event_cb(ui_settingrow3, ui_event_settingrow3, LV_EVENT_ALL, ui_settingrow3);
    lv_obj_add_event_cb(ui_settingrow4, ui_event_settingrow4, LV_EVENT_ALL, ui_settingrow4);
    lv_obj_add_event_cb(ui_settingrow5, ui_event_settingrow5, LV_EVENT_ALL, ui_settingrow5);
    lv_obj_add_event_cb(ui_settingrow6, ui_event_settingrow6, LV_EVENT_ALL, ui_settingrow6);
    lv_obj_add_event_cb(ui_rowitemyear, ui_event_rowitemyear, LV_EVENT_ALL, ui_rowitemyear);
    lv_obj_add_event_cb(ui_rowitemmonth, ui_event_rowitemmonth, LV_EVENT_ALL, ui_rowitemmonth);
    lv_obj_add_event_cb(ui_rowitemday, ui_event_rowitemday, LV_EVENT_ALL, ui_rowitemday);
    lv_obj_add_event_cb(ui_rowitemdateback, ui_event_rowitemback, LV_EVENT_ALL, ui_rowitemdateback);
    lv_obj_add_event_cb(ui_rowitemhour, ui_event_rowitemhour, LV_EVENT_ALL, ui_rowitemhour);
    lv_obj_add_event_cb(ui_rowitemmin, ui_event_rowitemmin, LV_EVENT_ALL, ui_rowitemmin);
    lv_obj_add_event_cb(ui_rowitemtimeback, ui_event_rowitemtimeback, LV_EVENT_ALL, ui_rowitemtimeback);
    lv_obj_add_event_cb(ui_resetOK, ui_event_resetOK, LV_EVENT_ALL, ui_resetOK);
    lv_obj_add_event_cb(ui_resetCANCEL, ui_event_resetCANCEL, LV_EVENT_ALL, ui_resetCANCEL);
    lv_obj_add_event_cb(ui_comp_get_child(ui_DialogFormattingSd, UI_COMP_DIALOGEG_DIALOGOK),
                        ui_event_DialogFormattingSdOk,
                        LV_EVENT_ALL,
                        ui_comp_get_child(ui_DialogFormattingSd, UI_COMP_DIALOGEG_DIALOGOK));
    lv_obj_add_event_cb(ui_comp_get_child(ui_DialogFormattingSd, UI_COMP_DIALOGEG_DIALOGCANCEL),
                        ui_event_DialogFormattingSdCancel,
                        LV_EVENT_ALL,
                        ui_comp_get_child(ui_DialogFormattingSd, UI_COMP_DIALOGEG_DIALOGCANCEL));
    lv_obj_add_event_cb(ui_infoOK, ui_event_infoOK, LV_EVENT_ALL, ui_infoOK);
    reticle_feature_init();
    reticle_feature_bind_events();
    play_event_init();
    lv_obj_add_event_cb(
        ui_comp_get_child(ui_poweroff, UI_COMP_DIALOGEG_DIALOGOK),
        ui_event_powerOffOK,
        LV_EVENT_ALL,
        NULL);
    lv_obj_add_event_cb(
        ui_comp_get_child(ui_poweroff, UI_COMP_DIALOGEG_DIALOGCANCEL),
        ui_event_powerOffCancel,
        LV_EVENT_ALL,
        NULL);
    lv_obj_add_event_cb(ui_bad_pixel, ui_event_bad_pixel, LV_EVENT_ALL, ui_bad_pixel);
    lv_obj_add_event_cb(ui_pixel_return, ui_event_pixel_return, LV_EVENT_ALL, ui_pixel_return);
    lv_obj_add_event_cb(ui_bad_pixel_item2, ui_event_pixel_item2, LV_EVENT_ALL, ui_bad_pixel_item2);
    lv_obj_add_event_cb(ui_bad_pixel_item3, ui_event_pixel_item3, LV_EVENT_ALL, ui_bad_pixel_item3);
    lv_obj_add_event_cb(ui_bad_pixel_item4, ui_event_pixel_item4, LV_EVENT_ALL, ui_bad_pixel_item4);
    lv_obj_add_event_cb(ui_bad_pixel_item5, ui_event_pixel_item5, LV_EVENT_ALL, ui_bad_pixel_item5);
    lv_obj_add_event_cb(ui_bad_pixel_item6, ui_event_pixel_item6, LV_EVENT_ALL, ui_bad_pixel_item6);
    lv_obj_add_event_cb(ui_comp_get_child(ui_DialogCompass, UI_COMP_DIALOGEG_DIALOGOK),
                        ui_event_CompassStart,
                        LV_EVENT_ALL,
                        ui_comp_get_child(ui_DialogCompass, UI_COMP_DIALOGEG_DIALOGOK));
    lv_obj_add_event_cb(ui_comp_get_child(ui_DialogCompass, UI_COMP_DIALOGEG_DIALOGCANCEL),
                        ui_event_CompassCancel,
                        LV_EVENT_ALL,
                        ui_comp_get_child(ui_DialogCompass, UI_COMP_DIALOGEG_DIALOGCANCEL));
    lv_obj_add_event_cb(ui_comp_get_child(ui_DialogPixelClear, UI_COMP_DIALOGEG_DIALOGOK),
                        ui_event_DialogPixelClearOk,
                        LV_EVENT_ALL,
                        ui_comp_get_child(ui_DialogPixelClear, UI_COMP_DIALOGEG_DIALOGOK));
    lv_obj_add_event_cb(ui_comp_get_child(ui_DialogPixelClear, UI_COMP_DIALOGEG_DIALOGCANCEL),
                        ui_event_DialogPixelClearCancel,
                        LV_EVENT_ALL,
                        ui_comp_get_child(ui_DialogPixelClear, UI_COMP_DIALOGEG_DIALOGCANCEL));
}