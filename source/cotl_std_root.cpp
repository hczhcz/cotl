#include "../cotl"

namespace cotl {

namespace stdlib {

// arg: self, caller, lib, tunnel

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    _COTL_CHECK_TUNNEL(false);

    PMaybe map(nullptr);
    libGet(id_std, lib, map);

    _COTL_CHECK_TYPE(map, cotl::Map, id_map);

    const map_t &map_data = map_p->get();

    #define _COTL_ADD_LIB_TO_STD(id) \
    do {\
        PMaybe map1(nullptr);\
        libGet((id), lib, map1);\
        _COTL_CHECK_TYPE(map1, cotl::Map, id_map);\
        const map_t &map1_data = map1_p->get();\
        map_data->insert(map1_data->begin(), map1_data->end());\
    } while (false)

    _COTL_ADD_LIB_TO_STD(id_type);
    _COTL_ADD_LIB_TO_STD(id_type_misc); // sub
    _COTL_ADD_LIB_TO_STD(id_runtime);
    _COTL_ADD_LIB_TO_STD(id_query);
    _COTL_ADD_LIB_TO_STD(id_math);
    _COTL_ADD_LIB_TO_STD(id_math_real); // sub
    // ...

    #undef _COTL_ADD_LIB_TO_STD
_COTL_FUNC_END

long long ago = addInitializer(init, init_lib_after);

}

}

}
