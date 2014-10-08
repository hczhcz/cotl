#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

namespace {

real_t inttoreal(int_t val) {
    return val;
}

std::string inttostr(int_t val) {
    return std::to_string(val);
}

std::string realtostr(real_t val) {
    return std::to_string(val);
}

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe tunnel1(
        _libmap(
            id_real, _libmap(
                id_int, _libfunc(libFunc<cotl::Int, cotl::Real, id_int, inttoreal, nullptr>)
            ),
            id_str, _libmap(
                id_int, _libfunc(libFunc<cotl::Int, cotl::Str, id_int, inttostr, nullptr>),
                id_real, _libfunc(libFunc<cotl::Real, cotl::Str, id_real, realtostr, nullptr>)
            )
        )
    );

    libSet<id_std>(id_cast, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_lib);

}

}
