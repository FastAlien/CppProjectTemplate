#include "arg/ArgumentParser.hpp"

#include "arg/Option.hpp"
#include "arg/ParseError.hpp"

#include <algorithm>
#include <cstddef>
#include <optional>
#include <string>

namespace arg {

std::vector<ParseError> ArgumentParser::parse(const int argc, const char** argv) const {
  std::vector<ParseError> errors;

  // argv[0] is program filename
  for (int i = 1; i < argc; ++i) {
    const std::string argument{argv[i]};
    const std::variant<Option, ParseError::Type> result = findOption(argument);
    constexpr size_t parseErrorIndex = 1;

    if (result.index() == parseErrorIndex) {
      errors.emplace_back(std::get<ParseError::Type>(result), argument);
      continue;
    }

    const auto& option = std::get<Option>(result);

    if (!option.hasParameter()) {
      option.executeAction();
      continue;
    }

    if (i >= argc - 1) {
      errors.emplace_back(ParseError::Type::MissingParameter, argument);
      continue;
    }

    option.executeAction(argv[++i]);
  }

  return errors;
}

std::variant<Option, ParseError::Type> ArgumentParser::findOption(const std::string& argument) const {
  if (argument[0] != '-') {
    return ParseError::Type::InvalidFormat;
  }

  if (argument.length() == 2) {
    auto option = findOptionBySymbol(argument[1]);
    if (!option) {
      return ParseError::Type::UnknownArgument;
    }
    return option.value();
  }

  if (argument[1] != '-') {
    return ParseError::Type::InvalidFormat;
  }

  auto option = findOptionByName(argument.substr(2));
  if (!option) {
    return ParseError::Type::UnknownArgument;
  }
  return option.value();
}

std::optional<Option> ArgumentParser::findOptionBySymbol(const char symbol) const {
  auto symbolEquals = [symbol](const Option& option) {
    return option.hasSymbol() && option.getSymbol() == symbol;
  };
  return findOption(symbolEquals);
}

std::optional<Option> ArgumentParser::findOptionByName(const std::string& name) const {
  auto nameEquals = [&name](const Option& option) {
    return option.getName() == name;
  };
  return findOption(nameEquals);
}

std::optional<Option> ArgumentParser::findOption(const ArgumentParser::FindOptionPredicate& predicate) const {
  auto it = std::find_if(options_.begin(), options_.end(), predicate);

  if (it == options_.end()) {
    return {};
  }

  return {*it};
}

} // namespace arg
