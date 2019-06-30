#include "AnyOperators.h"
#include "ExceptionAnyOperator.h"


///////////////////////////////////////////////////////////////////////////////
//  OPERATOR +
//  OPERATOR - (binary and unary)
//  OPERATOR *
//  OPERATOR /
//  OPERATOR %
//
//  OPERATOR &&
//  OPERATOR ||
//  OPERATOR !
//
//  OPERATOR ==
//  OPERATOR !=
//
//  OPERATOR <
//  OPERATOR <=
//  OPERATOR >
//  OPERATOR >=
///////////////////////////////////////////////////////////////////////////////


// OPERATOR+ //////////////////////////////////////////////////////////////////
Any operator+(const Any &a1, const Any &a2)
{
	bool b1ds = isa<double>(a1);
	bool b1is = isa<int>(a1);
	
	bool b2ds = isa<double>(a2);
	bool b2is = isa<int>(a2);
	
	if (b1ds && b2ds)      {return convertTo<double>(a1) + convertTo<double>(a2);}
	else if (b1is && b2is) {return convertTo<int>(a1)    + convertTo<int>(a2);}
	else if (b1ds && b2is) {return convertTo<double>(a1) + convertTo<int>(a2);}
	else if (b1is && b2ds) {return convertTo<int>(a1)    + convertTo<double>(a2);}
	
	QString message = "operator+(const Any&, const Any&) : types not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}

// OPERATOR- //////////////////////////////////////////////////////////////////
Any operator-(const Any &a1, const Any &a2)
{
	bool b1ds = isa<double>(a1);
	bool b1is = isa<int>(a1);
	
	bool b2ds = isa<double>(a2);
	bool b2is = isa<int>(a2);
	
	if (b1ds && b2ds)      {return convertTo<double>(a1) - convertTo<double>(a2);}
	else if (b1is && b2is) {return convertTo<int>(a1)    - convertTo<int>(a2);}
	else if (b1ds && b2is) {return convertTo<double>(a1) - convertTo<int>(a2);}
	else if (b1is && b2ds) {return convertTo<int>(a1)    - convertTo<double>(a2);}
	
	QString message = "operator-(const Any&, const Any&) : types not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}

Any operator-(const Any &a)
{
	if (isa<double>(a))   {return -convertTo<double>(a);}
	else if (isa<int>(a)) {return -convertTo<int>(a);}
	
	QString message = "operator-(const Any&) : type not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}

// OPERATOR* //////////////////////////////////////////////////////////////////
Any operator*(const Any &a1, const Any &a2)
{
	bool b1ds = isa<double>(a1);
	bool b1is = isa<int>(a1);
	
	bool b2ds = isa<double>(a2);
	bool b2is = isa<int>(a2);
	
	if (b1ds && b2ds)      {return convertTo<double>(a1) * convertTo<double>(a2);}
	else if (b1is && b2is) {return convertTo<int>(a1)    * convertTo<int>(a2);}
	else if (b1ds && b2is) {return convertTo<double>(a1) * convertTo<int>(a2);}
	else if (b1is && b2ds) {return convertTo<int>(a1)    * convertTo<double>(a2);}
	
	QString message = "operator*(const Any&, const Any&) : types not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}

// OPERATOR/ //////////////////////////////////////////////////////////////////
Any operator/(const Any &a1, const Any &a2)
{
	bool b1ds = isa<double>(a1);
	bool b1is = isa<int>(a1);
	
	bool b2ds = isa<double>(a2);
	bool b2is = isa<int>(a2);
	
	if (b1ds && b2ds)      {return convertTo<double>(a1) / convertTo<double>(a2);}
	else if (b1is && b2is) {return convertTo<int>(a1)    / convertTo<int>(a2);}
	else if (b1ds && b2is) {return convertTo<double>(a1) / convertTo<int>(a2);}
	else if (b1is && b2ds) {return convertTo<int>(a1)    / convertTo<double>(a2);}
	
	QString message = "operator/(const Any&, const Any&) : types not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}

// OPERATOR% //////////////////////////////////////////////////////////////////
Any operator%(const Any &a1, const Any &a2)
{
	bool b1is = isa<int>(a1);
	bool b2is = isa<int>(a2);
	
	if (b1is && b2is) {return convertTo<int>(a1) % convertTo<int>(a2);}
	
	QString message = "operator%(const Any&, const Any&) : types not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}






// OPERATOR&& /////////////////////////////////////////////////////////////////
Any operator&&(const Any &a1, const Any &a2)
{
	bool b1bs = isa<bool>(a1);
	bool b2bs = isa<bool>(a2);
	
	if (b1bs && b2bs) {return convertTo<bool>(a1) && convertTo<bool>(a2);}
	
	QString message = "operator&&(const Any&, const Any&) : types not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}

// OPERATOR|| /////////////////////////////////////////////////////////////////
Any operator||(const Any &a1, const Any &a2)
{
	bool b1bs = isa<bool>(a1);
	bool b2bs = isa<bool>(a2);
	
	if (b1bs && b2bs) {return convertTo<bool>(a1) || convertTo<bool>(a2);}
	
	QString message = "operator||(const Any&, const Any&) : types not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}

// OPERATOR! //////////////////////////////////////////////////////////////////
Any operator!(const Any &a)
{
	if (isa<bool>(a)) {return !convertTo<bool>(a);}
	
	QString message = "operator!(const Any&) : type not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}






// OPERATOR== /////////////////////////////////////////////////////////////////
Any operator==(const Any &a1, const Any &a2)
{
	bool b1ds = isa<double>(a1);
	bool b1is = isa<int>(a1);
	bool b1bs = isa<bool>(a1);
	
	bool b2ds = isa<double>(a2);
	bool b2is = isa<int>(a2);
	bool b2bs = isa<bool>(a2);
	
	if (b1ds && b2ds)      {return convertTo<double>(a1) == convertTo<double>(a2);}
	else if (b1is && b2is) {return convertTo<int>(a1)    == convertTo<int>(a2);}
	else if (b1bs && b2bs) {return convertTo<bool>(a1)   == convertTo<bool>(a2);}
	return false;
}

// OPERATOR!= /////////////////////////////////////////////////////////////////
Any operator!=(const Any &a1, const Any &a2)
{
	
	return !operator==(a1,a2);
}






// OPERATOR < /////////////////////////////////////////////////////////////////
Any operator<(const Any &a1, const Any &a2)
{
	bool b1ds = isa<double>(a1);
	bool b1is = isa<int>(a1);
	
	bool b2ds = isa<double>(a2);
	bool b2is = isa<int>(a2);
	
	if (b1ds && b2ds)      {return convertTo<double>(a1) < convertTo<double>(a2);}
	else if (b1is && b2is) {return convertTo<int>(a1)    < convertTo<int>(a2);}
	else if (b1ds && b2is) {return convertTo<double>(a1) < convertTo<int>(a2);}
	else if (b1is && b2ds) {return convertTo<int>(a1)    < convertTo<double>(a2);}
	
	QString message = "operator<(const Any&, const Any&) : types not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}

// OPERATOR <= ////////////////////////////////////////////////////////////////
Any operator<=(const Any &a1, const Any &a2)
{
	bool b1ds = isa<double>(a1);
	bool b1is = isa<int>(a1);
	
	bool b2ds = isa<double>(a2);
	bool b2is = isa<int>(a2);
	
	if (b1ds && b2ds)      {return convertTo<double>(a1) <= convertTo<double>(a2);}
	else if (b1is && b2is) {return convertTo<int>(a1)    <= convertTo<int>(a2);}
	else if (b1ds && b2is) {return convertTo<double>(a1) <= convertTo<int>(a2);}
	else if (b1is && b2ds) {return convertTo<int>(a1)    <= convertTo<double>(a2);}
	
	QString message = "operator<=(const Any&, const Any&) : types not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}

// OPERATOR > /////////////////////////////////////////////////////////////////
Any operator>(const Any &a1, const Any &a2)
{
	bool b1ds = isa<double>(a1);
	bool b1is = isa<int>(a1);
	
	bool b2ds = isa<double>(a2);
	bool b2is = isa<int>(a2);
	
	if (b1ds && b2ds)      {return convertTo<double>(a1) > convertTo<double>(a2);}
	else if (b1is && b2is) {return convertTo<int>(a1)    > convertTo<int>(a2);}
	else if (b1ds && b2is) {return convertTo<double>(a1) > convertTo<int>(a2);}
	else if (b1is && b2ds) {return convertTo<int>(a1)    > convertTo<double>(a2);}
	
	QString message = "operator>(const Any&, const Any&) : types not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}

// OPERATOR >= ////////////////////////////////////////////////////////////////
Any operator>=(const Any &a1, const Any &a2)
{
	bool b1ds = isa<double>(a1);
	bool b1is = isa<int>(a1);
	
	bool b2ds = isa<double>(a2);
	bool b2is = isa<int>(a2);
	
	if (b1ds && b2ds)      {return convertTo<double>(a1) >= convertTo<double>(a2);}
	else if (b1is && b2is) {return convertTo<int>(a1)    >= convertTo<int>(a2);}
	else if (b1ds && b2is) {return convertTo<double>(a1) >= convertTo<int>(a2);}
	else if (b1is && b2ds) {return convertTo<int>(a1)    >= convertTo<double>(a2);}
	
	QString message = "operator>=(const Any&, const Any&) : types not supported";
	throw ExceptionAnyOperator{qPrintable(message)};
}