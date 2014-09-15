#ifndef _COTL_STD_UTIL_HPP
#define _COTL_STD_UTIL_HPP

#include "cotl_helper.hpp"

namespace cotlstd {

#define _COTL_FUNC_BEGIN \
    try {\
        (void) self; (void) caller; (void) lib; (void) tunnel;\
        {

#ifdef _COTL_USE_ERR_CATCH
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
        }
#else
    #define _COTL_FUNC_END \
            }\
        } catch (...) {\
            throw;\
        }
#endif

inline void libGet(const PVal &target, const PMaybe &lib, PMaybe &tunnel) {
    lib.call<true>(target, nullptr, tunnel);
}

inline void libGet(const int_t type, const PMaybe &lib, PMaybe &tunnel) {
    libGet(_atom(type), lib, tunnel);
}

inline void libSet(const PVal &target, const PMaybe &lib, PMaybe &tunnel) {
    lib.call<false>(target, nullptr, tunnel);
}

inline void libSet(const int_t type, const PMaybe &lib, PMaybe &tunnel) {
    libSet(_atom(type), lib, tunnel);
}

inline void libExec(const PVal &target, const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel) {
    PMaybe data(nullptr);

    libGet(target, lib, data);

    data.call(caller, lib, tunnel);
}

template <bool ret>
inline void libExec(const PVal &target, const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel) {
    PMaybe data(nullptr);

    libGet(target, lib, data);

    data.call<ret>(caller, lib, tunnel);
}

inline void libExec(const int_t type, const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel) {
    libExec(_atom(type), caller, lib, tunnel);
}

template <bool ret>
inline void libExec(const int_t type, const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel) {
    libExec<ret>(_atom(type), caller, lib, tunnel);
}

}

#endif
