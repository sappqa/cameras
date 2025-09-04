#include "arcball_camera.h"
#include "common.h"

static vec3 _sphere_start;
static vec3 _position;
static vec3 _target;
static vec3 _up;
static float _distance = 30.0f;
static mat4x4 _view;


void arcball_camera_init() {
    vec3 position = {0, 0, -_distance};
    vec3 target = {0, 0, 0};
    vec3 up = {0, 1, 0};
    
    arcball_camera_set_view(position, target, up);
}

static void _arcball_camera_update_view() {
    mat4x4 new_view;
    mat4x4_look_at(new_view, _position, _target, _up);
    mat4x4_dup(_view, new_view);
}

void arcball_camera_set_view(vec3 position, vec3 target, vec3 up) {
    vec3_dup(_position, position);
    vec3_dup(_target, target);
    vec3_dup(_up, up);
    _arcball_camera_update_view();
}

static void _ndc_to_sphere(vec2 ndc, vec3 sphere) {
    float x2 = ndc[0] * ndc[0];
    float y2 = ndc[1] * ndc[1];

    float z = 0.0f;
    if (x2 + y2 <= 1.0f) {
        z = sqrtf(1 - x2 - y2);
    }
    
    vec3_dup(sphere, (vec3) {ndc[0], ndc[1], z});
}

static void _mouse_to_ndc(float mouse_x, float mouse_y, vec2 ndc_out) {
    float ndc_x = (float)(2 * mouse_x - RENDER_WINDOW_WIDTH) / (float)RENDER_WINDOW_WIDTH;
    float ndc_y = (float)(RENDER_WINDOW_HEIGHT - 2 * mouse_y) / (float)RENDER_WINDOW_HEIGHT;
    vec2_dup(ndc_out, (vec2) {ndc_x, ndc_y});
}

void arcball_camera_set_start_point(float mouse_x, float mouse_y) {
    vec2 ndc;
    _mouse_to_ndc(mouse_x, mouse_y, ndc);
    _ndc_to_sphere(ndc, _sphere_start);
}

void arcball_camera_get_projection(mat4x4 proj) {
    mat4x4 perspective;
    mat4x4_perspective(perspective, RADIANS(45.0f), RENDER_WINDOW_ASPECT, 0.01f, 100.0f);
    mat4x4_mul(proj, perspective, _view);
}

float arcball_camera_get_distance() {
    return _distance;
}

void camera_set_distance(float distance) {

}

void arcball_camera_rotate(float mouse_x, float mouse_y) {
    vec2 ndc; vec3 sphere_current;
    _mouse_to_ndc(mouse_x, mouse_y, ndc);
    _ndc_to_sphere(ndc, sphere_current);

    vec3 cross;
    vec3_mul_cross(cross, _sphere_start, sphere_current);
    vec3_norm(cross, cross);

    float ab = vec3_mul_inner(_sphere_start, sphere_current);
    float mag_a = vec3_len(_sphere_start);
    float mag_b = vec3_len(sphere_current);
    float denom = mag_a * mag_b;
    float theta = acos(ab / denom);

    quat rot;
    quat_rotate(rot, theta, cross);

    vec4 camera_position;
    vec3_sub(camera_position, _position, _target);
    vec4 position_rotated; mat4x4_mul_vec4(position_rotated, rot, camera_position);

    vec3 new_position;
    vec3_add(new_position, _target, position_rotated);

    arcball_camera_set_view(new_position, _target, _up);
    // camera_up(_up);
}