#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(stdIncrement)
_COTL_FUNC_BEGIN
    if (auto self_p = self.raw<cotl::Int>()) {
        if (tunnel) {
            if (auto tunnel_p = tunnel.as<cotl::Int>()) {
                self_p->getVar() = tunnel_p->get();
                tunnel = nullptr;
            } else {
                throw;
            }
        } else {
            ++(self_p->getVar());
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdDecrement)
_COTL_FUNC_BEGIN
    if (auto self_p = self.raw<cotl::Int>()) {
        if (tunnel) {
            if (auto tunnel_p = tunnel.as<cotl::Int>()) {
                self_p->getVar() = tunnel_p->get();
                tunnel = nullptr;
            } else {
                throw;
            }
        } else {
            --(self_p->getVar());
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdRefPtr)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Ptr>()) {
        self_p->get()(caller, lib, tunnel); // _COTL_CALL
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdStack)
_COTL_FUNC_BEGIN
    if (auto self_p = self.raw<cotl::Arr>()) {
        arr_t &data = self_p->getVar();
        if (tunnel) {
            PVal helper(tunnel); // notice: use copy constructor in push_back
            data->push_back(helper);
            tunnel = nullptr;
        } else {
            tunnel = data->back();
            data->pop_back();
        }
    } else {
        throw;
    }
_COTL_FUNC_END

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    if (tunnel) {
        throw;
    } else {
        lib.call<false>(
            _atom(id_type_misc),
            _ptr(_libmap(
                id_null, _libfunc(stdLiteral),
                id_false, _libfunc(stdLiteral),
                id_true, _libfunc(stdLiteral),
                id_increment, _libfunc(stdIncrement),
                id_decrement, _libfunc(stdDecrement),
                id_refptr, _libfunc(stdRefPtr),
                id_stack, _libfunc(stdStack)
            ), id_quote),
            tunnel
        );
    }
_COTL_FUNC_END

long long ago = addInitializer(init, init_core);

}

}
