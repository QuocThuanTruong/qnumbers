#ifndef _QFLOAT_H
#define _QFLOAT_H

#include "BitUtils.h"
#include "IntegerStringUtils.h"

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
	void printQFloat(const QFloat& src);

	QFloat convertDecToBin(const string& src);
	string convertBinToDec(const QFloat& src);
};

#endif // !_QFLOAT_H