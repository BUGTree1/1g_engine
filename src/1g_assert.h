#pragma once
#ifndef __1G_ASSERT_H__
#define __1G_ASSERT_H__

#include "common.h"
#include "log.h"

namespace e1g {

template<typename T>
void errorz(T v, std::string str) {
    if (v == 0) {
        error(str);
    }
}

template<typename T>
void errornz(T v, std::string str) {
    if (v != 0) {
        error(str);
    }
}

}

#endif //__1G_ASSERT_H__