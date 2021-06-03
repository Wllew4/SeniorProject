#include "ast/lexing/Token.h"

#include <iomanip>
#include <sstream>
#include <string.h>

std::string Token::ToString()
{
	constexpr const char* tokenTypes[] = {
		"StrDecl",	    "NumDecl",
		"StrLit",       "NumLit",
		"ID",           "Print",
		"Println",      "EQ",
		"Plus",         "Minus",
		"Mult",         "Div",
		"Modulus",      "If",
		"Else",         "While",
		"LThan",        "GThan",
		"OpBrace",      "ClBrace",
		"Semicolon",    "EOF"
	};

	std::stringstream outStringStream;
	outStringStream << "TOKEN:\tType: "
		<< tokenTypes[type]
		<< std::setw(20 - strlen(tokenTypes[type]))
		<< "Value: " << value;

	std::string out = outStringStream.str();

	return out;
}