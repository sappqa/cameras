#include "mouse_input_handler.h"
#include "camera_include.h"
#include <stdio.h>

static int _left_down = 0;
static int _right_down = 0;
static int _middle_down = 0;
static double _last_xpos;
static double _last_ypos;
static double _mouse_down_x;
static double _mouse_down_y;

static struct camera_selector {
    void (*mouse_left_press)(GLFWwindow* window);
    void (*mouse_move)(GLFWwindow* window, double xpos, double ypos);
};

static struct camera_selector active_camera;


static void _left_press_arcball(GLFWwindow* window) {
    glfwGetCursorPos(window, &_mouse_down_x, &_mouse_down_y);
    arcball_camera_set_start_point(_mouse_down_x, _mouse_down_y);
}

static void _left_press(GLFWwindow* window) {
    _left_down = 1;
    if (active_camera.mouse_left_press != NULL) {
        active_camera.mouse_left_press(window);
    }
}

static void _left_release() {
    _left_down = 0;
}

static void _right_press() {
    _right_down = 1;
}

static void _right_release() {
    _right_down = 0;
}

static void _middle_press() {
    _middle_down = 1;
}

static void _middle_release() {
    _middle_down = 0;
}

void handle_mouse_button_input(GLFWwindow* window, int button, int action, int mods) {
    void (*callback)() = NULL;

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        callback = action ? &_left_press : &_left_release;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        callback = action ? &_right_press : &_right_release;
    }
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        callback = action ? &_middle_press : &_middle_release;
    }

    if (callback != NULL) {
        callback();
    }
}

static void _mouse_move_arcball(GLFWwindow* window, double xpos, double ypos) {
    if (_left_down) {
        arcball_camera_rotate(xpos, ypos);
    }
}

static void _mouse_move_orbit(GLFWwindow* window, double xpos, double ypos) {
    double dx = xpos - _last_xpos;
    double dy = ypos - _last_ypos;

    if (_left_down) {
        orbit_camera_rotate(dx, dy);
    }
    
    _last_xpos = xpos;
    _last_ypos = ypos;
}

void handle_mouse_move_input(GLFWwindow* window, double xpos, double ypos) {
    active_camera.mouse_move(window, xpos, ypos);
}

void handle_mouse_scroll_input(GLFWwindow* window, double xoffset, double yoffset) {
    // camera_set_distance(camera_get_distance() + yoffset * .025);
}

void mouse_input_handler_init() {
    #ifdef USE_ARCBALL_CAMERA
    active_camera.mouse_left_press = _left_press_arcball;
    active_camera.mouse_move = _mouse_move_arcball;
    #elif USE_ORBIT_CAMERA
    active_camera.mouse_left_press = NULL;
    active_camera.mouse_move = _mouse_move_orbit;
    #endif
}