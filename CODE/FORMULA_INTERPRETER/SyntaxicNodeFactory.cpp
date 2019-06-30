#include "SyntaxicNodeFactory.h"

#include "SyntaxicNodeLValue.h"
#include "SyntaxicNodeRValue.h"
#include "SyntaxicNodeUnaryOperator.h"
#include "SyntaxicNodeBinaryOperator.h"

#include "../DATA_AND_OPERATORS/AnyOperators.h"
#include "../DATA_AND_OPERATORS/AnyFunctions.h"


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CREATE NODE
//  CREATE FUNCTION
//  CREATE OPERATOR
///////////////////////////////////////////////////////////////////////////////


// CREATE NODE ////////////////////////////////////////////////////////////////
AbstractSyntaxicNode* SyntaxicNodeFactory::createNode(const Token &t, AbstractSyntaxicNode *parent)
{
	if (t.type == TokenType::LValue)
	{
		return new SyntaxicNodeLValue{t.value,parent};
	}
	else if (t.type == TokenType::RValue)
	{
		return new SyntaxicNodeRValue{t.value,parent};
	}
	else if (t.type == TokenType::Function)
	{
		return this->createFunction(t.value,parent);
	}
	else if (t.type == TokenType::Operator)
	{
		return this->createOperator(t.value,parent);
	}
	
	return nullptr;
}

// CREATE FUNCTION ////////////////////////////////////////////////////////////
AbstractSyntaxicNode* SyntaxicNodeFactory::createFunction(const QString &fctName, AbstractSyntaxicNode *parent)
{
	if (fctName == "abs")
	{
		//UnaryOperator uo = [](const Any& a){return abs(a);};
		//return new SyntaxicNodeUnaryOperator{uo,parent};
	}
	else if (fctName == "pow")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return pow(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (fctName == "sqrt")
	{
		//UnaryOperator uo = [](const Any& a){return sqrt(a);};
		//return new SyntaxicNodeUnaryOperator{uo,parent};
	}
	else if (fctName == "exp")
	{
		//UnaryOperator uo = [](const Any& a){return exp(a);};
		//return new SyntaxicNodeUnaryOperator{uo,parent};
	}
	else if (fctName == "log")
	{
		//UnaryOperator uo = [](const Any& a){return log(a);};
		//return new SyntaxicNodeUnaryOperator{uo,parent};
	}
	else if (fctName == "log10")
	{
		//UnaryOperator uo = [](const Any& a){return log10(a);};
		//return new SyntaxicNodeUnaryOperator{uo,parent};
	}
	else if (fctName == "cos")
	{
		UnaryOperator uo = [](const Any& a){return cos(a);};
		return new SyntaxicNodeUnaryOperator{uo,parent};
	}
	else if (fctName == "sin")
	{
		//UnaryOperator uo = [](const Any& a){return sin(a);};
		//return new SyntaxicNodeUnaryOperator{uo,parent};
	}
	else if (fctName == "tan")
	{
		//UnaryOperator uo = [](const Any& a){return tan(a);};
		//return new SyntaxicNodeUnaryOperator{uo,parent};
	}
	else if (fctName == "tan2")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return tan2(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (fctName == "acos")
	{
		//UnaryOperator uo = [](const Any& a){return acos(a);};
		//return new SyntaxicNodeUnaryOperator{uo,parent};
	}
	else if (fctName == "asin")
	{
		//UnaryOperator uo = [](const Any& a){return asin(a);};
		//return new SyntaxicNodeUnaryOperator{uo,parent};
	}
	else if (fctName == "atan")
	{
		//UnaryOperator uo = [](const Any& a){return atan(a);};
		//return new SyntaxicNodeUnaryOperator{uo,parent};
	}
	else if (fctName == "atan2")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return atan2(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	
	return nullptr;
}

// CREATE OPERATOR ////////////////////////////////////////////////////////////
AbstractSyntaxicNode* SyntaxicNodeFactory::createOperator(const QString &op, AbstractSyntaxicNode *parent)
{
	if (op == "+")
	{
		BinaryOperator bo = [](const Any& a1, const Any& a2){return operator+(a1,a2);};
		return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "-")
	{
		BinaryOperator bo = [](const Any& a1, const Any& a2){return operator-(a1,a2);};
		return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "*")
	{
		BinaryOperator bo = [](const Any& a1, const Any& a2){return operator*(a1,a2);};
		return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "/")
	{
		BinaryOperator bo = [](const Any& a1, const Any& a2){return operator/(a1,a2);};
		return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "**")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return pow(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "^")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator^(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "<")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator<(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "<=")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator<=(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == ">")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator>(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == ">=")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator>=(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "==")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator==(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "!=")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator!=(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "!")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator!(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "%")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator%(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "&")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator&(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "&&")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator&&(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "|")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator|(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "||")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator||(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "~")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator~(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == "<<")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator<<(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	else if (op == ">>")
	{
		//BinaryOperator bo = [](const Any& a1, const Any& a2){return operator>>(a1,a2);};
		//return new SyntaxicNodeBinaryOperator{bo,parent};
	}
	
	return nullptr;
}

