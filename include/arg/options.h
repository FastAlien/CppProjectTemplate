#ifndef ARG_OPTIONS_H
#define ARG_OPTIONS_H

#include "option.h"

#include <algorithm>
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace arg {

class Options {
public:
    Options() = default;

    explicit Options(std::initializer_list<Option> options)
        : options_{options} {}

    Options& addOption(Option option) {
        options_.emplace_back(std::move(option));
        return *this;
    }

    auto begin() const {
        return options_.begin();
    }

    auto end() const {
        return options_.end();
    }

    [[nodiscard]]
    std::optional<Option> findBySymbol(const char symbol) const {
        auto symbolEquals = [symbol](const Option& option) {
            return option.hasSymbol() && option.symbol() == symbol;
        };
        return findOption(symbolEquals);
    }

    [[nodiscard]]
    std::optional<Option> findByName(const std::string& name) const {
        auto nameEquals = [&name](const Option& option) {
            return option.name() == name;
        };
        return findOption(nameEquals);
    }

private:
    using FindOptionPredicate = std::function<bool(const Option&)>;

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

#endif //ARG_OPTIONS_H
