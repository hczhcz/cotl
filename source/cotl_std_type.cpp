#include "../cotl"

namespace cotlstd {

// arg: self, caller, lib, tunnel

// TODO: use function directly
//       remove alias
/*_COTL_FUNC_ALIAS(stdAtom, stdLiteral)
_COTL_FUNC_ALIAS(stdInt, stdLiteral)
_COTL_FUNC_ALIAS(stdReal, stdLiteral)
_COTL_FUNC_ALIAS_DECL(stdFunc, stdLibFunc)
_COTL_FUNC_ALIAS_DECL(stdPtr, stdWrapPtr)
_COTL_FUNC_ALIAS_DECL(stdPair, stdWrapPair)
_COTL_FUNC_ALIAS(stdStr, stdLiteral)
_COTL_FUNC_ALIAS_DECL(stdArr, stdWrapArr)
_COTL_FUNC_ALIAS_DECL(stdMap, stdLibMap)*/

namespace {

_COTL_FUNC_T(init)
_COTL_FUNC_BEGIN
    // TODO
    /*(void) stdAtom;
    (void) stdInt;
    (void) stdReal;
    (void) stdFunc;
    (void) stdPtr;
    (void) stdPair;
    (void) stdStr;
    (void) stdArr;
    (void) stdMap;*/

_COTL_FUNC_END

long long ago = addInitializer(init);

}

}
