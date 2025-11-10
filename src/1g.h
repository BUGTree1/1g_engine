#ifndef __1G_H__
#define __1G_H__

#include "utils.h"

// ---------------------
//  Common types
// \/-------------------

typedef struct {
    size_t type;
    void* data;
} Component;

typedef struct {
    dynamic_array(Component) components;
} GameObject;

typedef struct {
    dynamic_array(GameObject) gameobjects;
} Scene;

GameObject* get_gameobject(Scene* scene, size_t idx);
Component* get_component(GameObject* gameobject, size_t idx);

// ---------------------
//  Common components
// \/-------------------

typedef struct {
    vec3 position;
    vec3 rotation;
    vec3 scale;
} Transform;

typedef struct {
    SDL_Vertex* vertices;
} Mesh;

// ---------------------
//  Meshes
// \/-------------------

Mesh* load_mesh(const char* path);

// ---------------------
//  Meshes
// \/-------------------

#endif // __1G_H__