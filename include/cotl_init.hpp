#ifndef _COTL_INIT_HPP
#define _COTL_INIT_HPP

#include "cotl_helper.hpp"

namespace cotl {

inline
namespace published {

enum init_t {
    INIT_BEGIN,

    init_core = INIT_BEGIN,
    init_lib,
    init_lib_after,
    init_user,
    init_user_after,
    init_test,

    INIT_END
};

int_t addInitializer(const func_t func, const init_t init);

void callInitializer(const PMaybe &lib);

void boot(const PVal &exec, PMaybe &tunnel);

}

}

#endif
