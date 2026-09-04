
cmake_minimum_required(VERSION 3.16)

project(zk1756lcUiAarch64V01c01Glibc LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 可选：交叉编译时避免 try_run
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Do not pin the LVGL configuration path. Remove values left by an older
# CLion profile so os_desktop.cmake can use the project-root lv_conf.h.
unset(LV_BUILD_CONF_PATH CACHE)
unset(LV_BUILD_CONF_DIR CACHE)

add_subdirectory(freetype)

if(WIN32)
    find_package(SDL2 CONFIG REQUIRED)
endif()

set(LV_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(LV_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CONFIG_LV_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(CONFIG_LV_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CONFIG_LV_USE_THORVG_INTERNAL OFF CACHE BOOL "" FORCE)
add_subdirectory(lvgl)

# LVGL's desktop helper collects every source below lvgl/src. Keep the source
# selection in the application project so the vendored LVGL tree stays intact.
get_target_property(LVGL_SOURCES lvgl SOURCES)
set(LVGL_SOURCE_SKIP_PATTERNS
        "^debugging/"
        "^others/"
        "^drivers/display/(drm|ft81x|ili9341|lcd|lovyan_gfx|nv3007|nxp_elcdif|renesas_glcdc|st_ltdc|st7735|st7789|st7796|tft_espi)/"
        "^drivers/(draw|evdev|libinput|nuttx|opengles|qnx|uefi|wayland|windows|x11)/"
        "^draw/(dma2d|espressif|eve|nanovg|nema_gfx|nxp|opengles|renesas|sdl|snapshot|vg_lite)/"
        "^draw/sw/blend/(arm2d|helium|neon|riscv_v)/"
        "^draw/convert/(helium|neon)/"
        "^draw/lv_draw_(3d|vector)\\.c$"
        "^draw/sw/lv_draw_sw_vector\\.c$"
        "^libs/(barcode|ffmpeg|frogfs|FT800-FT813|gif|gltf|gstreamer|libjpeg_turbo|libpng|libwebp|lz4|nanovg|qrcode|rle|rlottie|svg|thorvg|tiny_ttf|tjpgd|vg_lite_driver)/"
        "^libs/fsdrv/lv_fs_(arduino_esp_littlefs|arduino_sd|cbfs|fatfs|frogfs|littlefs|memfs|posix|uefi|win32)\\.(c|cpp)$"
        "^libs/freetype/lv_ftsystem\\.c$"
        "^font/(binfont_loader|font_manager|imgfont)/"
        "^font/lv_font_(dejavu_16_persian_hebrew|source_han_sans_sc_14_cjk|source_han_sans_sc_16_cjk|unscii_8|unscii_16|montserrat_28_compressed)\\.c$"
        "^core/lv_obj_property\\.c$"
        "^indev/lv_(gridnav|indev_gesture)\\.c$"
        "^misc/lv_(matrix|profiler_builtin|profiler_builtin_posix)\\.c$"
        "^stdlib/(clib|micropython|rtthread|uefi)/"
        "^widgets/(3dtexture|gif|ime|lottie)/"
        "^widgets/(objx_templ|property)/"
)

if(WIN32)
    list(APPEND LVGL_SOURCE_SKIP_PATTERNS
            "^drivers/display/fb/"
            "^osal/lv_(cmsis_rtos2|freertos|linux|mqx|pthread|rtthread|sdl2|windows)\\.c$"
    )
else()
    list(APPEND LVGL_SOURCE_SKIP_PATTERNS
            "^drivers/sdl/"
            "^osal/lv_(cmsis_rtos2|freertos|linux|mqx|os_none|rtthread|sdl2|windows)\\.c$"
    )
endif()

set(LVGL_FILTERED_SOURCES)
foreach(LVGL_SOURCE IN LISTS LVGL_SOURCES)
    file(RELATIVE_PATH LVGL_SOURCE_RELATIVE
            "${PROJECT_SOURCE_DIR}/lvgl/src"
            "${LVGL_SOURCE}")
    string(REPLACE "\\" "/" LVGL_SOURCE_RELATIVE "${LVGL_SOURCE_RELATIVE}")

    set(LVGL_SKIP_SOURCE OFF)
    foreach(LVGL_SKIP_PATTERN IN LISTS LVGL_SOURCE_SKIP_PATTERNS)
        if(LVGL_SOURCE_RELATIVE MATCHES "${LVGL_SKIP_PATTERN}")
            set(LVGL_SKIP_SOURCE ON)
            break()
        endif()
    endforeach()

    if(NOT LVGL_SKIP_SOURCE)
        list(APPEND LVGL_FILTERED_SOURCES "${LVGL_SOURCE}")
    endif()
endforeach()

set_property(TARGET lvgl PROPERTY SOURCES "${LVGL_FILTERED_SOURCES}")
# lv_conf.h is a configuration header, not a translation unit. Keep it out of
# the target source list so CLion and clangd do not treat it as compilable code.
list(LENGTH LVGL_SOURCES LVGL_SOURCE_COUNT)
list(LENGTH LVGL_FILTERED_SOURCES LVGL_FILTERED_SOURCE_COUNT)
message(STATUS "LVGL sources: ${LVGL_FILTERED_SOURCE_COUNT}/${LVGL_SOURCE_COUNT}")

target_compile_options(lvgl
        PRIVATE
        -Wno-psabi
)

target_include_directories(lvgl
        PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/freetype/include
)

target_link_libraries(lvgl
        PUBLIC
        freetype
)

if(WIN32)
    target_link_libraries(lvgl PUBLIC SDL2::SDL2)
endif()

target_compile_definitions(lvgl
        PUBLIC
        FT2_BUILD_LIBRARY
)

add_subdirectory(ui)

if(WIN32)
    add_executable(${PROJECT_NAME} windows_simulator.c)
    target_compile_definitions(${PROJECT_NAME}
            PRIVATE
            UI_SIMULATOR_FONT_PATH="${PROJECT_SOURCE_DIR}/ui/fonts/"
    )
else()
    add_executable(${PROJECT_NAME} main.c)
endif()

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ui_app
)

target_compile_options(${PROJECT_NAME}
        PRIVATE
        -Wall
        -Wextra
        -Wno-unused
)

target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        _DEFAULT_SOURCE
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/ui
        ${PROJECT_SOURCE_DIR}/lvgl
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_custom_target(run COMMAND $<TARGET_FILE:${PROJECT_NAME}> DEPENDS ${PROJECT_NAME})
