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

int_t mul(const int_t &a, const int_t &b) {
    return a * b;
}

int_t div(const int_t &a, const int_t &b) {
    return a / b;
}

int_t mod(const int_t &a, const int_t &b) {
    return a % b;
}

int_t rsub(const int_t &a, const int_t &b) {
    return b - a;
}

int_t rdiv(const int_t &a, const int_t &b) {
    return b / a;
}

int_t rmod(const int_t &a, const int_t &b) {
    return b % a;
}

int_t merr(const int_t &a, const int_t &b) {
    (void) a;
    (void) b;

    throw "math error"; // TODO
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
            id_mod, _libfunc(libFunc<cotl::Int, cotl::Int, cotl::Int, id_mod, mod, merr>),
            id_rsub, _libfunc(libFunc<cotl::Int, cotl::Int, cotl::Int, id_rsub, rsub, rsub>),
            id_rdiv, _libfunc(libFunc<cotl::Int, cotl::Int, cotl::Int, id_rdiv, rdiv, rdiv>),
            id_rmod, _libfunc(libFunc<cotl::Int, cotl::Int, cotl::Int, id_rmod, rmod, merr>)
        )
    );

    libSet(id_math_int, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_core);

}

}
