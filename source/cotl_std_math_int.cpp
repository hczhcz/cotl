#include "../cotl"

namespace cotl {

namespace stdlib {

// arg: self, caller, lib, tunnel

namespace {

int_t add(int_t a, int_t b) {
    return a + b;
}

int_t sub(int_t a, int_t b) {
    return a - b;
}

int_t mul(int_t a, int_t b) {
    return a * b;
}

int_t div(int_t a, int_t b) {
    return a / b;
}

int_t mod(int_t a, int_t b) {
    return a % b;
}

int_t rsub(int_t a, int_t b) {
    return b - a;
}

int_t rdiv(int_t a, int_t b) {
    return b / a;
}

int_t rmod(int_t a, int_t b) {
    return b % a;
}

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe tunnel1(
        _libmap(
            id_add, _libfunc(libFunc<cotl::Int, cotl::Int, cotl::Int, id_add, add, sub>),
            id_sub, _libfunc(libFunc<cotl::Int, cotl::Int, cotl::Int, id_sub, sub, add>),
            id_mul, _libfunc(libFunc<cotl::Int, cotl::Int, cotl::Int, id_mul, mul, div>),
            id_div, _libfunc(libFunc<cotl::Int, cotl::Int, cotl::Int, id_div, div, mul>),
            id_mod, _libfunc(libFunc<cotl::Int, cotl::Int, cotl::Int, id_mod, mod, nullptr>),
            id_rsub, _libfunc(libFunc<cotl::Int, cotl::Int, cotl::Int, id_rsub, rsub, rsub>),
            id_rdiv, _libfunc(libFunc<cotl::Int, cotl::Int, cotl::Int, id_rdiv, rdiv, rdiv>),
            id_rmod, _libfunc(libFunc<cotl::Int, cotl::Int, cotl::Int, id_rmod, rmod, nullptr>)
        )
    );

    libSet<id_std, id_math>(id_math_int, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_lib_1);

}

}

}
