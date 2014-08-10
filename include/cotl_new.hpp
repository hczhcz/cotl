#ifndef _COTL_NEW_HPP
#define _COTL_NEW_HPP

namespace cotl {

Atom *_atom(const int_t type) {
    // TODO
    // return new (UseGC) ();
}

Int *_int(const int_t type, const int_t &data) {
    // TODO
    // return new (UseGC) ();
}

Real *_real(const int_t type, const real &data) {
    // TODO
    // return new (UseGC) ();
}

Str *_str(const int_t type, const std::string &data) {
    // TODO
    // return new (UseGC) ();
}

Arr *_arr(const int_t type, ...) {
    // TODO
    // return new (UseGC) ();
}

Ptr *_ptr(const int_t type, const PVal &data) {
    // TODO
    // return new (UseGC) ();
}

Pair *_pair(const int_t type, const PVal &data1, const PVal &data2) {
    // TODO
    // return new (UseGC) ();
}


}

#endif
