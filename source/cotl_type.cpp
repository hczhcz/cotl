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

void Atom::repl(std::ostream &stream, const int_t level) const {
    stream << "atom(" << getType() << ")";
}

void Int::repl(std::ostream &stream, const int_t level) const {
    stream << "int(" << getType() << ", " << get() << ")";
}

void Real::repl(std::ostream &stream, const int_t level) const {
    stream << "real(" << getType() << ", " << get() << ")";
}

void Str::repl(std::ostream &stream, const int_t level) const {
    stream << "str(" << getType() << ", " << get() << ")";
}

void Arr::repl(std::ostream &stream, const int_t level) const {
    stream << "arr(" << getType() << ",";

    for (auto i = get().begin(); i != get().end(); ++i) {
        stream << "\n" << _Indent(level) << i->first;
        i->second->repl(stream, level + 1);
    }

    stream << "\n" << _Indent(level) << stream << ")";
}

void Ptr::repl(std::ostream &stream, const int_t level) const {
    stream << "ptr(" << getType() << ", ";
    get()->repl(stream, level);
    stream << ")";
}

void Pair::repl(std::ostream &stream, const int_t level) const {
    stream << "pair(" << getType() << ", ";
    get1()->repl(stream, level);
    stream << ", ";
    get2()->repl(stream, level);
    stream << ")";
}

}
