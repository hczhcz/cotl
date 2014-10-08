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

_COTL_FUNC_T(published::stdQuote)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id_quote);
    _COTL_CHECK_TUNNEL(false);

    tunnel = self_p->get();
_COTL_FUNC_END

_COTL_FUNC_T(published::stdBlackhole)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF_VAR(cotl::Ptr, id_blackhole);
    _COTL_CHECK_TUNNEL(true);

    self_p->set(PVal(tunnel));
    tunnel = nullptr;
_COTL_FUNC_END

_COTL_FUNC_T(published::stdContainer)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF_VAR(cotl::Ptr, id_container);

    if (tunnel) {
        self_p->set(PVal(tunnel));
        tunnel = nullptr;
    } else {
        tunnel = self_p->get();
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdConst)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id_const);
    _COTL_CHECK_TUNNEL(false);

    self_p->get().call(caller, lib, tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(stdTarget)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id_target);
    _COTL_CHECK_TUNNEL(true);

    self_p->get().call(caller, lib, tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(stdRef)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id_ref);

    self_p->get().call(caller, lib, tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(stdBefore)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id_before);

    PMaybe data(nullptr);
    self_p->get().first.call<false>(caller, lib, data);

    self_p->get().second.call(caller, lib, tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(stdAfter)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id_after);

    self_p->get().first.call(caller, lib, tunnel);

    PMaybe data(nullptr);
    self_p->get().second.call<false>(caller, lib, data);
_COTL_FUNC_END

_COTL_FUNC_T(stdAlso)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id_also);
    _COTL_CHECK_TUNNEL(false); // TODO with tunnel input?

    PMaybe tunnel1(nullptr);
    PMaybe tunnel2(nullptr);

    self_p->get().first.call(caller, lib, tunnel1);
    self_p->get().second.call(caller, lib, tunnel2);

    if (tunnel1 && tunnel2) {
        tunnel = _pair(PVal(tunnel1), PVal(tunnel2), id_also);
    } else if (tunnel1) {
        tunnel = tunnel1;
    } else if (tunnel2) {
        tunnel = tunnel2;
    } else {
        tunnel = nullptr;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdVoid)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id_void);
    _COTL_CHECK_TUNNEL(false);

    self_p->get().call(caller, lib, tunnel);
    tunnel = nullptr; // throw away
_COTL_FUNC_END

_COTL_FUNC_T(stdExec)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id_exec);

    PMaybe data(nullptr);
    self_p->get().call<true>(caller, lib, data);
    data.call(caller, lib, tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(stdWrite)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id_write);
    _COTL_CHECK_TUNNEL(false);

    PMaybe data(nullptr);
    self_p->get().first.call<true>(caller, lib, data);
    self_p->get().second.call<false>(caller, lib, data);
_COTL_FUNC_END

_COTL_FUNC_T(stdIftunnel)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id_iftunnel);

    if (tunnel) {
        self_p->get().first.call(caller, lib, tunnel);
    } else {
        self_p->get().second.call(caller, lib, tunnel);
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

_COTL_FUNC_T(stdTry)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id_try);

    try {
        self_p->get().first.call(caller, lib, tunnel);
    } catch (...) {
        self_p->get().second.call(caller, lib, tunnel);
    }
_COTL_FUNC_END

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe tunnel1(
        _libmap(
            id_auto, _libfunc(stdAuto),
            id_literal, _libfunc(stdLiteral),
            id_bind, _libfunc(stdBind),

            id_quote, _libfunc(stdQuote),
            id_blackhole, _libfunc(stdBlackhole),
            id_container, _libfunc(stdContainer),

            id_const, _libfunc(stdConst),
            id_target, _libfunc(stdTarget),
            id_ref, _libfunc(stdRef),

            id_before, _libfunc(stdBefore),
            id_after, _libfunc(stdAfter),
            id_also, _libfunc(stdAlso),

            id_void, _libfunc(stdVoid),
            id_exec, _libfunc(stdExec),
            id_write, _libfunc(stdWrite),
            id_iftunnel, _libfunc(stdIftunnel),

            id_caller, _libfunc(stdCaller),
            id_lib, _libfunc(stdLib),

            id_try, _libfunc(stdTry)
        )
    );

    libSet<id_std>(id_runtime, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_core);

}

}
