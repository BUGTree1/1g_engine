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
    std::vector<Component> components;
} GameObject;

typedef struct {
    std::vector<GameObject> gameobjects;
} Scene;

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

//Mesh* load_obj(string path);

#endif // __1G_H__