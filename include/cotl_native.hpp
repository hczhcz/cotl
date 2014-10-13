#ifndef _COTL_NATIVE_HPP
#define _COTL_NATIVE_HPP

#include "cotl_helper.hpp"

namespace cotl {

namespace valtype {

class Val;

}

inline
namespace ptrtype {

using PValRaw = valtype::Val *;
using PValConst = const valtype::Val *;

template <bool maybe> class PValProto;

}

inline
namespace type {

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
    ) // if changed, check cotl_ptr.hpp, cotl_ptr_inline.hpp and cotl_std_util.hpp

using func_t = _COTL_FUNC_T(*);

template <class T>
using hold_t = std::unique_ptr<T, gcutil::MemDel<T>>;

using str_t = hold_t<std::string>;

#ifdef _COTL_USE_DEQUE
    using arr_t = hold_t<std::deque<
        PVal, gcutil::MemAlloc<PVal>
    >>;
#else
    using arr_t = hold_t<std::vector<
        PVal, gcutil::MemAlloc<PVal>
    >>;
#endif

#ifdef _COTL_USE_UNORDERED_MAP
    using map_t = hold_t<std::unordered_map<
        int_t, PVal,
        std::hash<int_t>,
        std::equal_to<int_t>,
        gcutil::MemAlloc<std::pair<const int_t, PVal>>
    >>;
#else
    using map_t = hold_t<std::map<
        int_t, PVal,
        std::less<int_t>,
        gcutil::MemAlloc<std::pair<const int_t, PVal>>
    >>;
#endif

}

}

#endif
