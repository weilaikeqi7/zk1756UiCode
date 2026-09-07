cmake_minimum_required(VERSION 3.16)

add_library(ui_app STATIC)

set(UI_GENERATED_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/core/ui.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/core/ui_helpers.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/core/ui_theme_manager.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/core/ui_themes.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/screens/ui_MainPage.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/screens/ui_PlayBar.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/screens/ui_ScrFileMgr.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/screens/ui_Temp.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/screens/ui_Self.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_btn.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_cmpdatetimebar.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_cmpfocuscell.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_cmpmodetoggle.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_cmptableheader.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_cmptablerow4col.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_dateitem.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_dialogeg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_distance.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_distancelabel.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_div_.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_hook.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_listitem.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_listlabel.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_num.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_paneleg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_rowenter.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_rowitem.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_rowitem1.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_rowlabel.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_rowswitch.c
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_mcitem.c
)

set(UI_FOUNDATION_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/app_state.c
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/font.c
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/lv_port_indev.c
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/popup_stack.c
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/timer_handle.c
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/ui_attitude_scale.c
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/ui_focus_manager.c
)

set(UI_IPC_REQUEST_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/requests/ui_ipc_request_system_video_network.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/requests/ui_ipc_request_media.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/requests/ui_ipc_request_video_peripheral_system.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/requests/ui_ipc_request_queries_operations.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/requests/ui_ipc_request_user_config.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/requests/ui_ipc_request_reticle.c
)

set(UI_IPC_TRANSPORT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/transport/ui_ipc_event_queue.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/transport/ui_ipc_receiver.c
)

set(UI_RUNTIME_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime/ui_runtime.c
)

set(UI_IPC_VALIDATION_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/validation/ui_ipc_message_validator.c
)

set(UI_IPC_DISPATCH_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/dispatch/ui_ipc_event_processor.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/dispatch/ui_ipc_notification_dispatch.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/dispatch/ui_ipc_response_dispatch.c
)

set(UI_IPC_NOTIFICATION_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/notifications/ui_ipc_notification_system_device_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/notifications/ui_ipc_notification_video_media_handler.c
)

set(UI_IPC_RESPONSE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_system_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_system_ui_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_video_input_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_video_output_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_compass_gnss_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_network_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_range_finder_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_pan_tilt_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_infrared_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_media_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_query_operation_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_user_config_handler.c
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_reticle_handler.c
)

