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

    self_p->get().call(caller, lib, tunnel); // TODO limit?
_COTL_FUNC_END

_COTL_FUNC_T(stdTarget)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id_target);
    _COTL_CHECK_TUNNEL(true);

    self_p->get().call(caller, lib, tunnel); // TODO limit?
_COTL_FUNC_END

_COTL_FUNC_T(stdRef)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id_ref);

    self_p->get().call(caller, lib, tunnel);
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
    // TODO: hard binding
    self_p->get().second.call(caller,
        _pair(_quote(PVal(lib)), PVal(map), id_use, stdUse),
    tunnel);
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

            id_exec, _libfunc(stdExec),
            id_write, _libfunc(stdWrite),

            id_caller, _libfunc(stdCaller),
            id_lib, _libfunc(stdLib),

            id_use, _libfunc(stdUse),
            id_with, _libfunc(stdWith)
        )
    );

    libSet(id_runtime, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_core);

}

}
