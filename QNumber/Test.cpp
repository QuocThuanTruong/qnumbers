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
	cout << "b: ";
	c.printQInt(2);
	c.printQInt(10);
	c.printQInt(16);

	QInt d;
	d.scanQInt(b, 10);
	
	(c + d).printQInt(10);
	(c * d).printQInt(10);
	(c / d).printQInt(10);
	
	return 0;
}