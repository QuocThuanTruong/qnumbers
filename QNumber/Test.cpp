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
	c.scanQInt(a, 10);
	cout << "a: ";
	c.printQInt(16);

	QInt d;
	d.scanQInt(b, 10);
	cout << "b: ";
	d.printQInt(2);


	cout << "a & b\n";
	(c & d).printQInt(2);

	cout << "a | b\n";
	(c | d).printQInt(2);

	cout << "a ^ b\n";
	(c ^ d).printQInt(2);

	cout << "~a\n";
	(~c).printQInt(2);
	
	cout << "a >> 2\n";
	(c >> 2).printQInt(10);

	cout << "b << 4\n";
	(d << 2).printQInt(10);

	c.rol();
	cout << "rol a\n";
	c.printQInt(2);

	d.ror();
	cout << "ror b\n";
	d.printQInt(2);

	
	cout << IntegerStringUtils::convertFractionPartToBin("3017578125") << endl; //0.3017578125

	return 0;
}