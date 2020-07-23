#include "catch2/catch.hpp"

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

using OptionAction = std::function<void(const std::string &value)>;

class Option {
public:
    Option(std::string name, char symbol, std::string help, std::string value, std::optional<OptionAction> action)
            : name_{std::move(name)},
              symbol_{symbol},
              help_{std::move(help)},
              value_{std::move(value)},
              action_{std::move(action)} {
    }

    [[nodiscard]]
    const std::string &name() const {
        return name_;
    }

    [[nodiscard]]
    bool hasSymbol() const {
        return symbol_ != 0;
    }

    [[nodiscard]]
    char symbol() const {
        return symbol_;
    }

    [[nodiscard]]
    bool hasValue() const {
        return !value_.empty();
    }

    [[nodiscard]]
    const std::string &value() const {
        return value_;
    }

    void action(const std::string &value) const {
        if (!action_.has_value()) {
            return;
        }
        auto action = action_.value();
        action(value);
    }

    [[nodiscard]]
    const std::string &help() const {
        return help_;
    }

private:
    const std::string name_;
    const char symbol_ = 0;
    const std::string value_;
    const std::optional<OptionAction> action_;
    const std::string help_;
};

class OptionBuilder {
public:
    OptionBuilder &name(const std::string &name) {
        name_ = name;
        return *this;
    }

    OptionBuilder &symbol(char symbol) {
        symbol_ = symbol;
        return *this;
    }

    OptionBuilder &value(std::string name, std::string &value) {
        value_ = std::move(name);
        action_ = [&value](const std::string &v) { value = v; };
        return *this;
    }

    OptionBuilder &enables(bool &value) {
        value_.clear();
        action_ = [&value](const std::string &v) { value = true; };
        return *this;
    }

    OptionBuilder &setAction(const std::optional<OptionAction> &action) {
        action_ = action;
        return *this;
    }

    OptionBuilder &setHelp(const std::string &help) {
        help_ = help;
        return *this;
    }

    OptionBuilder &setValue(std::string value) {
        value_ = std::move(value);
        return *this;
    }

    Option build() {
        assert(!name_.empty());
        assert(value_.empty() == action_.has_value());
        return Option(name_, symbol_, help_, value_, action_);
    }

private:
    std::string name_;
    char symbol_ = 0;
    std::string help_;
    std::string value_;
    std::optional<OptionAction> action_;
};

class ArgumentParser {
public:
    using BuildFunction = std::function<void(OptionBuilder &)>;

    ArgumentParser &addOption(const BuildFunction &buildOption) {
        OptionBuilder builder;
        buildOption(builder);
        auto option = builder.build();

        assert(names_.find(option.name()) == names_.cend());
        assert(symbols_.find(option.symbol()) == symbols_.cend());

        const auto index = options_.size();
        options_.emplace_back(std::make_unique<Option>(option));

        symbols_[option.symbol()] = index;
        names_[option.name()] = index;

        return *this;
    }

    void parse(int argc, const char **argv) const {
        // 0 is program filename
        for (int i = 1; i < argc; ++i) {
            const std::string name{argv[i]};
            std::optional<std::reference_wrapper<Option>> optionalOption;

            if (name.length() <= 1) {
                // TODO One char param
                continue;
            }

            if (name[0] != '-') {
                // TODO Incorrect option format
                continue;
            }

            if (name.length() == 2) {
                optionalOption = findOptionBySymbol(name[1]);
            }

            if (!optionalOption) {
                if (name[1] != '-') {
                    // TODO Incorrect long option format
                    continue;
                }
                optionalOption = findOptionByName(name.substr(2));
            }

            if (!optionalOption) {
                // TODO Option not found
                continue;
            }

            auto option = optionalOption.value().get();
            if (option.hasValue()) {
                if (i >= argc - 1) {
                    // TODO Missing option value
                    continue;
                }
                option.action(argv[++i]);
                continue;
            }

            option.action("");
        }
    }

    std::string help() {
        std::string help;
        auto formatOption = [this, &help] (const Option& option) { help += formatOptionHelp(option); };

        std::for_each(std::cbegin(options_), std::cend(options_), formatOption);

        return help;
    }

private:
    [[nodiscard]]
    std::optional<std::reference_wrapper<Option>> findOptionBySymbol(const char symbol) const {
        try {
            auto optionIndex = symbols_.at(symbol);
            return *options_.at(optionIndex);
        } catch (std::out_of_range &e) {
            return std::nullopt;
        }
    }

    [[nodiscard]]
    std::optional<std::reference_wrapper<Option>> findOptionByName(const std::string &name) const {
        try {
            auto optionIndex = names_.at(name);
            return *options_.at(optionIndex);
        } catch (std::out_of_range &e) {
            return std::nullopt;
        }
    }

    // TODO Add help formatter?
    std::string formatOptionHelp(const Option &option) {
        std::string help;

        help += ' ';

        if (option.hasSymbol()) {
            help += '-';
            help += option.symbol();
        }

        if (option.hasValue()) {
            help += " <";
            help += option.value();
            help += '>';
            help += ' ';
        } else {
            help += "\t\t";
        }

        help += option.help();
        help += '\n';

        return help;
    }

    std::vector<std::unique_ptr<Option>> options_;
    std::map<std::string, size_t> names_;
    std::map<char, size_t> symbols_;
};

TEST_CASE("Arguments are parsed", "[arguments]") {
    bool showHelp = false;
    bool listFiles = false;
    std::string inputFile;
    std::string port;

    ArgumentParser parser;

    parser.addOption([&showHelp](OptionBuilder &builder) {
        builder.name("help")
                .symbol('h')
                .name("Show help text")
                .enables(showHelp);
    });

    // TODO Consider changing to builder pattern.
//    parser.addOption("list", 'l')
//            .help("List files")
//            .enables(listFiles);
//
//    parser.addOption("input-file", 'i')
//            .help("Open file with given filename")
//            .value("filename", inputFile);
//
//    parser.addOption("port", 'p')
//            .help("Port number")
//            .value("port", port);

    std::cout << "Usage: curl [options...]" << '\n' << parser.help() << '\n';

    const size_t argc = 5;
    const char *argv[argc] = {"curl", "--help", "--list", "--port", "8080"};

    parser.parse(argc, argv);

    REQUIRE(showHelp);
    REQUIRE(listFiles);
    REQUIRE(inputFile.empty());
    REQUIRE(port == "8080");

    // TODO REQUIRE(parser.help() == "--help\tShow help text\n--list\tList
    // files\n");
}
