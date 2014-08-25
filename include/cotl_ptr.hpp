#ifndef _COTL_PTR_HPP
#define _COTL_PTR_HPP

#include "cotl_helper.hpp"

namespace cotl {

class PVal {
private:
    PValRaw _val;

    inline PVal() = delete;
    inline PVal(PVal &&) = delete;
    inline PVal &operator=(PVal &&) = delete;
    inline void *operator new(size_t) = delete;

    inline void checkNull() {
        if (!_val) {
            // TODO
        }
    }

    #ifdef _COTL_USE_REF_COUNT
        inline void doInc();
        // defined in cotl_type.hpp

        inline void doDec();
        // defined in cotl_type.hpp
    #endif

public:
    inline PVal(const PValRaw val): _val(val) {
        checkNull();

        #ifdef _COTL_USE_REF_COUNT
            doInc();
        #endif
    }

    inline PVal(const PVal &ptr): _val(ptr._val) {
        #ifdef _COTL_USE_REF_COUNT
            doInc();
        #endif
    };

    /* inline PVal(PVal &&ptr): _val(ptr._val) {
        ptr._val = nullptr;
    } */

    inline ~PVal() {
        #ifdef _COTL_USE_REF_COUNT
            doDec();
        #endif
    }

    inline PVal &operator=(const PValRaw val) {
        #ifdef _COTL_USE_REF_COUNT
            doDec();
        #endif

        _val = val;
        checkNull();

        #ifdef _COTL_USE_REF_COUNT
            doInc();
        #endif

        return *this;
    };

    inline PVal &operator=(const PVal &ptr) {
        #ifdef _COTL_USE_REF_COUNT
            doDec();
        #endif

        _val = ptr._val;

        #ifdef _COTL_USE_REF_COUNT
            doInc();
        #endif

        return *this;
    };

    /* inline PVal &operator=(PVal &&ptr) {
        #ifdef _COTL_USE_REF_COUNT
            doDec();
        #endif

        _val = ptr._val;
        ptr._val = nullptr;

        return *this;
    } */

    inline PValRaw operator->() const {
        return _val;
    }

    inline operator bool() const {
        return _val;
    }

    inline void operator()(const PVal &caller, const PVal &lib, PVal &tunnel /* could be null */) const;
    // defined in cotl_type.hpp

    template <class T>
    inline T *as() const {
        return dynamic_cast<T *>(_val);
    }

    inline PValRaw raw() const {
        return _val;
    }
};

}

#endif
