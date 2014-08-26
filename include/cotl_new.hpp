#ifndef _COTL_NEW_HPP
#define _COTL_NEW_HPP

#include "cotl_helper.hpp"

namespace cotl {

#ifdef _COTL_USE_REF_COUNT
    inline int_t getRef(PValRaw obj) {
        if (obj) {
            return obj->_ref;
        } else {
            return 0;
        }
    }

    inline void setRef(PValRaw obj, int_t ref) {
        obj->_ref = ref;
    }
#endif

inline Atom *_atom(
    const int_t type = id_atom, const func_t func = autotype, PValRaw reused = nullptr
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = getRef(reused);
    #endif

    Atom * result = new (reused) Atom(type, func);

    #ifdef _COTL_USE_REF_COUNT
        setRef(result, ref);
    #endif

    return result;
}

inline Int *_int(const int_t &data,
    const int_t type = id_int, const func_t func = autotype, PValRaw reused = nullptr
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = getRef(reused);
    #endif

    Int * result = new (reused) Int(data, type, func);

    #ifdef _COTL_USE_REF_COUNT
        setRef(result, ref);
    #endif

    return result;
}

inline Real *_real(const real_t &data,
    const int_t type = id_real, const func_t func = autotype, PValRaw reused = nullptr
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = getRef(reused);
    #endif

    Real * result = new (reused) Real(data, type, func);

    #ifdef _COTL_USE_REF_COUNT
        setRef(result, ref);
    #endif

    return result;
}

inline Func *_func(const func_t &data,
    const int_t type = id_func, const func_t func = autotype, PValRaw reused = nullptr
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = getRef(reused);
    #endif

    Func * result = new (reused) Func(data, type, func);

    #ifdef _COTL_USE_REF_COUNT
        setRef(result, ref);
    #endif

    return result;
}

inline Ptr *_ptr(const PVal &data,
    const int_t type = id_ptr, const func_t func = autotype, PValRaw reused = nullptr
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = getRef(reused);
    #endif

    Ptr * result = new (reused) Ptr(data, type, func);

    #ifdef _COTL_USE_REF_COUNT
        setRef(result, ref);
    #endif

    return result;
}

inline Str *_str(const std::string &data,
    const int_t type = id_str, const func_t func = autotype, PValRaw reused = nullptr
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = getRef(reused);
    #endif

    Str * result = new (reused) Str(data, type, func);

    #ifdef _COTL_USE_REF_COUNT
        setRef(result, ref);
    #endif

    return result;
}

inline Arr *_arr(
    const int_t type = id_arr, const func_t func = autotype, PValRaw reused = nullptr
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = getRef(reused);
    #endif

    Arr *result = new (reused) Arr(type, func);

    // note: global --GC-> Val --RAII-> ptr --RAII-> map --GCalloc--> map data
    result->getVar() = map_t(new map_t::element_type());

    return result;

    #ifdef _COTL_USE_REF_COUNT
        setRef(result, ref);
    #endif

    return result;
}

template <class... Args>
inline Arr *_arr(const int_t key, const PVal &value, const Args... data /* (key, value) loop */) {
    Arr *result = _arr(data...);

    result->getVar()->insert(std::pair<int_t, PVal>(key, value));

    return result;
}

inline Pair *_pair(const PVal &data1, const PVal &data2,
    const int_t type = id_pair, const func_t func = autotype, PValRaw reused = nullptr
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = getRef(reused);
    #endif

    Pair * result = new (reused) Pair(std::pair<PVal, PVal>(data1, data2), type, func);

    #ifdef _COTL_USE_REF_COUNT
        setRef(result, ref);
    #endif

    return result;
}

}

#endif
