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
        const PVal &lib,\
        PMaybe &tunnel /* could be null */\
    ) // if changed, check cotl_ptr.hpp and cotl_ptr_inline.hpp

using func_t = _COTL_FUNC_T(*);

#define _COTL_FUNC_BEGIN \
    try {\
        (void) self; (void) caller; (void) lib; (void) tunnel;\
        {

// TODO: check if PMaybe is nullptr
#define _COTL_FUNC_END \
        }\
    } catch (const PVal &e) {\
        throw _arr(0, self, 1, caller, 2, lib, 3, tunnel, 4, e, id_error);\
    } catch (...) {\
        throw _arr(0, self, 1, caller, 2, lib, 3, tunnel, id_error);\
    }

#define _COTL_FUNC_ALIAS(name, oldname) \
    const auto name = oldname;

#define _COTL_FUNC_ALIAS_DECL(name, oldname) \
    _COTL_FUNC_T(oldname);\
    const auto name = oldname;

#ifdef _COTL_USE_UNORDERED_MAP
    using map_t = std::shared_ptr<std::unordered_map<
        int_t, PVal,
        std::hash<int_t>,
        std::equal_to<int_t>,
        MemAlloc<std::pair<int_t, PVal>>
    >>;
#else
    using map_t = std::shared_ptr<std::map<
        int_t, PVal,
        std::less<int_t>,
        MemAlloc<std::pair<int_t, PVal>>
    >>;
#endif

}

}

#endif
