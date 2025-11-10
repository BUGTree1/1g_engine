#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "1g.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;

    int width;
    int height;

    double fps;
    double delta_time;
    double time;

    Scene* scene;
} renderer_data;

renderer_data renderer_init(Scene* scene);
void renderer_update(renderer_data data);
void renderer_end(renderer_data data);

#endif //__RENDERER_H__