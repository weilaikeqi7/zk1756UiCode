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
        ${CMAKE_CURRENT_SOURCE_DIR}/screens/ui_Self.c
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
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/popup_stack.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/timer_handle.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/ui_attitude_scale.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/ui_focus_manager.c
)

set(UI_IPC_SEND_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_send_system.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_send_media.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_send_device.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_send_framework.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_send_user_config.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_send_reticle.c
)

set(UI_IPC_QUEUE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_event_queue.c
)

set(UI_IPC_RUNTIME_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_receiver.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/runtime/ui_runtime.c
)

set(UI_IPC_VALIDATION_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_message_validator.c
)

set(UI_IPC_DISPATCH_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_event_processor.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_notification_dispatch.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_response_dispatch.c
)

set(UI_IPC_NOTIFICATION_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_notification_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_notification_video_handler.c
)

set(UI_IPC_RESPONSE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_response_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_response_media_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_response_device_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_response_framework_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_response_user_config_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_response_reticle_handler.c
)

set(UI_IPC_LINUX_SOURCES
        ${UI_IPC_QUEUE_SOURCES}
        ${UI_IPC_RUNTIME_SOURCES}
        ${UI_IPC_VALIDATION_SOURCES}
        ${UI_IPC_DISPATCH_SOURCES}
        ${UI_IPC_NOTIFICATION_SOURCES}
        ${UI_IPC_RESPONSE_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_request_sender.c
)

if(WIN32)
    set(UI_PLATFORM_SOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/simulator/windows_ipc_stub.c
    )
else()
    set(UI_PLATFORM_SOURCES ${UI_IPC_LINUX_SOURCES})
endif()

set(UI_MENU_NAVIGATION_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_handle.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_mainrows.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/menu_handle.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/menu_handle_page3.c
)

set(UI_MENU_VIDEO_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_tools.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_image.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_image_adjust.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_image_mode.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_device.c
)

set(UI_MENU_USER_CONFIG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_usercfg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_usercfg_events.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_datetime.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_declination.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_declination_digits.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_declination_settings.c
)

set(UI_MENU_DIALOG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_dialog.c
)

set(UI_MENU_SOURCES
        ${UI_MENU_NAVIGATION_SOURCES}
        ${UI_MENU_VIDEO_SOURCES}
        ${UI_MENU_USER_CONFIG_SOURCES}
        ${UI_MENU_DIALOG_SOURCES}
)

set(UI_MEDIA_CORE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/media/play_handle.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/media/play_handle_nav.c
)

set(UI_MEDIA_EVENT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/media/play_handle_events.c
)

set(UI_MEDIA_SOURCES
        ${UI_MEDIA_CORE_SOURCES}
        ${UI_MEDIA_EVENT_SOURCES}
)

set(UI_RETICLE_MODEL_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_model.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_distance_mgr.c
)

set(UI_RETICLE_UI_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/distance_editor.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_distance_mgr_ui.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_feature.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_feature_dialog.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_feature_level2.c
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_feature_level34.c
)

set(UI_RETICLE_SOURCES
        ${UI_RETICLE_MODEL_SOURCES}
        ${UI_RETICLE_UI_SOURCES}
)

set(UI_CORE_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/app_state.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/font.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/lv_port_indev.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/popup_stack.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/roeTypes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/timer_handle.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/ui_attitude_scale.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core/ui_focus_manager.h
)

set(UI_IPC_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_notification_handler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_response_handler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_event_queue.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_dispatch_internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_message_validator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_dispatch.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_notification_types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_response_types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_request_internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_request_sender.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_request_types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_protocol.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_response_helpers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_message.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc/ui_ipc_receiver.h
)

set(UI_RUNTIME_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/user/runtime/ui_runtime.h
)

set(UI_MENU_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_handle.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/mainpage_event_usercfg_internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/menu/menu_handle.h
)

set(UI_MEDIA_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/user/media/play_handle.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/media/play_handle_internal.h
)

set(UI_RETICLE_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/distance_editor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_distance_mgr.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_feature.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_feature_internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_model.h
        ${CMAKE_CURRENT_SOURCE_DIR}/user/reticle/reticle_types.h
)

set(UI_MISC_SOURCES)

target_sources(ui_app
        PRIVATE
        ${UI_GENERATED_SOURCES}
        ${UI_CORE_SOURCES}
        ${UI_IPC_SEND_SOURCES}
        ${UI_PLATFORM_SOURCES}
        ${UI_MENU_SOURCES}
        ${UI_MEDIA_SOURCES}
        ${UI_RETICLE_SOURCES}
        ${UI_CORE_HEADERS}
        ${UI_IPC_HEADERS}
        ${UI_RUNTIME_HEADERS}
        ${UI_MENU_HEADERS}
        ${UI_MEDIA_HEADERS}
        ${UI_RETICLE_HEADERS}
        ${UI_MISC_SOURCES}
)

target_include_directories(ui_app
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/components
        ${CMAKE_CURRENT_SOURCE_DIR}/screens
        ${CMAKE_CURRENT_SOURCE_DIR}/user/core
        ${CMAKE_CURRENT_SOURCE_DIR}/user/ipc
        ${CMAKE_CURRENT_SOURCE_DIR}/user/runtime
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
)

if(NOT WIN32)
    target_link_libraries(ui_app PUBLIC m pthread)
else()
    target_compile_definitions(ui_app
            PUBLIC
            UI_IMAGES_PATH="A:${PROJECT_SOURCE_DIR}/ui/images/"
    )
endif()

target_compile_definitions(ui_app
        PRIVATE
        _DEFAULT_SOURCE
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
        ${UI_IPC_SEND_SOURCES}
        ${UI_IPC_QUEUE_SOURCES}
        ${UI_IPC_RUNTIME_SOURCES}
        ${UI_IPC_VALIDATION_SOURCES}
        ${UI_IPC_DISPATCH_SOURCES}
        ${UI_IPC_NOTIFICATION_SOURCES}
        ${UI_IPC_RESPONSE_SOURCES}
        ${UI_PLATFORM_SOURCES}
        ${UI_MENU_NAVIGATION_SOURCES}
        ${UI_MENU_VIDEO_SOURCES}
        ${UI_MENU_USER_CONFIG_SOURCES}
        ${UI_MENU_DIALOG_SOURCES}
        ${UI_MEDIA_SOURCES}
        ${UI_MEDIA_CORE_SOURCES}
        ${UI_MEDIA_EVENT_SOURCES}
        ${UI_RETICLE_SOURCES}
        ${UI_RETICLE_MODEL_SOURCES}
        ${UI_RETICLE_UI_SOURCES}
        ${UI_CORE_HEADERS}
        ${UI_IPC_HEADERS}
        ${UI_RUNTIME_HEADERS}
        ${UI_MENU_HEADERS}
        ${UI_MEDIA_HEADERS}
        ${UI_RETICLE_HEADERS}
        ${UI_MISC_SOURCES}
)
