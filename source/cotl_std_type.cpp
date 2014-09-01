#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel


_COTL_FUNC_ALIAS(stdAtom, stdLiteral)
_COTL_FUNC_ALIAS(stdInt, stdLiteral)
_COTL_FUNC_ALIAS(stdReal, stdLiteral)
_COTL_FUNC_ALIAS_DECL(stdFunc, stdLibFunc)
_COTL_FUNC_ALIAS_DECL(stdPtr, stdWrapPtr)
_COTL_FUNC_ALIAS_DECL(stdPair, stdWrapPair)
_COTL_FUNC_ALIAS(stdStr, stdLiteral)
_COTL_FUNC_ALIAS_DECL(stdArr, stdWrapArr)

_COTL_FUNC_T(initType)
_COTL_FUNC_BEGIN
    // TODO
    (void) stdAtom;
    (void) stdInt;
    (void) stdReal;
    (void) stdFunc;
    (void) stdPtr;
    (void) stdPair;
    (void) stdStr;
    (void) stdArr;

_COTL_FUNC_END

namespace {

long long ago = addInitializer(initType);

}

}
