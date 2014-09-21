#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(stdIncrement)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF_VAR(cotl::Int, id_increment);

    if (tunnel) {
        _COTL_CHECK_TYPE(tunnel, cotl::Int, id_any);

        self_p->set(tunnel_p->get());
        tunnel = nullptr;
    } else {
        ++(self_p->getVar());
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdDecrement)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF_VAR(cotl::Int, id_decrement);

    if (tunnel) {
        _COTL_CHECK_TYPE(tunnel, cotl::Int, id_any);

        self_p->set(tunnel_p->get());
        tunnel = nullptr;
    } else {
        --(self_p->getVar());
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdRefPtr)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id_refptr);

    self_p->get().call(caller, lib, tunnel);
_COTL_FUNC_END

_COTL_FUNC_T(stdStack)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Arr, id_stack);

    const arr_t &data = self_p->get();
    if (tunnel) {
        PVal helper(tunnel); // for libstdc++ without gc
        data->push_back(helper);
        tunnel = nullptr;
    } else {
        tunnel = data->back();
        data->pop_back();
    }
_COTL_FUNC_END

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe tunnel1(
        _libmap(
            id_null, _libfunc(stdLiteral),
            id_false, _libfunc(stdLiteral),
            id_true, _libfunc(stdLiteral),
            id_increment, _libfunc(stdIncrement),
            id_decrement, _libfunc(stdDecrement),
            id_refptr, _libfunc(stdRefPtr),
            id_stack, _libfunc(stdStack)
        )
    );

    libSet(id_type_misc, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_core);

}

}
