#ifndef ARG_OPTION_H
#define ARG_OPTION_H

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

namespace arg {

class Option {
public:
    using Action = std::function<void(const std::string& value)>;

    Option(const std::string& name, const char symbol, const std::string& help, bool& enabledValue)
        : Option{name, symbol, help, "", [&enabledValue](const std::string& value) { enabledValue = true; }} {}

    Option(const std::string& name, const char symbol, const std::string& help, const std::string& valueName, std::string& bindedValue)
        : Option{name, symbol, help, valueName, [&bindedValue](const std::string& value) { bindedValue = value; }} {}

    [[nodiscard]]
    const std::string& name() const {
        return name_;
    }

    [[nodiscard]]
    bool hasSymbol() const {
        return symbol_ != 0;
    }

    [[nodiscard]]
    char symbol() const {
        return symbol_;
    }

    [[nodiscard]]
    bool hasValue() const {
        return !value_.empty();
    }

    [[nodiscard]]
    const std::string& value() const {
        return value_;
    }

    void action(const std::string& value) const {
        if (!action_.has_value()) {
            return;
        }

        auto action = action_.value();
        action(value);
    }

    [[nodiscard]] const std::string& help() const {
        return help_;
    }

private:
    Option(std::string name, char symbol, std::string help, std::string value,
           std::optional<Action> action)
        : symbol_{symbol}, name_{std::move(name)}, value_{std::move(value)},
          action_{std::move(action)}, help_{std::move(help)} {}

    const char symbol_;
    const std::string name_;
    const std::string value_;
    const std::optional<Action> action_;
    const std::string help_;
};

}

#endif //ARG_OPTION_H
