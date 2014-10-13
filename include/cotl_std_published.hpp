#ifndef _COTL_STD_RUNTIME_HPP
#define _COTL_STD_RUNTIME_HPP

#include "cotl_helper.hpp"

namespace cotl {

namespace stdlib {

// runtime
_COTL_FUNC_T(stdAuto);
_COTL_FUNC_T(stdLiteral);
_COTL_FUNC_T(stdBind);

_COTL_FUNC_T(stdQuote);
_COTL_FUNC_T(stdContainer);
_COTL_FUNC_T(stdBlackhole);

// type
_COTL_FUNC_T(stdLibFunc);
_COTL_FUNC_T(stdLibMap);
_COTL_FUNC_T(stdWrapPtr);
_COTL_FUNC_T(stdWrapPair);
_COTL_FUNC_T(stdWrapArr);

// query
_COTL_FUNC_T(stdUse);
_COTL_FUNC_T(stdWith);
_COTL_FUNC_T(stdWithnew);
_COTL_FUNC_T(stdCapture);

}

}

#endif
