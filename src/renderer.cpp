#include "renderer.h"
#include "log.h"

using namespace std;
using namespace glm;

namespace e1g {

void set_best_renderer_driver(SDL_Window* window) {
    //printf("Available renderers:\n");

    int renderers_count = SDL_GetNumRenderDrivers();

    set<string> renderer_names;

    for (int i = 0; i < renderers_count; i++) {
        string name = SDL_GetRenderDriver(i);
        renderer_names.emplace(name);

        //cout << i << " : " << name << endl;
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
    }else if(renderer_names.find("opengles2") != renderer_names.end()){
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengles2");
    }else{
        SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
        warning("Couldn't find supported SDL driver rendering in software mode!");
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
    SDL_SetRenderDrawColor(data.renderer, 0, 0, 0, 255);
    SDL_RenderClear(data.renderer);

    for (int i = 0; i < data.scene->gameobjects.size(); i++) {
        for (int j = 0; j < data.scene->gameobjects[i]->components.size(); j++) {
            data.scene->gameobjects[i]->components[j]->render(&data);
        }
    }

    SDL_SetRenderDrawColor(data.renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(data.renderer, 0, 0, ("FPS: " + to_string(data.fps)).c_str());
    SDL_RenderPresent(data.renderer);
}

void renderer_end(renderer_data data){
    SDL_DestroyRenderer(data.renderer);
    SDL_DestroyWindow(data.window);
    SDL_Quit();
}

}