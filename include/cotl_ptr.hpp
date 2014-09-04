#ifndef _COTL_PTR_HPP
#define _COTL_PTR_HPP

#include "cotl_helper.hpp"

namespace cotl {

template <bool maybe>
class PValProto {
private:
    PValRaw _val;

    inline PValProto() = delete;
    // TODO: necessary?
    // inline void *operator new(size_t) = delete;
    // inline void operator delete(void *) = delete;

    inline bool legal() const;
    // defined in cotl_inline.hpp

    inline bool exist() const;
    // defined in cotl_inline.hpp

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
            throw;
        }

        #ifdef _COTL_USE_REF_COUNT
            doInc();
        #endif
    }

    inline PValProto(const PMaybe &ptr): _val(ptr._val) {
        if (!legal()) {
            throw;
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

    inline PValProto(PMaybe &&ptr): _val(ptr._val) {
        if (!legal()) {
            throw;
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
            throw;
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
            throw;
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
            throw;
        }

        ptr._val = nullptr;

        return *this;
    }

    inline PValProto<maybe> &operator=(PVal &&) = delete; // not allowed

    inline PValConst operator->() const;
    // defined in cotl_inline.hpp

    inline PValConst operator->();
    // defined in cotl_inline.hpp

    inline void operator()(
        const PMaybe &caller, const PVal &lib, PMaybe &tunnel /* could be null */
    ) const;
    // defined in cotl_inline.hpp

    inline void operator()(
        const PMaybe &caller, const PVal &lib, PMaybe &tunnel /* could be null */
    );
    // defined in cotl_inline.hpp

    inline operator bool() const {
        return exist();
    }

    template <class T>
    inline const T *as() const {
        if (exist()) {
            return dynamic_cast<T *>(_val);
        } else {
            return nullptr;
        }
    }

    template <class T>
    inline T *raw() const {
        if (exist()) {
            return dynamic_cast<T *>(_val);
        } else {
            return nullptr;
        }
    }

    inline PValRaw raw() const {
        return _val;
    }
};

}

#endif
