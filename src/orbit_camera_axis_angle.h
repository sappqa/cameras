#pragma once
#include "linmath.h"

void orbit_camera_init();
void orbit_camera_set_view(vec3 position, vec3 target, vec3 up);
void orbit_camera_up(vec3 out);
void orbit_camera_forward(vec3 out);
void orbit_camera_right(vec3 out);
void orbit_camera_get_position(vec3 position);
void orbit_camera_set_position(vec3 position);
void orbit_camera_get_target(vec3 target);
void orbit_camera_set_target(vec3 target);
void orbit_camera_get_projection(mat4x4 proj);
float orbit_camera_get_zoom();
void orbit_camera_set_zoom(float zoom);
void orbit_camera_rotate(float dx, float dy);