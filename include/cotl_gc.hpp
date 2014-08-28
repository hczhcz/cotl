#ifndef _COTL_GC_HPP
#define _COTL_GC_HPP

#include "cotl_helper.hpp"

#ifdef _COTL_USE_GC
    #ifdef _COTL_USE_GLOBAL_GC
        // use libgc from OS
        #include <gc/gc.h>
        #include <gc/gc_cpp.h>
        #include <gc/gc_allocator.h>
    #else
        // use local bdwgc
        #include "../gc/include/gc.h"
        #include "../gc/include/gc_cpp.h"
        #include "../gc/include/gc_allocator.h"
    #endif
#endif

namespace cotl {

#ifdef _COTL_USE_GC
    #define _COTL_MALLOC(size) GC_MALLOC(size)
    #define _COTL_FREE(ptr) GC_FREE(ptr)
    #define _COTL_MEMINIT() GC_INIT()

    typedef gc_cleanup MemBase;
    template <class T>
    using MemAlloc = typename ::traceable_allocator<T>;
#else
    #define _COTL_MALLOC(size) malloc(size)
    #define _COTL_FREE(ptr) free(ptr)
    #define _COTL_MEMINIT() do {} while (false)

    typedef class {} MemBase;
    template <class T>
    using MemAlloc = typename std::allocator<T>;
#endif

}

#endif
