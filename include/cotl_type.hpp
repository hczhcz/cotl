#ifndef _COTL_TYPE_HPP
#define _COTL_TYPE_HPP

#include "cotl_helper.hpp"

namespace cotl {

class Val: public virtual gc {
private:
    int_t _type;
    func_t _func;

protected:
    inline Val(const int_t type, const func_t func): _type(type), _func(func) {}

    inline Val(const Val &) = delete;

    inline Val &operator=(const Val &) = delete;

    inline void setType(const int_t type) {
        _type = type;
    }

    inline void setFunc(const func_t func) {
        _func = func;
    }

    inline func_t getFunc() const {
        return _func;
    }

public:
    inline void operator()(PVal caller, PVal lib, PVal tunnel /* could be null */) {
        _func(this, caller, lib, tunnel);
    }

    inline int_t getType() const {
        return _type;
    }

    virtual void repr(std::ostream &stream, const int_t level) const = 0;
};

class Atom: public Val {
protected:
    inline Atom(const int_t type, const func_t func): Val(type, func) {}

public:
    friend inline Atom *_atom(const int_t type, const func_t func);

    virtual void repr(std::ostream &stream, const int_t level) const;
};

template <class T> class NativeVal;

typedef NativeVal<int_t> Int;
typedef NativeVal<real_t> Real;
typedef NativeVal<func_t> Func;
typedef NativeVal<std::string> Str;
typedef NativeVal<std::map<int_t, PVal>> Arr;
typedef NativeVal<PVal> Ptr;

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

    inline NativeVal(const int_t type, const func_t func, const T &data):
        Val(type, func), _data(data) {}

public:
    friend inline Int *_int(const int_t type, const int_t &data, const func_t func);
    friend inline Real *_real(const int_t type, const real_t &data, const func_t func);
    friend inline Func *_func(const int_t type, const func_t &data, const func_t func);
    friend inline Str *_str(const int_t type, const std::string &data, const func_t func);
    friend inline Arr *_arr(const int_t type, const func_t func);
    friend inline Ptr *_ptr(const int_t type, const PVal &data, const func_t func);

    virtual void repr(std::ostream &stream, const int_t level) const;

    inline T &getVar() {
        return _data;
    }

    inline const T &get() const {
        return _data;
    }
};

class Pair: public Val {
private:
    PVal _data1;
    PVal _data2;

protected:
    inline Pair(const int_t type, const func_t func, const PVal &data1, const PVal &data2):
        Val(type, func), _data1(data1), _data2(data2) {}

    inline void set1(const PVal &data) {
        _data1 = data;
    }

    inline void set2(const PVal &data) {
        _data2 = data;
    }

public:
    friend inline Pair *_pair(const int_t type, const PVal &data1, const PVal &data2, const func_t func);

    inline PVal &getVar1() {
        return _data1;
    }

    inline const PVal &get1() const {
        return _data1;
    }

    inline PVal &getVar2() {
        return _data2;
    }

    inline const PVal &get2() const {
        return _data2;
    }

    virtual void repr(std::ostream &stream, const int_t level) const;
};

}

#endif
