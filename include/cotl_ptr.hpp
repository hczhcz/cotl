#ifndef _COTL_PTR_HPP
#define _COTL_PTR_HPP

#include "cotl_helper.hpp"

namespace cotl {

class PVal {
private:
    Val *_val;

    inline PVal() = delete;
    inline PVal(const Val &) = delete;
    inline PVal(Val &&) = delete;
    inline PVal &operator=(const Val &) = delete;
    inline PVal &operator=(Val &&) = delete;
    inline void *operator new(size_t size) = delete;

    #ifdef _COTL_USE_REF_COUNT
        inline void doInc();
        // defined in cotl_type.hpp

        inline void doDec();
        // defined in cotl_type.hpp
    #endif

public:
    inline PVal(Val *val): _val(val) {}

    inline Val *operator->() {
        return _val;
    }

    inline const Val *operator->() const {
        return _val;
    }

    inline operator bool() const {
        return _val;
    }

    inline void operator()(PVal caller, PVal lib, PVal tunnel /* could be null */);
    // defined in cotl_type.hpp

    template <class T>
    inline T *as() {
        return dynamic_cast<T *>(_val);
    }
};

}

#endif
