#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe tunnel1(nullptr);
    libExec<true>(id_std, self, lib, tunnel1);

    if (auto map_p = tunnel1.raw<cotl::Map, id_map>()) {
        map_t &map_data = map_p->getVar();

        {
            PMaybe tunnel2(nullptr);
            libExec<true>(id_type, self, lib, tunnel2);

            if (auto map2_p = tunnel2.as<cotl::Map, id_map>()) {
                const map_t &map1_data = map2_p->get();
                map_data->insert(map1_data->begin(), map1_data->end());
            } else {
                throw "bad map type";
            }
        }

        {
            PMaybe tunnel2(nullptr);
            libExec<true>(id_runtime, self, lib, tunnel2);

            if (auto map2_p = tunnel2.as<cotl::Map, id_map>()) {
                const map_t &map1_data = map2_p->get();
                map_data->insert(map1_data->begin(), map1_data->end());
            } else {
                throw "bad map type";
            }
        }
    } else {
        throw "bad map type";
    }
_COTL_FUNC_END

long long ago = addInitializer(init, init_lib_after);

}

}
