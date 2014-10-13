#ifndef _COTL_HPP
#define _COTL_HPP

// c/c++ library
#include "cotl_clib.hpp"
#include "cotl_gc.hpp"

// type definitions
#include "cotl_native.hpp"
#include "cotl_ptr.hpp"
#include "cotl_type.hpp"
#include "cotl_id.hpp"

// cotl std library
#include "cotl_std_id.hpp"
#include "cotl_std_published.hpp"

// utilities
#include "cotl_new.hpp"
#include "cotl_repr.hpp"
#include "cotl_init.hpp"
#include "cotl_lib.hpp"

namespace cotl {

namespace stdlib {

using namespace cotl::initutil;
using namespace cotl::libutil;

}

}

// implementation
#include "cotl_ptr_inline.hpp"

#endif
