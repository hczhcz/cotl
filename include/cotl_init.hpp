#ifndef _COTL_INIT_HPP
#define _COTL_INIT_HPP

#include "cotl_helper.hpp"

namespace cotl {

namespace initutil {

enum init_t {
    INIT_BEGIN,

    init_core = INIT_BEGIN,
    init_core_1,
    init_lib,
    init_lib_1,
    init_lib_2,
    init_lib_3,
    init_lib_after,
    init_user,
    init_user_1,
    init_user_2,
    init_user_3,
    init_user_after,
    init_test,

    INIT_END
};

int_t addInitializer(const func_t func, const init_t init);

void callInitializer(const PMaybe &lib);

}

inline
namespace published {

void boot(const PVal &exec, PMaybe &tunnel);

}

}

#endif
