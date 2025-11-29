#include "1g.h"
#include "SDL3/SDL_events.h"
#include "renderer.h"

using namespace std;

int main(int argc, char** argv) {
	Scene scene = Scene();

    scene.gameobjects.push_back(GameObject());

    scene.gameobjects[0].components.push_back(Component());
    scene.gameobjects[0].components[0].type = 0;
    scene.gameobjects[0].components[0].data = new Transform;

    scene.gameobjects[0].components.push_back(Component());
    scene.gameobjects[0].components[1].type = 1;
    scene.gameobjects[0].components[1].data = new Mesh;

	renderer_data rend_data = renderer_init(&scene);
	renderer_update(rend_data);

    double last_time = 0;
    double current_time = 0;
    SDL_Event event;
	int running = 1;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = 0;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) running = 0;
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