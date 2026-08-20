cmake_minimum_required(VERSION 3.16)

add_library(ui_app STATIC)

set(UI_GENERATED_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/ui.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ui_helpers.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ui_theme_manager.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ui_themes.c
        ${CMAKE_CURRENT_SOURCE_DIR}/screens/ui_MainPage.c
        ${CMAKE_CURRENT_SOURCE_DIR}/screens/ui_PlayBar.c
        ${CMAKE_CURRENT_SOURCE_DIR}/screens/ui_ScrFileMgr.c
        ${CMAKE_CURRENT_SOURCE_DIR}/screens/ui_Temp.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_btn.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_cmpdatetimebar.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_cmpfocuscell.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_cmpmodetoggle.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_cmptableheader.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_cmptablerow4col.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_dateitem.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_dialogeg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_distance.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_distancelabel.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_div_.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_hook.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_listitem.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_listlabel.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_num.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_paneleg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_rowenter.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_rowitem.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_rowitem1.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_rowlabel.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_rowswitch.c
        ${CMAKE_CURRENT_SOURCE_DIR}/components/ui_comp_mcitem.c
)

set(UI_CORE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/app_state.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/font.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/lv_port_indev.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/msg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/popup_stack.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/timer_handle.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/ui_attitude_scale.c
)

set(UI_IPC_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/handleNotify.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/handleNotify_video.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/handleRcvRes.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/handleRcvRes_media.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/handleRcvRes_device.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/handleRcvRes_usercfg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/handleRcvRes_reticle.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ipcMsgQue4UiRcvNotify.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ipcMsgQue4UiRcvRes.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ipcMsgQue4UiSndRequest.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ipcMsgQue4UiSndSystem.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ipcMsgQue4UiSndMedia.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ipcMsgQue4UiSndDevice.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ipcMsgQue4UiSndUsercfg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ipcMsgQue4UiSndReticle.c
)

set(UI_SYSTEM_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_handle.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_mainrows.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_tools.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_usercfg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_usercfg_events.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_image.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_image_adjust.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_image_mode.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_device.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_datetime.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_declination.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_declination_digits.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_declination_settings.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_dialog.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/menu_handle.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/menu_handle_page3.c
)

set(UI_MEDIA_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/media/play_handle.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/media/play_handle_events.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/media/play_handle_nav.c
)

set(UI_RETICLE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/distance_editor.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_distance_mgr.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_distance_mgr_ui.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_feature.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_feature_dialog.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_feature_level2.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_feature_level34.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_model.c
)

set(UI_MISC_SOURCES)

target_sources(ui_app
        PRIVATE
        ${UI_GENERATED_SOURCES}
        ${UI_CORE_SOURCES}
        ${UI_IPC_SOURCES}
        ${UI_SYSTEM_SOURCES}
        ${UI_MEDIA_SOURCES}
        ${UI_RETICLE_SOURCES}
        ${UI_MISC_SOURCES}
)

target_include_directories(ui_app
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/components
        ${CMAKE_CURRENT_SOURCE_DIR}/screens
        ${CMAKE_CURRENT_SOURCE_DIR}/user
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu
        ${CMAKE_CURRENT_SOURCE_DIR}/user/media
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/lvgl
)

target_link_libraries(ui_app
        PUBLIC
        lvgl
        freetype
        m
        pthread
)

target_compile_definitions(ui_app
        PUBLIC
        LV_CONF_INCLUDE_SIMPLE=1
)

target_compile_options(ui_app
        PRIVATE
        -Wall
        -Wextra
        -Wno-unused
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
        ${UI_GENERATED_SOURCES}
        ${UI_CORE_SOURCES}
        ${UI_IPC_SOURCES}
        ${UI_SYSTEM_SOURCES}
        ${UI_MEDIA_SOURCES}
        ${UI_RETICLE_SOURCES}
        ${UI_MISC_SOURCES}
)
