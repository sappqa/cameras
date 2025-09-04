cmake_minimum_required(VERSION 3.15)
project(cameras LANGUAGES C)

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/render_window.c
    ${CMAKE_CURRENT_SOURCE_DIR}/render_graphics.c
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders.c
    ${CMAKE_CURRENT_SOURCE_DIR}/mouse_input_handler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/arcball_camera.c
    PARENT_SCOPE)
