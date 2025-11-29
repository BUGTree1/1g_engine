#include "1g.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_thread.h"

using namespace std;

GameObject::GameObject(){
    components = vector<Component*>();
}
GameObject::GameObject(std::vector<Component*> comps){
    components = comps;
}
void GameObject::add_component(Component comp){
    components.push_back(&comp);
}
void GameObject::add_component(Component* comp){
    components.push_back(comp);
}

Scene::Scene(){
    gameobjects = vector<GameObject*>();
}
Scene::Scene(std::vector<GameObject*> gos){
    gameobjects = gos;
}
void Scene::add_gameobject(GameObject go){
    gameobjects.push_back(&go);
}
void Scene::add_gameobject(GameObject* go){
    gameobjects.push_back(go);
}


Mesh_Renderer::Mesh_Renderer(){
    mesh = new Mesh;
    mesh->vertices = vector<SDL_Vertex>();
};

void Mesh_Renderer::render(renderer_data* data) {
    GameObject* go = data->scene->gameobjects[0];
    Transform* transform = (Transform*)go->components[0];
    Mesh_Renderer* mesh_renderer = (Mesh_Renderer*)go->components[1];
    Mesh* mesh = mesh_renderer->mesh;

    float size = 100.0f;
    float speed = 2.0f;
    vec3 center = {data->width / 2.0f, data->height / 2.0f, 0.0f};

    vec3 p1 = { -size , -size };
    vec3 p2 = { 0.0f  , size  };
    vec3 p3 = { size  , -size };

    float* p1r = rotate_3d_z(p1, data->time * speed);
    float* p2r = rotate_3d_z(p2, data->time * speed);
    float* p3r = rotate_3d_z(p3, data->time * speed);

    p1r = rotate_3d_y(p1r, data->time * speed);
    p2r = rotate_3d_y(p2r, data->time * speed);
    p3r = rotate_3d_y(p3r, data->time * speed);

    p1r = rotate_3d_x(p1r, data->time * speed);
    p2r = rotate_3d_x(p2r, data->time * speed);
    p3r = rotate_3d_x(p3r, data->time * speed);

    mesh->vertices = (vector<SDL_Vertex>){
        { { center[0] + p1r[0], center[1] + p1r[1] }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
        { { center[0] + p2r[0], center[1] + p2r[1] }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
        { { center[0] + p3r[0], center[1] + p3r[1] }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } }
    };

    SDL_RenderGeometry(data->renderer, NULL, &mesh->vertices[0], 3, NULL, 0);
}