set(UI_IPC_LINUX_SOURCES
        ${UI_IPC_TRANSPORT_SOURCES}
        ${UI_RUNTIME_SOURCES}
        ${UI_IPC_VALIDATION_SOURCES}
        ${UI_IPC_DISPATCH_SOURCES}
        ${UI_IPC_NOTIFICATION_SOURCES}
        ${UI_IPC_RESPONSE_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/requests/ui_ipc_request_sender.c
)

if(WIN32)
    set(UI_PLATFORM_SOURCES
            ${CMAKE_CURRENT_SOURCE_DIR}/platform/windows/windows_ipc_stub.c
    )
else()
    set(UI_PLATFORM_SOURCES ${UI_IPC_LINUX_SOURCES})
endif()

set(UI_MENU_NAVIGATION_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/navigation/menu_event_registry.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/navigation/menu_main_rows.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/navigation/menu_visibility.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/navigation/menu_page3_visibility.c
)

set(UI_MENU_VIDEO_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/video/menu_video_tools.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/video/menu_video_image.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/video/menu_video_adjust.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/video/menu_video_mode.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/video/menu_video_device.c
)

set(UI_MENU_SETTINGS_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/settings/menu_settings_user.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/settings/menu_settings_user_events.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/settings/menu_settings_datetime.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/settings/menu_settings_declination.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/settings/menu_settings_declination_digits.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/settings/menu_settings_declination_editor.c
)

set(UI_MENU_DIALOG_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/dialogs/menu_dialog_events.c
)

set(UI_MENU_SOURCES
        ${UI_MENU_NAVIGATION_SOURCES}
        ${UI_MENU_VIDEO_SOURCES}
        ${UI_MENU_SETTINGS_SOURCES}
        ${UI_MENU_DIALOG_SOURCES}
)

set(UI_PLAYBACK_CORE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/business/playback/playback_controller.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/playback/playback_navigation.c
)

set(UI_PLAYBACK_EVENT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/business/playback/playback_events.c
)

set(UI_PLAYBACK_SOURCES
        ${UI_PLAYBACK_CORE_SOURCES}
        ${UI_PLAYBACK_EVENT_SOURCES}
)

set(UI_RETICLE_MODEL_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle/reticle_model.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle/reticle_distance_mgr.c
)

set(UI_RETICLE_UI_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle/distance_editor.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle/reticle_distance_mgr_ui.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle/reticle_feature.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle/reticle_feature_dialog.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle/reticle_feature_level2.c
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle/reticle_feature_level34.c
)

set(UI_RETICLE_SOURCES
        ${UI_RETICLE_MODEL_SOURCES}
        ${UI_RETICLE_UI_SOURCES}
)

set(UI_FOUNDATION_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/app_state.h
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/font.h
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/lv_port_indev.h
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/popup_stack.h
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/roeTypes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/timer_handle.h
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/ui_attitude_scale.h
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation/ui_focus_manager.h
)

set(UI_GENERATED_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/core/ui.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/core/ui_helpers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/core/ui_events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/core/ui_theme_manager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/core/ui_themes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_btn.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_cmpdatetimebar.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_cmpfocuscell.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_cmpmodetoggle.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_cmptableheader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_cmptablerow4col.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_dateitem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_dialogeg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_distance.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_distancelabel.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_div_.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_hook.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_listitem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_listlabel.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_mcitem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_num.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_paneleg.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_rowenter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_rowitem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_rowitem1.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_rowlabel.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components/ui_comp_rowswitch.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/screens/ui_MainPage.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/screens/ui_PlayBar.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/screens/ui_ScrFileMgr.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/screens/ui_Self.h
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/screens/ui_Temp.h
)

set(UI_IPC_PROTOCOL_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/protocol/ui_ipc_protocol.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/protocol/ui_ipc_message.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/protocol/ui_ipc_request_types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/protocol/ui_ipc_response_types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/protocol/ui_ipc_notification_types.h
)

set(UI_IPC_TRANSPORT_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/transport/ui_ipc_event_queue.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/transport/ui_ipc_receiver.h
)

set(UI_IPC_VALIDATION_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/validation/ui_ipc_message_validator.h
)

set(UI_IPC_DISPATCH_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/dispatch/ui_ipc_dispatch.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/dispatch/ui_ipc_dispatch_internal.h
)

set(UI_IPC_REQUEST_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/requests/ui_ipc_request_internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/requests/ui_ipc_request_sender.h
)

set(UI_IPC_NOTIFICATION_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/notifications/ui_ipc_notification_handler.h
)

set(UI_IPC_RESPONSE_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_handler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses/ui_ipc_response_helpers.h
)

set(UI_IPC_HEADERS
        ${UI_IPC_PROTOCOL_HEADERS}
        ${UI_IPC_TRANSPORT_HEADERS}
        ${UI_IPC_VALIDATION_HEADERS}
        ${UI_IPC_DISPATCH_HEADERS}
        ${UI_IPC_REQUEST_HEADERS}
        ${UI_IPC_NOTIFICATION_HEADERS}
        ${UI_IPC_RESPONSE_HEADERS}
)

set(UI_RUNTIME_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime/ui_runtime.h
)

set(UI_MENU_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/navigation/menu_event_registry.h
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/navigation/menu_visibility.h
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/internal/menu_event_internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/internal/menu_user_settings_internal.h
)

set(UI_PLAYBACK_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/business/playback/playback_controller.h
        ${CMAKE_CURRENT_SOURCE_DIR}/business/playback/playback_internal.h
)

set(UI_RETICLE_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle/distance_editor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle/reticle_distance_mgr.h
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle/reticle_feature.h
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle/reticle_feature_internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle/reticle_model.h
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle/reticle_types.h
)

set(UI_MISC_SOURCES)

target_sources(ui_app
        PRIVATE
        ${UI_GENERATED_SOURCES}
        ${UI_GENERATED_HEADERS}
        ${UI_FOUNDATION_SOURCES}
        ${UI_IPC_REQUEST_SOURCES}
        ${UI_PLATFORM_SOURCES}
        ${UI_MENU_SOURCES}
        ${UI_PLAYBACK_SOURCES}
        ${UI_RETICLE_SOURCES}
        ${UI_FOUNDATION_HEADERS}
        ${UI_IPC_HEADERS}
        ${UI_RUNTIME_HEADERS}
        ${UI_MENU_HEADERS}
        ${UI_PLAYBACK_HEADERS}
        ${UI_RETICLE_HEADERS}
        ${UI_MISC_SOURCES}
)

target_include_directories(ui_app
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/core
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/components
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/screens
        ${CMAKE_CURRENT_SOURCE_DIR}/foundation
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/protocol
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/transport
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/validation
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/dispatch
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/requests
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/notifications
        ${CMAKE_CURRENT_SOURCE_DIR}/ipc/responses
        ${CMAKE_CURRENT_SOURCE_DIR}/runtime
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/navigation
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/video
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/settings
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/dialogs
        ${CMAKE_CURRENT_SOURCE_DIR}/business/menu/internal
        ${CMAKE_CURRENT_SOURCE_DIR}/business/playback
        ${CMAKE_CURRENT_SOURCE_DIR}/business/reticle
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
        ${UI_GENERATED_HEADERS}
        ${UI_FOUNDATION_SOURCES}
        ${UI_IPC_REQUEST_SOURCES}
        ${UI_IPC_TRANSPORT_SOURCES}
        ${UI_RUNTIME_SOURCES}
        ${UI_IPC_VALIDATION_SOURCES}
        ${UI_IPC_DISPATCH_SOURCES}
        ${UI_IPC_NOTIFICATION_SOURCES}
        ${UI_IPC_RESPONSE_SOURCES}
        ${UI_PLATFORM_SOURCES}
        ${UI_MENU_NAVIGATION_SOURCES}
        ${UI_MENU_VIDEO_SOURCES}
        ${UI_MENU_SETTINGS_SOURCES}
        ${UI_MENU_DIALOG_SOURCES}
        ${UI_PLAYBACK_SOURCES}
        ${UI_PLAYBACK_CORE_SOURCES}
        ${UI_PLAYBACK_EVENT_SOURCES}
        ${UI_RETICLE_SOURCES}
        ${UI_RETICLE_MODEL_SOURCES}
        ${UI_RETICLE_UI_SOURCES}
        ${UI_FOUNDATION_HEADERS}
        ${UI_IPC_HEADERS}
        ${UI_RUNTIME_HEADERS}
        ${UI_MENU_HEADERS}
        ${UI_PLAYBACK_HEADERS}
        ${UI_RETICLE_HEADERS}
        ${UI_MISC_SOURCES}
)
