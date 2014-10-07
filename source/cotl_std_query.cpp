#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(stdUse)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id_use);

    PMaybe lib1(nullptr);
    self_p->get().first.call<true>(caller, lib, lib1);
    // TODO: hard binding
    self_p->get().second.call(caller, lib1, tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(stdWith)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id_with);

    PMaybe lib1(nullptr);
    self_p->get().first.call<true>(caller, lib, lib1);
    // TODO: hard binding
    self_p->get().second.call(caller,
        _pair(_quote(PVal(lib)), PVal(lib1), id_use, stdUse),
    tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(stdDef)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id_def);

    PMaybe val(nullptr);
    self_p->get().call<true>(caller, lib, val);

    if (tunnel) {
        libSet(PVal(val), lib, tunnel);
    } else {
        libGet(PVal(val), lib, tunnel);
    }
_COTL_FUNC_END

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe tunnel1(
        _libmap(
            id_use, _libfunc(stdUse),
            id_with, _libfunc(stdWith),
            id_def, _libfunc(stdDef)
        )
    );

    libSet(id_query, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_lib);

}

}
