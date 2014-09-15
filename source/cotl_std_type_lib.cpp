#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(published::stdLibFunc)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Func>()) {
        self_p->get()(PVal(caller), nullptr, lib, tunnel); // _COTL_CALL
    } else {
        throw "bad self type";
    }
_COTL_FUNC_END

_COTL_FUNC_T(published::stdLibMap)
_COTL_FUNC_BEGIN
    if (auto self_p = self.raw<cotl::Map>()) {
        int_t type = caller->getType();

        if (self_p->get()->count(type)) {
            if (tunnel) {
                self_p->getVar()->at(type) = tunnel;

                tunnel = nullptr;
            } else {
                tunnel = self_p->get()->at(type);
            }
        } else {
            // key not found
            if (tunnel) {
                // insert new item
                self_p->getVar()->insert({{type, PVal(tunnel)}});

                tunnel = nullptr;
            } else {
                // call (next) lib
                if (lib) {
                    libGet(caller, lib, tunnel);
                } else {
                    throw "bad lib query";
                }
            }
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
                id_func, _libfunc(stdLibFunc),
                id_map, _libfunc(stdLibMap)
            ), id_quote)
        );

        libSet(id_type_lib, lib, tunnel1);
    }
_COTL_FUNC_END

long long ago = addInitializer(init, init_core);

}

}
