#ifndef _COTL_TYPE_HPP
#define _COTL_TYPE_HPP

#include "cotl_helper.hpp"

namespace cotl {

class Val: public gc_cleanup {
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
            const size_t maxsize = sizeof(Val) + 16;

            assert(size <= maxsize);

            return GC_MALLOC(maxsize);
        }
    }

    inline void operator delete(void *obj) {
        GC_FREE(obj);
    }

    inline Val(const int_t type, const func_t func): gc_cleanup(), _type(type), _func(func) {}

    virtual ~Val() {}

    inline void setType(const int_t type) {
        _type = type;
    }

    inline void setFunc(const func_t func) {
        _func = func;
    }

    #ifdef _COTL_USE_REF_COUNT
        friend class PValProto<false>;
        friend class PValProto<true>;
        friend inline int_t getRef(PValRaw obj);
        friend inline void setRef(PValRaw obj, int_t ref);

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

    virtual void repr(std::ostream &stream, const int_t level) const = 0 /* abstract */;
};

class Atom: public Val {
protected:
    inline Atom(const int_t type, const func_t func): Val(type, func) {}

    virtual ~Atom() {}

public:
    friend Atom *_atom(const int_t type, const func_t func, PValRaw reused);

    virtual void repr(std::ostream &stream, const int_t level) const;
};

template <class T> class NativeVal;

typedef NativeVal<int_t> Int;
typedef NativeVal<real_t> Real;
typedef NativeVal<func_t> Func;
typedef NativeVal<PVal> Ptr;
typedef NativeVal<std::pair<PVal, PVal>> Pair;
typedef NativeVal<std::string> Str;
typedef NativeVal</* std::map or std::unordered_map */map_t> Arr;

template <class T>
class NativeVal: public Val {
private:
    T _data;

protected:
    inline void set(const T &data) {
        _data = data;
    }

    inline NativeVal(const int_t type, const func_t func):
        Val(type, func), _data() {}

    inline NativeVal(const T &data, const int_t type, const func_t func):
        Val(type, func), _data(data) {}

    virtual ~NativeVal() {}

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
    friend Arr *_arr(
        const int_t type, const func_t func, PValRaw reused
    );

    virtual void repr(std::ostream &stream, const int_t level) const;

    // should not be overused
    inline T &getVar() {
        return _data;
    }

    inline const T &get() const {
        return _data;
    }
};

}

#endif
