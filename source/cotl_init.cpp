#include "../cotl"

namespace cotl {

namespace {

const int_t initListSize = 4096;
int_t initListIndex = 0;
func_t initializerList[initListSize];

}

inline
namespace published {

int_t addInitializer(func_t func) {
    assert(initListIndex < initListSize);

    initializerList[initListIndex] = func;
    ++initListIndex;

    return 0;
}

void callInitializer(const PVal &lib) {
    PVal blank(_atom(id_error));
    PMaybe caller(nullptr);
    PMaybe tunnel(nullptr);

    for (int_t i = 0; i < initListIndex; ++i) {
        initializerList[i](blank, caller, lib, tunnel); // _COTL_CALL

        if (tunnel) {
            throw;
        }
    }
}

void boot(const PVal &exec, PMaybe &tunnel) {
    PMaybe caller(nullptr);
    PVal lib(_atom()); // TODO // lib = (not_found, arr())

    callInitializer(lib);

    exec(caller, lib, tunnel); // _COTL_CALL
}

}

}
