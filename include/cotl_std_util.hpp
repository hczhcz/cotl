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

#define _COTL_CHECK_TYPE(target, type, id) \
    auto target##_p = target.as<type, id>();\
    do {\
        if (!target##_p) {\
            throw "bad " #target " type";\
        }\
    } while (false)

#define _COTL_CHECK_TYPE_VAR(target, type, id) \
    auto target##_p = target.raw<type, id>();\
    do {\
        if (!target##_p) {\
            throw "bad " #target " type";\
        }\
    } while (false)

#define _COTL_CHECK_TUNNEL(exist) \
    do {\
        if (bool(tunnel) != (exist)) {\
            throw "bad tunnel existence";\
        }\
    } while (false)

inline void libGet(const PVal &target, const PMaybe &lib, PMaybe &tunnel) {
    lib.call<true>(target, nullptr, tunnel);
}

inline void libGet(const int_t type, const PMaybe &lib, PMaybe &tunnel) {
    libGet(_atom(type), lib, tunnel);
}

inline void libSet(const PVal &target, const PMaybe &lib, PMaybe &tunnel) {
    lib.call<false>(target, nullptr, tunnel);
}

inline void libSet(const int_t type, const PMaybe &lib, PMaybe &tunnel) {
    libSet(_atom(type), lib, tunnel);
}

inline void libExec(const PVal &target, const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel) {
    PMaybe data(nullptr);

    libGet(target, lib, data);

    data.call(caller, lib, tunnel);
}

template <bool ret>
inline void libExec(const PVal &target, const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel) {
    PMaybe data(nullptr);

    libGet(target, lib, data);

    data.call<ret>(caller, lib, tunnel);
}

inline void libExec(const int_t type, const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel) {
    libExec(_atom(type), caller, lib, tunnel);
}

template <bool ret>
inline void libExec(const int_t type, const PMaybe &caller, const PMaybe &lib, PMaybe &tunnel) {
    libExec<ret>(_atom(type), caller, lib, tunnel);
}

inline void doDispatch(
    const PVal &val,
    const PVal &self, const PMaybe &lib, PMaybe &tunnel
) {
    PMaybe dlib1(nullptr);
    PMaybe vlib1(nullptr);
    PMaybe func(nullptr);

    libGet(id_dispatch,   lib, dlib1);
    libGet(val,         dlib1, vlib1);

    libGet(self,        vlib1, func);
    func.call(_ptr(_ptr(val, id_quote), self->getType()), lib, tunnel);
}

inline void doDispatch(
    const PVal &val1, const PVal &val2,
    const PVal &self, const PMaybe &lib, PMaybe &tunnel
) {
    PMaybe dlib1(nullptr);
    PMaybe dlib2(nullptr);
    PMaybe vlib1(nullptr);
    PMaybe vlib2(nullptr);
    PMaybe func(nullptr);

    libGet(id_dispatch,   lib, dlib1);
    libGet(val1,        dlib1, vlib1);
    libGet(id_dispatch, vlib1, dlib2);
    libGet(val2,        dlib2, vlib2);

    libGet(self,        vlib2, func);
    func.call(_pair(_ptr(val1, id_quote), _ptr(val2, id_quote), self->getType()), lib, tunnel);
}

template <class T1, class Tr, int_t id,
    typename Tr::DataType (&fr)(
        const typename T1::DataType &
    ),
    typename T1::DataType (&fw)(
        const typename Tr::DataType &
    )
>
_COTL_FUNC_T(libFunc)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Ptr, id);

    if (tunnel) {
        _COTL_CHECK_TYPE(tunnel, Tr, id_any); // TODO id_any ??

        PMaybe data(_(fw(tunnel_p->get())));
        self_p->get->call<false>(caller, lib, data);

        tunnel = nullptr;
    } else {
        PMaybe data(nullptr);
        self_p->get->call<true>(caller, lib, data);

        _COTL_CHECK_TYPE(data, T1, id_any); // TODO id_any ??

        tunnel = _(fr(data_p->get()));
    }
_COTL_FUNC_END

template <class T1, class T2, class Tr, int_t id,
    typename Tr::DataType (&fr)(
        const typename T1::DataType &,
        const typename T2::DataType &
    ),
    typename T1::DataType (&fw)(
        const typename Tr::DataType &,
        const typename T2::DataType &
    )
>
_COTL_FUNC_T(libFunc)
_COTL_FUNC_BEGIN
    _COTL_CHECK_SELF(cotl::Pair, id);
    const PVal &first(self_p->get().first);
    const PVal &second(self_p->get().second);

    if (tunnel) {
        _COTL_CHECK_TYPE(tunnel, Tr, id_any); // TODO id_any ??

        PMaybe data2(nullptr);
        second.call<true>(caller, lib, data2);

        _COTL_CHECK_TYPE(data2, T2, id_any); // TODO id_any ??

        PMaybe data1(_(fw(tunnel_p->get(), data2_p->get())));
        first.call<false>(caller, lib, data1);

        tunnel = nullptr;
    } else {
        PMaybe data1(nullptr);
        first.call<true>(caller, lib, data1);

        _COTL_CHECK_TYPE(data1, T1, id_any); // TODO id_any ??

        PMaybe data2(nullptr);
        second.call<true>(caller, lib, data2);

        _COTL_CHECK_TYPE(data2, T2, id_any); // TODO id_any ??

        tunnel = _(fr(data1_p->get(), data2_p->get()));
    }
_COTL_FUNC_END

}

#endif
