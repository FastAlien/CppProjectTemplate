#ifndef ARG_OPTION_H
#define ARG_OPTION_H

#include <functional>
#include <optional>
#include <string>

namespace arg {

class Option {
public:
    Option(const char symbol, const std::string& name, const std::string& description, bool& enabledValue)
        : Option{symbol, name, description, "", [&enabledValue](const std::string& value) { enabledValue = true; }} {}

    Option(const std::string& name, const std::string& description, bool& enabledValue)
        : Option{0, name, description, "", [&enabledValue](const std::string& value) { enabledValue = true; }} {}

    Option(const char symbol, const std::string& name, const std::string& description, const std::string& valueName, std::string& bindedValue)
        : Option{symbol, name, description, valueName, [&bindedValue](const std::string& value) { bindedValue = value; }} {}

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

    void executeAction(const std::string& value) const {
        if (action_.has_value()) {
            auto action = action_.value();
            action(value);
        }
    }

    [[nodiscard]]
    const std::string& help() const {
        return help_;
    }

private:
    using Action = std::function<void(const std::string& value)>;

    Option(char symbol, std::string name, std::string help, std::string value, std::optional<Action> action);

    const char symbol_;
    const std::string name_;
    const std::string value_;
    const std::optional<Action> action_;
    const std::string help_;
};

}

#endif //ARG_OPTION_H
