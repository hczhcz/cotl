#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(published::stdAuto)
_COTL_FUNC_BEGIN
    PMaybe lib1(nullptr);
    PMaybe func(nullptr);

    lib(self, lib1, func); // _COTL_CALL

    func(self, lib, tunnel); // _COTL_CALL
_COTL_FUNC_END

_COTL_FUNC_T(published::stdLiteral)
_COTL_FUNC_BEGIN
    if (tunnel) {
        throw;
    } else {
        tunnel = self;
    }
_COTL_FUNC_END

_COTL_FUNC_T(published::stdBind)
_COTL_FUNC_BEGIN
    PMaybe lib1(nullptr);
    PMaybe func(nullptr);

    lib(self, lib1, func); // _COTL_CALL

    if (auto func_p = func.as<cotl::Func>()) {
        self.raw()->setFunc(func_p->get());
        self(caller, lib, tunnel); // _COTL_CALL
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdQuote)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Ptr>()) {
        if (tunnel) {
            throw;
        } else {
            tunnel = self_p->get();
        }
    } else {
        throw;
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
        throw;
    }
_COTL_FUNC_END

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    PMaybe caller1(nullptr);
    PMaybe lib1(nullptr);
    PMaybe tunnel1(nullptr);

    caller1 = _atom(id_auto);
    tunnel1 = _func(stdAuto, id_func, stdLibFunc);
    lib.call<false>(caller1, lib1, tunnel1); // _COTL_CALL

    caller1 = _atom(id_literal);
    tunnel1 = _func(stdLiteral, id_func, stdLibFunc);
    lib.call<false>(caller1, lib1, tunnel1); // _COTL_CALL

    caller1 = _atom(id_bind);
    tunnel1 = _func(stdBind, id_func, stdLibFunc);
    lib.call<false>(caller1, lib1, tunnel1); // _COTL_CALL

    caller1 = _atom(id_quote);
    tunnel1 = _func(stdQuote, id_func, stdLibFunc);
    lib.call<false>(caller1, lib1, tunnel1); // _COTL_CALL

    caller1 = _atom(id_contain);
    tunnel1 = _func(stdContain, id_func, stdLibFunc);
    lib.call<false>(caller1, lib1, tunnel1); // _COTL_CALL
_COTL_FUNC_END

long long ago = addInitializer(init);

}

}
