#ifndef ARG_PARSE_H
#define ARG_PARSE_H

#include "options.h"

#include <utility>

namespace arg {

class ArgumentParser {
public:
    explicit ArgumentParser(Options options)
        : options_{std::move(options)} {}

    void parse(const int argc, const char** argv) const;

private:
    Options options_;
};

}

#endif //ARG_PARSE_H
