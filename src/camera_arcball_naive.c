#include "camera_arcball.h"
#include "common.h"
#include <stdio.h>

static vec3 _starting_position = {0};
static vec3 _position = {0};
static vec3 _target = {0};
static vec3 _up = {0};
static mat4x4 _projection;
static float _zoom = 0.0f;

static float _distance = 40.0f;
static float _azimuth = 0.0f;
static float _altitude = 0.0f;
static float _roll = 0.0f;

static const vec3 X_AXIS = {1, 0, 0};
static const vec3 Y_AXIS = {0, 1, 0};


void camera_init() {
    vec3 target = {0, 0, 0};
    vec3 up = {0, 1, 0};
    vec3 position = {0, 0, -_distance};

    memcpy(_position, position, sizeof(vec3));
    memcpy(_target, target, sizeof(vec3));
    memcpy(_up, up, sizeof(vec3));
}

void camera_get_position(vec3 position) {
    memcpy(position, _position, sizeof(vec3));
}

void camera_set_position(vec3 position) {
    memcpy(_position, position, sizeof(vec3));
}

void camera_get_target(vec3 target) {
    memcpy(target, _target, sizeof(vec3));
}

void camera_set_target(vec3 target) {
    memcpy(_target, target, sizeof(vec3));
}

void camera_get_projection(mat4x4 proj) {
    mat4x4 view, perspective;
    mat4x4_look_at(view, _position, _target, _up);
    mat4x4_perspective(perspective, RADIANS(45.0f), RENDER_WINDOW_ASPECT, 0.01f, 100.0f);
    mat4x4_mul(proj, perspective, view);
}

float camera_get_zoom() {
    return _zoom;
}

void camera_set_zoom(float zoom) {
    _zoom = zoom;
    // vec3_sub(_position_offset, _target, _position);
    // vec3_scale(_position_offset, _position_offset, zoom);
}

/*

This is an attempt to implement an arcball camera using axis-angle rotation.

The idea:
- use dx and dy to calculate pitch and yaw rotation angles in radians by dividing by viewport dimensions.
- yaw is horizontal rotation. Rotate around world up axis, which is <0,1,0>
- pitch is vertical rotation.
    - after rotating the camera horizontally, recompute the right vector and use that as the axis of rotation for the pitch.
There are a few issues with this implementation:
- 

*/
void camera_rotate(float dx, float dy) {
    float dx_rad = (2 * M_PI / (float)RENDER_WINDOW_WIDTH) * dx;
    float dy_rad = (M_PI / (float)RENDER_WINDOW_HEIGHT) * dy;

    mat4x4 yaw;
    mat4x4 _; mat4x4_identity(_);
    mat4x4_rotate(yaw, _, _up[0], _up[1], _up[2], -dx_rad);

    vec4 dir_inv;
    vec3_sub(dir_inv, _position, _target);
    vec4 pos_yaw; mat4x4_mul_vec4(pos_yaw, yaw, dir_inv);

    vec3 forward;
    vec3_sub(forward, _target, pos_yaw);
    vec3_norm(forward, forward);

    vec3 right;
    vec3_mul_cross(right, forward, _up);
    vec3_norm(right, right);

    mat4x4 pitch;
    mat4x4_rotate(pitch, _, right[0], right[1], right[2], -dy_rad);

    vec4 pos_pitch_yaw;
    mat4x4_mul_vec4(pos_pitch_yaw, pitch, pos_yaw);

    vec3 new_position;
    vec3_add(new_position, _target, pos_pitch_yaw);
    vec3_dup(_position, new_position);
}

