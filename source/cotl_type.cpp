#include "../cotl"

namespace cotl {

static void outputIndent(std::ostream &stream, const int_t indent) {
    for (int_t i = 0; i < indent; ++i) {
        stream << "    ";
    }
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

static void outputFunc(std::ostream &stream, const func_t func) {
    stream << "func_t(0x" << std::hex << int_t(func) << std::dec << ")";
}

static void outputAppendFunc(std::ostream &stream, const func_t func) {
    if (func != autotype) {
        stream << ", ";
        outputFunc(stream, func);
    }
}

void Atom::repr(std::ostream &stream, const int_t level) const {
    (void) level; // unused

    stream << "_atom(" << getType();
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Int::repr(std::ostream &stream, const int_t level) const {
    (void) level; // unused

    stream << "_int(" << getType() << ", " << get();
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Real::repr(std::ostream &stream, const int_t level) const {
    (void) level; // unused

    stream << "_real(" << getType() << ", " << get();
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Func::repr(std::ostream &stream, const int_t level) const {
    (void) level; // unused

    stream << "_func(" << getType() << ", ";
    outputFunc(stream, get());
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Ptr::repr(std::ostream &stream, const int_t level) const {
    stream << "_ptr(" << getType() << ", ";
    get()->repr(stream, level);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Str::repr(std::ostream &stream, const int_t level) const {
    (void) level; // unused

    stream << "_str(" << getType() << ", ";
    outputStr(stream, get());
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Arr::repr(std::ostream &stream, const int_t level) const {
    stream << "_arr(" << getType() << std::endl;

    for (auto i = get()->begin(); i != get()->end(); ++i) {
        outputIndent(stream, level + 1);
        stream << ", " << i->first << ", ";
        i->second->repr(stream, level + 1);
        stream << std::endl;
    }

    outputIndent(stream, level);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Pair::repr(std::ostream &stream, const int_t level) const {
    stream << "_pair(" << getType() << std::endl;

    outputIndent(stream, level + 1);
    stream << ", ";
    get().first->repr(stream, level + 1);
    stream << std::endl;

    outputIndent(stream, level + 1);
    stream << ", ";
    get().second->repr(stream, level + 1);
    stream << std::endl;

    outputIndent(stream, level);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

}
