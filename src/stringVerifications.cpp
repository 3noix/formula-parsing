#include "stringVerifications.h"
#include <QRegExp>
#include <QStringList>


///////////////////////////////////////////////////////////////////////////////
// RESUME :
//
//  IS BOOL
//  IS DOUBLE STRICT
//  IS DOUBLE
//  IS INT
//  IS HARD-CODED STRING
//  IS PARAM NAME
//
//  STRING CAN BE CONVERTED TO
//  CONVERT TO STRING
//  CONVERT TO STRING SHORT
//
//  CONVERT FROM STRING
//  TYPE TO STRING
///////////////////////////////////////////////////////////////////////////////


// IS BOOL ////////////////////////////////////////////////////////////////////
bool isBool(const QString &str)
{
	return (str == "true" || str == "false");
}

// IS DOUBLE STRICT ///////////////////////////////////////////////////////////
bool isDoubleStrict(const QString &str)
{
	if (!str.contains('.')) {return false;}
	
	bool ok = true;
	str.toDouble(&ok);
	return ok;
}

// IS DOUBLE //////////////////////////////////////////////////////////////////
bool isDouble(const QString &str)
{
	bool ok = true;
	str.toDouble(&ok);
	return ok;
}

// IS INT /////////////////////////////////////////////////////////////////////
bool isInt(const QString &str)
{
	bool ok = true;
	str.toInt(&ok);
	return ok;
}

// IS HARD-CODED STRING ///////////////////////////////////////////////////////
bool isHardCodedString(const QString &str)
{
	bool b1 = (str.startsWith('\''));
	bool b2 = (str.endsWith('\''));
	bool b3 = (str.count('\'') == 2);
	return (b1 && b2 && b3);
}

// STRING CAN BE CONVERTED TO /////////////////////////////////////////////////
bool stringCanBeConvertedTo(const QString &typeStr, const QString &valueStr)
{
	if (typeStr == "bool" && isBool(valueStr)) {return true;}
	if (typeStr == "double" && isDoubleStrict(valueStr)) {return true;}
	if (typeStr == "int" && isInt(valueStr)) {return true;}
	return false;
}

// IS PARAM NAME //////////////////////////////////////////////////////////////
bool isParamName(const QString &str)
{
	// premiers tests
	if (str == "") {return false;}
	if (!str[0].isLetter()) {return false;}
	
	// test autres caractères
	for (int i=1; i<str.size(); ++i)
	{
		QChar carac = str[i];
		if ((!carac.isLetter()) && (!carac.isDigit()) && (carac != '_'))
		{return false;}
	}
	
	return true;
}






// CONVERT TO STRING //////////////////////////////////////////////////////////
QString convertToString(bool b)
{
	if (b) {return "true";}
	return "false";
}

QString convertToString(double d)
{
	return QString::number(d,'e');
}

QString convertToString(int i)
{
	return QString::number(i);
}

// CONVERT TO STRING SHORT ////////////////////////////////////////////////////
QString convertToStringShort(bool b)
{
	if (b) {return "t";}
	return "f";
}

QString convertToStringShort(double d)
{
	QString str = QString::number(d,'e');
	str.replace(QRegExp("0+e"),"e");
	str.replace(".e","e");
	str.replace("e+00","");
	return str;
}

QString convertToStringShort(int i)
{
	return QString::number(i);
}






// CONVERT FROM STRING ////////////////////////////////////////////////////////
template <>
bool convertFromString(const QString &str, bool *ok)
{
	if (str == "true")
	{
		if (ok) {*ok = true;}
		return true;
	}
	else if (str == "false")
	{
		if (ok) {*ok = true;}
		return false;
	}
	else
	{
		if (ok) {*ok = false;}
		return false;
	}
}

template <>
double convertFromString(const QString &str, bool *ok)
{
	return str.toDouble(ok);
}

template <>
int convertFromString(const QString &str, bool *ok)
{
	return str.toInt(ok);
}

// TYPE TO STRING /////////////////////////////////////////////////////////////
template <>
QString typeToString(const bool &b)
{
	Q_UNUSED(b)
	return "bool";
};

template <>
QString typeToString(const double &d)
{
	Q_UNUSED(d)
	return "double";
};

template <>
QString typeToString(const int &i)
{
	Q_UNUSED(i)
	return "int";
};

template <>
QString typeToString(const unsigned long long int &i)
{
	Q_UNUSED(i)
	return "unsigned long long int";
};

template <>
QString typeToString(const unsigned long int &i)
{
	Q_UNUSED(i)
	return "unsigned long int";
};

template <>
QString typeToString(const long long int &i)
{
	Q_UNUSED(i)
	return "long long int";
};

template <>
QString typeToString(const long int &i)
{
	Q_UNUSED(i)
	return "long int";
};

template <>
QString typeToString(const float &f)
{
	Q_UNUSED(f)
	return "float";
};

