#ifndef _QINT_H
#define _QINT_H

#include "BitUtils.h"
#include "IntegerStringUtils.h"

#define BIT_IN_QINT 128
#define SIZE_QINT 16

typedef IntegerStringUtils SUtils;
typedef BitUtils BUtils;

class QInt
{
private:
	int data[TOTAL_BLOCK];
public:
	QInt();
	QInt(const string& src, const int base);
	~QInt();
public:
	void scanQInt(const string& src, const int base);
	void printQInt(const int base);

	static string convertQIntToBin(QInt src);
	static string convertQIntToDec(QInt src);
	static string convertQIntToHex(QInt src);

	static QInt convertBinToQInt(const string& src);
	static QInt convertDecToQInt(const string& src);
	static QInt convertHexToQInt(const string& src);


	bool isNegative();
	bool equalZero();
	static QInt convertToTwoComplement(QInt src);
	static QInt inverseTwoComplement(QInt src);

	QInt operator + (const QInt& other);
	QInt operator - (const QInt& other);
	QInt operator * (const QInt& other);
	QInt operator / (const QInt& other);

	bool operator > (const QInt& other);
	bool operator < (const QInt& other);
	bool operator == (const QInt& other);
	bool operator != (const QInt& other);
	bool operator >= (const QInt& other);
	bool operator <= (const QInt& other);
	QInt& operator = (const QInt& other);

	QInt operator & (const QInt& other);
	QInt operator | (const QInt& other);
	QInt operator ^ (const QInt& other);
	QInt operator ~ () const;

	QInt operator >> (const int& offset);
	QInt operator << (const int& offset);
	QInt& rol(const int& offset);
	QInt& ror(const int& offset);
};
#endif // !_QINT_H
