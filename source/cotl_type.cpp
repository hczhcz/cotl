#include "../cotl"

namespace cotl {

struct indent_t {
    int_t _level;

    indent_t(const int_t level): _level(level) {}
};

static std::ostream &operator<<(std::ostream &stream, const indent_t indent) {
    for (int_t i = 0; i < indent._level; ++i) {
        stream << "\t";
    }

    return stream;
}

static void outputStr(std::ostream &stream, const std::string &str) {
    stream << "\"";

    for (auto i = str.begin(); i != str.end(); ++i) {
        char val = *i;

        switch (val) {
        case '\0':
            stream << "\\0";
            break;
        case '\a':
            stream << "\\a";
            break;
        case '\b':
            stream << "\\b";
            break;
        case '\t':
            stream << "\\t";
            break;
        case '\n':
            stream << "\\n";
            break;
        case '\v':
            stream << "\\v";
            break;
        case '\f':
            stream << "\\f";
            break;
        case '\r':
            stream << "\\r";
            break;
        case '\'':
        case '\"':
        case '\?':
        case '\\':
            stream << "\\" << val;
            break;
        default:
            if ((val < 0x20) || (val >= 0x7F)) { // 0-31, 127, 128-255
                const char hexChar[] = "0123456789ABCDEF";
                stream << "\\x" << hexChar[(val >> 4) & 0xF] << hexChar[val & 0xF];
            } else {
                stream << val;
            }
            break;
        }
    }

    stream << "\"";
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

    stream << "_str(" << getType() << ", ";
    outputStr(stream, get());
    stream << ")";
}

template <>
void Arr::repr(std::ostream &stream, const int_t level) const {
    stream << "_arr(" << getType() << ", " << get().size() << ",";

    for (auto i = get().begin(); i != get().end(); ++i) {
        stream << std::endl << indent_t(level + 1) << i->first << ", ";
        i->second->repr(stream, level + 1);
    }

    stream << std::endl << indent_t(level) << ")";
}

template <>
void Ptr::repr(std::ostream &stream, const int_t level) const {
    stream << "_ptr(" << getType() << ", ";
    get()->repr(stream, level);
    stream << ")";
}

void Pair::repr(std::ostream &stream, const int_t level) const {
    stream << "_pair(" << getType() << "," << std::endl << indent_t(level + 1);
    get1()->repr(stream, level + 1);
    stream << "," << std::endl << indent_t(level + 1);
    get2()->repr(stream, level + 1);
    stream << std::endl << indent_t(level) << ")";
}

}
