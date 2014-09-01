#ifndef _COTL_INIT_HPP
#define _COTL_INIT_HPP

#include "cotl_helper.hpp"

namespace cotl {

inline
namespace published {

int_t addInitializer(const func_t func);

void callInitializer(const PVal &lib);

void boot(const PVal &exec, PMaybe &tunnel);

}

}

#endif
