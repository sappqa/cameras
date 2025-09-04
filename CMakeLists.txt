cmake_minimum_required(VERSION 3.15)
project(cameras LANGUAGES C)

set(SOURCES thirdparty/glad/src/glad.c)
set(INCLUDES ${CMAKE_SOURCE_DIR} thirdparty/linmath/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git)
FetchContent_MakeAvailable(glfw)

include_directories(${INCLUDES})

add_subdirectory(thirdparty/glad)
add_subdirectory(src)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE _POSIX_C_SOURCE=200112L)
# target_compile_definitions(${PROJECT_NAME} PRIVATE USE_ARCBALL_CAMERA)
target_compile_definitions(${PROJECT_NAME} PRIVATE USE_ORBIT_CAMERA)

target_link_libraries(${PROJECT_NAME} glfw glad)