#include <stdio.h>
#include <stdbool.h>
#include "platform/1g_platform.h"
#include "utils.h"

#define DEBUG_FPS

void debug_fps(double);
#ifdef DEBUG_FPS
#define FPS_INTERVAL 100
size_t fps_count = 0;
double FPS_avg_arr[FPS_INTERVAL];
double FPS_avg = 0.0f;

#undef debug_fps
void debug_fps(double delta_time){
	if(fps_count > FPS_INTERVAL) {
		fps_count = 0;
		FPS_avg = 0;
		for (size_t i = 0; i < FPS_INTERVAL; i++) {
			FPS_avg += FPS_avg_arr[i];
		}
		FPS_avg /= FPS_INTERVAL;
		
		printf("FPS: %f\n", FPS_avg);
	}else{
		FPS_avg_arr[fps_count] = (1 / delta_time);
		fps_count++;
	}
}
#else
void debug_fps(double){

}
#endif

int main(int, char **) {
	debug_fps(1);
	return 0;
}