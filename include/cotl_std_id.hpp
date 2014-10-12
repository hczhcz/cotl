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

        // pair
        id_pair  = IDX_TYPE + 96,

        // str
        id_str   = IDX_TYPE + 112,

        // arr
        id_arr   = IDX_TYPE + 128,
        id_stack,
        id_code, // code list

        // map
        id_map   = IDX_TYPE + 144,

        // special
        id_error = IDX_TYPE + 160,
            // members
            id_error_self,
            id_error_caller,
            id_error_lib,
            id_error_tunnel,
            id_error_func,
            id_error_detail,

        // override packages

        id_type_wrap = IDX_TYPE + 176,
        id_type_lib,
        id_type_misc
};

template <class T> struct DefaultId {};
template <> struct DefaultId<cotl::Atom> {static const int_t get = id_atom;};
template <> struct DefaultId<cotl::Int>  {static const int_t get = id_int;};
template <> struct DefaultId<cotl::Real> {static const int_t get = id_real;};
template <> struct DefaultId<cotl::Func> {static const int_t get = id_func;};
template <> struct DefaultId<cotl::Ptr>  {static const int_t get = id_ptr;};
template <> struct DefaultId<cotl::Pair> {static const int_t get = id_pair;};
template <> struct DefaultId<cotl::Str>  {static const int_t get = id_str;};
template <> struct DefaultId<cotl::Arr>  {static const int_t get = id_arr;};
template <> struct DefaultId<cotl::Map>  {static const int_t get = id_map;};

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
            id_blackhole,
            id_container,

            id_const,
            id_target,
            id_ref,

            id_before,
            id_after,
            id_also,

            id_void,
            id_exec,
            id_write,
            id_iftunnel,

            id_try,

        id_cast,

        id_dispatch,

        id_query,
            id_use,
            id_with,
            id_withnew,
            id_capture,

            id_def,
            id_quickdef,

            // members
            id_caller,
            id_global,

        id_math,
            id_add, // TODO: both int and real (auto detect)
            id_sub,
            id_mul,
            id_div,
            id_mod,
            id_rsub,
            id_rdiv,
            id_rmod,

            id_math_int,
                // override: add, sub, mul, div, ... // TODO

            id_math_real,
                // override: add, sub, mul, div, ... // TODO

        id_structural,
            id_ifthen, // or use switch+map[bool]?
            id_for,
            id_forin,
            id_foreach,
            id_while,
            id_until,

        id_call, // func(), call, closure, etc

        id_bool,
            //

            // TODO
            id_bool_int, // bitand, bitor, etc

        id_strutil,

        id_arrutil,

        id_maputil,

        id_compare,

        id_hash,

        // id_container, // rename

        id_meta,

        id_io, // time / file / console

        id_regex
};

const char *getTypeName(const int_t type);

}

}

#endif
