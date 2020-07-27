#include "catch2/catch.hpp"
#include "project/arguments.h"

#include <cstddef>
#include <string>
#include <iostream>

using namespace project;

TEST_CASE("Arguments are parsed", "[arguments]") {
    bool showHelp = false;
    bool listFiles = false;
    std::string inputFile;
    std::string port;
    bool test = false;

    ArgumentParser parser{
        Option::build()
            .name("help")
            .symbol('h')
            .help("Show help text")
            .enables(showHelp),

        Option::build()
            .name("list")
            .symbol('l')
            .help("List files")
            .enables(listFiles),

        Option::build()
            .name("input-file")
            .symbol('i')
            .help("Read input from file")
            .value("filename", inputFile),

        Option::build()
            .name("port")
            .symbol('p')
            .help("Port number")
            .value("port", port)
    };

    parser.addOption(
        Option::build()
            .name("test")
            .help("Test option")
            .enables(test)
    );

    std::cout << "Usage: curl [options...]" << '\n' << parser.help() << '\n';

    const size_t argc = 5;
    const char* argv[argc] = {"curl", "--help", "--list", "--port", "8080"};

    parser.parse(argc, argv);

    REQUIRE(showHelp);
    REQUIRE(listFiles);
    REQUIRE(inputFile.empty());
    REQUIRE(port == "8080");
}
