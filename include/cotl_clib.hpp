#ifndef _COTL_CLIB_HPP
#define _COTL_CLIB_HPP

#include "cotl_helper.hpp"

#define NDEBUG
#include <cassert>

#include <cstdlib>
#include <cstddef>
#include <cstdarg>

#include <string>

#ifdef _COTL_USE_DEQUE
    #include <deque>
#else
    #include <vector>
#endif

#ifdef _COTL_USE_UNORDERED_MAP
    #include <unordered_map>
#else
    #include <map>
#endif

#include <memory>
#include <iostream>

#endif
