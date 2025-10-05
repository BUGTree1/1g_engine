#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <stdio.h>
#include <stdbool.h>
#include "utils.h"

typedef struct {
    SDL_Vertex* vertices;
} draw_data;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;

    int width;
    int height;

    double fps;
    double delta_time;
    double time;

    draw_data draw;
} renderer_data;

renderer_data renderer_init();
void renderer_update(renderer_data data);
void renderer_end(renderer_data data);

#endif //__RENDERER_H__