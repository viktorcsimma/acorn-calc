#include "ViewModel/HsCalcStateWrapper.hpp"
#include "Acorn.h"

#include <csignal> // for SIGINT

// This creates the CalcState object
// and returns the HsStablePtr.
// It is only a separate function
// because we need it for initialisation;
// it should _not_ be used elsewhere.
static HsStablePtr initStablePtr(RealBaseType baseType) {
    return (DyadicBase == baseType)
         ? initCalcDyadic()
         : initCalcRational();
}

HsCalcStateWrapper::HsCalcStateWrapper(RealBaseType baseType):
    calcStatePtr(initStablePtr(baseType)), baseType(baseType), computationThread(nullptr) {}

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

bool HsCalcStateWrapper::interruptEvaluation() {
    if (computationThread) {
        // the SIGINT signal is handled on the Haskell side
        // TODO: this is POSIX-specific;
        // we should solve it on Windows too
        pthread_kill(computationThread->native_handle(), SIGINT);
        // let's join it; that is safer
        // hopefully, it ends quickly
        computationThread->join();

        delete(computationThread);
        computationThread = nullptr;
        return true;
    } else return false;
}

HsCalcStateWrapper::~HsCalcStateWrapper() {
    interruptEvaluation();

    // there is no guarantee that a StablePtr is anything meaningful,
    // so we have to free it from Haskell
    if (DyadicBase == baseType) destructCalcDyadic(calcStatePtr);
    else destructCalcRational(calcStatePtr);
}
