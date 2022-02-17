#include "Lexer.h"
namespace Lexer {

	// to eat any blank space
	std::istream& ClassLexer::get_next_char(char& chr) {
		while (this->m_stream.get(chr) &&
			(std::isblank(chr) || chr == '\n')) {
			std::cout << "whitespace\n";
			return this->m_stream;
		}
	}

	Token& ClassLexer::get_current_token() {
		return m_current_token;
	}

	Token ClassLexer::fetch_next_token() {
		// lac  look ahead char
		char lac = 0;

		// read in char from stream
		this->get_next_char(lac);

		switch (lac) {
			case 0: // eof , stream
				this->m_current_token = { Kind::end };
				return this->m_current_token;

			case ';': case '+': case '-': case '*': 
			case '/': case '=': case '(': case ')':
				this->m_current_token = { static_cast<Kind>(lac) };
				return this->m_current_token;

			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9': case '.': 
			{
				// put back lac to the stream
				this->m_stream.putback(lac);

				this->m_stream >> this->m_current_token.number;

				this->m_current_token.kind = Kind::number;

				return this->m_current_token;
			}
			
			default: {
				if (std::isalpha(lac)) {
					this->m_current_token.name = lac;

					while (this->m_stream.get(lac) && std::isalnum(lac)) {
						this->m_current_token.name += lac;
					}
					// at this point lac is neither a alphabet not a num
					// so we have to pushback lac
					this->m_stream.putback(lac);

					this->m_current_token.kind = Kind::variable;

					return this->m_current_token;
				}
				else {
					// std::cerr << "Syntax Error " << std::endl;
					this->m_current_token = { Kind::print };
					return this->m_current_token;
				}
			}
		} // end of switch
	} // end of fetch_next_token
	
}