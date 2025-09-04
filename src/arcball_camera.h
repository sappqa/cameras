#pragma once
#include "linmath.h"

void arcball_camera_init();
void arcball_camera_set_start_point(float mouse_x, float mouse_y);
void arcball_camera_get_projection(mat4x4 proj);
float arcball_camera_get_distance();
void arcball_camera_set_distance(float zoom);
void arcball_camera_rotate(float mouse_x, float mouse_y);