#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "1g.h"

namespace e1g {

renderer_data renderer_init(Scene* scene);
void renderer_update(renderer_data data);
void renderer_end(renderer_data data);

}

#endif //__RENDERER_H__