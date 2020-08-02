#include "catch2/catch.hpp"

#include <cstddef>
#include <sstream>
#include <string>

namespace {

std::string createTestString() {
    std::string s;
    s += "Test data 1";
    s += "Test data 2";
    s += "Test data 3";
    return s;
}

void addToString(std::string& s) {
    s += "Test data 1";
    s += "Test data 2";
    s += "Test data 3";
}

} // namespace

TEST_CASE("std::string concatenation performance", "[string]") {
    const size_t iterations = 5000000;

    SECTION("string.operator+=()") {
        std::string s;
        for (size_t i = 0; i < iterations; ++i) {
            s += "Test data 1";
            s += "Test data 2";
            s += "Test data 3";
        }
    }

    SECTION("return string from function") {
        std::string s;
        for (size_t i = 0; i < iterations; ++i) {
            s += createTestString();
        }
    }

    SECTION("add to string in function") {
        std::string s;
        for (size_t i = 0; i < iterations; ++i) {
            addToString(s);
        }
    }

    SECTION("string.append()") {
        std::string s;
        for (size_t i = 0; i < iterations; ++i) {
            s.append("Test data 1");
            s.append("Test data 2");
            s.append("Test data 3");
        }
    }

    SECTION("stringstream") {
        std::stringstream ss;
        for (size_t i = 0; i < iterations; ++i) {
            ss << "Test data 1";
            ss << "Test data 2";
            ss << "Test data 3";
        }
        std::string s = ss.str();
    }
}
