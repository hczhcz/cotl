#ifndef _COTL_NEW_HPP
#define _COTL_NEW_HPP

#include "cotl_helper.hpp"

namespace cotl {

inline
namespace published {

Atom *_atom(
    const int_t type = id_atom, const func_t func = autotype, PValRaw reused = nullptr
);

Int *_int(const int_t &data,
    const int_t type = id_int, const func_t func = autotype, PValRaw reused = nullptr
);

Real *_real(const real_t &data,
    const int_t type = id_real, const func_t func = autotype, PValRaw reused = nullptr
);

Func *_func(const func_t &data,
    const int_t type = id_func, const func_t func = autotype, PValRaw reused = nullptr
);

Ptr *_ptr(const PVal &data,
    const int_t type = id_ptr, const func_t func = autotype, PValRaw reused = nullptr
);

Pair *_pair(const PVal &data1, const PVal &data2,
    const int_t type = id_pair, const func_t func = autotype, PValRaw reused = nullptr
);

Str *_str(const std::string &data,
    const int_t type = id_str, const func_t func = autotype, PValRaw reused = nullptr
);

Arr *_arr(
    const int_t type = id_arr, const func_t func = autotype, PValRaw reused = nullptr
);

template <class... Args>
inline Arr *_arr(const int_t key, const PVal &value, const Args... data /* (key, value) loop */) {
    Arr *result = _arr(data...);

    result->getVar()->insert(std::pair<int_t, PVal>(key, value));

    return result;
}

}

}

#endif
