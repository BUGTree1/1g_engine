#include "1g.h"

namespace e1g {

using namespace std;
using namespace glm;

GameObject::GameObject(){
    components = vector<Component*>();
}
GameObject::GameObject(std::vector<Component*> comps){
    for (int i = 0; i < comps.size(); i++) {
        comps[i]->gameobject = this;
    }
    components = comps;
}

void GameObject::add_component(Component* comp){
    comp->gameobject = this;
    components.push_back(comp);
}

Scene::Scene(){
    gameobjects = vector<GameObject*>();
}
Scene::Scene(std::vector<GameObject*> gos){
    for (int i = 0; i < gos.size(); i++) {
        gos[i]->scene = this;
    }
    gameobjects = gos;
}

void Scene::add_gameobject(GameObject* go){
    go->scene = this;
    gameobjects.push_back(go);
}


Mesh_Renderer::Mesh_Renderer(){
    mesh = new Mesh;
    mesh->vertices = vector<Vertex>();
};

void Mesh_Renderer::render(Render_Data* data) {
    Transform* transform = (Transform*)gameobject->components[0];
    Mesh_Renderer* mesh_renderer = (Mesh_Renderer*)gameobject->components[1];
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

    mesh->vertices = (vector<Vertex>){
        { {center[0] + p1.x, center[1] + p1.y, 0.0f}, {1.0f, 0.0f, 0.0f} },
        { {center[0] + p2.x, center[1] + p2.y, 0.0f}, {0.0f, 1.0f, 0.0f} },
        { {center[0] + p3.x, center[1] + p3.y, 0.0f}, {0.0f, 0.0f, 1.0f} }
    };

    //glBindVertexArray(data->vertex_array);
    //glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex), &mesh->vertices[0], GL_DYNAMIC_DRAW);

    glBindVertexArray(data->vertex_array);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

}