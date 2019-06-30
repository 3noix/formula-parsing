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
/*
Any cos(const Any &a)
{
	bool bds = isa<double>(a);
	bool bdv = isa<QVector<double>>(a);
	
	if (bds)
	{
		return cos(convertTo<double>(a));
	}
	else if (bdv)
	{
		QVector<double> input = convertTo<QVector<double>>(a);
		int n = input.size();
		QVector<double> result(n);
		for (int i=0; i<n; ++i) {result[i] = cos(input[i]);}
		return result;
	}
	
	QString message = "cos(const Any&) : type not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}
*/
