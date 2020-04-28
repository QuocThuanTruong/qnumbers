#include "IntegerStringUtils.h"
#include "BitUtils.h"
#include "QFloat.h"
#include "QInt.h"

int main()
{
	//TO DO
	//Test here
	string a = "-50";
	string b = "240";

	cout << "a: " << a << endl;
	cout << "b: " << b << endl;

	QInt c;
	c.scanQInt(a, 10);
	cout << "b: ";
	c.printQInt(2);
	c.printQInt(10);
	c.printQInt(16);

	QInt d;
	d.scanQInt(b, 10);
	
	(c + d).printQInt(10);

	cout << IntegerStringUtils::convertFractionPartToBin("1") << endl;

	QFloat e("0.1");
	e.printQFloat(2);
	// qua ben nay chay

	return 0;
}