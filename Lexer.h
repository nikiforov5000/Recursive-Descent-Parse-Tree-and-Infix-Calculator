#pragma once

#include <iostream>
#include <map>
#include <string>
#include <cctype>

namespace Lexer {
	using variable_t = std::map<std::string, double>;

	// Kind is for token type
	enum class Kind : char {
		end, print = ';', plus = '+', minus = '-',
		mul = '*', div = '/', assign = '=',
		p_open = '(', p_close = ')',
		number, variable
	};

	struct Token {
		Kind kind;
		std::string name;
		double number;
	};

	class ClassLexer {
	private:
		std::istream& m_stream;
		Token m_current_token;

	public:
		ClassLexer() : m_stream{ std::cin } {}
		Token& get_current_token();
		Token fetch_next_token();
		std::istream& get_next_char(char& chr);
	};

}
