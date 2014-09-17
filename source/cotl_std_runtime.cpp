#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(published::stdAuto)
_COTL_FUNC_BEGIN
    libExec(self, self, lib, tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(published::stdLiteral)
_COTL_FUNC_BEGIN
    if (tunnel) {
        throw "bad tunnel";
    } else {
        tunnel = self;
    }
_COTL_FUNC_END

_COTL_FUNC_T(published::stdBind)
_COTL_FUNC_BEGIN
    PMaybe func(nullptr);

    libGet(self, lib, func);

    if (auto func_p = func.as<cotl::Func, id_func>()) {
        self.raw()->setFunc(func_p->get());
        self.call(caller, lib, tunnel);
    } else {
        throw "bad func type";
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdQuote)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Ptr, id_quote>()) {
        if (tunnel) {
            throw "bad tunnel";
        } else {
            tunnel = self_p->get();
        }
    } else {
        throw "bad self type";
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdContain)
_COTL_FUNC_BEGIN
    if (auto self_p = self.raw<cotl::Ptr, id_contain>()) {
        if (tunnel) {
            self_p->set(PVal(tunnel));
            tunnel = nullptr;
        } else {
            tunnel = self_p->get();
        }
    } else {
        throw "bad self type";
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdCaller)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Atom, id_caller>()) {
        if (tunnel) {
            throw "bad tunnel";
        } else {
            tunnel = caller;
        }
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdLib)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Atom, id_lib>()) {
        if (tunnel) {
            throw "bad tunnel";
        } else {
            tunnel = lib;
        }
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdUse)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Pair, id_use>()) {
        PMaybe map(nullptr);
        self_p->get().first.call<true>(caller, lib, map);
        // TODO: hard binding
        self_p->get().second.call(caller, map, tunnel);
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdWith)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Pair, id_with>()) {
        PMaybe map(nullptr);
        self_p->get().first.call<true>(caller, lib, map);
        self_p->get().second.call(caller,
            _pair(_ptr(PVal(lib), id_quote, stdQuote), PVal(map), id_use, stdUse),
        tunnel);
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdWrite)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Pair, id_write>()) {
        PMaybe data(nullptr);
        self_p->get().first.call<true>(caller, lib, data);
        self_p->get().second.call<false>(caller, lib, data);
    }
_COTL_FUNC_END

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    if (tunnel) {
        throw "bad tunnel";
    } else {
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
    }
_COTL_FUNC_END

long long ago = addInitializer(init, init_core);

}

}
