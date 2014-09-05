#ifndef _COTL_STD_ID_HPP
#define _COTL_STD_ID_HPP

#include "cotl_helper.hpp"

namespace cotlstd {

enum {
    // the range of id
    IDX_BASE = -2333333,
    IDX_TOP = 0
};

enum {
    // std lib

    // types (int, real, arr, stack, null, true etc.)
    IDX_TYPE        = IDX_BASE + 23,
    IDX_TYPE_TOP    = IDX_BASE + 232,
    // core functions
    IDX_RUNTIME     = IDX_BASE + 233,
    IDX_RUNTIME_TOP = IDX_BASE + 2332,
    // library functions
    IDX_FUNC        = IDX_BASE + 2333,
    IDX_FUNC_TOP    = IDX_BASE + 23332,

    // non-std

    // user-defined native types / functions
    IDX_NATIVE      = IDX_BASE + 23333,
    IDX_NATIVE_TOP  = IDX_BASE + 233332,
    // user-defined values in cotl code
    IDX_USER        = IDX_BASE + 233333,
    IDX_USER_TOP    = IDX_BASE + 2333332
};

inline
namespace published {

enum {
    // atom
    id_atom = IDX_TYPE,
    id_null,

    // int
    id_int  = IDX_TYPE + 16,
    id_increment,
    id_decrement,

    // real
    id_real = IDX_TYPE + 32,

    // func
    id_func = IDX_TYPE + 48,
    id_libfunc,

    // ptr
    id_ptr  = IDX_TYPE + 64,
    id_wrapptr,
    id_refptr,

    // pair
    id_pair = IDX_TYPE + 80,
    id_wrappair,

    // str
    id_str  = IDX_TYPE + 96,

    // arr
    id_arr  = IDX_TYPE + 112,
    id_wraparr,
    id_stack,

    // map
    id_map  = IDX_TYPE + 128,
    id_wrapmap,
    id_libmap,

    // special
    id_error = IDX_TYPE + 144
};

enum {
    // atom
    ID_NULLARY = IDX_RUNTIME,
    id_false,
    id_true,

    // ptr
    ID_UNARY   = IDX_RUNTIME + 256,
    id_quote,
    id_contain,

    // pair
    ID_BINARY  = IDX_RUNTIME + 512,

    // any
    id_VARARY  = IDX_RUNTIME + 768,
    id_auto,
    id_literal,
    id_bind
};

}

}

#endif
