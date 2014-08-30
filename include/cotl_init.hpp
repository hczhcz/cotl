#ifndef _COTL_INIT_HPP
#define _COTL_INIT_HPP

#include "cotl_helper.hpp"

namespace cotl {

namespace {

const int_t initListSize = 4096;
int_t initListIndex = 0;

}

inline
namespace published {

int_t addInitializer(const func_t func);

void callInitializer(const PVal &lib);

}

}

#endif
