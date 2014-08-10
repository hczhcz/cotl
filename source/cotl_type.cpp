#include "../cotl"

namespace cotl {

struct _Indent {
    int_t _level;

    _Indent(const int_t level): _level(level) {}
};

static std::ostream &operator<<(std::ostream &stream, const _Indent indent) {
    for (int_t i = 0; i < indent._level; ++i) {
        stream << "\t";
    }

    return stream;
}

void Atom::repr(std::ostream &stream, const int_t level) const {
    stream << "atom(" << getType() << ")";
}

void Int::repr(std::ostream &stream, const int_t level) const {
    stream << "int(" << getType() << ", " << get() << ")";
}

void Real::repr(std::ostream &stream, const int_t level) const {
    stream << "real(" << getType() << ", " << get() << ")";
}

void Str::repr(std::ostream &stream, const int_t level) const {
    stream << "str(" << getType() << ", " << get() << ")";
}

void Arr::repr(std::ostream &stream, const int_t level) const {
    stream << "arr(" << getType() << ",";

    for (auto i = get().begin(); i != get().end(); ++i) {
        stream << "\n" << _Indent(level) << i->first;
        i->second->repr(stream, level + 1);
    }

    stream << "\n" << _Indent(level) << stream << ")";
}

void Ptr::repr(std::ostream &stream, const int_t level) const {
    stream << "ptr(" << getType() << ", ";
    get()->repr(stream, level);
    stream << ")";
}

void Pair::repr(std::ostream &stream, const int_t level) const {
    stream << "pair(" << getType() << ", ";
    get1()->repr(stream, level);
    stream << ", ";
    get2()->repr(stream, level);
    stream << ")";
}

}
