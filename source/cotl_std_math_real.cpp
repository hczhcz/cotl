#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

namespace {

real_t add(real_t a, real_t b) {
    return a + b;
}

real_t sub(real_t a, real_t b) {
    return a - b;
}

real_t mul(real_t a, real_t b) {
    return a * b;
}

real_t div(real_t a, real_t b) {
    return a / b;
}

real_t rsub(real_t a, real_t b) {
    return b - a;
}

real_t rdiv(real_t a, real_t b) {
    return b / a;
}

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe tunnel1(
        _libmap(
            id_add, _libfunc(libFunc<cotl::Real, cotl::Real, cotl::Real, id_add, add, sub>),
            id_sub, _libfunc(libFunc<cotl::Real, cotl::Real, cotl::Real, id_sub, sub, add>),
            id_mul, _libfunc(libFunc<cotl::Real, cotl::Real, cotl::Real, id_mul, mul, div>),
            id_div, _libfunc(libFunc<cotl::Real, cotl::Real, cotl::Real, id_div, div, mul>),
            id_rsub, _libfunc(libFunc<cotl::Real, cotl::Real, cotl::Real, id_rsub, rsub, rsub>),
            id_rdiv, _libfunc(libFunc<cotl::Real, cotl::Real, cotl::Real, id_rdiv, rdiv, rdiv>)
        )
    );

    libSet<id_math>(id_math_real, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_core);

}

}
