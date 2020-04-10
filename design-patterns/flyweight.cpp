/*
 * flyweight.cpp
 *
 *  Created on: Apr 10, 2020
 *      Author: KZ
 */

#include "../unit-testing/catch.hpp"

#include <string>
#include <vector>
#include <ostream>
#include <sstream>

struct TextRange {
	std::size_t start;
	std::size_t end;
	bool is_capital = false;
	//bool is_italic = false;
	int font_size = 12;

	TextRange(std::size_t start, std::size_t end, bool is_capital = false,
			int font_size = 12) :
			start { start }, end { end }, is_capital { is_capital }, font_size {
					font_size } {
	}

	bool contains(std::size_t index) const {
		return (index >= start) && (index < end);
	}

};

class FormattedText {
private:
	std::string unformatted_text;
	std::vector<TextRange> format_ranges;
	void add_range(std::size_t start, std::size_t end, bool is_capital = false,
			int font_size = 12) {
		format_ranges.emplace_back(start, end, is_capital, font_size);
	}

	bool check_capital(std::size_t i, bool& is_capital,
			std::string& result) const {
		bool capital_found = false;
		for (const auto& range : format_ranges) {
			if (range.is_capital && range.contains(i)) {
				if (is_capital) {
					capital_found = true;
					continue;
				}
				is_capital = true;
				capital_found = true;
				result += "<span style='text-transform:uppercase;'>";
				break;
			}
		}
		if (!capital_found && is_capital) {
			is_capital = false;
			result += "</span>";
		}
		return capital_found;
	}

public:
	FormattedText(std::string text) :
			unformatted_text { text } {
	}
	void capitalize(std::size_t start, std::size_t end) {
		add_range(start, end, true);
	}
	void set_font_size(std::size_t start, std::size_t end, int font_size) {
		add_range(start, end, false, font_size);
	}
	friend std::ostream& operator<<(std::ostream& out,
			const FormattedText & text) {
		std::string result;
		for (std::size_t i = 0; i < text.unformatted_text.length(); i++) {
			auto symbol = text.unformatted_text[i];
			for (const auto& range : text.format_ranges) {
				if (range.is_capital && range.contains(i)) {
					symbol = std::toupper(symbol);
					break;
				}
			}
			result += symbol;
		}
		out << result;
		return out;
	}
	std::string generate_html() const {
		std::string result;
		bool is_capital = false;
		int current_font_size = 12;
		for (std::size_t i = 0; i < unformatted_text.length(); i++) {
			auto symbol = unformatted_text[i];

			bool capital_found = check_capital(i, is_capital, result);
			result += symbol;
		}
		if (is_capital) {
			result += "</span>";
		}
		return result;
	}

};

TEST_CASE("capitalizing ranges of text", "[patterns]") {
	FormattedText text { "hello world!" };

	text.capitalize(6, 12);
	std::stringstream out;
	out << text;
	REQUIRE(out.str() == "hello WORLD!");
	REQUIRE(text.generate_html() ==
			"hello <span style='text-transform:uppercase;'>world!</span>");

	text.capitalize(7,9);
	REQUIRE(text.generate_html() ==
				"hello <span style='text-transform:uppercase;'>world!</span>");

	SECTION("two disjoint ranges") {
	text.capitalize(2,4);
	REQUIRE(text.generate_html() ==
				"he<span style='text-transform:uppercase;'>ll</span>o <span style='text-transform:uppercase;'>world!</span>");
	}

	SECTION("two intersecting ranges") {
	text.capitalize(3,8);
	REQUIRE(text.generate_html() ==
				"hel<span style='text-transform:uppercase;'>lo world!</span>");
	}

}

