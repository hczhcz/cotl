#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    if (tunnel) {
        throw "bad tunnel";
    } else {
        PMaybe tunnel1(lib);
        libExec<true>(id_std, self, tunnel1);

        if (auto map_p = tunnel1.raw<cotl::Map>()) {
            map_t &map_data = map_p->getVar();

            {
                PMaybe tunnel2(lib);
                libExec<true>(id_type, self, tunnel2);

                if (auto map2_p = tunnel2.as<cotl::Map>()) {
                    const map_t &map1_data = map2_p->get();
                    map_data->insert(map1_data->begin(), map1_data->end());
                } else {
                    throw "bad map type";
                }
            }

            {
                PMaybe tunnel2(lib);
                libExec<true>(id_runtime, self, tunnel2);

                if (auto map2_p = tunnel2.as<cotl::Map>()) {
                    const map_t &map1_data = map2_p->get();
                    map_data->insert(map1_data->begin(), map1_data->end());
                } else {
                    throw "bad map type";
                }
            }
        } else {
            throw "bad map type";
        }
    }
_COTL_FUNC_END

long long ago = addInitializer(init, init_lib_after);

}

}
