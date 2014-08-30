#include "../cotl"

namespace cotl {

namespace {

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
    PMaybe tunnel(nullptr);

    for (int_t i = 0; i < initListIndex; ++i) {
        initializerList[i](blank, blank, lib, tunnel);

        if (tunnel) {
            throw;
        }
    }
}

}

}
