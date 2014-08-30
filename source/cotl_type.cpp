#include "../cotl"

namespace cotl {

namespace {

void outputIndent(std::ostream &stream, const int_t indent) {
    for (int_t i = 0; i < indent; ++i) {
        stream << "    ";
    }
}

void outputStr(std::ostream &stream, const std::string &str) {
    stream << "\"";

    for (auto val: str) {
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

void outputType(std::ostream &stream, const int_t type, const int_t dtype) {
    if (type != dtype) {
        stream << type;
    }
}

void outputAppendType(std::ostream &stream, const int_t type, const int_t dtype) {
    if (type != dtype) {
        stream << ", " << type;
    }
}

void outputFunc(std::ostream &stream, const func_t func) {
    stream << "func_t(0x" << std::hex << int_t(func) << std::dec << ")";
}

void outputAppendFunc(std::ostream &stream, const func_t func) {
    if (func != stdAuto) {
        stream << ", ";
        outputFunc(stream, func);
    }
}

}

inline
namespace published {

void Atom::repr(std::ostream &stream, const int_t level) const {
    (void) level; // unused

    stream << "_atom(";
    outputType(stream, getType(), id_atom);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Int::repr(std::ostream &stream, const int_t level) const {
    (void) level; // unused

    stream << "_int(" << get();
    outputAppendType(stream, getType(), id_int);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Real::repr(std::ostream &stream, const int_t level) const {
    (void) level; // unused

    stream << "_real(" << get();
    outputAppendType(stream, getType(), id_real);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Func::repr(std::ostream &stream, const int_t level) const {
    (void) level; // unused

    stream << "_func(";
    outputFunc(stream, get());
    outputAppendType(stream, getType(), id_func);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Ptr::repr(std::ostream &stream, const int_t level) const {
    stream << "_ptr(" << std::endl;

    // next line
    outputIndent(stream, level + 1);
    get()->repr(stream, level + 1);
    outputAppendType(stream, getType(), id_ptr);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Pair::repr(std::ostream &stream, const int_t level) const {
    stream << "_pair(" << std::endl;

    // next line
    outputIndent(stream, level + 1);
    get().first->repr(stream, level + 1);
    stream << "," << std::endl;

    // next line
    outputIndent(stream, level + 1);
    get().second->repr(stream, level + 1);
    outputAppendType(stream, getType(), id_pair);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Str::repr(std::ostream &stream, const int_t level) const {
    (void) level; // unused

    stream << "_str(";
    outputStr(stream, get());
    outputAppendType(stream, getType(), id_str);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Arr::repr(std::ostream &stream, const int_t level) const {
    stream << "_arr(";

    for (auto i = get()->begin(); i != get()->end(); ++i) {
        if (i != get()->begin()) {
            stream << ",";
        }
        stream << std::endl;

        // next line
        outputIndent(stream, level + 1);
        stream << i->first << ", ";
        i->second->repr(stream, level + 1);
    }

    outputAppendType(stream, getType(), id_arr);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

}

}
