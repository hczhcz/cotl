#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe tunnel1(
        _libmap(
            id_atom, _libfunc(stdLiteral),
            id_int, _libfunc(stdLiteral),
            id_real, _libfunc(stdLiteral),
            id_func, _libfunc(stdLibFunc),
            id_ptr, _libfunc(stdWrapPtr),
            id_pair, _libfunc(stdWrapPair),
            id_str, _libfunc(stdLiteral),
            id_arr, _libfunc(stdWrapArr),
            id_map, _libfunc(stdLibMap),
            id_error, _libfunc(stdLiteral)
        )
    );

    libSet(id_type, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_core);

}

}
