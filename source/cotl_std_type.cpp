#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    PMaybe caller1(nullptr);
    PMaybe lib1(nullptr);
    PMaybe tunnel1(nullptr);

    caller1 = _atom(id_atom);
    tunnel1 = _func(stdLiteral, id_func, stdLibFunc);
    lib.call<false>(caller1, lib1, tunnel1); // _COTL_CALL

    caller1 = _atom(id_int);
    tunnel1 = _func(stdLiteral, id_func, stdLibFunc);
    lib.call<false>(caller1, lib1, tunnel1); // _COTL_CALL

    caller1 = _atom(id_real);
    tunnel1 = _func(stdLiteral, id_func, stdLibFunc);
    lib.call<false>(caller1, lib1, tunnel1); // _COTL_CALL

    caller1 = _atom(id_func);
    tunnel1 = _func(stdLibFunc, id_func, stdLibFunc);
    lib.call<false>(caller1, lib1, tunnel1); // _COTL_CALL

    caller1 = _atom(id_ptr);
    tunnel1 = _func(stdWrapPtr, id_func, stdLibFunc);
    lib.call<false>(caller1, lib1, tunnel1); // _COTL_CALL

    caller1 = _atom(id_pair);
    tunnel1 = _func(stdWrapPair, id_func, stdLibFunc);
    lib.call<false>(caller1, lib1, tunnel1); // _COTL_CALL

    caller1 = _atom(id_str);
    tunnel1 = _func(stdLiteral, id_func, stdLibFunc);
    lib.call<false>(caller1, lib1, tunnel1); // _COTL_CALL

    caller1 = _atom(id_arr);
    tunnel1 = _func(stdWrapArr, id_func, stdLibFunc);
    lib.call<false>(caller1, lib1, tunnel1); // _COTL_CALL

    caller1 = _atom(id_map);
    tunnel1 = _func(stdLibMap, id_func, stdLibFunc);
    lib.call<false>(caller1, lib1, tunnel1); // _COTL_CALL
_COTL_FUNC_END

long long ago = addInitializer(init, init_core);

}

}
