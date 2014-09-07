#ifndef _COTL_STD_UTIL_HPP
#define _COTL_STD_UTIL_HPP

#include "cotl_helper.hpp"

namespace cotlstd {

#define _COTL_FUNC_BEGIN \
    try {\
        (void) self; (void) caller; (void) lib; (void) tunnel;\
        {

// TODO: check if PMaybe is nullptr
// TODO: force explicit check on PMaybe -> PVal
#define _COTL_FUNC_END \
        }\
    } catch (const PVal &e) {\
        throw _arr(self, caller, lib, tunnel, e, id_error);\
    } catch (...) {\
        throw _arr(self, caller, lib, tunnel, id_error);\
    }// TODO TODO

}

#endif
