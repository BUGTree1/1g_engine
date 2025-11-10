#include "1g.h"

GameObject* get_gameobject(Scene* scene, size_t idx){
    return &scene->gameobjects.items[idx];
}

Component* get_component(GameObject* gameobject, size_t idx){
    return &gameobject->components.items[idx];
}