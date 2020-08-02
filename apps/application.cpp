#include "project/factorial.hpp"
#include <iostream>

using project::factorial;

int main(int argc, const char* argv[]) {
    const int value = 10;
    std::cout << "Factorial of " << value << " is " << factorial(value) << std::endl;
    return 0;
}
