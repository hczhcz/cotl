#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe map(nullptr);
    libGet(id_std, lib, map);

    _COTL_CHECK_TYPE(map, cotl::Map, id_map);

    const map_t &map_data = map_p->get();

    {
        PMaybe map1(nullptr);
        libGet(id_type, lib, map1);

        _COTL_CHECK_TYPE(map1, cotl::Map, id_map);

        const map_t &map1_data = map1_p->get();
        map_data->insert(map1_data->begin(), map1_data->end());
    }

    {
        PMaybe map1(nullptr);
        libGet(id_runtime, lib, map1);

        _COTL_CHECK_TYPE(map1, cotl::Map, id_map);

        const map_t &map1_data = map1_p->get();
        map_data->insert(map1_data->begin(), map1_data->end());
    }
_COTL_FUNC_END

long long ago = addInitializer(init, init_lib_after);

}

}
