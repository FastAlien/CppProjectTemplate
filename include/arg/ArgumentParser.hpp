#pragma once
#ifndef ARG_ARGUMENTPARSER_HPP
#define ARG_ARGUMENTPARSER_HPP

#include "ParseError.hpp"

#include <functional>
#include <initializer_list>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace arg {

class Option;

class ArgumentParser {
public:
  explicit ArgumentParser(std::vector<Option> options)
      : options_{std::move(options)} {}

  ArgumentParser(std::initializer_list<Option> options)
      : options_{options} {}

  std::vector<ParseError> parse(int argc, const char** argv) const;

private:
  using FindOptionPredicate = std::function<bool(const Option&)>;

  [[nodiscard]] std::variant<Option, ParseError::Type> findOption(const std::string& argument) const;
  [[nodiscard]] std::optional<Option> findOptionBySymbol(char symbol) const;
  [[nodiscard]] std::optional<Option> findOptionByName(const std::string& name) const;
  [[nodiscard]] std::optional<Option> findOption(const FindOptionPredicate& predicate) const;

  const std::vector<Option> options_;
};

} // namespace arg

#endif // ARG_ARGUMENTPARSER_HPP
