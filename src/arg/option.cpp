#include "arg/option.h"

#include <utility>

namespace arg {

Option::Option(const char symbol, const std::string name, const std::string help, const std::string value, const std::optional<Action> action)
    : symbol_{symbol},
      name_{std::move(name)},
      help_{std::move(help)},
      value_{std::move(value)},
      action_{std::move(action)} {}

}
