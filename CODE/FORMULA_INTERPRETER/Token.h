#ifndef TOKEN
#define TOKEN


#include <QString>


enum class TokenType
{
	Unknown,
	RValue, // number or Boolean
	LValue, // variable name
	Function,
	Operator,
	LeftParenthesis,
	RightParenthesis,
	ArgumentSeparator
};


struct Token
{
	QString value;
	TokenType type;
};


#endif

