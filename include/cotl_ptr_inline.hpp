#ifndef _COTL_PTR_INLINE_HPP
#define _COTL_PTR_INLINE_HPP

#include "cotl_helper.hpp"

namespace cotl {

inline
namespace ptrtype {

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
inline void PValProto<maybe>::call(
    const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel
) const {
    if (!exist()) {
        throw "bad pointer call";
    }

    _val->getFunc()(PVal(*this), caller, lib, tunnel); // _COTL_CALL
}

template <bool maybe>
template <bool ret>
inline void PValProto<maybe>::call(
    const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel
) const {
    call(caller, lib, tunnel);

    if (bool(tunnel) != ret) {
        throw "bad call return";
    }
}

template <bool maybe>
template <class T, int_t id>
inline const T *PValProto<maybe>::as() const {
    if (exist() && id == _val->getType()) {
        return dynamic_cast<T *>(_val);
    } else {
        return nullptr;
    }
}

template <bool maybe>
template <class T>
inline const T *PValProto<maybe>::asany() const {
    if (exist()) {
        return dynamic_cast<T *>(_val);
    } else {
        return nullptr;
    }
}

template <bool maybe>
template <class T, int_t id>
inline T *PValProto<maybe>::raw() const {
    if (exist() && id == _val->getType()) {
        return dynamic_cast<T *>(_val);
    } else {
        return nullptr;
    }
}

template <bool maybe>
inline PValRaw PValProto<maybe>::sure() const {
    if (exist()) {
        return _val;
    } else {
        return _null();
    }
}

}

}

#endif
