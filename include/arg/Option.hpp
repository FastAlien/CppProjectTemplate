#pragma once
#ifndef ARG_OPTION_HPP
#define ARG_OPTION_HPP

#include <functional>
#include <optional>
#include <string>

namespace arg {

class Option {
public:
  Option(const std::string& name, const std::string& description, bool& boundValue)
      : Option{0, name, description, boundValue} {}

  Option(const char symbol, const std::string& name, const std::string& description, bool& boundValue)
      : Option{symbol, name, description, std::nullopt, [&boundValue](const std::string& value) { boundValue = true; }} {}

  Option(const std::string& name, const std::string& description, const std::string& parameterName, std::string& boundValue)
      : Option{0, name, description, parameterName, boundValue} {}

  Option(const char symbol, const std::string& name, const std::string& description, const std::string& parameterName, std::string& boundValue)
      : Option{symbol, name, description, parameterName, [&boundValue](const std::string& value) { boundValue = value; }} {}

  [[nodiscard]] bool hasSymbol() const {
    return symbol_ != 0;
  }

  [[nodiscard]] char getSymbol() const {
    return symbol_;
  }

  [[nodiscard]] const std::string& getName() const {
    return name_;
  }

  [[nodiscard]] const std::string& getDescription() const {
    return description_;
  }

  [[nodiscard]] bool hasParameter() const {
    return parameterName_.has_value();
  }

  [[nodiscard]] const std::string& getParameter() const {
    return parameterName_.value();
  }

  void executeAction(const std::string& value = "") const {
    action_(value);
  }

private:
  using Action = std::function<void(const std::string& value)>;

  Option(const char symbol, std::string name, std::string description, std::optional<std::string> parameterName, Action action)
      : symbol_{symbol},
        name_{std::move(name)},
        description_{std::move(description)},
        parameterName_{std::move(parameterName)},
        action_{std::move(action)} {}

  const char symbol_;
  const std::string name_;
  const std::string description_;
  const std::optional<std::string> parameterName_;
  Action action_;
};

} // namespace arg

#endif //ARG_OPTION_HPP
