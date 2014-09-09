#include "../cotl"

namespace cotl {

namespace {

int_t initListIndex = 0;

struct {
    func_t func;
    init_t init;
} initializerList[_COTL_VAL_INIT_SIZE];

}

inline
namespace published {

int_t addInitializer(const func_t func, const init_t init) {
    assert(initListIndex < _COTL_VAL_INIT_SIZE);

    initializerList[initListIndex] = {func, init};
    ++initListIndex;

    return 0;
}

void callInitializer(const PMaybe &lib) {
    PVal blank(_atom(id_error));
    PMaybe caller(nullptr);
    PMaybe tunnel(nullptr);

    for (int_t j = INIT_BEGIN; j < INIT_END; ++j) {
        for (int_t i = 0; i < initListIndex; ++i) {
            if (initializerList[i].init == j) {
                initializerList[i].func(blank, caller, lib, tunnel); // _COTL_CALL

                if (tunnel) {
                    throw;
                }
            }
        }
    }
}

void boot(const PVal &exec, PMaybe &tunnel) {
    PMaybe caller(nullptr);

    auto lib_p = _libmap();
    lib_p->getVar()->insert({{
        id_std, _ptr(lib_p, id_quote)
    }}); // add reference of self
    PMaybe lib(lib_p);

    callInitializer(lib);

    exec.call(caller, lib, tunnel);
}

}

}
