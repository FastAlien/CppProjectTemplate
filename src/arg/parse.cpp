#include "arg/parse.h"

#include "arg/option.h"
#include "arg/options.h"

#include <optional>
#include <string>

namespace arg {

void ArgumentParser::parse(const int argc, const char** argv) const {
    // argv[0] is program filename
    for (int i = 1; i < argc; ++i) {
        const std::string name{argv[i]};

        if (name.length() <= 1) {
            // TODO One char param
            continue;
        }

        if (name[0] != '-') {
            // TODO Incorrect option format
            continue;
        }

        if (name.length() == 2) {
            const char symbol = name[1];
            auto optionalOption = options_.findBySymbol(symbol);

            if (!optionalOption) {
                // TODO Option not found
                continue;
            }

            if (!optionalOption->hasValue()) {
                optionalOption->action("");
                continue;
            }

            if (i >= argc - 1) {
                // TODO Missing option value
                continue;
            }

            optionalOption->action(argv[++i]);
            continue;
        }

        if (name[1] != '-') {
            // TODO Incorrect long option format
            continue;
        }

        auto optionalOption = options_.findByName(name.substr(2));

        if (!optionalOption) {
            // TODO Option not found
            continue;
        }

        if (!optionalOption->hasValue()) {
            optionalOption->action("");
            continue;
        }

        if (i >= argc - 1) {
            // TODO Missing option value
            continue;
        }

        optionalOption->action(argv[++i]);
    }
}

}