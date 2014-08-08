#ifndef _COTL_TYPE_HPP
#define _COTL_TYPE_HPP

namespace cotl {

class Val {
private:
    long _type;

protected:
    inline Val(long type): _type(type) {};

    Val(const Val &) = delete;

    void setType(long type) {
        _type = type;
    }

public:
    long getType() {
        return _type;
    }
};

template <class T>
class NativeVal: public Val {
private:
    T _data;

    inline NativeVal(long type, T data): Val(type), _data(data) {};

public:
    inline T get() {
        return _data;
    }
};

class Atom: public Val {
};

class Int: public NativeVal<long> {
};

class Str: public NativeVal<std::string> {
};

class Arr: public NativeVal<std::map<long, Val *>> {
};

class Ptr: public NativeVal<Val *> {
};

class Pair: public NativeVal<std::pair<Val *, Val *>> {
};

}

#endif
