#ifndef HS_CALC_STATE_WRAPPER_HPP_
#define HS_CALC_STATE_WRAPPER_HPP_

#include <string>

#include <TinyHsFFI.h>
#include "Acorn.h"

#include "ViewModel/RealBaseType.hpp"

class HsCalcStateWrapper {
    private:
    static const RealBaseType DEFAULT_BASE_TYPE = DyadicBase;

    // Indicates whether the Haskell r

    // A pointer to the Haskell CalcState object;
    // this is what will be passed to Haskell functions.
    const HsStablePtr calcStatePtr;
    // The underlying type of reals
    // (e.g. Dyadic if the object is a CalcState (C Dyadic)).
    // For now, this can't be changed;
    // the only way is to create a new CalcState object,
    // with all variables lost.
    // (But there wouldn't be much demand, anyway.)
    const RealBaseType baseType;

    public:
    // The constructor.
    // This creates the Haskell object and fetches its pointer.
    // Beware: it assumes that the runtime has been initalised.
    HsCalcStateWrapper(RealBaseType baseType = DEFAULT_BASE_TYPE);
    // Executes a command and returns a string as a result,
    // in the format "0.12345 :: Rational".
    // Might return an error (starting with "error:").
    // The precision is given in the number of digits after the decimal point.
    std::string execCommand(const char* command, int precision) const;
    // Recalculates the last result with another precision.
    // Note that this does _not_ have the side effects tthere possible were.
    std::string reevalCommand(int precision) const;

    // The destructor.
    // This also frees the StablePtr
    // but does not shut down the runtime.
    ~HsCalcStateWrapper();

    // We delete the copy constructor and the assignment operator.
    HsCalcStateWrapper(const HsCalcStateWrapper& temp_obj) = delete; 
    HsCalcStateWrapper& operator=(const HsCalcStateWrapper& temp_obj) = delete; 
};

#endif
