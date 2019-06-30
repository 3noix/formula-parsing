#include "AnyFunctions.h"
#include "../ExceptionInterpreter.h"
#include <math.h>


///////////////////////////////////////////////////////////////////////////////
//  ABS
//  POW
//  SQRT
//
//  EXP
//  LOG
//  LOG 10
//
//  COS
//  SIN
//  TAN
//  ACOS
//  ASIN
//  ATAN
///////////////////////////////////////////////////////////////////////////////


// ABS ////////////////////////////////////////////////////////////////////////
Any abs(const Any &a)
{
	if (isa<double>(a))
	{
		return fabs(convertTo<double>(a));
	}
	else if (isa<int>(a))
	{
		return abs(convertTo<int>(a));
	}
	
	QString message = "abs(const Any&) : type not supported";
	throw ExceptionInterpreter{message};
}

// POW ////////////////////////////////////////////////////////////////////////
Any pow(const Any &a1, const Any &a2)
{
	bool b1ds = isa<double>(a1);
	bool b1is = isa<int>(a1);
	
	bool b2ds = isa<double>(a2);
	bool b2is = isa<int>(a2);
	
	if (b1ds && b2ds)      {return pow(convertTo<double>(a1), convertTo<double>(a2));}
	else if (b1is && b2is) {return pow(convertTo<int>(a1),    convertTo<int>(a2));}
	else if (b1ds && b2is) {return pow(convertTo<double>(a1), convertTo<int>(a2));}
	else if (b1is && b2ds) {return pow(convertTo<int>(a1),    convertTo<double>(a2));}
	
	QString message = "pow(const Any&, const Any&) : types not supported";
	throw ExceptionInterpreter{message};
}

// SQRT ///////////////////////////////////////////////////////////////////////
Any sqrt(const Any &a)
{
	if (isa<double>(a))
	{
		double d = convertTo<double>(a);
		if (d < 0.0) {return {};}
		return sqrt(d);
	}
	else if (isa<int>(a))
	{
		int i = convertTo<int>(a);
		if (i < 0) {return {};}
		double d = i;
		return sqrt(d);
	}
	
	QString message = "sqrt(const Any&) : type not supported";
	throw ExceptionInterpreter{message};
}






// EXP ////////////////////////////////////////////////////////////////////////
Any exp(const Any &a)
{
	if (isa<double>(a))
	{
		return exp(convertTo<double>(a));
	}
	else if (isa<int>(a))
	{
		double d = convertTo<int>(a);
		return exp(d);
	}
	
	QString message = "exp(const Any&) : type not supported";
	throw ExceptionInterpreter{message};
}

// LOG ////////////////////////////////////////////////////////////////////////
Any log(const Any &a)
{
	if (isa<double>(a))
	{
		return log(convertTo<double>(a));
	}
	else if (isa<int>(a))
	{
		double d = convertTo<int>(a);
		return log(d);
	}
	
	QString message = "log(const Any&) : type not supported";
	throw ExceptionInterpreter{message};
}

// LOG 10 /////////////////////////////////////////////////////////////////////
Any log10(const Any &a)
{
	if (isa<double>(a))
	{
		return log10(convertTo<double>(a));
	}
	else if (isa<int>(a))
	{
		double d = convertTo<int>(a);
		return log10(d);
	}
	
	QString message = "log10(const Any&) : type not supported";
	throw ExceptionInterpreter{message};
}






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
	throw ExceptionInterpreter{message};
}

// SIN ////////////////////////////////////////////////////////////////////////
Any sin(const Any &a)
{
	if (isa<double>(a))
	{
		return sin(convertTo<double>(a));
	}
	else if (isa<int>(a))
	{
		double d = convertTo<int>(a);
		return sin(d);
	}
	
	QString message = "sin(const Any&) : type not supported";
	throw ExceptionInterpreter{message};
}

// TAN ////////////////////////////////////////////////////////////////////////
Any tan(const Any &a)
{
	if (isa<double>(a))
	{
		return tan(convertTo<double>(a));
	}
	else if (isa<int>(a))
	{
		double d = convertTo<int>(a);
		return tan(d);
	}
	
	QString message = "tan(const Any&) : type not supported";
	throw ExceptionInterpreter{message};
}

// ACOS ///////////////////////////////////////////////////////////////////////
Any acos(const Any &a)
{
	if (isa<double>(a))
	{
		return acos(convertTo<double>(a));
	}
	else if (isa<int>(a))
	{
		double d = convertTo<int>(a);
		return acos(d);
	}
	
	QString message = "acos(const Any&) : type not supported";
	throw ExceptionInterpreter{message};
}

// ASIN ///////////////////////////////////////////////////////////////////////
Any asin(const Any &a)
{
	if (isa<double>(a))
	{
		return asin(convertTo<double>(a));
	}
	else if (isa<int>(a))
	{
		double d = convertTo<int>(a);
		return asin(d);
	}
	
	QString message = "asin(const Any&) : type not supported";
	throw ExceptionInterpreter{message};
}

// ATAN ///////////////////////////////////////////////////////////////////////
Any atan(const Any &a)
{
	if (isa<double>(a))
	{
		return atan(convertTo<double>(a));
	}
	else if (isa<int>(a))
	{
		double d = convertTo<int>(a);
		return atan(d);
	}
	
	QString message = "atan(const Any&) : type not supported";
	throw ExceptionInterpreter{message};
}

