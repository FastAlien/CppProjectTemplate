#include "project/factorial.h"

namespace project {

int factorial(int number) {
    return number <= 1 ? number : factorial(number - 1) * number;
}

} // namespace project
