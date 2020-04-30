#ifndef _QFLOAT_H
#define _QFLOAT_H

#include "QInt.h"
#include "BitUtils.h"
#include "IntegerStringUtils.h"

#define BIT_IN_QFLOAT 128
#define SIZE_QFLOAT 16
#define BIT_IN_SIGN 1
#define BIT_IN_EXP 15
#define BIT_IN_SIGNIFICAND 112
#define BIAS 16383

typedef IntegerStringUtils SUtils;
typedef BitUtils BUtils;

class QFloat
{
private:
	int data[TOTAL_BLOCK];
public:
	QFloat();
	QFloat(const string& src, const int base);
	~QFloat();
public:
	void scanQFloat(const string& src, const int base);
	void printQFloat(const int base);

	static string convertQFloatToDec(QFloat src);
	static string convertQFloatToBin(QFloat src);

	static QFloat convertDecToQFloat(const string& src);
	static QFloat convertBinToQFloat(const string& src);

	static bool isZero(string srcExpBin, string srcSignificandBin);
	static bool isDernomalized(string srcExpBin, string srcSignificandBin);
	static bool isInfinity(string srcExpBin, string srcSignificandBin);
	static bool isNaN(string srcExpBin, string srcSignificandBin);
};

#endif // !_QFLOAT_H