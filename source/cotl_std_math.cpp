#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

namespace {

int_t add(const int_t &a, const int_t &b) {
    return a + b;
}

int_t sub(const int_t &a, const int_t &b) {
    return a - b;
}

int_t rsub(const int_t &a, const int_t &b) {
    return a - b;
}

_COTL_FUNC_T(test)
_COTL_FUNC_BEGIN
    libFunc<cotl::Int, cotl::Int, cotl::Int, id_add, add, rsub>(self, caller, lib, tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe tunnel1(
        _libmap(
            id_add, _libfunc(test)
        )
    );

    libSet(id_math, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_core);

}

}
