#include "IntegerStringUtils.h"
#include "BitUtils.h"
#include "QFloat.h"
#include "QInt.h"

int main()
{
	//TO DO
	//Test here
	string a = "5579";
	string b = "240";

	cout << "a: " << a << endl;
	cout << "b: " << b << endl;

	QInt c;
	c.scanQInt(b, 10);
	cout << "b: ";
	c.printQInt(2);
	c.printQInt(10);
	c.printQInt(16);

	return 0;
}