#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    if (tunnel) {
        throw;
    } else {
        PMaybe query(_atom(id_std));
        PMaybe map(nullptr);

        query.call<true>(caller, lib, map); // _COTL_CALL

        if (auto map_p = map.raw<cotl::Map>()) {
            map_t &map_data = map_p->getVar();

            {
                PMaybe query1(_atom(id_type));
                PMaybe map1(nullptr);

                query1.call<true>(caller, lib, map1); // _COTL_CALL

                if (auto map1_p = map1.as<cotl::Map>()) {
                    const map_t &map1_data = map1_p->get();
                    map_data->insert(map1_data->begin(), map1_data->end());
                } else {
                    throw;
                }
            }

            {
                PMaybe query1(_atom(id_runtime));
                PMaybe map1(nullptr);

                query1.call<true>(caller, lib, map1); // _COTL_CALL

                if (auto map1_p = map1.as<cotl::Map>()) {
                    const map_t &map1_data = map1_p->get();
                    map_data->insert(map1_data->begin(), map1_data->end());
                } else {
                    throw;
                }
            }
        } else {
            throw;
        }
    }
_COTL_FUNC_END

long long ago = addInitializer(init, init_lib_after);

}

}
