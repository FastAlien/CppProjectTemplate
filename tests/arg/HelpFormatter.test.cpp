#include "arg/HelpFormatter.hpp"
#include "arg/Option.hpp"

#include "catch2/catch.hpp"

#include <string>
#include <vector>

using namespace arg;

SCENARIO("Formatting help for options", "[help]") {
  GIVEN("An instance of HelpFormatter") {
    const HelpFormatter helpFormatter;

    WHEN("Formatting help for one option with long name, without parameters") {
      bool helpEnabled = false;
      const std::vector<Option> options{
          {"help", "Display help", helpEnabled}};

      THEN("Help has correct format") {
        const auto expected = " --help   Display help\n";
        REQUIRE(helpFormatter.format(options) == expected);
      }
    }

    WHEN("Formatting help for one option with symbol and long name, without parameters") {
      bool helpEnabled = false;
      const std::vector<Option> options{
          {'h', "help", "Display help", helpEnabled}};

      THEN("Help has correct format") {
        const auto expected = " -h --help   Display help\n";
        REQUIRE(helpFormatter.format(options) == expected);
      }
    }

    WHEN("Formatting help for one option with symbol, with parameters") {
      std::string inputFilename;
      const std::vector<Option> options{
          {"input-file", "Load config from specified file", "filename", inputFilename}};

      THEN("Help has correct format") {
        const auto expected = " --input-file <filename>   Load config from specified file\n";
        REQUIRE(helpFormatter.format(options) == expected);
      }
    }

    WHEN("Formatting help for one option with symbol and long name, with parameters") {
      std::string inputFilename;
      const std::vector<Option> options{
          {'i', "input-file", "Load config from specified file", "filename", inputFilename}};

      THEN("Help has correct format") {
        const auto expected = " -i --input-file <filename>   Load config from specified file\n";
        REQUIRE(helpFormatter.format(options) == expected);
      }
    }

    WHEN("Formatting help for multiple options") {
      bool helpEnabled = false;
      std::string inputFilename;
      bool listFilesEnabled = false;
      const std::vector<Option> options{
          {'h', "help", "Display help", helpEnabled},
          {'i', "input-file", "Load config from specified file", "filename", inputFilename},
          {"list-files", "List all files", listFilesEnabled}};

      THEN("Help has correct format") {
        const auto expected = " -h --help   Display help\n"
                              " -i --input-file <filename>   Load config from specified file\n"
                              " --list-files   List all files\n";
        REQUIRE(helpFormatter.format(options) == expected);
      }
    }
  }
}