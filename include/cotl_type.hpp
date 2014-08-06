#ifndef _COTL_TYPE_HPP
#define _COTL_TYPE_HPP

namespace cotl {

class Val {
protected:
    inline Val(void) {};

    Val(const Val &) = delete;

public:
};

class Int: public Val {
private:
    int _data;

    inline Int(int data): _data(data) {};

public:
    inline int get() {
        return _data;
    };
};

}

#endif
