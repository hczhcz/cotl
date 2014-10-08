#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(stdIncrement)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF_VAR(cotl::Int, id_increment);

    if (tunnel) {
        _COTL_CHECK_TYPE(tunnel, cotl::Int, id_int); // TODO tunnel cast

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
        _COTL_CHECK_TYPE(tunnel, cotl::Int, id_int); // TODO tunnel cast

        self_p->set(tunnel_p->get());
        tunnel = nullptr;
    } else {
        --(self_p->getVar());
    }
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

_COTL_FUNC_T(stdCode)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Arr, id_code);
    _COTL_CHECK_TUNNEL(false);

    const arr_t &self_data = self_p->get();

    for (size_t i = 0; i != self_data->size(); ++i) {
        PMaybe tunnel1(nullptr);

        (*self_data)[i].call<false>(caller, lib, tunnel1);
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
            id_stack, _libfunc(stdStack),
            id_code, _libfunc(stdCode)
        )
    );

    libSet<id_std, id_type>(id_type_misc, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_core_1);

}

}
