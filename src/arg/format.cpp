#include "arg/format.h"

#include "arg/option.h"

#include <algorithm>
#include <string>
#include <vector>

namespace {

std::string formatOption(const arg::Option& option) {
    std::string help;

    help += ' ';

    if (option.hasSymbol()) {
        help += '-';
        help += option.symbol();
    } else {
        help += "  ";
    }

    help += " --";
    help += option.name();
    help += ' ';

    if (option.hasValue()) {
        help += '<';
        help += option.value();
        help += "> ";
    }

    help += "  ";
    help += option.help();
    help += '\n';

    return help;
}

}

namespace arg {

std::string HelpFormatter::format(const std::vector<Option>& options) const {
    std::string help;
    auto appendOptionHelp = [&help](const Option& option) { help += formatOption(option); };
    std::for_each(options.begin(), options.end(), appendOptionHelp);
    return help;
}

}
