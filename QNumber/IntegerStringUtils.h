#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

#define SIZE_INT32 32

#include <iostream>
#include <string>
using namespace std;

class IntegerStringUtils
{
public:
	static string convertDecToBin(string src);
	static string convertHexToBin(string src);
	static string convertBinToHex(string src);

	static string convertFractionPartToBin(string srcFrac);

	static string divideDecStringByTwo(const string&);
	static bool isNegative(const string&);
	static string addTwoPositiveIntegerString(string srcA, string srcB);
	static string mulOfPositiveIntegerAndTwo(string src);
	static string powerOfTwo(unsigned int exp);

	static string mulOfPositiveIntegerAndFive(string src);
};

#endif // !_STRING_UTILS_H
