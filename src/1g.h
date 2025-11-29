#ifndef __1G_H__
#define __1G_H__

#include "utils.h"

// ---------------------
//  Common types
// \/-------------------

struct renderer_data;
struct GameObject;

class Component {
public:
    GameObject* gameobject;
    virtual void update(renderer_data* data) {};
    virtual void render(renderer_data* data) {};
};

struct Scene;

class GameObject {
public:
    Scene* scene;
    std::vector<Component*> components;
    GameObject();
    GameObject(std::vector<Component*> comps);

    void add_component(Component comp);
    void add_component(Component* comp);
};

class Scene {
public:
    std::vector<GameObject*> gameobjects;
    Scene();
    Scene(std::vector<GameObject*> gos);

    void add_gameobject(GameObject go);
    void add_gameobject(GameObject* go);
};

struct renderer_data {
    SDL_Window* window;
    SDL_Renderer* renderer;

    int width;
    int height;

    double fps;
    double delta_time;
    double time;

    Scene* scene;
};

// ---------------------
//  Common components
// \/-------------------

class Transform : public Component {
public:
    vec3 position;
    vec3 rotation;
    vec3 scale;
};

struct Mesh {
    std::vector<SDL_Vertex> vertices;
};

class Mesh_Renderer : public Component {
public:
    Mesh_Renderer();
    
    Mesh* mesh;
    void render(renderer_data* data) override;
};

// ---------------------
//  Meshes
// \/-------------------

//Mesh* load_obj(string path);

#endif // __1G_H__