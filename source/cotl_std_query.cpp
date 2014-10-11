#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(published::stdUse)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id_use);

    PMaybe lib1(nullptr);
    self_p->get().first.call<true>(caller, lib, lib1);

    // TODO: hard binding

    self_p->get().second.call(caller, lib1, tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(published::stdWith)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id_with);

    PMaybe lib1(nullptr);
    self_p->get().first.call<true>(caller, lib, lib1);

    // TODO: hard binding

    self_p->get().second.call(caller,
        _pair(_quote(PVal(lib)), PVal(lib1), id_use, stdUse),
    tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(published::stdWithnew)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id_withnew);

    self_p->get().call(caller,
        _pair(_quote(PVal(lib)), _libmap(), id_use, stdUse),
    tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(published::stdCapture)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id_capture);

    self_p->get().call(caller,
        _pair(
            _quote(PVal(lib)),
            _libmap(
                id_caller, caller.sure(),
                id_global, lib.sure()
            ),
            id_use, stdUse
        ),
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

_COTL_FUNC_T(stdQuickdef)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id_quickdef);

    if (tunnel) {
        libSet(self_p->get(), lib, tunnel);
    } else {
        libGet(self_p->get(), lib, tunnel);
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
            id_withnew, _libfunc(stdWithnew),
            id_capture, _libfunc(stdCapture),
            id_def, _libfunc(stdDef),
            id_quickdef, _libfunc(stdQuickdef)
        )
    );

    libSet<id_std>(id_query, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_lib);

}

}
