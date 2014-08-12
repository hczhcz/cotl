#ifndef _COTL_GC_HPP
#define _COTL_GC_HPP

#include "cotl_helper.hpp"

#ifdef _COTL_USE_GLOBAL_GC
    // use libgc from OS
    #include <gc.h>
    #include <gc_cpp.h>

#else
    // use local bdwgc
    #include "../gc/include/gc.h"
    #include "../gc/include/gc_cpp.h"

#endif

#endif
