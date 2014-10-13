#include "../cotl"

namespace cotl {

namespace {

int_t initListIndex = 0;

struct {
    func_t func;
    initutil::init_t init;
} initializerList[_COTL_VAL_INIT_SIZE];

}

int_t initutil::addInitializer(const func_t func, const init_t init) {
    assert(initListIndex < _COTL_VAL_INIT_SIZE);

    initializerList[initListIndex] = {func, init};
    ++initListIndex;

    return 0;
}

void initutil::callInitializer(const PMaybe &lib) {
    PVal blank(_atom(id_error));
    PMaybe tunnel(nullptr);

    for (int_t j = INIT_BEGIN; j < INIT_END; ++j) {
        for (int_t i = 0; i < initListIndex; ++i) {
            if (initializerList[i].init == j) {
                initializerList[i].func(blank, nullptr, lib, tunnel); // _COTL_CALL

                if (tunnel) {
                    throw "bad initializer call return";
                }
            }
        }
    }
}

void util::boot(const PVal &exec, PMaybe &tunnel) try {
    auto lib_p = _libmap();
    PMaybe lib(lib_p);

    lib_p->getVar()->insert({{
        id_std, lib_p
    }}); // add reference of self

    // TODO not only stdlib

    initutil::callInitializer(lib);

    exec.call(nullptr, lib, tunnel);
#ifdef _COTL_USE_ERR_CATCH
} catch (PValRaw e) {
    PVal val(e); // hold the object

    std::cerr << "ERROR" << std::endl;
    std::cerr << val << std::endl;
} catch (...) {
    std::cerr << "ERROR" << std::endl;
    std::cerr << "_str(\"unknown error from root\", id_error)" << std::endl;
}
#else
} catch (...) {
    std::cerr << "ERROR" << std::endl;
    throw;
}
#endif

}
