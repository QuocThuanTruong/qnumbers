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
	string c = "11110111";

	QInt q;
	q.scanQInt(b, 10);
	q.printQInt(16);

	q.scanQInt(c, 2);
	q.printQInt(10);

	QFloat k;

	cout << k.convertFractionPartToBin("3017578125") << endl; //0.3017578125

	return 0;
}