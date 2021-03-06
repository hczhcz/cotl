#ifndef _COTL_LIBUTIL_HPP
#define _COTL_LIBUTIL_HPP

#include "cotl_helper.hpp"

namespace cotl {

namespace libutil {

#define _COTL_FUNC_BEGIN \
    try {\
        (void) self; (void) caller; (void) lib; (void) tunnel;\
        {

#ifdef _COTL_USE_ERR_CATCH
    #ifdef _COTL_USE_ERR_FULL
        #define _COTL_ERR_INFO \
            id_error_self, self,\
            id_error_caller, caller.sure(),\
            id_error_lib, lib.sure(),\
            id_error_tunnel, tunnel.sure(),\
            id_error_func, _str(__FUNCTION__)
    #else
        #define _COTL_ERR_INFO \
            id_error_caller, caller.sure(),\
            id_error_tunnel, tunnel.sure(),\
            id_error_func, _str(__FUNCTION__)
    #endif

    #define _COTL_FUNC_END \
            }\
        } catch (PValRaw e) {\
            throw _map(\
                _COTL_ERR_INFO,\
                id_error_detail, e,\
                id_error\
            );\
        } catch (const char *c) {\
            throw _map(\
                _COTL_ERR_INFO,\
                id_error_detail, _str(c, id_error),\
                id_error\
            );\
        } catch (...) {\
            throw _map(\
                _COTL_ERR_INFO,\
                id_error_detail, _str("unknown error", id_error),\
                id_error\
            );\
        } // TODO: better re-thrown val structure
#else
    #define _COTL_FUNC_END \
            }\
        } catch (...) {\
            throw;\
        }
#endif

#define _COTL_CHECK_SELF(type, id) \
    auto self_p = self.as<type, id>();\
    do {\
        if (!self_p) {\
            throw "bad self type";\
        }\
    } while (false)

#define _COTL_CHECK_SELF_VAR(type, id) \
    auto self_p = self.raw<type, id>();\
    do {\
        if (!self_p) {\
            throw "bad self type";\
        }\
    } while (false)

#define _COTL_CHECK_TYPE(val, type, id) \
    auto val##_p = (val).as<type, id>();\
    do {\
        if (!val##_p) {\
            doCast<id>(lib, (val));\
            val##_p = (val).as<type, id>();\
            if (!val##_p) {\
                throw "bad casting";\
            }\
        }\
    } while (false) // TODO cast, dispatch

#define _COTL_CHECK_TYPE_ANY(val, type, id) \
    auto val##_p = (val).asany<type>();\
    do {\
        if (!val##_p) {\
            doCast<id>(lib, (val));\
            val##_p = (val).as<type, id>();\
            if (!val##_p) {\
                throw "bad casting";\
            }\
        }\
    } while (false) // TODO cast, dispatch

#define _COTL_CHECK_TYPE_VAR(val, type, id) \
    auto val##_p = (val).raw<type, id>();\
    do {\
        if (!val##_p) {\
            doCast<id>(lib, (val));\
            val##_p = (val).as<type, id>();\
            if (!val##_p) {\
                throw "bad casting";\
            }\
        }\
    } while (false) // TODO cast, dispatch

#define _COTL_CHECK_TUNNEL(exist) \
    do {\
        if (bool(tunnel) != (exist)) {\
            throw "bad tunnel existence";\
        }\
    } while (false)

template <int_t type = IDX_UNDEF, int_t... Args>
inline void libGet(const PVal &val, const PMaybe &lib, PMaybe &tunnel) {
    if (type == IDX_UNDEF) {
        lib.call<true>(val, nullptr, tunnel);
    } else {
        PMaybe tunnel1(nullptr);

        libGet(_atom(type), lib, tunnel1);
        libGet<Args...>(val, tunnel1, tunnel);
    }
}

template <int_t... Args>
inline void libGet(const int_t type, const PMaybe &lib, PMaybe &tunnel) {
    libGet<Args...>(_atom(type), lib, tunnel);
}

template <int_t type = IDX_UNDEF, int_t... Args>
inline void libSet(const PVal &val, const PMaybe &lib, PMaybe &tunnel) {
    if (type == IDX_UNDEF) {
        lib.call<false>(val, nullptr, tunnel);
    } else {
        PMaybe tunnel1(nullptr);

        libGet(_atom(type), lib, tunnel1);
        libSet<Args...>(val, tunnel1, tunnel);
    }
}

template <int_t... Args>
inline void libSet(const int_t type, const PMaybe &lib, PMaybe &tunnel) {
    libSet<Args...>(_atom(type), lib, tunnel);
}

inline void libExec(const PVal &val, const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel) {
    PMaybe data(nullptr);

    libGet(val, lib, data);

    data.call(caller, lib, tunnel);
}

template <bool ret>
inline void libExec(const PVal &val, const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel) {
    PMaybe data(nullptr);

    libGet(val, lib, data);

    data.call<ret>(caller, lib, tunnel);
}

inline void libExec(const int_t type, const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel) {
    libExec(_atom(type), caller, lib, tunnel);
}

template <bool ret>
inline void libExec(const int_t type, const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel) {
    libExec<ret>(_atom(type), caller, lib, tunnel);
}

