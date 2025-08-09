#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define UNUSED(v) (void)(v)

#define DEBUG_FPS

#ifdef DEBUG_FPS
#define FPS_INTERVAL 10000
size_t fps_count = 0;
double FPS_avg_arr[FPS_INTERVAL];
double FPS_avg = 0.0f;
#endif

void debug_fps(SDL_Renderer* renderer, double delta_time){
	#ifdef DEBUG_FPS
	if(fps_count > FPS_INTERVAL) {
		fps_count = 0;
		FPS_avg = 0;
		for (size_t i = 0; i < FPS_INTERVAL; i++) {
			FPS_avg += FPS_avg_arr[i];
		}
		FPS_avg /= FPS_INTERVAL;
	}else{
		FPS_avg_arr[fps_count] = (1 / delta_time);
		fps_count++;
	}

	SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
	SDL_RenderDebugTextFormat(renderer,0.0f,0.0f,"FPS: %f", FPS_avg);
	#else
	UNUSED(renderer);
	UNUSED(delta_time);
	#endif
}

int main(int argc, char *argv[]) {
	UNUSED(argc);
	UNUSED(argv);

	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Window* window = SDL_CreateWindow("1G Engine", 800, 480, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window,"direct3d11");

	Uint64 time_start = SDL_GetPerformanceCounter();
	Uint64 time_end = SDL_GetPerformanceCounter();

	bool stop = false;
	while(!stop) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_EVENT_QUIT:
					stop = true;
				break;
			
				default:
				break;
			}
		}

		time_end = SDL_GetPerformanceCounter();
		Uint64 delta_time_uint = time_end - time_start;
		double delta_time = (double)delta_time_uint / (double)SDL_GetPerformanceFrequency();
		time_start = time_end;

		SDL_SetRenderDrawColor(renderer,0x18,0x44,0x22,0xFF);
		SDL_RenderClear(renderer);

		debug_fps(renderer,delta_time);

		// test 3d

		SDL_RenderPresent(renderer);
	}
	
	SDL_Quit();
	return 0;
}