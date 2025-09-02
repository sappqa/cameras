#include "camera_arcball.h"
#include "common.h"
#include <stdio.h>

static vec3 _position = {0};
static vec3 _target = {0};
static vec3 _up = {0};
static mat4x4 _view;
static mat4x4 _projection;
static float _zoom = 0.0f;
static float _distance = 40.0f;

static const vec3 X_AXIS = {1, 0, 0};
static const vec3 Y_AXIS = {0, 1, 0};


void camera_init() {
    vec3 position = {0, 0, -_distance};
    vec3 target = {0, 0, 0};
    vec3 up = {0, 1, 0};
    
    camera_set_view(position, target, up);
}

void _update_view() {
    mat4x4 new_view;
    mat4x4_look_at(new_view, _position, _target, _up);
    mat4x4_dup(_view, new_view);
}

void camera_set_view(vec3 position, vec3 target, vec3 up) {
    vec3_dup(_position, position);
    vec3_dup(_target, target);
    vec3_dup(_up, up);
    _update_view();
}

void camera_up(vec3 out) {
    mat4x4 _; mat4x4_identity(_); 
    if (mat4x4_equals(_, _view)) {
        vec3_dup(out, (vec3) {0.0f, 1.0f, 0.0f});
    }
    else {
        mat4x4 lookat_t; mat4x4_transpose(lookat_t, _view);
        vec3_dup(out, lookat_t[1]);
    }
}

void camera_forward(vec3 out) {
    mat4x4 _; mat4x4_identity(_); 
    if (mat4x4_equals(_, _view)) {
        vec3_dup(out, (vec3) {0.0f, 0.0f, 0.0f});
    }
    else {
        mat4x4 lookat_t; mat4x4_transpose(lookat_t, _view);
        vec3_dup(out, lookat_t[2]);
    }
}

void camera_right(vec3 out) {
    mat4x4 _; mat4x4_identity(_); 
    if (mat4x4_equals(_, _view)) {
        vec3_dup(out, (vec3) {1.0f, 0.0f, 0.0f});
    }
    else {
        mat4x4 lookat_t; mat4x4_transpose(lookat_t, _view);
        vec3_dup(out, lookat_t[0]);
    }
}

void camera_get_projection(mat4x4 proj) {
    mat4x4 perspective;
    mat4x4_perspective(perspective, RADIANS(45.0f), RENDER_WINDOW_ASPECT, 0.01f, 100.0f);
    mat4x4_mul(proj, perspective, _view);
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
 
*/
void camera_rotate(float dx, float dy) {
    float dx_rad = (2 * M_PI / (float)RENDER_WINDOW_WIDTH) * dx;
    float dy_rad = (M_PI / (float)RENDER_WINDOW_HEIGHT) * dy;

    mat4x4 yaw;
    mat4x4 _; mat4x4_identity(_);
    mat4x4_rotate(yaw, _, _up[0], _up[1], _up[2], -dx_rad);

    vec4 dir_inv;
    vec3_sub(dir_inv, _position, _target);
    vec4 yaw_offset; mat4x4_mul_vec4(yaw_offset, yaw, dir_inv);
    // vec3 pos_yaw;
    // vec3_add(pos_yaw, _target, yaw_offset);

    mat4x4 pitch;
    vec3 right; camera_right(right);
    mat4x4_rotate(pitch, _, right[0], right[1], right[2], -dy_rad);

    vec4 offset_pitch_yaw;
    mat4x4_mul_vec4(offset_pitch_yaw, pitch, yaw_offset);

    vec3 new_position;
    vec3_add(new_position, _target, offset_pitch_yaw);

    camera_set_view(new_position, _target, _up);

    camera_up(_up);
}

