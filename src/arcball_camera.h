#ifdef USE_ARCBALL_CAMERA
#pragma once
#include "linmath.h"

void camera_init();
void camera_get_projection(mat4x4 proj);
float camera_get_zoom();
void camera_set_zoom(float zoom);
void camera_rotate(float start_x, float start_y, float end_x, float end_y);
#endif