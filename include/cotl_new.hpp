#ifndef _COTL_NEW_HPP
#define _COTL_NEW_HPP

#include "cotl_helper.hpp"

namespace cotl {

inline Atom *_atom(const int_t type, const func_t func = autotype, Val *reused = nullptr) {
    return new (reused) Atom(type, func);
}

inline Int *_int(const int_t type, const int_t &data, const func_t func = autotype, Val *reused = nullptr) {
    return new (reused) Int(type, func, data);
}

inline Real *_real(const int_t type, const real_t &data, const func_t func = autotype, Val *reused = nullptr) {
    return new (reused) Real(type, func, data);
}

inline Func *_func(const int_t type, const func_t &data, const func_t func = autotype, Val *reused = nullptr) {
    return new (reused) Func(type, func, data);
}

inline Ptr *_ptr(const int_t type, const PVal &data, const func_t func = autotype, Val *reused = nullptr) {
    return new (reused) Ptr(type, func, data);
}

inline Str *_str(const int_t type, const std::string &data, const func_t func = autotype, Val *reused = nullptr) {
    return new (reused) Str(type, func, data);
}

inline Arr *_arr(const int_t type, const func_t func = autotype, Val *reused = nullptr) {
    Arr *result = new (reused) Arr(type, func);

    result->getVar() = map_t(new map_t::element_type());

    return result;
}

template <class... Args>
Arr *_arr(const int_t type, const int_t key, const PVal value, const Args... data /* (key, value) loop */) {
    Arr *result = _arr(type, data...);

    result->getVar()->insert(std::pair<int_t, PVal>(key, value));

    return result;
}

inline Pair *_pair(const int_t type, const PVal &data1, const PVal &data2, const func_t func = autotype, Val *reused = nullptr) {
    return new (reused) Pair(type, func, std::pair<PVal, PVal>(data1, data2));
}

}

#endif
