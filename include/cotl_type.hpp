#ifndef _COTL_TYPE_HPP
#define _COTL_TYPE_HPP

namespace cotl {

class Val {
private:
    int_t _type;

protected:
    inline Val(int_t type): _type(type) {};

    inline Val(const Val &) = delete;

    inline void setType(int_t type) {
        _type = type;
    }

public:
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
    inline NativeVal(int_t type, T data): Val(type), _data(data) {};

    inline void set(T data) {
        _data = data;
    }

public:
    inline T get() {
        return _data;
    }

    inline const T getConst() const {
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

class Arr: public NativeVal<std::map<int_t, Val *>> {
};

class Ptr: public NativeVal<Val *> {
};

class Pair: public NativeVal<std::pair<Val *, Val *>> {
};

}

#endif
