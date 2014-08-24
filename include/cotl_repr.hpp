#ifndef _COTL_REPR_HPP
#define _COTL_REPR_HPP

#include "cotl_helper.hpp"

namespace cotl {

inline std::ostream &operator<<(std::ostream &stream, const PVal &value) {
    value->repr(stream, 0);
    return stream;
}

inline std::ostream &operator<<(std::ostream &stream, const Val *value) {
    value->repr(stream, 0);
    return stream;
}

}

#endif
