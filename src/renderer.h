#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "1g.h"

namespace e1g {

class Renderer {
public:
    Render_Data* data;
    Scene* scene;

    void init(Scene* scene);
    void update();
    void end();
};

}

#endif //__RENDERER_H__