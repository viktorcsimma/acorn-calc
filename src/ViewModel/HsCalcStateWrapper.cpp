#include "ViewModel/HsCalcStateWrapper.hpp"

// This initialises the Haskell runtime,
// creates the CalcState object
// and returns the HsStablePtr.
// It is only a separate function
// because we need it for initialisation;
// it should _not_ be used elsewhere.
HsStablePtr initHaskell(RealBaseType baseType) {
    // command-line arguments given to the Haskell runtime
    int argc = 1;
    const char* progname = "acorn-calc";
    const char* argv[] = { progname };
    // TODO: we have to put this somewhere else; the RTS should be initialised once
    hs_init(&argc, (char***) argv);

    return (Dyadic == baseType)
         ? initCalcDyadic()
         : initCalcRational();
}

HsCalcStateWrapper::HsCalcStateWrapper(RealBaseType baseType):
  calcStatePtr(initHaskell(baseType)), baseType(baseType) {}

std::string
  HsCalcStateWrapper::execCommand(const char* command, int precision) const {
    const char* result
      = (Dyadic == baseType)
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
      = (Dyadic == baseType)
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
    if (Dyadic == baseType) destructCalcDyadic(calcStatePtr);
    else destructCalcRational(calcStatePtr);

    // and we shut down the runtime
    // TODO: we have to put this somewhere else; the RTS cannot reinitialise itself after this
    hs_exit();
}
