#include "arg/parse.h"
#include "arg/format.h"
#include "arg/option.h"
#include "arg/options.h"

#include "catch2/catch.hpp"

#include <cstddef>
#include <string>
#include <iostream>

using namespace arg;

TEST_CASE("Arguments are parsed", "[arguments]") {
    bool showHelp = false;
    bool listFiles = false;
    std::string inputFile;
    std::string port;
    bool test = false;

    Options options{
        {"help", 'h', "Show help text", showHelp},
        {"list", 'l', "List all files", listFiles},
        {"input-file", 'i', "Read input from file", "filename", inputFile},
        {"port", 'p', "Port number", "port", port}
    };

    options.addOption({"test", 't', "Test option", test});

    const HelpFormatter helpFormatter;
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
