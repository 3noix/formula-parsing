#include "AnyFunctions.h"
#include "ExceptionAnyOperator.h"
#include <math.h>


///////////////////////////////////////////////////////////////////////////////
//  COS
///////////////////////////////////////////////////////////////////////////////


// COS ////////////////////////////////////////////////////////////////////////
Any cos(const Any &a)
{
	if (isa<double>(a))
	{
		return cos(convertTo<double>(a));
	}
	else if (isa<int>(a))
	{
		double d = convertTo<int>(a);
		return cos(d);
	}
	
	QString message = "cos(const Any&) : type not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}

