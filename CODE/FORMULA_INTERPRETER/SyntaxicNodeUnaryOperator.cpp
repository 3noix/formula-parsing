#include "SyntaxicNodeUnaryOperator.h"
#include "../ExceptionInterpreter.h"


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  EVAL
//  TO STRING HELPER
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ET DESTRUCTEUR ////////////////////////////////////////////////
SyntaxicNodeUnaryOperator::SyntaxicNodeUnaryOperator(const UnaryOperator &uo, AbstractSyntaxicNode *parent) :
	AbstractSyntaxicNode{1,parent}
{
	m_uo = uo;
}

// EVAL ///////////////////////////////////////////////////////////////////////
Any SyntaxicNodeUnaryOperator::eval(SimuData *sd) const
{
	if (m_children.size() != 1)
	{
		QString msg = "Unary operator: operand not set";
		throw ExceptionInterpreter{msg};
	}
	
	return m_uo(m_children[0]->eval(sd));
}

// TO STRING HELPER ///////////////////////////////////////////////////////////
QString SyntaxicNodeUnaryOperator::toStringHelper(int offset) const
{
	QString str = QString{2*offset,' '} + "UO\n";
	if (m_children.size() == 1) {str += m_children[0]->toStringHelper(offset+1);}
	return str;
}

