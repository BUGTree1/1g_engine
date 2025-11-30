#pragma once
#ifndef __LOG_H__
#define __LOG_H__

#include "common.h"

// ---------------------
//  Logging
// \/-------------------

void error(std::string msg);
void warning(std::string msg);
void todo(std::string msg);

#endif //__LOG_H__