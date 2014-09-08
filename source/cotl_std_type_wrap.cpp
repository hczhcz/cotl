#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

_COTL_FUNC_T(stdWrapAtom)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Atom>()) {
        if (tunnel) {
            throw;
        } else {
            tunnel = _atom(
                self_p->getType(), self_p->getFunc()
            );
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdWrapInt)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Int>()) {
        if (tunnel) {
            throw;
        } else {
            tunnel = _int(
                self_p->get(),
                self_p->getType(), self_p->getFunc()
            );
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdWrapReal)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Real>()) {
        if (tunnel) {
            throw;
        } else {
            tunnel = _real(
                self_p->get(),
                self_p->getType(), self_p->getFunc()
            );
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdWrapFunc)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Func>()) {
        if (tunnel) {
            throw;
        } else {
            tunnel = _func(
                self_p->get(),
                self_p->getType(), self_p->getFunc()
            );
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(published::stdWrapPtr)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Ptr>()) {
        if (tunnel) {
            if (auto tunnel_p = tunnel.as<cotl::Ptr>()) {
                PMaybe tunnel1(tunnel_p->get());

                self_p->get().call<false>(caller, lib, tunnel1); // _COTL_CALL

                tunnel = nullptr;
            } else {
                throw;
            }
        } else {
            PMaybe tunnel1(nullptr);

            self_p->get().call<true>(caller, lib, tunnel1); // _COTL_CALL

            tunnel = _ptr(
                tunnel1,
                self_p->getType(), self_p->getFunc()
            );
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(published::stdWrapPair)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Pair>()) {
        if (tunnel) {
            if (auto tunnel_p = tunnel.as<cotl::Pair>()) {
                PMaybe tunnel1(tunnel_p->get().first);
                PMaybe tunnel2(tunnel_p->get().second);

                self_p->get().first.call<false>(caller, lib, tunnel1); // _COTL_CALL
                self_p->get().second.call<false>(caller, lib, tunnel2); // _COTL_CALL

                tunnel = nullptr;
            } else {
                throw;
            }
        } else {
            PMaybe tunnel1(nullptr);
            PMaybe tunnel2(nullptr);

            self_p->get().first.call<true>(caller, lib, tunnel1); // _COTL_CALL
            self_p->get().second.call<true>(caller, lib, tunnel2); // _COTL_CALL

            tunnel = _pair(
                tunnel1, tunnel2,
                self_p->getType(), self_p->getFunc()
            );
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(stdWrapStr)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Str>()) {
        if (tunnel) {
            throw;
        } else {
            tunnel = _str(
                self_p->get(),
                self_p->getType(), self_p->getFunc()
            );
        }
    } else {
        throw;
    }
_COTL_FUNC_END

_COTL_FUNC_T(published::stdWrapArr)
_COTL_FUNC_BEGIN
    if (auto self_p = self.as<cotl::Arr>()) {
        if (tunnel) {
            if (auto tunnel_p = tunnel.as<cotl::Arr>()) {
                const arr_t &self_data = self_p->get();
                const arr_t &tunnel_data = tunnel_p->get();

                if (self_data->size() == tunnel_data->size()) {
                    // notice: without range check
                    for (size_t i = 0; i != self_data->size(); ++i) {
                        PMaybe tunnel1((*tunnel_data)[i]);

                        (*self_data)[i].call<false>(caller, lib, tunnel1); // _COTL_CALL
                    }

                    tunnel = nullptr;
                } else {
                    throw;
                }
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

                (*self_data)[i].call<true>(caller, lib, tunnel1); // _COTL_CALL

                PVal helper(tunnel1); // notice: use copy constructor in push_back
                tunnel_data->push_back(helper);
            }

            tunnel = tunnel_p;
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
                    if (tunnel_data->count(val.first)) {
                        PMaybe tunnel1(tunnel_data->at(val.first));

                        val.second.call<false>(caller, lib, tunnel1); // _COTL_CALL
                    } else {
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

                val.second.call<true>(caller, lib, tunnel1); // _COTL_CALL

                tunnel_data->insert({{val.first, tunnel1}});
            }

            tunnel = tunnel_p;
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
        PMaybe tunnel1(
            _ptr(_libmap(
                id_atom, _libfunc(stdWrapAtom),
                id_int, _libfunc(stdWrapInt),
                id_real, _libfunc(stdWrapReal),
                id_func, _libfunc(stdWrapFunc),
                id_ptr, _libfunc(stdWrapPtr),
                id_pair, _libfunc(stdWrapPair),
                id_str, _libfunc(stdWrapStr),
                id_arr, _libfunc(stdWrapArr),
                id_map, _libfunc(stdWrapMap)
                // TODO: really necessary?
                // id_error, _libfunc(stdWrapErr)
            ), id_quote)
        );

        lib.call<false>(_atom(id_type_wrap), nullptr, tunnel1); // _COTL_CALL
    }
_COTL_FUNC_END

long long ago = addInitializer(init, init_core);

}

}
