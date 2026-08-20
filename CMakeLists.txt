
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

add_subdirectory(freetype)
set(LV_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(LV_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lvgl)

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

target_compile_definitions(lvgl
        PUBLIC
        LV_CONF_INCLUDE_SIMPLE=1
        FT2_BUILD_LIBRARY
)

add_subdirectory(ui)

add_executable(${PROJECT_NAME} main.c)

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

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/ui
        ${PROJECT_SOURCE_DIR}/lvgl
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_custom_target(run COMMAND ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME} DEPENDS ${PROJECT_NAME})