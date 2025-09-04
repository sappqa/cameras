/*
This basic arcball implementation is achieved by accumulating small rotation quaternions mapped from each mouse movement delta into a global orientation quaternion.
The camera position is recomputed each frame simply by applying the global orientation to a default starting position.
*/

#include "arcball_camera.h"
#include "common.h"
#include "stdio.h"

static vec3 _sphere_start;
static float _distance = 30.0f;
static quat _orientation;
static mat4x4 _view;

static void _arcball_camera_update_view() {
    vec3 seed_position = {0, 0, _distance};
    vec3 target = {0, 0, 0};
    vec3 seed_up = {0, 1, 0};

    vec3 position_oriented, up_oriented;
    quat_mul_vec3(position_oriented, _orientation, seed_position);
    quat_mul_vec3(up_oriented, _orientation, seed_up);

    vec3 position;
    vec3_add(position, target, position_oriented);

    mat4x4 new_view;
    mat4x4_look_at(_view, position, target, up_oriented);
}

void arcball_camera_init() {
    quat_identity(_orientation);
    _arcball_camera_update_view();
}

static void _ndc_to_sphere(vec2 ndc, vec3 sphere) {
    float x2 = ndc[0] * ndc[0];
    float y2 = ndc[1] * ndc[1];

    if (x2 + y2 <= 1.0f) {
        float z = sqrtf(1 - x2 - y2);
        vec3_dup(sphere, (vec3) {ndc[0], ndc[1], z});
    }
    else {
        vec2 norm; vec2_norm(norm, ndc);
        vec3_dup(sphere, (vec3) {norm[0], norm[1], 0.0f});
    }

    vec3_norm(sphere, sphere);
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

    float cos_theta = vec3_mul_inner(_sphere_start, sphere_current);
    cos_theta = fmaxf(-1.0f, fminf(1.0f, cos_theta));
    float theta = -acos(cos_theta);

    quat rotation;
    quat_rotate(rotation, theta, cross);
    quat_mul(_orientation, _orientation, rotation);
    quat_norm(_orientation, _orientation);

    _arcball_camera_update_view();
    vec3_dup(_sphere_start, sphere_current);
}