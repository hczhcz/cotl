#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(published::stdLibFunc)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Func, id_func);

    self_p->get()(PVal(caller), nullptr, lib, tunnel); // _COTL_CALL
_COTL_FUNC_END

_COTL_FUNC_T(published::stdLibMap)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Map, id_map);

    int_t type = caller->getType();

    if (self_p->get()->count(type)) {
        if (tunnel) {
            self_p->get()->at(type) = tunnel;

            tunnel = nullptr;
        } else {
            tunnel = self_p->get()->at(type);
        }
    } else {
        // key not found
        if (tunnel) {
            // insert new item
            self_p->get()->insert({{type, PVal(tunnel)}});

            tunnel = nullptr;
        } else {
            // call (next) lib
            if (lib) {
                libGet(PVal(caller), lib, tunnel);
            } else {
                tunnel = nullptr; // TODO
                // throw "bad lib query";
            }
        }
    }
_COTL_FUNC_END

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe tunnel1(
        _libmap(
            id_func, _libfunc(stdLibFunc),
            id_map, _libfunc(stdLibMap)
        )
    );

    libSet<id_std, id_type>(id_type_lib, lib, tunnel1);
_COTL_FUNC_END

long long ago = addInitializer(init, init_core_1);

}

}
