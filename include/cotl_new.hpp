#ifndef _COTL_NEW_HPP
#define _COTL_NEW_HPP

namespace cotl {

const func_t dfunc = 0;

inline Atom *_atom(const int_t type) {
    return new (UseGC) Atom(type, dfunc);
}

inline Int *_int(const int_t type, const int_t &data) {
    return new (UseGC) Int(type, dfunc, data);
}

inline Real *_real(const int_t type, const real_t &data) {
    return new (UseGC) Real(type, dfunc, data);
}

inline Str *_str(const int_t type, const std::string &data) {
    return new (UseGC) Str(type, dfunc, data);
}

inline Arr *_arr(const int_t type) {
    return new (UseGC) Arr(type, dfunc);
}

inline Arr *_arr(const int_t type, int_t count /* not const */, ... /* int_t index, PVal data, (loop) */) {
    Arr *result = _arr(type);

    va_list vl;
    int_t max = count;

    count *= 2;

    va_start(vl, count);
    for (int_t i = 0; i < max; ++i) {
        int_t key = va_arg(vl, int_t);
        result->getVar()[key] = va_arg(vl, PVal);
    }
    va_end(vl);

    return result;
}

inline Ptr *_ptr(const int_t type, const PVal &data) {
    return new (UseGC) Ptr(type, dfunc, data);
}

inline Pair *_pair(const int_t type, const PVal &data1, const PVal &data2) {
    return new (UseGC) Pair(type, dfunc, data1, data2);
}


}

#endif
