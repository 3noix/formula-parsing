#ifndef VECTORS_OPERATORS
#define VECTORS_OPERATORS


#include <QVector>
#include <QString>
#include "ExceptionAnyOperator.h"


// OPERATOR+ //////////////////////////////////////////////////////////////////
template <typename T>
QVector<T> operator+(const QVector<T> &v1, const QVector<T> &v2)
{
	int n1 = v1.size();
	if (n1 != v2.size())
	{
		QString message = "operator+(const QVector<T>&, const QVector<T>&) : size mismatch";
		throw ExceptionAnyOperator{qPrintable(message)};
	}
	
	QVector<T> v(n1);
	for (int i=0; i<n1; ++i) {v[i] = v1[i] + v2[i];}
	return v;
};


template <typename T>
QVector<T> operator+(const QVector<T> &v1, T s2)
{
	int n1 = v1.size();
	QVector<T> v(n1);
	for (int i=0; i<n1; ++i) {v[i] = v1[i] + s2;}
	return v;
};


template <typename T>
QVector<T> operator+(T s1, const QVector<T> &v2)
{
	int n2 = v2.size();
	QVector<T> v(n2);
	for (int i=0; i<n2; ++i) {v[i] = s1 + v2[i];}
	return v;
};






// OPERATOR- //////////////////////////////////////////////////////////////////
template <typename T>
QVector<T> operator-(const QVector<T> &v1, const QVector<T> &v2)
{
	int n1 = v1.size();
	if (n1 != v2.size())
	{
		QString message = "operator-(const QVector<T>&, const QVector<T>&) : size mismatch";
		throw ExceptionAnyOperator{qPrintable(message)};
	}
	
	QVector<T> v(n1);
	for (int i=0; i<n1; ++i) {v[i] = v1[i] - v2[i];}
	return v;
};


template <typename T>
QVector<T> operator-(const QVector<T> &v1, T s2)
{
	int n1 = v1.size();
	QVector<T> v(n1);
	for (int i=0; i<n1; ++i) {v[i] = v1[i] - s2;}
	return v;
};


template <typename T>
QVector<T> operator-(T s1, const QVector<T> &v2)
{
	int n2 = v2.size();
	QVector<T> v(n2);
	for (int i=0; i<n2; ++i) {v[i] = s1 - v2[i];}
	return v;
};

template <typename T>
QVector<T> operator-(const QVector<T> &v1)
{
	int n1 = v1.size();
	QVector<T> v(n1);
	for (int i=0; i<n1; ++i) {v[i] = -v1[i];}
	return v;
};






// OPERATOR* //////////////////////////////////////////////////////////////////
template <typename T>
QVector<T> operator*(const QVector<T> &v1, const QVector<T> &v2)
{
	int n1 = v1.size();
	if (n1 != v2.size())
	{
		QString message = "operator*(const QVector<T>&, const QVector<T>&) : size mismatch";
		throw ExceptionAnyOperator{qPrintable(message)};
	}
	
	QVector<T> v(n1);
	for (int i=0; i<n1; ++i) {v[i] = v1[i] * v2[i];}
	return v;
};


template <typename T>
QVector<T> operator*(const QVector<T> &v1, T s2)
{
	int n1 = v1.size();
	QVector<T> v(n1);
	for (int i=0; i<n1; ++i) {v[i] = v1[i] * s2;}
	return v;
};


template <typename T>
QVector<T> operator*(T s1, const QVector<T> &v2)
{
	int n2 = v2.size();
	QVector<T> v(n2);
	for (int i=0; i<n2; ++i) {v[i] = s1 * v2[i];}
	return v;
};






// OPERATOR/ //////////////////////////////////////////////////////////////////
template <typename T>
QVector<T> operator/(const QVector<T> &v1, const QVector<T> &v2)
{
	int n1 = v1.size();
	if (n1 != v2.size())
	{
		QString message = "operator/(const QVector<T>&, const QVector<T>&) : size mismatch";
		throw ExceptionAnyOperator{qPrintable(message)};
	}
	
	QVector<T> v(n1);
	for (int i=0; i<n1; ++i) {v[i] = v1[i] / v2[i];}
	return v;
};


template <typename T>
QVector<T> operator/(const QVector<T> &v1, T s2)
{
	int n1 = v1.size();
	QVector<T> v(n1);
	for (int i=0; i<n1; ++i) {v[i] = v1[i] / s2;}
	return v;
};


template <typename T>
QVector<T> operator/(T s1, const QVector<T> &v2)
{
	int n2 = v2.size();
	QVector<T> v(n2);
	for (int i=0; i<n2; ++i) {v[i] = s1 / v2[i];}
	return v;
};






// OPERATOR&& /////////////////////////////////////////////////////////////////
template <typename T>
QVector<T> operator&&(const QVector<T> &v1, const QVector<T> &v2)
{
	int n1 = v1.size();
	if (n1 != v2.size())
	{
		QString message = "operator&&(const QVector<T>&, const QVector<T>&) : size mismatch";
		throw ExceptionAnyOperator{qPrintable(message)};
	}
	
	QVector<T> v(n1);
	for (int i=0; i<n1; ++i) {v[i] = v1[i] && v2[i];}
	return v;
};


template <typename T>
QVector<T> operator&&(const QVector<T> &v1, T s2)
{
	int n1 = v1.size();
	QVector<T> v(n1);
	for (int i=0; i<n1; ++i) {v[i] = v1[i] && s2;}
	return v;
};


template <typename T>
QVector<T> operator&&(T s1, const QVector<T> &v2)
{
	int n2 = v2.size();
	QVector<T> v(n2);
	for (int i=0; i<n2; ++i) {v[i] = s1 && v2[i];}
	return v;
};






// OPERATOR|| /////////////////////////////////////////////////////////////////
template <typename T>
QVector<T> operator||(const QVector<T> &v1, const QVector<T> &v2)
{
	int n1 = v1.size();
	if (n1 != v2.size())
	{
		QString message = "operator||(const QVector<T>&, const QVector<T>&) : size mismatch";
		throw ExceptionAnyOperator{qPrintable(message)};
	}
	
	QVector<T> v(n1);
	for (int i=0; i<n1; ++i) {v[i] = v1[i] || v2[i];}
	return v;
};


template <typename T>
QVector<T> operator||(const QVector<T> &v1, T s2)
{
	int n1 = v1.size();
	QVector<T> v(n1);
	for (int i=0; i<n1; ++i) {v[i] = v1[i] || s2;}
	return v;
};


template <typename T>
QVector<T> operator||(T s1, const QVector<T> &v2)
{
	int n2 = v2.size();
	QVector<T> v(n2);
	for (int i=0; i<n2; ++i) {v[i] = s1 || v2[i];}
	return v;
};






// OPERATOR! //////////////////////////////////////////////////////////////////
template <typename T>
QVector<T> operator!(const QVector<T> &v1)
{
	int n1 = v1.size();
	QVector<T> v(n1);
	for (int i=0; i<n1; ++i) {v[i] = !v1[i];}
	return v;
};


#endif

