#ifndef _COTL_TYPE_HPP
#define _COTL_TYPE_HPP

namespace cotl {

class Val {
private:
    int_t _type;
    func_t _func;

protected:
    inline Val(int_t type, func_t func): _type(type), _func(func) {};

    inline Val(const Val &) = delete;

    inline Val &operator=(const Val &) = delete;

    inline void setType(int_t type) {
        _type = type;
    }

    inline void setFunc(func_t func) {
        _func = func;
    }

public:
    inline void operator()(Val &job, Val &stack, Val &tunnel /* could be null */) {
        _func(*this, job, stack, tunnel);
    }

    inline int_t getType() const {
        return _type;
    }

    virtual void repl(std::ostream &stream, int_t level) const;
};

template <class T>
class NativeVal: public Val {
private:
    T _data;

protected:
    inline NativeVal(int_t type, func_t func, T data): Val(type, func), _data(data) {};

    inline void set(T data) {
        _data = data;
    }

public:
    inline T &getVar() {
        return _data;
    }

    inline const T &get() const {
        return _data;
    }
};

class Atom: public Val {
};

class Int: public NativeVal<int_t> {
};

class Real: public NativeVal<real_t> {
};

class Str: public NativeVal<std::string> {
};

class Arr: public NativeVal<std::map<int_t, PVal>> {
};

class Ptr: public NativeVal<PVal> {
};

class Pair: public Val {
private:
    PVal _data1;
    PVal _data2;

protected:
    inline Pair(const int_t type, const func_t func, const PVal data1, const PVal data2):
        Val(type, func), _data1(data1), _data2(data2) {}

    inline void set1(const PVal data) {
        _data1 = data;
    }

    inline void set2(const PVal data) {
        _data2 = data;
    }

public:
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
};

}

#endif
