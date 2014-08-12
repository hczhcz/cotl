#ifndef _COTL_NATIVE_HPP
#define _COTL_NATIVE_HPP

#include "cotl_helper.hpp"

namespace cotl {

typedef long long int_t;
typedef double real_t;

class Val; // forward
typedef Val *PVal;

#define _COTL_FUNC_T(name) void (name)(\
    Val &caller, Val &job, Val &stack, Val &tunnel /* could be null */\
)

typedef _COTL_FUNC_T(*func_t);

#define _COTL_FUNC_USE_PARAM() do {\
    (void) caller; (void) job; (void) stack; (void) tunnel;\
} while (0)

}

#endif
