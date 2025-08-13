#pragma once
#ifndef __1G_PLATFORM_H__
#define __1G_PLATFORM_H__

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include "1g_windows.h"
#else
#include "1g_posix.h"
#endif

#endif //__1G_PLATFORM_H__