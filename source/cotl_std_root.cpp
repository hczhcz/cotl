#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe map(nullptr);
    libExec<true>(id_std, self, lib, map);

    _COTL_CHECK_TYPE(map, cotl::Map, id_map);

    const map_t &map_data = map_p->get();

    {
        PMaybe map1(nullptr);
        libExec<true>(id_type, self, lib, map1);

        _COTL_CHECK_TYPE(map1, cotl::Map, id_map);

        const map_t &map1_data = map1_p->get();
        map_data->insert(map1_data->begin(), map1_data->end());
    }

    {
        PMaybe map1(nullptr);
        libExec<true>(id_runtime, self, lib, map1);

        _COTL_CHECK_TYPE(map1, cotl::Map, id_map);

        const map_t &map1_data = map1_p->get();
        map_data->insert(map1_data->begin(), map1_data->end());
    }
_COTL_FUNC_END

long long ago = addInitializer(init, init_lib_after);

}

}
