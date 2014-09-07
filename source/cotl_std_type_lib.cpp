#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(published::stdLibFunc)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Func>()) {
        PMaybe caller1(nullptr);
        self_p->get()(caller, caller1, lib, tunnel); // _COTL_CALL
    } else {
        throw;
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
                self_p->getVar()->insert(std::pair<int_t, PVal>(type, tunnel));

                tunnel = nullptr;
            } else {
                // call (next) lib
                PMaybe lib1(nullptr);

                lib(caller, lib1, tunnel); // _COTL_CALL
            }
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
