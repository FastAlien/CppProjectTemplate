#pragma once
#ifndef ARG_PARSEERROR_HPP
#define ARG_PARSEERROR_HPP

#include <string>

namespace arg {

class ParseError {
public:
  enum class Type {
    InvalidFormat,
    UnknownArgument,
    MissingParameter
  };

  ParseError(const Type type, std::string argument)
      : type_{type},
        argument_{std::move(argument)} {}

  [[nodiscard]] Type getType() const {
    return type_;
  }

  [[nodiscard]] const std::string& getArgument() const {
    return argument_;
  }

private:
  const Type type_;
  const std::string argument_;
};

} // namespace arg

#endif //ARG_PARSEERROR_HPP
