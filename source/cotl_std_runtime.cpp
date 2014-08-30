#include "../cotl"

namespace cotlstd {

inline
namespace published {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(stdAuto)
_COTL_FUNC_BEGIN
    PMaybe func(nullptr);

    lib(self, lib, func);

    if (func) {
        func(self, lib, func);
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdLiteral)
_COTL_FUNC_BEGIN
    if (tunnel) {
        throw;
    } else {
        tunnel = self;
    }
_COTL_FUNC_END

}

_COTL_FUNC_T(initRuntime)
_COTL_FUNC_BEGIN
    // TODO

_COTL_FUNC_END

static
long long ago = addInitializer(initRuntime);

}
