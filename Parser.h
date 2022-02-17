#pragma once
#include "Lexer.h"

namespace Parser {
	/*
		Recursive SDecent Parse Tree
		

		// root of decent parse tree
		calculator: 
			end // end of stream, or eof
			expr_list 0

		expr_list:
			expr ';' // print symbol
			expr_list expr ';' left recurtion

		expr:					
			term				(0)
			expr '+' term		(0)
			expr '-' term		(0)

		term:
			prim				(0)
			term '*' prim		(0)
			term '/'			(0)

		prim
			number				(0)
			variable			(0)
			variable '=' expr	(0)
			'-' prim			(0)
			'(' expr ')'		(0)
	*/
	using namespace Lexer;
	class ClassParser {
	private:
		ClassLexer m_lexer;
		variable_t m_variable;
	public:
		// handle addition and sustruction
		double expr(bool bNextToken);

		// handle multiply and division
		double term(bool bNextToken);

		// extract number from the stream token
		// assign to a variable
		// handle unary minus
		// handle parentasees
		double prim(bool bNextToken);

		void calculate();
	};
}
