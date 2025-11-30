#pragma once
#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <SDL3/SDL.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

// ---------------------
//  Logging
// \/-------------------

void error(std::string msg);
void warning(std::string msg);
void todo(std::string msg);

#endif //__UTILS_H__