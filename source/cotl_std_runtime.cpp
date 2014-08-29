#include "../cotl"

namespace cotlstd {

inline
namespace published {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(stdauto)
_COTL_FUNC_BEGIN
    PMaybe func(nullptr);

    lib(self, lib, func);

    if (func) {
        func(self, lib, func);
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdliteral)
_COTL_FUNC_BEGIN
    if (tunnel) {
        throw;
    } else {
        tunnel = self;
    }
_COTL_FUNC_END

}

}
