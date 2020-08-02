#include "arg/ArgumentParser.hpp"
#include "arg/ParseError.hpp"
#include "catch2/catch.hpp"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

using namespace arg;

SCENARIO("Parsing arguments", "[parse]") {
  GIVEN("An argument parser with options") {
    bool helpEnabled = false;
    bool listFilesEnabled = false;
    std::string inputFilename;
    std::string port;

    const ArgumentParser argumentParser{
        {'h', "help", "Show help text", helpEnabled},
        {'l', "list", "List all files", listFilesEnabled},
        {'i', "input-file", "Read input from file", "filename", inputFilename},
        {'p', "port", "Port number", "port", port}};

    WHEN("Argument with unknown long name is parsed") {
      const size_t argc = 2;
      const char* argv[argc] = {"program", "--helpo"};
      auto errors = argumentParser.parse(argc, argv);

      THEN("Return value contains unknown argument error") {
        REQUIRE(errors.size() == 1);
        REQUIRE(errors[0].getArgument() == "--helpo");
        REQUIRE(errors[0].getType() == ParseError::Type::UnknownArgument);
      }

      THEN("Bound values didn't changed") {
        REQUIRE(!helpEnabled);
        REQUIRE(!listFilesEnabled);
        REQUIRE(inputFilename.empty());
        REQUIRE(port.empty());
      }
    }

    WHEN("Argument with unknown symbol is parsed") {
      const size_t argc = 2;
      const char* argv[argc] = {"program", "-z"};
      auto errors = argumentParser.parse(argc, argv);

      THEN("Return value contains unknown argument error") {
        REQUIRE(errors.size() == 1);
        REQUIRE(errors[0].getArgument() == "-z");
        REQUIRE(errors[0].getType() == ParseError::Type::UnknownArgument);
      }

      THEN("Bound values didn't changed") {
        REQUIRE(!helpEnabled);
        REQUIRE(!listFilesEnabled);
        REQUIRE(inputFilename.empty());
        REQUIRE(port.empty());
      }
    }

    WHEN("Valid arguments are parsed") {
      const size_t argc = 5;
      const char* argv[argc] = {"program", "--help", "--list", "--port", "8080"};
      auto errors = argumentParser.parse(argc, argv);

      THEN("Return value is empty") {
        REQUIRE(errors.empty());
      }

      THEN("Bound values has changed") {
        REQUIRE(helpEnabled);
        REQUIRE(listFilesEnabled);
        REQUIRE(inputFilename.empty());
        REQUIRE(port == "8080");
      }
    }
  }
}
