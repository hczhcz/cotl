#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(published::stdAuto)
_COTL_FUNC_BEGIN
    PMaybe func(nullptr);

    lib(self, lib, func); // _COTL_CALL

    if (func) {
        func(self, lib, tunnel); // _COTL_CALL
    } else {
        throw;
    }
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
    PMaybe func(nullptr);

    lib(self, lib, func); // _COTL_CALL

    if (func) {
        if (auto func_p = func.as<cotl::Func>()) {
            self.raw()->setFunc(func_p->get());
            self(caller, lib, tunnel); // _COTL_CALL
        } else {
            throw;
        }
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
    // TODO

_COTL_FUNC_END

long long ago = addInitializer(init);

}

}
