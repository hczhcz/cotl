#ifndef _COTL_ID_HPP
#define _COTL_ID_HPP

#include "cotl_helper.hpp"

namespace cotl {

inline
namespace published {

enum {
    // the range of id
    IDX_BASE = -2333333,
    IDX_TOP = 0
};

enum {
    // special
    IDX_UNDEF      = IDX_BASE + 1,

    // std lib

    // types (int, real, arr, stack, null, true etc.)
    IDX_TYPE       = IDX_BASE + 23,
    IDX_TYPE_TOP   = IDX_BASE + 232,
    // core functions
    IDX_CORE       = IDX_BASE + 233,
    IDX_CORE_TOP   = IDX_BASE + 2332,
    // library functions
    IDX_LIB        = IDX_BASE + 2333,
    IDX_LIB_TOP    = IDX_BASE + 23332,

    // non-std

    // user-defined native types / functions
    IDX_NATIVE     = IDX_BASE + 23333,
    IDX_NATIVE_TOP = IDX_BASE + 233332,
    // user-defined values in cotl code
    IDX_USER       = IDX_BASE + 233333,
    IDX_USER_TOP   = IDX_BASE + 2333332
};

const char *getTypeName(const int_t type);

}

}

#endif
