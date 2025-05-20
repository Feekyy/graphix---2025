#ifndef CAMERA_H
#define CAMERA_H

#include "addons.h"

#include <stdbool.h>

typedef struct Camera
{
    vec3 position;
    vec3 rotation;
    vec3 speed;
    bool is_preview_visible;
} Camera;

// Function to initialize the camera state.
void init_camera(Camera* camera);

// Function to update the camera state based on the given time.
void update_camera(Camera* camera, double time);

// Function to set the camera view based on the current state.
void set_view(const Camera* camera);

// Function to rotate the camera around the world axes.
void rotate_camera(Camera* camera, double horizontal, double vertical);

// Function to set the camera speed in the x-axis.
void set_camera_speed(Camera* camera, double speed);

// Function to set the camera speed in the y-axis.
void set_camera_side_speed(Camera* camera, double speed);

// Function to set the camera speed in the z-axis.
void set_camera_vertical_speed(Camera* camera, double speed);

#endif
