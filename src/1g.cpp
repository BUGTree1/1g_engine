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

    vec3 p1 = vec3( 0.0f,  0.5f, 0.0f);
    vec3 p2 = vec3( 0.5f, -0.5f, 0.0f);
    vec3 p3 = vec3(-0.5f, -0.5f, 0.0f);

    float mouse_speed = 8.0f * data->delta_time;
    float cam_speed = 8.0f * data->delta_time;

    data->cam_rot.x += data->mouse_vel.y * mouse_speed;
    data->cam_rot.y += data->mouse_vel.x * mouse_speed;
    
    mat4 rotate_mat = eulerAngleXYZ(data->cam_rot.x, data->cam_rot.y, data->cam_rot.z);
    vec3 cam_forward = vec3(vec4(0.0f,0.0f,1.0f,1.0f) * rotate_mat);
    vec3 cam_up      = vec3(vec4(0.0f,1.0f,0.0f,1.0f) * rotate_mat);
    vec3 cam_right   = vec3(vec4(1.0f,0.0f,0.0f,1.0f) * rotate_mat);

    if(glfwGetKey(data->window, GLFW_KEY_W)){
        data->cam_pos += cam_forward * cam_speed;
    }
    if(glfwGetKey(data->window, GLFW_KEY_S)){
        data->cam_pos -= cam_forward * cam_speed;
    }
    if(glfwGetKey(data->window, GLFW_KEY_A)){
        data->cam_pos += cam_right * cam_speed;
    }
    if(glfwGetKey(data->window, GLFW_KEY_D)){
        data->cam_pos -= cam_right * cam_speed;
    }
    if(glfwGetKey(data->window, GLFW_KEY_SPACE)){
        data->cam_pos -= cam_up * cam_speed;
    }
    if(glfwGetKey(data->window, GLFW_KEY_LEFT_SHIFT)){
        data->cam_pos += cam_up * cam_speed;
    }

    mat4 translate_mat = translate(mat4(1.0f), data->cam_pos);

    mat4 model_mat = mat4(1.0f);
    mat4 view_mat = rotate_mat * translate_mat;
    mat4 proj_mat = perspective(radians(45.0f), data->window_aspect_ratio, 0.1f, 100.0f);

    mesh->vertices = (vector<Vertex>){
        (Vertex){p1, vec3(1.0f, 0.0f, 0.0f)},
        (Vertex){p2, vec3(0.0f, 1.0f, 0.0f)},
        (Vertex){p3, vec3(0.0f, 0.0f, 1.0f)}
    };

    glUseProgram(data->program);

    glUniformMatrix4fv(data->proj_loc, 1, GL_FALSE, value_ptr(proj_mat));
    glUniformMatrix4fv(data->view_loc, 1, GL_FALSE, value_ptr(view_mat));
    glUniformMatrix4fv(data->model_loc, 1, GL_FALSE, value_ptr(model_mat));

    glBindVertexArray(data->vao);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex), &mesh->vertices[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, data->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data->ebo);
    glBindVertexArray(data->vao);
    glDrawElements(GL_TRIANGLES, 3,  GL_UNSIGNED_INT, NULL);
}

}