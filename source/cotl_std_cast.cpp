#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

namespace {

real_t inttoreal(int_t val) {
    return val;
}

/*
str_t inttostr(int_t val) {
    return val;
}

str_t realtostr(real_t val) {
    return val;
}
*/

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe tunnel1(
        _libmap(
            id_real, _libmap(
                id_int, _libfunc(libFunc<cotl::Int, cotl::Real, id_int, inttoreal, nullptr>)
            ),
            id_str, _libmap()
        )
    );

    libSet(id_cast, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_lib);

}

}
