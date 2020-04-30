#include "IntegerStringUtils.h"
#include "BitUtils.h"
#include "QFloat.h"
#include "QInt.h"

int main()
{
	//TO DO
	//Test here
	string a = "0.6875";
	string b = "12.7258635";

	QFloat f;
	f.scanQFloat(b, 10);
	f.printQFloat(10);
	f.printQFloat(2);

	return 0;
}