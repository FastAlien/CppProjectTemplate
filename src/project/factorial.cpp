#include "project/factorial.hpp"

namespace project {

int factorial(int number) {
    return number <= 1 ? number : factorial(number - 1) * number;
}

} // namespace project
