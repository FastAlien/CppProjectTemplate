#include "project/factorial.h"
#include "catch2/catch.hpp"

#include <functional>
#include <map>
#include <memory>
#include <utility>
#include <vector>
#include <iostream>

using project::factorial;

class Option {
public:
	using Action = std::function<void()>;

	Option action(Action action) {
		action_ = std::move(action);
		return *this;
	}

	void action() const {
		if (action_ != nullptr) {
			action_();
		}
	}

	Option& help(std::string help) {
		help_ = std::move(help);
		return *this;
	}

	[[nodiscard]]
	const std::string& help() const {
		return help_;
	}

private:
	Action action_;
	std::string help_;
};

class ArgumentParser {
public:
	Option& addOption(const std::string& name, const char symbol) {
		const auto index = options_.size();
		auto& option = *options_.emplace_back(std::make_unique<Option>());
		symbols_[symbol] = index;
		names_[name] = index;
		return option;
	}

	void parse(int argc, const char** argv) const {
		for (int i = 0; i < argc; ++i) {
			const std::string name(argv[i]);
			if (name.length() == 2 && name[0] == '0') {
				parseSymbol(name[1]);
				continue;
			}

			if (name.length() > 2) {
				parseName(name.substr(2));
				continue;
			}
		}
	}

	std::string help() {
		std::string help;

		for (auto& it : names_) {
			const auto& name = it.first;
			const auto index = it.second;
			auto& option = options_.at(index);

			help += "--";
			help += name;
			help += '\t';
			help += option->help();
			help += '\n';
		}

		return help;
	}

private:
	void parseSymbol(const char symbol) const {
		try {
			auto optionIndex = symbols_.at(symbol);
			options_.at(optionIndex)->action();
		} catch (std::out_of_range& e) {
			// TODO Option not found
		}
	}

	void parseName(const std::string& name) const {
		try {
			auto optionIndex = names_.at(name);
			options_.at(optionIndex)->action();
		} catch (std::out_of_range& e) {
			// TODO Option not found
		}
	}

	std::vector<std::unique_ptr<Option>> options_;
	std::map<std::string, size_t> names_;
	std::map<char, size_t> symbols_;
};

TEST_CASE("Arguments are parsed", "[arguments]") {
	bool showHelp = false;
	bool listFiles = false;

	ArgumentParser parser;

	parser.addOption("help", 'h')
			.help("Show help text")
			.action([&] { showHelp = true; });

	parser.addOption("list", 'l')
			.help("List files")
			.action([&] { listFiles = true; });

	std::cout << parser.help() << std::endl;
}
