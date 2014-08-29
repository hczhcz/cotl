#ifndef _COTL_REPR_HPP
#define _COTL_REPR_HPP

#include "cotl_helper.hpp"

namespace cotl {

inline
namespace published {

inline std::ostream &operator<<(std::ostream &stream, const PVal &value) {
    value->repr(stream, 0);
    return stream;
}

}

}

#endif
