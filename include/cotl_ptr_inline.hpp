#ifndef _COTL_PTR_INLINE_HPP
#define _COTL_PTR_INLINE_HPP

#include "cotl_helper.hpp"

namespace cotl {

template <bool maybe>
inline bool PValProto<maybe>::legal() const {
    return maybe || _val;
}

template <bool maybe>
inline bool PValProto<maybe>::exist() const {
    return !maybe || _val;
}

template <bool maybe>
inline void PValProto<maybe>::giveVal() {
    _val = _atom(cotlstd::id_null);
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

template <>
inline PValConst PValProto<true>::operator->() const = delete;

template <bool maybe>
inline PValConst PValProto<maybe>::operator->() const {
    assert(exist());
    return _val;
}

template <bool maybe>
inline PValConst PValProto<maybe>::operator->() {
    if (!exist()) {
        giveVal();

        #ifdef _COTL_USE_REF_COUNT
            doInc();
        #endif
    }

    return _val;
}

template <>
inline void PValProto<true>::operator()(
    const PVal &, const PVal &, PMaybe &
) const = delete;

template <bool maybe>
inline void PValProto<maybe>::operator()(
    const PVal &caller, const PVal &lib, PMaybe &tunnel /* could be null */
) const {
    assert(exist());
    _val->getFunc()(*this, caller, lib, tunnel);
}

template <bool maybe>
inline void PValProto<maybe>::operator()(
    const PVal &caller, const PVal &lib, PMaybe &tunnel /* could be null */
) {
    if (!exist()) {
        giveVal();

        #ifdef _COTL_USE_REF_COUNT
            doInc();
        #endif
    }

    _val->getFunc()(*this, caller, lib, tunnel);
}

}

#endif
