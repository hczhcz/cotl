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

_COTL_FUNC_T(stdLibFunc)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Func>()) {
        if (caller) {
            PMaybe caller1(nullptr);
            self_p->get()(caller, caller1, lib, tunnel); // _COTL_CALL
        } else {
            throw;
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdWrapPtr)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Ptr>()) {
        if (tunnel) {
            if (auto tunnel_p = tunnel.as<cotl::Ptr>()) {
                PMaybe tunnel1(tunnel_p->get());

                self_p->get()(caller, lib, tunnel1); // _COTL_CALL

                if (tunnel1) {
                    throw;
                } else {
                    tunnel = nullptr;
                }
            } else {
                throw;
            }
        } else {
            PMaybe tunnel1(nullptr);

            self_p->get()(caller, lib, tunnel1); // _COTL_CALL

            tunnel = _ptr(
                tunnel1,
                self_p->getType(), self_p->getFunc()
            );
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

_COTL_FUNC_T(stdWrapPair)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Pair>()) {
        if (tunnel) {
            if (auto tunnel_p = tunnel.as<cotl::Pair>()) {
                PMaybe tunnel1(tunnel_p->get().first);
                PMaybe tunnel2(tunnel_p->get().second);

                self_p->get().first(caller, lib, tunnel1); // _COTL_CALL
                self_p->get().second(caller, lib, tunnel2); // _COTL_CALL

                if (tunnel1 || tunnel2) {
                    throw;
                } else {
                    tunnel = nullptr;
                }
            } else {
                throw;
            }
        } else {
            PMaybe tunnel1(nullptr);
            PMaybe tunnel2(nullptr);

            self_p->get().first(caller, lib, tunnel1); // _COTL_CALL
            self_p->get().second(caller, lib, tunnel2); // _COTL_CALL

            tunnel = _pair(
                tunnel1, tunnel2,
                self_p->getType(), self_p->getFunc()
            );
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdWrapMap)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Map>()) {
        if (tunnel) {
            if (auto tunnel_p = tunnel.as<cotl::Map>()) {
                const map_t &self_data = self_p->get();
                const map_t &tunnel_data = tunnel_p->get();

                for (auto &val: *self_data) {
                    PMaybe tunnel1(tunnel_data->at(val.first));

                    val.second(caller, lib, tunnel1); // _COTL_CALL

                    if (tunnel1) {
                        throw;
                    }
                }

                tunnel = nullptr;
            } else {
                throw;
            }
        } else {
            auto tunnel_p = _map(self_p->getType(), self_p->getFunc());

            const map_t &self_data = self_p->get();
            map_t &tunnel_data = tunnel_p->getVar();

            for (auto &val: *self_data) {
                PMaybe tunnel1(nullptr);

                val.second(caller, lib, tunnel1); // _COTL_CALL

                tunnel_data->insert({{val.first, tunnel1}});
            }

            tunnel = tunnel_p;
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdStack)
_COTL_FUNC_BEGIN
    if (auto self_p = self.raw<cotl::Map>()) {
        map_t &data = self_p->getVar();
        if (tunnel) {
            data->insert({{data->size(), tunnel}});
            tunnel = nullptr;
        } else {
            tunnel = data->at(data->size() - 1);
            data->erase(data->size() - 1);
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(initTypeEx)
_COTL_FUNC_BEGIN
    // TODO

_COTL_FUNC_END

namespace {

long long ago = addInitializer(initTypeEx);

}

}
