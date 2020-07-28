#include "arg/format.h"

#include "arg/option.h"

namespace arg {

std::string DefaultOptionHelpFormatter::operator()(const Option& option) const {
    std::string optionHelp{" "};

    if (option.hasSymbol()) {
        optionHelp += '-';
        optionHelp += option.symbol();
    } else {
        optionHelp += "  ";
    }

    optionHelp += " --";
    optionHelp += option.name();
    optionHelp += ' ';

    if (option.hasValue()) {
        optionHelp += '<';
        optionHelp += option.value();
        optionHelp += "> ";
    }

    optionHelp += "  ";
    optionHelp += option.help();
    optionHelp += '\n';

    return optionHelp;
}

}