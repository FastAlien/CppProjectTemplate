#include "arg/HelpFormatter.hpp"

#include "arg/Option.hpp"

#include <algorithm>
#include <string>
#include <vector>

namespace arg {

std::string HelpFormatter::format(const std::vector<Option>& options) const {
  std::string help;
  std::for_each(options.begin(), options.end(), [this, &help](const Option& option) { appendOptionHelp(help, option); });
  return help;
}

void HelpFormatter::appendOptionHelp(std::string& help, const Option& option) const {
  help += ' ';

  if (option.hasSymbol()) {
    help += '-';
    help += option.getSymbol();
    help += ' ';
  }

  help += "--";
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
}

} // namespace arg
