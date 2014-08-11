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
    (void) level; // unused

    stream << "_atom(" << getType() << ")";
}

template <>
void Int::repr(std::ostream &stream, const int_t level) const {
    (void) level; // unused

    stream << "_int(" << getType() << ", " << get() << ")";
}

template <>
void Real::repr(std::ostream &stream, const int_t level) const {
    (void) level; // unused

    stream << "_real(" << getType() << ", " << get() << ")";
}

template <>
void Str::repr(std::ostream &stream, const int_t level) const {
    (void) level; // unused

    stream << "_str(" << getType() << ", " << get() << ")";
}

template <>
void Arr::repr(std::ostream &stream, const int_t level) const {
    stream << "_arr(" << getType() << ", " << get().size() << ",";

    for (auto i = get().begin(); i != get().end(); ++i) {
        stream << std::endl << _Indent(level) << i->first << ", ";
        i->second->repr(stream, level + 1);
    }

    stream << std::endl << _Indent(level) << stream << ")";
}

template <>
void Ptr::repr(std::ostream &stream, const int_t level) const {
    stream << "_ptr(" << getType() << ", ";
    get()->repr(stream, level);
    stream << ")";
}

void Pair::repr(std::ostream &stream, const int_t level) const {
    stream << "_pair(" << getType() << ", ";
    get1()->repr(stream, level);
    stream << ", ";
    get2()->repr(stream, level);
    stream << ")";
}

}
