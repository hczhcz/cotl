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

inline
namespace published {

enum {
    id_type = IDX_TYPE,

        // atom
        id_atom  = IDX_TYPE + 16,
        id_null,
        id_false,
        id_true,

        // int
        id_int   = IDX_TYPE + 32,
        id_increment,
        id_decrement,

        // real
        id_real  = IDX_TYPE + 48,

        // func
        id_func  = IDX_TYPE + 64,

        // ptr
        id_ptr   = IDX_TYPE + 80,
        id_refptr,

        // pair
        id_pair  = IDX_TYPE + 96,

        // str
        id_str   = IDX_TYPE + 112,

        // arr
        id_arr   = IDX_TYPE + 128,
        id_stack,

        // map
        id_map   = IDX_TYPE + 144,

        // special
        id_error = IDX_TYPE + 160,

        // override packages

        id_type_wrap = IDX_TYPE + 176,
        id_type_lib,
        id_type_misc
};

enum {
    id_std = IDX_CORE,
        // id_type,
            // <types> // value: aliases

            // id_type_wrap,
                // override: base types except error

            // id_type_lib,
                // override: func, map

            // id_type_misc,
                // override: non-base types

        id_runtime,
            id_auto,
            id_literal,
            id_bind,
            id_quote,
            id_contain,
            // working:
            id_with,
            id_write,

        id_dispatch, // TODO: dispatch // or casting
            //

        id_math,
            id_add, // TODO: both int and real (auto detect)
            id_sub,
            id_mul,
            id_div,

            id_math_int,
                // override: add, sub, mul, div
                id_mod,

            id_math_real,
                // override: add, sub, mul, div

        id_bool,
            //

            // TODO
            id_bool_int, // bitand, bitor, etc

        id_strutil,

        id_arrutil,

        id_maputil,

        id_call, // func(), call, closure, etc

        id_compare,

        id_hash,

        id_container,

        id_branch, // if, switch

        id_loop, // for, while, etc

        id_meta,

        id_io, // time / file / console

        id_regex
};

}

}

#endif
