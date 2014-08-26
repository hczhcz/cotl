#ifndef _COTL_PTR_INLINE_HPP
#define _COTL_PTR_INLINE_HPP

#include "cotl_helper.hpp"

namespace cotl {

template <bool maybe>
inline void PValProto<maybe>::checkNull() {
    if (!maybe && !_val) {
        _val = _atom(cotlstd::id_error);
    }
}

template <bool maybe>
inline bool PValProto<maybe>::exist() const {
    return !maybe || _val;
}

#ifdef _COTL_USE_REF_COUNT
    template <bool maybe>
    inline void PValProto<maybe>::doInc() const {
        if (exist()) {
            _val->incRef();
        }
    }

    template <bool maybe>
    inline void PValProto<maybe>::doDec() const {
        if (exist()) {
            _val->decRef();
        }
    }
#endif

template <bool maybe>
inline PValRaw PValProto<maybe>::operator->() const{
    if (exist()) {
        return _val;
    } else {
        return _atom(cotlstd::id_error);
    }
}

template <bool maybe>
inline void PValProto<maybe>::operator()(const PVal &caller, const PVal &lib, PMaybe &tunnel /* could be null */) const {
    if (exist()) {
        _val->getFunc()(*this, caller, lib, tunnel);
    } else {
        tunnel = _atom(cotlstd::id_error);
    }
}

}

#endif
