#include "IntegerStringUtils.h"
#include "BitUtils.h"
#include "QFloat.h"
#include "QInt.h"

int main()
{
	//TO DO
	//Test here
	string a = "250";
	string b = "-50";

	cout << "a: " << a << endl;
	cout << "b: " << b << endl;

	QInt c;
	c.scanQInt(a, 10);
	cout << "a: ";
	c.printQInt(2);
	c.printQInt(10);
	c.printQInt(16);

	QInt d;
	d.scanQInt(b, 10);
	
	(c + d).printQInt(10);

	cout << "c / d: ";
	(c / d).printQInt(10);

	//cout << IntegerStringUtils::convertFractionPartToBin("1") << endl;

	QFloat e("9457837593845.123146", 10);
	e.printQFloat(2);
	// qua ben nay chay

	return 0;
}