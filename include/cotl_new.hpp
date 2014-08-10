#ifndef _COTL_NEW_HPP
#define _COTL_NEW_HPP

namespace cotl {

func_t dfunc;

inline Atom *_atom(const int_t type) {
    return new (UseGC) Atom(type, dfunc);
}

inline Int *_int(const int_t type, const int_t &data) {
    // return new (UseGC) Atom(type, dfunc);
}

inline Real *_real(const int_t type, const real_t &data) {
    // TODO
    // return new (UseGC) ();
}

inline Str *_str(const int_t type, const std::string &data) {
    // TODO
    // return new (UseGC) ();
}

inline Arr *_arr(const int_t type, ...) {
    // TODO
    // return new (UseGC) ();
}

inline Ptr *_ptr(const int_t type, const PVal &data) {
    // TODO
    // return new (UseGC) ();
}

inline Pair *_pair(const int_t type, const PVal &data1, const PVal &data2) {
    // TODO
    // return new (UseGC) ();
}


}

#endif
