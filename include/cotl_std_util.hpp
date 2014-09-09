#ifndef _COTL_STD_UTIL_HPP
#define _COTL_STD_UTIL_HPP

#include "cotl_helper.hpp"

namespace cotlstd {

#define _COTL_FUNC_BEGIN \
    try {\
        (void) self; (void) caller; (void) lib; (void) tunnel;\
        {

// TODO: force explicit check on PMaybe -> PVal
#define _COTL_FUNC_END \
        }\
    } catch (cotl::PValRaw e) {\
        throw _arr(\
            self, caller.sure(), lib.sure(), tunnel.sure(),\
            e,\
            id_error\
        );\
    } catch (const char *c) {\
        throw _arr(\
            self, caller.sure(), lib.sure(), tunnel.sure(),\
            _str(c, id_error),\
            id_error\
        );\
    } catch (...) {\
        throw _arr(\
            self, caller.sure(), lib.sure(), tunnel.sure(),\
            _str("unknown error", id_error),\
            id_error\
        );\
    } // TODO TODO

}

#endif
