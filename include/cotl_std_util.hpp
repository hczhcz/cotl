#ifndef _COTL_STD_UTIL_HPP
#define _COTL_STD_UTIL_HPP

#include "cotl_helper.hpp"

namespace cotlstd {

#define _COTL_FUNC_BEGIN \
    try {\
        (void) self; (void) caller; (void) lib; (void) tunnel;\
        {

#ifdef _COTL_USE_ERR_CATCH
    #define _COTL_FUNC_END \
            }\
        } catch (cotl::PValRaw e) {\
            throw _arr(\
                self, caller.sure(), lib.sure(), tunnel.sure(),\
                e,\
                id_error\
            );\
        } catch (const char *c) {\
            throw _arr(\
                self, caller.sure(), lib.sure(), tunnel.sure(),\
                _str(c, id_error),\
                id_error\
            );\
        } catch (...) {\
            throw _arr(\
                self, caller.sure(), lib.sure(), tunnel.sure(),\
                _str("unknown error", id_error),\
                id_error\
            );\
        }
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
    auto val##_p = val.as<type, id>();\
    do {\
        if (!val##_p) {\
            doCast(id, lib, val);\
        }\
    } while (false) // TODO cast, dispatch

#define _COTL_CHECK_TYPE_VAR(val, type, id) \
    auto val##_p = val.raw<type, id>();\
    do {\
        if (!val##_p) {\
            doCast(id, lib, val);\
        }\
    } while (false) // TODO cast, dispatch

#define _COTL_CHECK_TUNNEL(exist) \
    do {\
        if (bool(tunnel) != (exist)) {\
            throw "bad tunnel existence";\
        }\
    } while (false)

template <std::nullptr_t placeholder = nullptr> // void arg template
inline void libGet(const PVal &val, const PMaybe &lib, PMaybe &tunnel) {
    lib.call<true>(val, nullptr, tunnel);
}

template <int_t type, int_t... Args>
inline void libGet(const PVal &val, const PMaybe &lib, PMaybe &tunnel) {
    PMaybe tunnel1(nullptr);

    libGet(_atom(type), lib, tunnel1);
    libGet<Args...>(val, tunnel1, tunnel);
}

template <int_t... Args>
inline void libGet(const int_t type, const PMaybe &lib, PMaybe &tunnel) {
    libGet<Args...>(_atom(type), lib, tunnel);
}

template <std::nullptr_t placeholder = nullptr> // void arg template
inline void libSet(const PVal &val, const PMaybe &lib, PMaybe &tunnel) {
    lib.call<false>(val, nullptr, tunnel);
}

template <int_t type, int_t... Args>
inline void libSet(const PVal &val, const PMaybe &lib, PMaybe &tunnel) {
    PMaybe tunnel1(nullptr);

    libGet(_atom(type), lib, tunnel1);
    libSet<Args...>(val, tunnel1, tunnel);
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

inline void doCast(
    const int_t id, const PMaybe &lib, PMaybe &val
) {
    PMaybe func(nullptr);

    libGet<id_cast>(id, lib, func);

    PMaybe caller(_ptr(_ptr(PVal(val), id_quote), id));
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
    func.call(_ptr(_ptr(val, id_quote), self->getType()), lib, tunnel);
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
    func.call(_pair(_ptr(val1, id_quote), _ptr(val2, id_quote), self->getType()), lib, tunnel);
}

template <class T1, class Tr, int_t id,
    typename Tr::DataType (*fr)(typename T1::DataType),
    typename T1::DataType (*fw)(typename Tr::DataType)
>
_COTL_FUNC_T(libFunc)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id);

    if (!bool(fr) && !bool(fw)) {
        throw;
    } else if (bool(fr) && bool(fw)) {
        // OK
    } else {
        _COTL_CHECK_TUNNEL(bool(fw));
    }

    const PVal &arg(self_p->get());

    if (tunnel) {
        _COTL_CHECK_TYPE(tunnel, Tr, id_any); // TODO id_any ??

        PMaybe data(_(fw(tunnel_p->get())));
        arg.call<false>(caller, lib, data);

        tunnel = nullptr;
    } else {
        PMaybe data(nullptr);
        arg.call<true>(caller, lib, data);

        _COTL_CHECK_TYPE(data, T1, id_any); // TODO id_any ??

        tunnel = _(fr(data_p->get()));
    }
_COTL_FUNC_END

template <class T1, class T2, class Tr, int_t id,
    typename Tr::DataType (*fr)(typename T1::DataType, typename T2::DataType),
    typename T1::DataType (*fw)(typename Tr::DataType, typename T2::DataType)
>
_COTL_FUNC_T(libFunc)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id);

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
        _COTL_CHECK_TYPE(tunnel, Tr, id_any); // TODO id_any ??

        PMaybe data2(nullptr);
        arg2.call<true>(caller, lib, data2);

        _COTL_CHECK_TYPE(data2, T2, id_any); // TODO id_any ??

        PMaybe data1(_(fw(tunnel_p->get(), data2_p->get())));
        arg1.call<false>(caller, lib, data1);

        tunnel = nullptr;
    } else {
        PMaybe data1(nullptr);
        arg1.call<true>(caller, lib, data1);

        _COTL_CHECK_TYPE(data1, T1, id_any); // TODO id_any ??

        PMaybe data2(nullptr);
        arg2.call<true>(caller, lib, data2);

        _COTL_CHECK_TYPE(data2, T2, id_any); // TODO id_any ??

        tunnel = _(fr(data1_p->get(), data2_p->get()));
    }
_COTL_FUNC_END

}

#endif
