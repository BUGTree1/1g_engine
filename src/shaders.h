#pragma once
#ifndef __SHADERS_H__
#define __SHADERS_H__

namespace e1g {

static const char* vertex_shader_text = 
R"MS(
#version 460 core
in vec3 vCol;
in vec3 vPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
out vec3 color;
void main()
{
    gl_Position = proj * view * model * vec4(vPos, 1.0);
    color = vCol;
}
)MS";
 
static const char* fragment_shader_text =
R"MS(
#version 460 core
in vec3 color;
out vec4 fragment;
void main()
{
    fragment = vec4(color, 1.0);
};
)MS";

}

#endif //__SHADERS_H__