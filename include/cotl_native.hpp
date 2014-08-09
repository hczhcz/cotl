#ifndef _COTL_NATIVE_HPP
#define _COTL_NATIVE_HPP

namespace cotl {

typedef long long int_t;
typedef double real_t;

class Val; // forward
typedef void (*func_t)(Val &job, Val &stack, Val &caller, Val &tunnel /* could be null */);

}

#endif
