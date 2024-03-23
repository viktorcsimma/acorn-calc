#include "ViewModel/PreciseOutputViewModel.hpp"

PreciseOutputViewModel::PreciseOutputViewModel
        (HsCalcStateWrapper* calcStateWrapper,
         int initialPrecision,
         std::string initialResult):
    calcStateWrapper(calcStateWrapper),
    precision(initialPrecision), result(initialResult) {}

void PreciseOutputViewModel::setPrecision(int precision) {
    this->precision = precision;
    // this does not have side effects
    result = calcStateWrapper->reevalCommand(precision);
}

const std::string& PreciseOutputViewModel::getResult() const {
    return result;
}
