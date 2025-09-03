#pragma once
#include "linmath.h"


void camera_init();
void camera_set_view(vec3 position, vec3 target, vec3 up);
void camera_up(vec3 out);
void camera_forward(vec3 out);
void camera_right(vec3 out);
void camera_get_position(vec3 position);
void camera_set_position(vec3 position);
void camera_get_target(vec3 target);
void camera_set_target(vec3 target);
void camera_get_projection(mat4x4 proj);
float camera_get_zoom();
void camera_set_zoom(float zoom);
void camera_rotate(float dx, float dy);