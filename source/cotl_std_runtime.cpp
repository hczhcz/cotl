#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(published::stdAuto)
_COTL_FUNC_BEGIN
    libExec(self, self, lib, tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(published::stdLiteral)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    tunnel = self;
_COTL_FUNC_END

_COTL_FUNC_T(published::stdBind)
_COTL_FUNC_BEGIN
    PMaybe func(nullptr);

    libGet(self, lib, func);

    _COTL_CHECK_TYPE(func, cotl::Func, id_func);

    self.raw()->setFunc(func_p->get());
    self.call(caller, lib, tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(stdQuote)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id_quote);
    _COTL_CHECK_TUNNEL(false);

    tunnel = self_p->get();
_COTL_FUNC_END

_COTL_FUNC_T(stdContain)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF_VAR(cotl::Ptr, id_contain);

    if (tunnel) {
        self_p->set(PVal(tunnel));
        tunnel = nullptr;
    } else {
        tunnel = self_p->get();
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdCaller)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Atom, id_caller);
    _COTL_CHECK_TUNNEL(false);

    tunnel = caller;
_COTL_FUNC_END

_COTL_FUNC_T(stdLib)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Atom, id_lib);
    _COTL_CHECK_TUNNEL(false);

    tunnel = lib;
_COTL_FUNC_END

_COTL_FUNC_T(stdUse)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id_use);

    PMaybe map(nullptr);
    self_p->get().first.call<true>(caller, lib, map);
    // TODO: hard binding
    self_p->get().second.call(caller, map, tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(stdWith)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id_with);

    PMaybe map(nullptr);
    self_p->get().first.call<true>(caller, lib, map);
    self_p->get().second.call(caller,
        _pair(_ptr(PVal(lib), id_quote, stdQuote), PVal(map), id_use, stdUse),
    tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(stdWrite)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id_write);

    PMaybe data(nullptr);
    self_p->get().first.call<true>(caller, lib, data);
    self_p->get().second.call<false>(caller, lib, data);
_COTL_FUNC_END

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe tunnel1(
        _ptr(_libmap(
            id_auto, _libfunc(stdAuto),
            id_literal, _libfunc(stdLiteral),
            id_bind, _libfunc(stdBind),
            id_quote, _libfunc(stdQuote),
            id_contain, _libfunc(stdContain),
            id_caller, _libfunc(stdCaller),
            id_lib, _libfunc(stdLib),
            id_use, _libfunc(stdUse),
            id_with, _libfunc(stdWith),
            id_write, _libfunc(stdWrite)
        ), id_quote)
    );

    libSet(id_runtime, lib, tunnel1);

    // hack
    PMaybe tunnel2(_libfunc(stdQuote));

    libSet(id_quote, lib, tunnel2);
_COTL_FUNC_END

long long ago = addInitializer(init, init_core);

}

}
