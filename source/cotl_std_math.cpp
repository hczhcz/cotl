#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe tunnel1(nullptr);

    libGet(id_math_real, lib, tunnel1); // TODO
    libSet(id_math, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_lib);

}

}
