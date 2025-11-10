#include "1g.h"
#define NOB_IMPLEMENTATION
#include "renderer.h"


int main(int argc, char** argv) {
	Scene* scene = (Scene*)malloc(sizeof(Scene));

    da_append(&scene->gameobjects, (GameObject){0});

    da_append(&get_gameobject(scene, 0)->components, (Component){0});
    get_component(get_gameobject(scene, 0), 0)->type = 0;
    get_component(get_gameobject(scene, 0), 0)->data = &(Transform){0};

    da_append(&get_gameobject(scene, 0)->components, (Component){0});
    get_component(get_gameobject(scene, 0), 1)->type = 1;
    get_component(get_gameobject(scene, 0), 1)->data = &(Mesh){0};

	renderer_data rend_data = renderer_init(scene);
	renderer_update(rend_data);

    double last_time = 0;
    double current_time = 0;
    SDL_Event event;
	int running = 1;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) running = 0;
        }
		SDL_GetWindowSizeInPixels(rend_data.window,&rend_data.width,&rend_data.height);

		renderer_update(rend_data);
        
        current_time = (double)SDL_GetPerformanceCounter() / (double)SDL_GetPerformanceFrequency();
		rend_data.delta_time = current_time - last_time;
		rend_data.fps = 1.0 / rend_data.delta_time;
		last_time = current_time;
		rend_data.time = current_time;
    }
	renderer_end(rend_data);
	return 0;
}