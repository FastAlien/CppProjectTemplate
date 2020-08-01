#include "arg/HelpFormatter.hpp"
#include "arg/Option.hpp"

#include <string>
#include <vector>

namespace {

std::string formatOption(const arg::Option& option) {
  std::string help;
  help += ' ';

  if (option.hasSymbol()) {
    help += '-';
    help += option.getSymbol();
  } else {
    help += "  ";
  }

  help += " --";
  help += option.getName();
  help += ' ';

  if (option.hasParameter()) {
    help += '<';
    help += option.getParameter();
    help += "> ";
  }

  help += "  ";
  help += option.getDescription();
  help += '\n';

  return help;
}

} // namespace

namespace arg {

std::string HelpFormatter::format(const std::vector<Option>& options) const {
  std::string help;
  for (const auto& option : options) {
    help += formatOption(option);
  }
  return help;
}

} // namespace arg
