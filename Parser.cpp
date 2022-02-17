#include "Parser.h"

namespace Parser {
	using namespace Lexer;

	double ClassParser::prim(bool bNextToken) {
		if (bNextToken) {
			this->m_lexer.fetch_next_token();
		}
		switch (this->m_lexer.get_current_token().kind) {
			case Kind::number:
			{
				double v = this->m_lexer.get_current_token().number;
				// fetch next token for further processing
				this->m_lexer.fetch_next_token();

				return v;
			}

			case Kind::variable:
			{
				double& v = this->m_variable[this->m_lexer.get_current_token().name];
				if (this->m_lexer.fetch_next_token().kind == Kind::assign) {
					v = this->expr(true);
				}
				return v;
			}

			case Kind::minus:
				return this->prim(true);

			case Kind::p_open:
			{
				double v = this->expr(true);
				if (this->m_lexer.get_current_token().kind != Kind::p_close) {
					std::cerr << " Syntax Error:\')\' is expected " << std::endl;
				}
				// eat up closing parenthesis )
				this->m_lexer.fetch_next_token();

				return v;
			}
			default: {
				std::cerr << "Syntax Error /parser/prim/switch" << std::endl;
				return 0;
			}
		}// end of switch statemant
	} // end of function prime
	double ClassParser::term(bool bNextToken) {
		double left = prim(bNextToken);

		switch (this->m_lexer.get_current_token().kind) {
			case Kind::mul:
				left *= this->prim(true); return left;

			case Kind::div:
				left /= this->prim(true); return left;

			default:
				return left;
		}
	}
	double ClassParser::expr(bool bNextToken) {
		double left = this->term(bNextToken);

		switch (this->m_lexer.get_current_token().kind) {
			case Kind::plus:
				left += this->term(true); return left;

			case Kind::minus:
				left -= this->term(true); return left;

			default: 
				return left;
		}
	}
	void ClassParser::calculate() {
		for (this->m_lexer.fetch_next_token();
			this->m_lexer.get_current_token().kind != Kind::end;
			this->m_lexer.fetch_next_token()) 
		{
			std::cout << this->expr(false) << std::endl;
		}
	}


}