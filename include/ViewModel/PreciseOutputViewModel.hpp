#ifndef PRECISE_OUTPUT_VIEW_MODEL_HPP_
#define PRECISE_OUTPUT_VIEW_MODEL_HPP_

#include "ViewModel/HsCalcStateWrapper.hpp"

#include <string>

// Represents the members
// the precise output window needs.
// Contains a HsCalcStateWrapper pointer
// which, however, does _not_ get freed on destruction
// (that remains the responsibility of the main view model).
class PreciseOutputViewModel {
    private:
        const HsCalcStateWrapper* calcStateWrapper;
        int precision;
        std::string result;
    public:
        // Gets a pointer to an already-initialised HsCalcStateWrapper
        // which does _not_ get freed on destruction.
        // It also gets the initial result string
        // so that it need not be reevaluated immediately.
        PreciseOutputViewModel(HsCalcStateWrapper* calcStateWrapper,
                               int initialPrecision,
                               std::string initialResult);
        // Sets a new precision and reevaluates the output with it.
        void setPrecision (int precision);
        // A getter for a reference to the result string to be displayed.
        const std::string& getResult() const;
};

#endif
