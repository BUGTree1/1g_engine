#include "renderer.h"
#include "1g.h"
#include "SDL3/SDL_render.h"
#include "utils.h"

using namespace std;

void set_best_renderer_driver(SDL_Window* window) {
    //printf("Available renderers:\n");

    int renderers_count = SDL_GetNumRenderDrivers();

    set<string> renderer_names;

    for (int i = 0; i < renderers_count; i++) {
        string name = SDL_GetRenderDriver(i);
        renderer_names.emplace(name);

        //printf("%d: %s\n", i, name);
    }

    if(renderer_names.find("direct3d11") != renderer_names.end()){
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d11");
    }else if(renderer_names.find("direct3d12") != renderer_names.end()){
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d12");
    }else if(renderer_names.find("direct3d") != renderer_names.end()){
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d");
    }else if(renderer_names.find("metal") != renderer_names.end()){
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");
    }else if(renderer_names.find("opengl") != renderer_names.end()){
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    }else{
        error("Couldn't find supported SDL driver!");
    }
}

renderer_data renderer_init(Scene* scene) {
    renderer_data data = {0, 0, 800, 600};

    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window* window = SDL_CreateWindow("1G Engine", data.width, data.height, SDL_WINDOW_RESIZABLE);

    set_best_renderer_driver(window);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    
    data.window = window;
    data.renderer = renderer;
    data.scene = scene;
    
    return data;
}

void renderer_update(renderer_data data){
    GameObject* go = &data.scene->gameobjects[0];
    Transform* transform = (Transform*)go->components[0].data;
    Mesh* mesh = (Mesh*)go->components[1].data;

    float size = 100.0f;
    float speed = 2.0f;
    vec3 center = {data.width / 2.0f, data.height / 2.0f, 0.0f};

    vec3 p1 = { -size , -size };
    vec3 p2 = { 0.0f  , size  };
    vec3 p3 = { size  , -size };

    float* p1r = rotate_3d_z(p1, data.time * speed);
    float* p2r = rotate_3d_z(p2, data.time * speed);
    float* p3r = rotate_3d_z(p3, data.time * speed);

    p1r = rotate_3d_y(p1r, data.time * speed);
    p2r = rotate_3d_y(p2r, data.time * speed);
    p3r = rotate_3d_y(p3r, data.time * speed);

    p1r = rotate_3d_x(p1r, data.time * speed);
    p2r = rotate_3d_x(p2r, data.time * speed);
    p3r = rotate_3d_x(p3r, data.time * speed);

    mesh->vertices = (SDL_Vertex[]){
        { { center[0] + p1r[0], center[1] + p1r[1] }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
        { { center[0] + p2r[0], center[1] + p2r[1] }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
        { { center[0] + p3r[0], center[1] + p3r[1] }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } }
    };
    
    SDL_SetRenderDrawColor(data.renderer, 0, 0, 0, 255);
    SDL_RenderClear(data.renderer);
    SDL_RenderGeometry(data.renderer, NULL, mesh->vertices, 3, NULL, 0);
    SDL_RenderPresent(data.renderer);
}

void renderer_end(renderer_data data){
    SDL_DestroyRenderer(data.renderer);
    SDL_DestroyWindow(data.window);
    SDL_Quit();
}