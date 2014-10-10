#include "../cotl"

namespace cotl {

namespace {

void outputIndent(std::ostream &stream, const int_t level) {
    for (int_t i = 0; i < level; ++i) {
        stream << "    ";
    }
}

void outputSplit(std::ostream &stream, const int_t level) {
    if (level >= 0) {
        stream << "," << std::endl;
        outputIndent(stream, level);
    } else {
        stream << ", ";
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

void outputAppendType(std::ostream &stream, const int_t type, const int_t dtype) {
    if (type != dtype) {
        stream << ", " << type;
    }
}

void outputAppendTypeX(std::ostream &stream, const int_t type, const int_t dtype, bool &after) {
    if (type != dtype) {
        if (after) {
            stream << ", ";
        }
        if (type != id_error) {
            stream << type;
        } else {
            // TODO: better repr support of id and func
            // TODO: support circular-ref and multi-ref objects
            stream << "id_error";
        }
        after = true;
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

void outputAppendFuncX(std::ostream &stream, const func_t func, bool &after) {
    if (func != stdAuto) {
        if (after) {
            stream << ", ";
        }
        outputFunc(stream, func);
        after = true;
    }
}

}

inline
namespace published {

void Atom::each(void callback(const PVal &), const bool rev) {
    (void) rev;

    callback(PVal(this));
}

template <>
void Int::each(void callback(const PVal &), const bool rev) {
    (void) rev;

    callback(PVal(this));
}

template <>
void Real::each(void callback(const PVal &), const bool rev) {
    (void) rev;

    callback(PVal(this));
}

template <>
void Func::each(void callback(const PVal &), const bool rev) {
    (void) rev;

    callback(PVal(this));
}

template <>
void Ptr::each(void callback(const PVal &), const bool rev) {
    if (!rev) {
        callback(PVal(this));
    }

    getVar().raw()->each(callback, rev);

    if (rev) {
        callback(PVal(this));
    }
}

template <>
void Pair::each(void callback(const PVal &), const bool rev) {
    if (!rev) {
        callback(PVal(this));
    }

    getVar().first.raw()->each(callback, rev);
    getVar().second.raw()->each(callback, rev);

    if (rev) {
        callback(PVal(this));
    }
}

template <>
void Str::each(void callback(const PVal &), const bool rev) {
    (void) rev;

    callback(PVal(this));
}

template <>
void Arr::each(void callback(const PVal &), const bool rev) {
    if (!rev) {
        callback(PVal(this));
    }

    for (auto i = getVar()->begin(); i != getVar()->end(); ++i) {
        i->raw()->each(callback, rev);
    }

    if (rev) {
        callback(PVal(this));
    }
}

template <>
void Map::each(void callback(const PVal &), const bool rev) {
    if (!rev) {
        callback(PVal(this));
    }

    for (auto i = getVar()->begin(); i != getVar()->end(); ++i) {
        i->second.raw()->each(callback, rev);
    }

    if (rev) {
        callback(PVal(this));
    }
}

void Atom::repr(std::ostream &stream, const int_t level) const {
    if (level >= _COTL_VAL_REPR_DEPTH) {
        stream << "...";
        return;
    }

    stream << "_atom(";
    bool after = false;
    outputAppendTypeX(stream, getType(), id_atom, after);
    outputAppendFuncX(stream, getFunc(), after);
    stream << ")";
}

template <>
void Int::repr(std::ostream &stream, const int_t level) const {
    if (level >= _COTL_VAL_REPR_DEPTH) {
        stream << "...";
        return;
    }

    stream << "_int(" << get();
    outputAppendType(stream, getType(), id_int);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Real::repr(std::ostream &stream, const int_t level) const {
    if (level >= _COTL_VAL_REPR_DEPTH) {
        stream << "...";
        return;
    }

    stream << "_real(" << get();
    outputAppendType(stream, getType(), id_real);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Func::repr(std::ostream &stream, const int_t level) const {
    if (level >= _COTL_VAL_REPR_DEPTH) {
        stream << "...";
        return;
    }

    stream << "_func(";
    outputFunc(stream, get());
    outputAppendType(stream, getType(), id_func);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Ptr::repr(std::ostream &stream, const int_t level) const {
    if (level >= _COTL_VAL_REPR_DEPTH) {
        stream << "...";
        return;
    }

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
    if (level >= _COTL_VAL_REPR_DEPTH) {
        stream << "...";
        return;
    }

    stream << "_pair(" << std::endl;

    // next line
    outputIndent(stream, level + 1);
    get().first->repr(stream, level + 1);

    outputSplit(stream, level + 1); // next line

    get().second->repr(stream, level + 1);
    outputAppendType(stream, getType(), id_pair);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Str::repr(std::ostream &stream, const int_t level) const {
    if (level >= _COTL_VAL_REPR_DEPTH) {
        stream << "...";
        return;
    }

    stream << "_str(";
    outputStr(stream, *get());
    outputAppendType(stream, getType(), id_str);
    outputAppendFunc(stream, getFunc());
    stream << ")";
}

template <>
void Arr::repr(std::ostream &stream, const int_t level) const {
    if (level >= _COTL_VAL_REPR_DEPTH) {
        stream << "...";
        return;
    }

    stream << "_arr(";

    for (auto i = get()->begin(); i != get()->end(); ++i) {
        if (i != get()->begin()) {
            outputSplit(stream, level + 1);
        } else {
            stream << std::endl;
            outputIndent(stream, level + 1);
        }

        (*i)->repr(stream, level + 1);
    }

    bool after = !get()->empty();
    outputAppendTypeX(stream, getType(), id_arr, after);
    outputAppendFuncX(stream, getFunc(), after);
    stream << ")";
}

template <>
void Map::repr(std::ostream &stream, const int_t level) const {
    if (level >= _COTL_VAL_REPR_DEPTH) {
        stream << "...";
        return;
    }

    stream << "_map(";

    for (auto i = get()->begin(); i != get()->end(); ++i) {
        if (i != get()->begin()) {
            outputSplit(stream, level + 1);
        } else {
            stream << std::endl;
            outputIndent(stream, level + 1);
        }

        stream << i->first << ", ";
        i->second->repr(stream, level + 1);
    }

    bool after = !get()->empty();
    outputAppendTypeX(stream, getType(), id_map, after);
    outputAppendFuncX(stream, getFunc(), after);
    stream << ")";
}

}

}
