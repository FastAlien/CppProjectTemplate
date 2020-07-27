#ifndef PROJECT_ARGUMENTS_H
#define PROJECT_ARGUMENTS_H

#include <algorithm>
#include <cassert>
#include <functional>
#include <initializer_list>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace project {

class OptionBuilder;

class Option {
public:
    using Action = std::function<void(const std::string& value)>;

    static OptionBuilder build();

    [[nodiscard]]
    const std::string& name() const {
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
    const std::string& value() const {
        return value_;
    }

    void action(const std::string& value) const {
        if (!action_.has_value()) {
            return;
        }

        auto action = action_.value();
        action(value);
    }

    [[nodiscard]] const std::string& help() const {
        return help_;
    }

private:
    friend class OptionBuilder;

    Option(std::string name, char symbol, std::string help, std::string value,
           std::optional<Action> action)
        : symbol_{symbol}, name_{std::move(name)}, value_{std::move(value)},
          action_{std::move(action)}, help_{std::move(help)} {}

    const char symbol_;
    const std::string name_;
    const std::string value_;
    const std::optional<Action> action_;
    const std::string help_;
};

class OptionBuilder {
public:
    OptionBuilder() = default;

    explicit OptionBuilder(const OptionBuilder&) = delete;

    OptionBuilder operator=(const OptionBuilder&) = delete;

    OptionBuilder& name(const std::string& name) {
        name_ = name;
        return *this;
    }

    OptionBuilder& symbol(char symbol) {
        symbol_ = symbol;
        return *this;
    }

    OptionBuilder& help(const std::string& help) {
        help_ = help;
        return *this;
    }

    OptionBuilder& value(std::string name, std::string& value) {
        value_ = std::move(name);
        action_ = [&value](const std::string& v) {
            value = v;
        };
        return *this;
    }

    OptionBuilder& enables(bool& value) {
        value_.clear();
        action_ = [&value](const std::string& v) {
            value = true;
        };
        return *this;
    }

    operator Option() {
        assert(!name_.empty());
        assert(action_.has_value());
        return Option(name_, symbol_, help_, value_, action_);
    }

private:
    char symbol_ = 0;
    std::string name_;
    std::string help_;
    std::string value_;
    std::optional<Option::Action> action_;
};

OptionBuilder Option::build() {
    return {};
}

class ArgumentParser {
public:
    explicit ArgumentParser(std::initializer_list<Option> options)
        : options_{options} {}

    void addOption(Option option) {
        options_.emplace_back(option);
    }

    void parse(const int argc, const char** argv) const {
        // argv[0] is program filename
        for (int i = 1; i < argc; ++i) {
            const std::string name{argv[i]};

            if (name.length() <= 1) {
                // TODO One char param
                continue;
            }

            if (name[0] != '-') {
                // TODO Incorrect option format
                continue;
            }

            if (name.length() == 2) {
                const char symbol = name[1];
                auto optionalOption = findOptionBySymbol(symbol);

                if (!optionalOption) {
                    // TODO Option not found
                    continue;
                }

                if (!optionalOption->hasValue()) {
                    optionalOption->action("");
                    continue;
                }

                if (i >= argc - 1) {
                    // TODO Missing option value
                    continue;
                }

                optionalOption->action(argv[++i]);
                continue;
            }

            if (name[1] != '-') {
                // TODO Incorrect long option format
                continue;
            }

            auto optionalOption = findOptionByName(name.substr(2));

            if (!optionalOption) {
                // TODO Option not found
                continue;
            }

            if (!optionalOption->hasValue()) {
                optionalOption->action("");
                continue;
            }

            if (i >= argc - 1) {
                // TODO Missing option value
                continue;
            }

            optionalOption->action(argv[++i]);
        }
    }

    std::string help() const {
        std::string help;
        auto formatOption = [this, &help](const Option& option) {
            help += formatOptionHelp(option);
        };
        std::for_each(options_.begin(), options_.end(), formatOption);

        return help;
    }

private:
    using FindOptionPredicate = std::function<bool(const Option&)>;

    [[nodiscard]]
    std::optional<Option> findOptionBySymbol(const char symbol) const {
        auto symbolEquals = [symbol](const Option& option) {
            return option.hasSymbol() && option.symbol() == symbol;
        };
        return findOption(symbolEquals);
    }

    [[nodiscard]]
    std::optional<Option> findOptionByName(const std::string& name) const {
        auto nameEquals = [&name](const Option& option) {
            return option.name() == name;
        };
        return findOption(nameEquals);
    }

    [[nodiscard]]
    std::optional<Option> findOption(const FindOptionPredicate& predicate) const {
        auto it = std::find_if(options_.begin(), options_.end(), predicate);

        if (it == options_.end()) {
            return std::nullopt;
        }

        return *it;
    }

    // TODO Add help formatting class?
    std::string formatOptionHelp(const Option& option) const {
        std::string optionHelp{" "};

        if (option.hasSymbol()) {
            optionHelp += '-';
            optionHelp += option.symbol();
        } else {
            optionHelp += "  ";
        }

        optionHelp += " --";
        optionHelp += option.name();
        optionHelp += ' ';

        if (option.hasValue()) {
            optionHelp += '<';
            optionHelp += option.value();
            optionHelp += "> ";
        }

        optionHelp += "  ";
        optionHelp += option.help();
        optionHelp += '\n';

        return optionHelp;
    }

    std::vector<Option> options_;
};

}

#endif //PROJECT_ARGUMENTS_H
