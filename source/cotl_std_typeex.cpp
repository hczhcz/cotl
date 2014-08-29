#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(stdincrement)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Int>()) {
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

_COTL_FUNC_T(stddecrement)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Int>()) {
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

_COTL_FUNC_T(stdlibfunc)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Func>()) {
        self_p->get()(caller, self, lib, tunnel);
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdwrapptr)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Ptr>()) {
        if (tunnel) {
            if (auto tunnel_p = tunnel.as<cotl::Ptr>()) {
                PMaybe tunnel1(tunnel_p->get());

                self_p->get()(self, lib, tunnel1);

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

            self_p->get()(self, lib, tunnel1);

            tunnel = _ptr(
                tunnel1,
                self_p->getType(), self_p->getFunc()
            );
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdrefptr)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Ptr>()) {
        self_p->get()(self, lib, tunnel);
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdwrappair)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Pair>()) {
        if (tunnel) {
            if (auto tunnel_p = tunnel.as<cotl::Pair>()) {
                PMaybe tunnel1(tunnel_p->get().first);
                PMaybe tunnel2(tunnel_p->get().second);

                self_p->get().first(self, lib, tunnel1);
                self_p->get().second(self, lib, tunnel2);

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

            self_p->get().first(self, lib, tunnel1);
            self_p->get().second(self, lib, tunnel2);

            tunnel = _pair(
                tunnel1, tunnel2,
                self_p->getType(), self_p->getFunc()
            );
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdwraparr)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Arr>()) {
        if (tunnel) {
            if (auto tunnel_p = tunnel.as<cotl::Arr>()) {
                map_t &self_data = self_p->getVar();
                map_t &tunnel_data = tunnel_p->getVar();

                for (auto &val: *self_data) {
                    PMaybe tunnel1(tunnel_data->at(val.first));

                    val.second(self, lib, tunnel1);

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

            map_t &self_data = self_p->getVar();
            map_t &tunnel_data = tunnel_p->getVar();

            for (auto &val: *self_data) {
                PMaybe tunnel1(nullptr);

                val.second(self, lib, tunnel1);

                tunnel_data->insert({{val.first, tunnel1}});
            }

            tunnel = tunnel_p;
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdstack)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Arr>()) {
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

}
