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

_COTL_FUNC_T(stdWarpArr)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Arr>()) {
        if (tunnel) {
            if (auto tunnel_p = tunnel.as<cotl::Arr>()) {
                const arr_t &self_data = self_p->get();
                const arr_t &tunnel_data = tunnel_p->get();

                if (self_data->size() != tunnel_data->size()) {
                    throw;
                }

                // notice: without range check
                for (size_t i = 0; i != self_data->size(); ++i) {
                    PMaybe tunnel1((*tunnel_data)[i]);

                    (*self_data)[i](caller, lib, tunnel1); // _COTL_CALL

                    if (tunnel1) {
                        throw;
                    }
                }

                tunnel = nullptr;
            } else {
                throw;
            }
        } else {
            auto tunnel_p = _arr(self_p->getType(), self_p->getFunc());

            const arr_t &self_data = self_p->get();
            arr_t &tunnel_data = tunnel_p->getVar();

            // notice: without range check
            for (size_t i = 0; i != self_data->size(); ++i) {
                PMaybe tunnel1(nullptr);

                (*self_data)[i](caller, lib, tunnel1); // _COTL_CALL

                tunnel_data->push_back(tunnel1);
            }

            tunnel = tunnel_p;
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdStack)
_COTL_FUNC_BEGIN
    if (auto self_p = self.raw<cotl::Arr>()) {
        arr_t &data = self_p->getVar();
        if (tunnel) {
            data->push_back(tunnel);
            tunnel = nullptr;
        } else {
            tunnel = data->back();
            data->pop_back();
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

_COTL_FUNC_T(stdLibMap)
_COTL_FUNC_BEGIN
    if (auto self_p = self.raw<cotl::Map>()) {
        if (caller){
            if (tunnel) {
                self_p->getVar()->at(caller->getType()) = tunnel;

                tunnel = nullptr;
            } else {
                tunnel = self_p->get()->at(caller->getType());
            }
        } else {
            throw;
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
