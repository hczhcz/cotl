#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(exec)
_COTL_FUNC_BEGIN

_COTL_FUNC_END

_COTL_FUNC_T(autotype)
_COTL_FUNC_BEGIN

    PMaybe func(nullptr);

    lib(self, lib, func);

    // caller->getType()

_COTL_FUNC_END

}
