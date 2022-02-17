#include "Parser.h"

void test_lexer() {
	using namespace Lexer;
	Lexer::ClassLexer lexer;

	while (lexer.fetch_next_token().kind != Kind::end) {
		switch (lexer.get_current_token().kind) {
		case Kind::variable:
			std::cout << "Variable: " << lexer.get_current_token().name << std::endl;
			break;
		case Kind::number:
			std::cout << "Number: " << lexer.get_current_token().number << std::endl;
			break;
		default: 
			std::cout << "Operator: " << (char)lexer.get_current_token().kind << std::endl;
		}
	}
}

void test_parse() {
	Parser::ClassParser parser;
	parser.calculate();
}

int main() {
	//test_lexer();
	test_parse();
}