#include "catch2/catch.hpp"

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>

namespace {

class Benchmark {
public:
  explicit Benchmark(const char* name)
      : name_{name},
        startTime_{clock::now()} {}

  ~Benchmark() {
    using namespace std::chrono;
    const auto elapsedMs = duration<float, std::milli>(clock::now() - startTime_);
    std::cout << "Test " << name_ << " elapsed time: " << elapsedMs.count() << "ms\n";
  }

private:
  using clock = std::chrono::high_resolution_clock;
  using time_point = std::chrono::time_point<clock>;

  const char* name_;
  const time_point startTime_;
};

std::string createTestString() {
  std::string s;
  s += "Test data 1";
  s += "Test data 2";
  s += "Test data 3";
  return s;
}

void appendToString(std::string& s) {
  s += "Test data 1";
  s += "Test data 2";
  s += "Test data 3";
}

}

TEST_CASE("std::string concatenation performance", "[.] [string]") {
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

  SECTION("append to string in function") {
    std::string s;
    for (size_t i = 0; i < iterations; ++i) {
      appendToString(s);
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