#ifndef _COTL_NEW_HPP
#define _COTL_NEW_HPP

#include "cotl_helper.hpp"

namespace cotl {

inline Atom *_atom(
    const int_t type = id_atom, const func_t func = autotype, PValRaw reused = nullptr
) {
    return new (reused) Atom(type, func);
}

inline Int *_int(const int_t &data,
    const int_t type = id_int, const func_t func = autotype, PValRaw reused = nullptr
) {
    return new (reused) Int(data, type, func);
}

inline Real *_real(const real_t &data,
    const int_t type = id_real, const func_t func = autotype, PValRaw reused = nullptr
) {
    return new (reused) Real(data, type, func);
}

inline Func *_func(const func_t &data,
    const int_t type = id_func, const func_t func = autotype, PValRaw reused = nullptr
) {
    return new (reused) Func(data, type, func);
}

inline Ptr *_ptr(const PVal &data,
    const int_t type = id_ptr, const func_t func = autotype, PValRaw reused = nullptr
) {
    return new (reused) Ptr(data, type, func);
}

inline Str *_str(const std::string &data,
    const int_t type = id_str, const func_t func = autotype, PValRaw reused = nullptr
) {
    return new (reused) Str(data, type, func);
}

inline Arr *_arr(
    const int_t type = id_arr, const func_t func = autotype, PValRaw reused = nullptr
) {
    Arr *result = new (reused) Arr(type, func);

    // note: global --GC-> Val --RAII-> ptr --RAII-> map --GCalloc--> map data
    result->getVar() = map_t(new map_t::element_type());

    return result;
}

template <class... Args>
Arr *_arr(const int_t key, const PVal &value, const Args... data /* (key, value) loop */) {
    Arr *result = _arr(data...);

    result->getVar()->insert(std::pair<int_t, PVal>(key, value));

    return result;
}

inline Pair *_pair(const PVal &data1, const PVal &data2,
    const int_t type = id_pair, const func_t func = autotype, PValRaw reused = nullptr
) {
    return new (reused) Pair(std::pair<PVal, PVal>(data1, data2), type, func);
}

}

#endif