template <int_t type>
inline void doCast(const PMaybe &lib, PMaybe &val) {
    PMaybe func(nullptr);

    libGet<id_cast, type>(PVal(val), lib, func);

    PMaybe caller(_ptr(_quote(PVal(val)), val->getType())); // TODO simplify
    val = nullptr;

    func.call<true>(caller, lib, val);
}

inline void doDispatch(
    const PVal &val,
    const PVal &self, const PMaybe &lib, PMaybe &tunnel
) {
    PMaybe vlib1(nullptr);
    PMaybe func(nullptr);

    libGet<id_dispatch>(val, lib, vlib1);

    libGet(self, vlib1, func);
    func.call(_ptr(_quote(val), self->getType()), lib, tunnel);
}

inline void doDispatch(
    const PVal &val1, const PVal &val2,
    const PVal &self, const PMaybe &lib, PMaybe &tunnel
) {
    PMaybe vlib1(nullptr);
    PMaybe vlib2(nullptr);
    PMaybe func(nullptr);

    libGet<id_dispatch>(val1,   lib, vlib1);
    libGet<id_dispatch>(val2, vlib1, vlib2);

    libGet(self, vlib2, func);
    func.call(_pair(_quote(val1), _quote(val2), self->getType()), lib, tunnel);
}

template <class T1, class Tr, int_t id,
    DeclOut<Tr> (*fr)(DeclOut<T1>),
    DeclOut<T1> (*fw)(DeclOut<Tr>)
>
_COTL_FUNC_T(libFunc)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(Ptr, id);

    if (!bool(fr) && !bool(fw)) {
        throw;
    } else if (bool(fr) && bool(fw)) {
        // OK
    } else {
        _COTL_CHECK_TUNNEL(bool(fw));
    }

    const PVal &arg(self_p->get());

    if (tunnel) {
        _COTL_CHECK_TYPE_ANY(tunnel, Tr, DefaultId<Tr>::get);

        PMaybe data(_in(fw(_out(tunnel_p))));
        arg.call<false>(caller, lib, data);

        tunnel = nullptr;
    } else {
        PMaybe data(nullptr);
        arg.call<true>(caller, lib, data);

        _COTL_CHECK_TYPE(data, T1, DefaultId<T1>::get);

        tunnel = _in(fr(_out(data_p)));
    }
_COTL_FUNC_END

template <class T1, class T2, class Tr, int_t id,
    DeclOut<Tr> (*fr)(DeclOut<T1>, DeclOut<T2>),
    DeclOut<T1> (*fw)(DeclOut<Tr>, DeclOut<T2>)
>
_COTL_FUNC_T(libFunc)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(Pair, id);

    if (!bool(fr) && !bool(fw)) {
        throw;
    } else if (bool(fr) && bool(fw)) {
        // OK
    } else {
        _COTL_CHECK_TUNNEL(bool(fw));
    }

    const PVal &arg1(self_p->get().first);
    const PVal &arg2(self_p->get().second);

    if (tunnel) {
        _COTL_CHECK_TYPE_ANY(tunnel, Tr, DefaultId<Tr>::get);

        PMaybe data2(nullptr);
        arg2.call<true>(caller, lib, data2);

        _COTL_CHECK_TYPE(data2, T2, DefaultId<T2>::get);

        PMaybe data1(_in(fw(_out(tunnel_p), _out(data2_p))));
        arg1.call<false>(caller, lib, data1);

        tunnel = nullptr;
    } else {
        PMaybe data1(nullptr);
        arg1.call<true>(caller, lib, data1);

        _COTL_CHECK_TYPE(data1, T1, DefaultId<T1>::get);

        PMaybe data2(nullptr);
        arg2.call<true>(caller, lib, data2);

        _COTL_CHECK_TYPE(data2, T2, DefaultId<T2>::get);

        tunnel = _in(fr(_out(data1_p), _out(data2_p)));
    }
_COTL_FUNC_END

// param list
template <class... T, class Tr,
    DeclOut<Tr> (*fr)(DeclOut...<T1>) // ???
>
_COTL_FUNC_T(libFuncParam)
_COTL_FUNC_BEGIN
// TODO
/*
    _COTL_CHECK_SELF(Pair, id);

    if (!bool(fr) && !bool(fw)) {
        throw;
    } else if (bool(fr) && bool(fw)) {
        // OK
    } else {
        _COTL_CHECK_TUNNEL(bool(fw));
    }

    const PVal &arg1(self_p->get().first);
    const PVal &arg2(self_p->get().second);

    if (tunnel) {
        _COTL_CHECK_TYPE_ANY(tunnel, Tr, DefaultId<Tr>::get);

        PMaybe data2(nullptr);
        arg2.call<true>(caller, lib, data2);

        _COTL_CHECK_TYPE(data2, T2, DefaultId<T2>::get);

        PMaybe data1(_in(fw(_out(tunnel_p), _out(data2_p))));
        arg1.call<false>(caller, lib, data1);

        tunnel = nullptr;
    } else {
        PMaybe data1(nullptr);
        arg1.call<true>(caller, lib, data1);

        _COTL_CHECK_TYPE(data1, T1, DefaultId<T1>::get);

        PMaybe data2(nullptr);
        arg2.call<true>(caller, lib, data2);

        _COTL_CHECK_TYPE(data2, T2, DefaultId<T2>::get);

        tunnel = _in(fr(_out(data1_p), _out(data2_p)));
    }*/
_COTL_FUNC_END

}

}

#endif
