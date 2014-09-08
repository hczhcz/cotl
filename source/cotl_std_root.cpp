#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    if (tunnel) {
        throw;
    } else {
        PMaybe lib1(nullptr);
        PMaybe map(nullptr);

        lib.call<true>(self, lib1, map); // _COTL_CALL

        if (auto map_p = map.raw<cotl::Map>()) {
            map_t &map_data = map_p->getVar();

            if (auto map2_p = map_data->at(id_type).as<cotl::Map>()) {
                const map_t &map2_data = map2_p->get();
                map_data->insert(map2_data->begin(), map2_data->end());
            } else {
                throw;
            }

            if (auto map2_p = map_data->at(id_runtime).as<cotl::Map>()) {
                const map_t &map2_data = map2_p->get();
                map_data->insert(map2_data->begin(), map2_data->end());
            } else {
                throw;
            }
        } else {
            throw;
        }
    }
_COTL_FUNC_END

long long ago = addInitializer(init, init_lib_after);

}

}
