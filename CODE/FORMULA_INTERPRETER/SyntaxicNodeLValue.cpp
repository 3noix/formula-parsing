#include "SyntaxicNodeLValue.h"
#include "ExceptionInterpreter.h"


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  EVAL
//  TO STRING HELPER
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
SyntaxicNodeLValue::SyntaxicNodeLValue(const QString &varName, AbstractSyntaxicNode *parent) : AbstractSyntaxicNode{0,parent}
{
	m_varName = varName;
}

// EVAL ///////////////////////////////////////////////////////////////////////
Any SyntaxicNodeLValue::eval(const SimuData &sd) const
{
	if (!sd.hasParameter(m_varName))
	{
		QString msg = "Parameter \""+ m_varName + "\" is not in data";
		throw ExceptionInterpreter{msg};
	}
	
	return sd[m_varName];
}

// TO STRING HELPER ///////////////////////////////////////////////////////////
QString SyntaxicNodeLValue::toStringHelper(int offset) const
{
	return QString{2*offset,' '} + m_varName + "\n";
}

