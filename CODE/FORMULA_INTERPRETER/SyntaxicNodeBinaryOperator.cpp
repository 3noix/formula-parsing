#include "SyntaxicNodeBinaryOperator.h"
#include "../ExceptionInterpreter.h"


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  EVAL
//  TO STRING HELPER
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
SyntaxicNodeBinaryOperator::SyntaxicNodeBinaryOperator(const BinaryOperator &bo, AbstractSyntaxicNode *parent) :
	AbstractSyntaxicNode{2,parent}
{
	m_bo = bo;
}

// EVAL ///////////////////////////////////////////////////////////////////////
Any SyntaxicNodeBinaryOperator::eval(SimuData *sd) const
{
	if (m_children.size() == 0)
	{
		QString msg = "Binary operator: no operand set";
		throw ExceptionInterpreter{msg};
	}
	else if (m_children.size() == 1)
	{
		QString msg = "Binary operator: only one operand set";
		throw ExceptionInterpreter{msg};
	}
	
	return m_bo(m_children[1]->eval(sd),m_children[0]->eval(sd));
}

// TO STRING HELPER ///////////////////////////////////////////////////////////
QString SyntaxicNodeBinaryOperator::toStringHelper(int offset) const
{
	QString str = QString{2*offset,' '} + "BO\n";
	if (m_children.size() == 2) {str += m_children[1]->toStringHelper(offset+1);}
	if (m_children.size() >= 1) {str += m_children[0]->toStringHelper(offset+1);}
	return str;
}

