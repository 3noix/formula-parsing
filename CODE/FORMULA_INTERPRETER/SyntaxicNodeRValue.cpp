#include "SyntaxicNodeRValue.h"
#include "ExceptionInterpreter.h"
#include "../stringVerifications.h"


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  CONSTRUCTEUR
//  EVAL
//  TO STRING HELPER
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
SyntaxicNodeRValue::SyntaxicNodeRValue(const QString &rValueStr, AbstractSyntaxicNode *parent) : AbstractSyntaxicNode{0,parent}
{
	bool bok = false;
	
	// try bool
	m_rValue = convertFromString<bool>(rValueStr,&bok);
	if (bok) {return;}
	
	// try double
	m_rValue = convertFromString<double>(rValueStr,&bok);
	if (bok) {return;}
	
	// try int
	m_rValue = convertFromString<int>(rValueStr,&bok);
	if (bok) {return;}
	
	// otherwise
	QString errorMessage = "Unknown or not supported type for value: " + rValueStr;
	throw ExceptionInterpreter{errorMessage};
}

// EVAL ///////////////////////////////////////////////////////////////////////
Any SyntaxicNodeRValue::eval(const SimuData &sd) const
{
	Q_UNUSED(sd)
	return m_rValue;
}

// TO STRING HELPER ///////////////////////////////////////////////////////////
QString SyntaxicNodeRValue::toStringHelper(int offset) const
{
	return QString{2*offset,' '} + ::toString(m_rValue) + "\n";
}

