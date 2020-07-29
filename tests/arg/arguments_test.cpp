#include "arg/format.h"
#include "arg/option.h"
#include "arg/parse.h"

#include "catch2/catch.hpp"

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using namespace arg;

TEST_CASE("Arguments are parsed", "[arguments]") {
    bool showHelp = false;
    bool listFiles = false;
    std::string inputFile;
    std::string port;
    bool test = false;

    std::vector<Option> options{
        {'h', "help", "Show help text", showHelp},
        {'l', "list", "List all files", listFiles},
        {'i', "input-file", "Read input from file", "filename", inputFile},
        {'p', "port", "Port number", "port", port}
    };

    options.emplace_back("test", "Test option", test);

    const HelpFormatter helpFormatter{};
    std::cout << "Usage: curl [options...]" << '\n' << helpFormatter.format(options) << '\n';

    const size_t argc = 5;
    const char* argv[argc] = {"curl", "--help", "--list", "--port", "8080"};

    ArgumentParser parser{options};

    parser.parse(argc, argv);

    REQUIRE(showHelp);
    REQUIRE(listFiles);
    REQUIRE(inputFile.empty());
    REQUIRE(port == "8080");
}
