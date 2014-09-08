#ifndef _COTL_NEW_HPP
#define _COTL_NEW_HPP

#include "cotl_helper.hpp"

namespace cotl {

inline
namespace published {

Atom *_atom(
    const int_t type = id_atom, const func_t func = stdAuto, PValRaw reused = nullptr
);

Int *_int(const int_t &data,
    const int_t type = id_int, const func_t func = stdAuto, PValRaw reused = nullptr
);

Real *_real(const real_t &data,
    const int_t type = id_real, const func_t func = stdAuto, PValRaw reused = nullptr
);

Func *_func(const func_t &data,
    const int_t type = id_func, const func_t func = stdAuto, PValRaw reused = nullptr
);

Ptr *_ptr(const PVal &data,
    const int_t type = id_ptr, const func_t func = stdAuto, PValRaw reused = nullptr
);

Pair *_pair(const PVal &data1, const PVal &data2,
    const int_t type = id_pair, const func_t func = stdAuto, PValRaw reused = nullptr
);

Str *_str(const std::string &data,
    const int_t type = id_str, const func_t func = stdAuto, PValRaw reused = nullptr
);

Arr *_arr_m(arr_t &&container,
    const int_t type = id_arr, const func_t func = stdAuto, PValRaw reused = nullptr
);

Map *_map_m(map_t &&container,
    const int_t type = id_map, const func_t func = stdAuto, PValRaw reused = nullptr
);

// data construction

template <class... Args>
inline Arr *_arr_m(arr_t &&container,
    const PVal &value, const Args... args /* values */
) {
    container->push_back(value);

    return _arr_m(std::move(container), args...);
}

template <class... Args>
inline Arr *_arr(
    const Args... args /* values */
) {
    return _arr_m(arr_t(_COTL_RAWNEW(arr_t::element_type())), args...);
}

template <class... Args>
inline Map *_map_m(map_t &&container,
    const int_t key, const PVal &value, const Args... args /* (key, value) loop */
) {
    container->insert({{key, value}});

    return _map_m(std::move(container), args...);
}

template <class... Args>
inline Map *_map(
    const Args... args /* (key, value) loop */
) {
    return _map_m(map_t(_COTL_RAWNEW(map_t::element_type())), args...);
}

// alias to "lib" types

template <class... Args>
inline Func *_libfunc(
    const Args... args
) {
    return _func(args..., id_func, stdLibFunc);
}

template <class... Args>
inline Map *_libmap(
    const Args... args
) {
    return _map(args..., id_map, stdLibMap);
}

}

}

#endif
