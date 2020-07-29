#ifndef ARG_FORMAT_H
#define ARG_FORMAT_H

#include <string>
#include <vector>

namespace arg {

class Option;

class HelpFormatter {
public:
    HelpFormatter() = default;

    [[nodiscard]]
    std::string format(const std::vector<Option>& options) const;
};

}

#endif //ARG_FORMAT_H
