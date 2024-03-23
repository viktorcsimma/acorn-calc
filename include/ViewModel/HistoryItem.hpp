#ifndef HISTORY_ITEM_HPP_
#define HISTORY_ITEM_HPP_

#include <string>

// An expression and its result (given by strings)
// in the history.
struct HistoryItem {
    public:
        const std::string expression;
        const std::string result;

        HistoryItem(const std::string expression, const std::string result):
            expression(expression), result(result) {}
};

#endif
