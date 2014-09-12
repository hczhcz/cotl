#include "../cotl"

namespace cotl {

inline
namespace published {

Atom *_atom(
    const int_t type, const func_t func, PValRaw reused
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = _getRef(reused);
    #endif

    Atom * result = new (reused) Atom(type, func);

    #ifdef _COTL_USE_REF_COUNT
        _setRef(result, ref);
    #endif

    return result;
}

Int *_int(const int_t &data,
    const int_t type, const func_t func, PValRaw reused
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = _getRef(reused);
    #endif

    Int * result = new (reused) Int(data, type, func);

    #ifdef _COTL_USE_REF_COUNT
        _setRef(result, ref);
    #endif

    return result;
}

Real *_real(const real_t &data,
    const int_t type, const func_t func, PValRaw reused
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = _getRef(reused);
    #endif

    Real * result = new (reused) Real(data, type, func);

    #ifdef _COTL_USE_REF_COUNT
        _setRef(result, ref);
    #endif

    return result;
}

Func *_func(const func_t &data,
    const int_t type, const func_t func, PValRaw reused
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = _getRef(reused);
    #endif

    Func * result = new (reused) Func(data, type, func);

    #ifdef _COTL_USE_REF_COUNT
        _setRef(result, ref);
    #endif

    return result;
}

Ptr *_ptr(const PVal &data,
    const int_t type, const func_t func, PValRaw reused
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = _getRef(reused);
    #endif

    Ptr * result = new (reused) Ptr(data, type, func);

    #ifdef _COTL_USE_REF_COUNT
        _setRef(result, ref);
    #endif

    return result;
}

Pair *_pair(const PVal &data1, const PVal &data2,
    const int_t type, const func_t func, PValRaw reused
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = _getRef(reused);
    #endif

    Pair * result = new (reused) Pair(std::pair<PVal, PVal>(data1, data2), type, func);

    #ifdef _COTL_USE_REF_COUNT
        _setRef(result, ref);
    #endif

    return result;
}

Str *_str(const std::string &data,
    const int_t type, const func_t func, PValRaw reused
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = _getRef(reused);
    #endif

    Str * result = new (reused) Str(str_t(_COTL_RAWNEW(str_t::element_type(data))), type, func);

    #ifdef _COTL_USE_REF_COUNT
        _setRef(result, ref);
    #endif

    return result;
}

Arr *_arr_m(arr_t &&container,
    const int_t type, const func_t func, PValRaw reused
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = _getRef(reused);
    #endif

    Arr *result = new (reused) Arr(std::move(container), type, func);

    #ifdef _COTL_USE_REF_COUNT
        _setRef(result, ref);
    #endif

    return result;
}

Map *_map_m(map_t &&container,
    const int_t type, const func_t func, PValRaw reused
) {
    #ifdef _COTL_USE_REF_COUNT
        int_t ref = _getRef(reused);
    #endif

    Map *result = new (reused) Map(std::move(container), type, func);

    #ifdef _COTL_USE_REF_COUNT
        _setRef(result, ref);
    #endif

    return result;
}

}

}
