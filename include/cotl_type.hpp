#ifndef _COTL_TYPE_HPP
#define _COTL_TYPE_HPP

#include "cotl_helper.hpp"

namespace cotl {

class Val: public MemBase {
private:
    int_t _type;
    func_t _func;

    #ifdef _COTL_USE_REF_COUNT
        int_t _ref = 0;
    #endif

    inline Val() = delete;
    inline Val(const Val &) = delete;
    inline Val(Val &&) = delete;
    inline Val &operator=(const Val &) = delete;
    inline Val &operator=(Val &&) = delete;

protected:
    inline void *operator new(size_t size, PValRaw reused) {
        (void) size;

        if (reused) {
            reused->~Val();

            return reused;
        } else {
            const size_t maxsize = sizeof(Val) + 2 * sizeof(void *);

            assert(size <= maxsize);

            return _COTL_MALLOC(maxsize);
        }
    }

    inline void operator delete(void *obj) {
        _COTL_FREE(obj);
    }

    inline void operator delete(void *obj, PValRaw reused) {
        (void) reused;

        _COTL_FREE(obj);
    }

    inline Val(const int_t type, const func_t func): MemBase(), _type(type), _func(func) {}

    virtual ~Val() {}

    #ifdef _COTL_USE_REF_COUNT
        friend class PValProto<false>;
        friend class PValProto<true>;

        inline void incRef() {
            ++_ref;
        }

        inline void decRef() {
            --_ref;

            if (!_ref) {
                delete this;
            }
        }
    #endif

public:
    inline int_t getType() const {
        return _type;
    }

    inline func_t getFunc() const {
        return _func;
    }

    inline void setType(const int_t type) {
        _type = type;
    }

    inline void setFunc(const func_t func) {
        _func = func;
    }

    #ifdef _COTL_USE_REF_COUNT
        friend inline int_t _getRef(PValRaw obj) {
            if (obj) {
                return obj->_ref;
            } else {
                return 0;
            }
        }

        friend inline void _setRef(PValRaw obj, int_t ref) {
            obj->_ref = ref;
        }
    #endif

    virtual void repr(std::ostream &stream, const int_t level) const = 0 /* abstract */;
};

inline
namespace published {

class Atom: public Val {
protected:
    inline Atom(const int_t type, const func_t func): Val(type, func) {}

    virtual ~Atom() override {}

public:
    friend Atom *_atom(const int_t type, const func_t func, PValRaw reused);

    virtual void repr(std::ostream &stream, const int_t level) const override;
};

template <class T> class NativeVal;

using Int = NativeVal<int_t>;
using Real = NativeVal<real_t>;
using Func = NativeVal<func_t>;
using Ptr = NativeVal<PVal>;
using Pair = NativeVal<std::pair<PVal, PVal>>;
using Str = NativeVal<std::string>;
using Arr = NativeVal<arr_t>;
using Map = NativeVal<map_t>;

template <class T>
class NativeVal: public Val {
private:
    T _data;

    static_assert(sizeof(T) <= 2 * sizeof(void *), "size of NativeVal<T> is limited");

protected:
    inline NativeVal(const int_t type, const func_t func):
        Val(type, func), _data() {}

    inline NativeVal(const T &data, const int_t type, const func_t func):
        Val(type, func), _data(data) {}

    inline NativeVal(T &&data, const int_t type, const func_t func):
        Val(type, func), _data(std::move(data)) {}

    virtual ~NativeVal() override {}

public:
    friend Int *_int(const int_t &data,
        const int_t type, const func_t func, PValRaw reused
    );
    friend Real *_real(const real_t &data,
        const int_t type, const func_t func, PValRaw reused
    );
    friend Func *_func(const func_t &data,
        const int_t type, const func_t func, PValRaw reused
    );
    friend Ptr *_ptr(const PVal &data,
        const int_t type, const func_t func, PValRaw reused
    );
    friend Pair *_pair(const PVal &data1, const PVal &data2,
        const int_t type, const func_t func, PValRaw reused
    );
    friend Str *_str(const std::string &data,
        const int_t type, const func_t func, PValRaw reused
    );
    friend Arr *_arr_m(arr_t &&container,
        const int_t type, const func_t func, PValRaw reused
    );
    friend Map *_map_m(map_t &&container,
        const int_t type, const func_t func, PValRaw reused
    );

    virtual void repr(std::ostream &stream, const int_t level) const override;

    // should not be overused
    inline T &getVar() {
        return _data;
    }

    inline const T &get() const {
        return _data;
    }

    inline void set(const T &data) {
        _data = data;
    }
};

}

}

#endif
