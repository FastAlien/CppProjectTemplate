#pragma once
#ifndef ARG_HELPFORMATTER_HPP
#define ARG_HELPFORMATTER_HPP

#include <string>
#include <vector>

namespace arg {

class Option;

class HelpFormatter {
public:
  [[nodiscard]] std::string format(const std::vector<Option>& options) const;
};

} // namespace arg

#endif //ARG_HELPFORMATTER_HPP
