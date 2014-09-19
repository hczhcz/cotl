#ifndef _COTL_GC_HPP
#define _COTL_GC_HPP

#include "cotl_helper.hpp"

#ifdef _COTL_USE_GC
    #define GC_IGNORE_WARN

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

    using MemBase = gc_cleanup;
    template <class T>
    #ifdef _COTL_USE_WEAK_ALLOCATOR
        using MemAlloc = typename ::traceable_allocator<T>;
        #define _COTL_RAWNEW(obj) (new obj)
        #define _COTL_RAWDEL(obj) (delete obj)
    #else
        using MemAlloc = typename ::gc_allocator<T>;
        #define _COTL_RAWNEW(obj) (new (UseGC) obj)
        #define _COTL_RAWDEL(obj) ((void) obj)
    #endif
#else
    #define _COTL_MALLOC(size) malloc(size)
    #define _COTL_FREE(ptr) free(ptr)
    #define _COTL_MEMINIT() do {} while (false)

    class MemBase {};
    template <class T>
    using MemAlloc = typename std::allocator<T>;

    #define _COTL_RAWNEW(obj) (new obj)
    #define _COTL_RAWDEL(obj) (delete obj)
#endif

template <class T>
class MemDel {
public:
    inline void operator()(T *ptr) const {
        _COTL_RAWDEL(ptr);
    }
};

}

#endif
