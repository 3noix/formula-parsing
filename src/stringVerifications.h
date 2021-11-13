#ifndef STRING_VERIFICATIONS
#define STRING_VERIFICATIONS


#include <QString>
#include <QList>


bool isBool(const QString &str);
bool isDoubleStrict(const QString &str);
bool isDouble(const QString &str);
bool isInt(const QString &str);
bool isHardCodedString(const QString &str);
bool stringCanBeConvertedTo(const QString &typeStr, const QString &valueStr);

bool isParamName(const QString &str);


// convertToString
template <typename T> QString convertToString(const T &value)
{
	Q_UNUSED(value)
	return {};
};
QString convertToString(bool b);
QString convertToString(double d);
QString convertToString(int i);

// convertToStringShort
template <typename T> QString convertToStringShort(const T &value)
{
	Q_UNUSED(value)
	return {};
};
QString convertToStringShort(bool b);
QString convertToStringShort(double d);
QString convertToStringShort(int i);

// convertFromString
template <typename T> T convertFromString(const QString &str, bool *ok)
{
	if (ok) {*ok = false;}
	return {};
};
template <> bool convertFromString(const QString &str, bool *ok);
template <> double convertFromString(const QString &str, bool *ok);
template <> int convertFromString(const QString &str, bool *ok);

// typeToString
template <typename T> QString typeToString(const T &value)
{
	Q_UNUSED(value)
	return "Unknown";
};
template <> QString typeToString(const bool &b);
template <> QString typeToString(const double &d);
template <> QString typeToString(const int &i);
template <> QString typeToString(const unsigned long long int &i);
template <> QString typeToString(const unsigned long int &i);
template <> QString typeToString(const long long int &i);
template <> QString typeToString(const long int &i);
template <> QString typeToString(const float &f);


#endif

