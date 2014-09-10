#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(published::stdAuto)
_COTL_FUNC_BEGIN
    PMaybe func(nullptr);

    lib.call<true>(self, nullptr, func);

    func.call(self, lib, tunnel);
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

    lib.call<true>(self, nullptr, func);

    if (auto func_p = func.as<cotl::Func>()) {
        self.raw()->setFunc(func_p->get());
        self.call(caller, lib, tunnel);
    } else {
        throw "bad func type";
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdQuote)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Ptr>()) {
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
    if (auto self_p = self.raw<cotl::Ptr>()) {
        if (tunnel) {
            self_p->getVar() = tunnel;
            tunnel = nullptr;
        } else {
            tunnel = self_p->get();
        }
    } else {
        throw "bad self type";
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
                id_contain, _libfunc(stdContain)
            ), id_quote)
        );

        lib.call<false>(_atom(id_runtime), nullptr, tunnel1);

        // hack
        PMaybe tunnel2(_libfunc(stdQuote));
        lib.call<false>(_atom(id_quote), nullptr, tunnel2);
    }
_COTL_FUNC_END

long long ago = addInitializer(init, init_core);

}

}
