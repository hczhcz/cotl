#ifndef _COTL_REPL_HPP
#define _COTL_REPL_HPP

namespace cotl {

inline std::ostream &operator<<(std::ostream &stream, const Val &value) {
    value.repl(stream, 0);
    return stream;
}

}

#endif
