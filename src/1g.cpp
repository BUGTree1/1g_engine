#include "1g.h"

namespace e1g {

using namespace std;
using namespace glm;

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

    vec3 p1 = vec3( -size , -size , 0.0f);
    vec3 p2 = vec3( 0.0f  , size  , 0.0f);
    vec3 p3 = vec3( size  , -size , 0.0f);

    mat4 rotate_x_mat = glm::rotate(mat4(1.0f), (float)data->time * speed, vec3(1.0f, 0.0f, 0.0f));
    mat4 rotate_y_mat = glm::rotate(mat4(1.0f), (float)data->time * speed, vec3(0.0f, 1.0f, 0.0f));
    mat4 rotate_z_mat = glm::rotate(mat4(1.0f), (float)data->time * speed, vec3(0.0f, 0.0f, 1.0f));

    p1 = vec3(rotate_x_mat * vec4(p1, 1.0f));
    p2 = vec3(rotate_x_mat * vec4(p2, 1.0f));
    p3 = vec3(rotate_x_mat * vec4(p3, 1.0f));

    p1 = vec3(rotate_y_mat * vec4(p1, 1.0f));
    p2 = vec3(rotate_y_mat * vec4(p2, 1.0f));
    p3 = vec3(rotate_y_mat * vec4(p3, 1.0f));

    p1 = vec3(rotate_z_mat * vec4(p1, 1.0f));
    p2 = vec3(rotate_z_mat * vec4(p2, 1.0f));
    p3 = vec3(rotate_z_mat * vec4(p3, 1.0f));

    mesh->vertices = (vector<SDL_Vertex>){
        { { center[0] + p1.x, center[1] + p1.y }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
        { { center[0] + p2.x, center[1] + p2.y }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
        { { center[0] + p3.x, center[1] + p3.y }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } }
    };

    SDL_RenderGeometry(data->renderer, NULL, &mesh->vertices[0], 3, NULL, 0);
}

}