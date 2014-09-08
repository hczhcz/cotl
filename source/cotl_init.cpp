#include "../cotl"

namespace cotl {

namespace {

const int_t initListSize = 4096;
int_t initListIndex = 0;

struct {
    func_t func;
    init_t init;
} initializerList[initListSize];

}

inline
namespace published {

int_t addInitializer(const func_t func, const init_t init) {
    assert(initListIndex < initListSize);

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
    PMaybe lib(_libmap());

    callInitializer(lib);

    exec(caller, lib, tunnel); // _COTL_CALL
}

}

}
