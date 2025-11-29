#pragma once
#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <SDL3/SDL.h>
#include <cglm/cglm.h>

// ---------------------
//  3d Math
// \/-------------------

float* rotate_3d_x(vec3 p, float angle);
float* rotate_3d_y(vec3 p, float angle);
float* rotate_3d_z(vec3 p, float angle);


// ---------------------
//  Logging
// \/-------------------

void error(std::string msg);
void warning(std::string msg);
void todo(std::string msg);

#endif //__UTILS_H__