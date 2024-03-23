#include "ViewModel/HsCalcStateWrapper.hpp"

// This creates the CalcState object
// and returns the HsStablePtr.
// It is only a separate function
// because we need it for initialisation;
// it should _not_ be used elsewhere.
HsStablePtr initStablePtr(RealBaseType baseType) {
    return (DyadicBase == baseType)
         ? initCalcDyadic()
         : initCalcRational();
}

HsCalcStateWrapper::HsCalcStateWrapper(RealBaseType baseType):
  calcStatePtr(initStablePtr(baseType)), baseType(baseType) {}

std::string
  HsCalcStateWrapper::execCommand(const char* command, int precision) const {
    const char* result
      = (DyadicBase == baseType)
      ? (char*) execCommandDyadic(calcStatePtr, (char*) command, precision)
      : (char*) execCommandRational(calcStatePtr, (char*) command, precision);
    // we copy it into a string
    std::string toReturn(result);
    // in theory, this can be freed from here
    free((void *) result);
    // and we hope this gets a return-value optimisation
    return toReturn;
}

std::string HsCalcStateWrapper::reevalCommand(int precision) const {
    // similarly
    const char* result
      = (DyadicBase == baseType)
      ? (char*) reevalCommandDyadic(calcStatePtr, precision)
      : (char*) reevalCommandDyadic(calcStatePtr, precision);
    // we copy it into a string
    std::string toReturn(result);
    // in theory, this can be freed from here
    free((void *) result);
    // and we hope this gets a return-value optimisation
    return toReturn;
}

HsCalcStateWrapper::~HsCalcStateWrapper() {
    // there is no guarantee that a StablePtr is anything meaningful,
    // so we have to free it from Haskell
    if (DyadicBase == baseType) destructCalcDyadic(calcStatePtr);
    else destructCalcRational(calcStatePtr);
}
