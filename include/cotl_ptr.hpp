#ifndef _COTL_PTR_HPP
#define _COTL_PTR_HPP

#include "cotl_helper.hpp"

namespace cotl {

template <bool maybe>
class PValProto final {
private:
    PValRaw _val;

    inline PValProto() = delete;
    // inline void *operator new(size_t) = delete;
    // inline void operator delete(void *) = delete;

    inline bool legal() const {
        return maybe || _val;
    }

    inline bool exist() const{
        return !maybe || _val;
    }

    #ifdef _COTL_USE_REF_COUNT
        inline void doInc() const;
        // defined in cotl_inline.hpp

        inline void doDec() const;
        // defined in cotl_inline.hpp
    #endif

public:
    friend class PValProto<!maybe>;

    inline PValProto(const PValRaw val): _val(val) {
        if (!legal()) {
            throw "bad raw pointer";
        }

        #ifdef _COTL_USE_REF_COUNT
            doInc();
        #endif
    }

    inline explicit PValProto(const PMaybe &ptr): _val(ptr._val) {
        if (!legal()) {
            throw "bad copied pointer";
        }

        #ifdef _COTL_USE_REF_COUNT
            doInc();
        #endif
    }

    inline PValProto(const PVal &ptr): _val(ptr._val) {
        #ifdef _COTL_USE_REF_COUNT
            doInc();
        #endif
    }

    inline explicit PValProto(PMaybe &&ptr): _val(ptr._val) {
        if (!legal()) {
            throw "bad moved pointer";
        }

        ptr._val = nullptr;
    }

    inline PValProto(PVal &&) = delete; // not allowed

    inline ~PValProto() {
        #ifdef _COTL_USE_REF_COUNT
            doDec();
        #endif
    }

    inline PValProto<maybe> &operator=(const PValRaw val) {
        #ifdef _COTL_USE_REF_COUNT
            doDec();
        #endif

        _val = val;

        if (!legal()) {
            throw "bad assigned raw pointer";
        }

        #ifdef _COTL_USE_REF_COUNT
            doInc();
        #endif

        return *this;
    }

    inline PValProto<maybe> &operator=(const PMaybe &ptr) {
        #ifdef _COTL_USE_REF_COUNT
            doDec();
        #endif

        _val = ptr._val;

        if (!legal()) {
            throw "bad copy-assigned pointer";
        }

        #ifdef _COTL_USE_REF_COUNT
            doInc();
        #endif

        return *this;
    }

    inline PValProto<maybe> &operator=(const PVal &ptr) {
        #ifdef _COTL_USE_REF_COUNT
            doDec();
        #endif

        _val = ptr._val;

        #ifdef _COTL_USE_REF_COUNT
            doInc();
        #endif

        return *this;
    }

    inline PValProto<maybe> &operator=(PMaybe &&ptr) {
        #ifdef _COTL_USE_REF_COUNT
            doDec();
        #endif

        _val = ptr._val;

        if (!legal()) {
            throw "bad move-assigned pointer";
        }

        ptr._val = nullptr;

        return *this;
    }

    inline PValProto<maybe> &operator=(PVal &&) = delete; // not allowed

    inline PValConst operator->() const {
        if (!exist()) {
            throw "bad pointer dereference";
        }

        return _val;
    }

    // call without checking
    // for passing exec flow only
    inline void call(
        const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel
    ) const;
    // defined in cotl_inline.hpp

    template <bool ret>
    inline void call(
        const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel
    ) const;
    // defined in cotl_inline.hpp

    inline explicit operator bool() const {
        return exist();
    }

    inline explicit operator int_t() const = delete;

    template <class T, int_t id>
    inline const T *as() const;
    // defined in cotl_inline.hpp

    template <class T>
    inline const T *asany() const;
    // defined in cotl_inline.hpp

    template <class T, int_t id>
    inline T *raw() const;
    // defined in cotl_inline.hpp

    inline PValRaw raw() const {
        return _val;
    }

    inline PValRaw sure() const;
    // defined in cotl_inline.hpp
};

}

#endif
