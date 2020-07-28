#ifndef ARG_FORMAT_H
#define ARG_FORMAT_H

#include "option.h"
#include "options.h"

#include <string>

namespace arg {

struct [[maybe_unused]] DefaultOptionHelpFormatter {
    std::string operator()(const Option& option) const;
};

template<typename TOptionHelpFormatter = DefaultOptionHelpFormatter>
class HelpFormatter {
public:
    std::string format(const Options& options) const {
        std::string help;
        auto formatOption = [this, &help](const Option& option) {
            help += optionHelpFormatter_(option);
        };
        std::for_each(options.begin(), options.end(), formatOption);
        return help;
    }

private:
    TOptionHelpFormatter optionHelpFormatter_;
};

}

#endif //ARG_FORMAT_H
