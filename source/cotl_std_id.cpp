#include "../cotl"

namespace cotlstd {

inline
namespace published {

const char *getTypeName(const int_t type) {
    #define _COTL_ADD_ID(name) \
        case (name):\
            static const char *nm_##name = #name;\
            return nm_##name;\
            break

    switch (type) {
        // generated from cotl_std_id.hpp

        // type
        _COTL_ADD_ID(id_atom);
        _COTL_ADD_ID(id_null);
        _COTL_ADD_ID(id_false);
        _COTL_ADD_ID(id_true);
        _COTL_ADD_ID(id_int);
        _COTL_ADD_ID(id_increment);
        _COTL_ADD_ID(id_decrement);
        _COTL_ADD_ID(id_real);
        _COTL_ADD_ID(id_func);
        _COTL_ADD_ID(id_ptr);
        _COTL_ADD_ID(id_pair);
        _COTL_ADD_ID(id_str);
        _COTL_ADD_ID(id_arr);
        _COTL_ADD_ID(id_stack);
        _COTL_ADD_ID(id_code);
        _COTL_ADD_ID(id_map);
        _COTL_ADD_ID(id_error);
        _COTL_ADD_ID(id_error_self);
        _COTL_ADD_ID(id_error_caller);
        _COTL_ADD_ID(id_error_lib);
        _COTL_ADD_ID(id_error_tunnel);
        _COTL_ADD_ID(id_error_func);
        _COTL_ADD_ID(id_error_detail);
        _COTL_ADD_ID(id_type_wrap);
        _COTL_ADD_ID(id_type_lib);
        _COTL_ADD_ID(id_type_misc);

        // std
        _COTL_ADD_ID(id_std);

        // runtime
        _COTL_ADD_ID(id_runtime);
        _COTL_ADD_ID(id_auto);
        _COTL_ADD_ID(id_literal);
        _COTL_ADD_ID(id_bind);
        _COTL_ADD_ID(id_quote);
        _COTL_ADD_ID(id_blackhole);
        _COTL_ADD_ID(id_container);
        _COTL_ADD_ID(id_const);
        _COTL_ADD_ID(id_target);
        _COTL_ADD_ID(id_ref);
        _COTL_ADD_ID(id_before);
        _COTL_ADD_ID(id_after);
        _COTL_ADD_ID(id_also);
        _COTL_ADD_ID(id_void);
        _COTL_ADD_ID(id_exec);
        _COTL_ADD_ID(id_write);
        _COTL_ADD_ID(id_iftunnel);
        _COTL_ADD_ID(id_try);

        default:
            return nullptr;
            break;
    }

    #undef _COTL_ADD_ID
}

}

}
