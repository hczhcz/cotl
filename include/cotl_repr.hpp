#ifndef _COTL_REPR_HPP
#define _COTL_REPR_HPP

#include "cotl_helper.hpp"

namespace cotl {

inline
namespace published {

inline std::ostream &operator<<(std::ostream &stream, const PMaybe &val) {
    val->repr(stream, 0);
    return stream;
}

inline std::ostream &operator<<(std::ostream &stream, const PVal &val) {
    val->repr(stream, 0);
    return stream;
}

}

}

#endif
