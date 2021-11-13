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
	ArgumentSeparator,
	LValueOrFunction // useful temporarily in first steps
};


struct Token
{
	QString value;
	TokenType type;
};


#endif

