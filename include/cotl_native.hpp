#ifndef _COTL_NATIVE_HPP
#define _COTL_NATIVE_HPP

#include "cotl_helper.hpp"

namespace cotl {

typedef long long int_t;
typedef double real_t;

class Val; // forward
typedef Val *PVal;

#define _COTL_FUNC_T(name) void (name)(\
    PVal self, PVal caller, PVal lib, PVal &tunnel /* could be null */\
) // if changed, check cotl_type.hpp

typedef _COTL_FUNC_T(*func_t);

#define _COTL_FUNC_USE_PARAM() do {\
    (void) self; (void) caller; (void) lib; (void) tunnel;\
} while (0)

#define _COTL_FUNC_BEGIN _COTL_FUNC_USE_PARAM(); {
#define _COTL_FUNC_END }

#ifdef _COTL_USE_UNORDERED_MAP
    typedef std::unique_ptr<std::unordered_map<
        int_t, PVal,
        std::hash<int_t>,
        std::equal_to<int_t>,
        traceable_allocator<std::pair<const int_t, const PVal>>
    >> map_t;
#else
    typedef std::unique_ptr<std::map<
        int_t, PVal,
        std::less<int_t>,
        traceable_allocator<std::pair<const int_t, const PVal>>
    >> map_t;
#endif
}

#endif
