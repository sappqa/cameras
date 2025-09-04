#include "orbit_camera_axis_angle.h"
#include "common.h"
#include <stdio.h>

static float azimuth;
static float altitude;
static mat4x4 _view;
static float _distance = 20.0f;


static void _update_view() {
    float x = _distance * sinf(altitude) * sinf(azimuth);
    float y = _distance * cosf(altitude);
    float z = _distance * sinf(altitude) * cosf(azimuth);

    mat4x4 new_view;
    mat4x4_look_at(new_view, _position, _target, _up);
    mat4x4_dup(_view, new_view);
}

void orbit_camera_init() {
    _update_view();
}

void orbit_camera_get_projection(mat4x4 proj) {
    mat4x4 perspective;
    mat4x4_perspective(perspective, RADIANS(45.0f), RENDER_WINDOW_ASPECT, 0.01f, 100.0f);
    mat4x4_mul(proj, perspective, _view);
}

float orbit_camera_get_distance() {
    return _distance;
}

void orbit_camera_set_distance(float distance) {
    _distance = distance;
    // vec3_sub(_position_offset, _target, _position);
    // vec3_scale(_position_offset, _position_offset, zoom);
}

void orbit_camera_rotate(float dx, float dy) {
    float dx_rad = (2 * M_PI / (float)RENDER_WINDOW_WIDTH) * dx;
    float dy_rad = (M_PI / (float)RENDER_WINDOW_HEIGHT) * dy;

    _update_view();
}
