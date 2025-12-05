#ifndef __1G_H__
#define __1G_H__

#include "common.h"

namespace e1g {

// ---------------------
//  Common types
// \/-------------------

struct Vertex {
    glm::vec3 pos;
    glm::vec3 col;
};

struct Render_Data {
    GLFWwindow* window;

    int width;
    int height;

    double fps;
    double delta_time;
    double time;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;
};

class GameObject;

class Component {
public:
    GameObject* gameobject;
    virtual void update() {};
    virtual void render(Render_Data* data) {};
};

class Scene;

class GameObject {
public:
    Scene* scene;
    std::vector<Component*> components;
    GameObject();
    GameObject(std::vector<Component*> comps);

    void add_component(Component* comp);
};

class Scene {
public:
    std::vector<GameObject*> gameobjects;
    Scene();
    Scene(std::vector<GameObject*> gos);

    void add_gameobject(GameObject* go);
};

// ---------------------
//  Common components
// \/-------------------

class Transform : public Component {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

struct Mesh {
    std::vector<Vertex> vertices;
};

class Mesh_Renderer : public Component {
public:
    Mesh_Renderer();
    
    Mesh* mesh;
    void render(Render_Data* data) override;
};

// ---------------------
//  Meshes
// \/-------------------

//Mesh* load_obj(string path);

}

#endif // __1G_H__