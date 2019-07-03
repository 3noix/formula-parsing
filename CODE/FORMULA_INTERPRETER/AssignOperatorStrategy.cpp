#include "AssignOperatorStrategy.h"


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  ASSIGNMENT TO
//  HAS ERROR
//  ERROR MESSAGE
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
AssignOperatorStrategy::AssignOperatorStrategy()
{
	m_bError = false;
}

// ASSIGNMENT TO //////////////////////////////////////////////////////////////
QString AssignOperatorStrategy::assignmentTo(QVector<Token> &infixTokens)
{
	// not long enough for an assignment
	if (infixTokens.size() < 3)
	{
		m_bError = false;
		m_errorMessage = "";
		return {};
	}
	
	// check number of = operator(s) and its position(s)
	QList<int> eqPos;
	for (int i=0; i<infixTokens.size(); ++i)
	{
		const Token &t = infixTokens[i];
		if (t.type == TokenType::Operator && t.value == "=") {eqPos << i;}
	}
	
	// stop conditions
	if (eqPos.size() == 0) // no assignment => classical
	{
		m_bError = false;
		m_errorMessage = "";
		return {};
	}
	else if (eqPos.size() > 1) // several assignments => not supported
	{
		m_bError = true;
		m_errorMessage = "Only one assignment per formula is supported";
		return {};
	}
	else if (eqPos[0] != 1) // assignment not in the right place
	{
		m_bError = true;
		m_errorMessage = "Operator= must be the second token in the formula";
		return {};
	}
	
	// test the first token
	if (infixTokens[0].type != TokenType::LValue)
	{
		m_bError = true;
		m_errorMessage = "Operator= left operand must be a parameter name";
		return {};
	}
	
	QString paramName = infixTokens[0].value;
	infixTokens.removeFirst();
	infixTokens.removeFirst();
	m_bError = false;
	m_errorMessage = "";
	return paramName;
}

// HAS ERROR //////////////////////////////////////////////////////////////////
bool AssignOperatorStrategy::hasError() const
{
	return m_bError;
}

// ERROR MESSAGE //////////////////////////////////////////////////////////////
QString AssignOperatorStrategy::errorMessage() const
{
	return m_errorMessage;
}

