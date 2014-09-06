#ifndef _COTL_NATIVE_HPP
#define _COTL_NATIVE_HPP

#include "cotl_helper.hpp"

namespace cotl {

class Val;
using PValRaw = Val *;
using PValConst = const Val *;

template <bool maybe> class PValProto;

inline
namespace published {

using PMaybe = PValProto<true>;
using PVal = PValProto<false>;

using int_t = long;
using real_t = double;

#define _COTL_FUNC_T(name) \
    void (name)(\
        const PVal &self,\
        const PMaybe &caller,\
        const PMaybe &lib,\
        PMaybe &tunnel\
    ) // if changed, check cotl_ptr.hpp and cotl_ptr_inline.hpp

using func_t = _COTL_FUNC_T(*);

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

#define _COTL_FUNC_ALIAS(name, oldname) \
    const auto (name) = (oldname);

#define _COTL_FUNC_ALIAS_DECL(name, oldname) \
    _COTL_FUNC_T(oldname);\
    const auto (name) = (oldname);

template <class T>
using hold_t = std::unique_ptr<T, MemDel<T>>;

#ifdef _COTL_USE_DEQUE
    using arr_t = hold_t<std::deque<
        PVal, MemAlloc<std::pair<int_t, PVal>>
    >>;
#else
    using arr_t = hold_t<std::vector<
        PVal, MemAlloc<std::pair<int_t, PVal>>
    >>;
#endif

#ifdef _COTL_USE_UNORDERED_MAP
    using map_t = hold_t<std::unordered_map<
        int_t, PVal,
        std::hash<int_t>,
        std::equal_to<int_t>,
        MemAlloc<std::pair<int_t, PVal>>
    >>;
#else
    using map_t = hold_t<std::map<
        int_t, PVal,
        std::less<int_t>,
        MemAlloc<std::pair<int_t, PVal>>
    >>;
#endif

}

}

#endif
