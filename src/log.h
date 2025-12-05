#pragma once
#ifndef __LOG_H__
#define __LOG_H__

#include "common.h"

namespace e1g {

// ---------------------
//  Logging
// \/-------------------

void error(std::string msg, int error_code = 1);
void warning(std::string msg);
void todo(std::string msg);

}

#endif //__LOG_H__