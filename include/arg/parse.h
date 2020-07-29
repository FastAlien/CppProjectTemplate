#ifndef ARG_PARSE_H
#define ARG_PARSE_H

#include "option.h"

#include <algorithm>
#include <functional>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace arg {

class ArgumentParser {
public:
    explicit ArgumentParser(std::vector<Option> options)
        : options_{std::move(options)} {}

    void parse(int argc, const char** argv) const;

private:
    using FindOptionPredicate = std::function<bool(const Option&)>;

    [[nodiscard]]
    std::optional<Option> findOptionBySymbol(const char symbol) const {
        auto symbolEquals = [symbol](const Option& option) {
            return option.hasSymbol() && option.symbol() == symbol;
        };
        return findOption(symbolEquals);
    }

    [[nodiscard]]
    std::optional<Option> findOptionByName(const std::string& name) const {
        auto nameEquals = [&name](const Option& option) {
            return option.name() == name;
        };
        return findOption(nameEquals);
    }

    [[nodiscard]]
    std::optional<Option> findOption(const FindOptionPredicate& predicate) const {
        auto it = std::find_if(options_.begin(), options_.end(), predicate);
        if (it == options_.end()) {
            return std::nullopt;
        }
        return *it;
    }

    std::vector<Option> options_;
};

}

#endif //ARG_PARSE_H
