#ifndef _COTL_ID_HPP
#define _COTL_ID_HPP

#include "cotl_helper.hpp"

namespace cotl {

enum {
    // std lib

    // types (int, real, arr, stack, null, true etc.)
    IDX_TYPE = 23,
    // core functions
    IDX_RUNTIME =233,
    // library functions
    IDX_FUNC = 2333,

    // non-std

    // user-defined native types / functions
    IDX_NATIVE = 23333,
    // user-defined values in cotl
    IDX_USER = 233333
};

enum {
    // atom
    id_atom = IDX_TYPE,
    id_null,
    id_false,
    id_true,

    // int
    id_int = IDX_TYPE + 16,
    id_increase,
    id_decrease,

    // real
    id_real = IDX_TYPE + 32,

    // str
    id_str = IDX_TYPE + 48,

    // arr
    id_arr = IDX_TYPE + 64,
    id_stack,

    // ptr
    id_ptr = IDX_TYPE + 80,

    // pair
    id_pair = IDX_TYPE + 96
};

enum {
    id_exec = IDX_RUNTIME,
    id_lock
};

}

#endif
