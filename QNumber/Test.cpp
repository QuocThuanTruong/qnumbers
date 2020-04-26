#include "IntegerStringUtils.h"
#include "BitUtils.h"
#include "QInt.h"

int main()
{
	//TO DO
	//Test here
	string a = "5879";
	string b = "-15";
	string c = "11110111";

	QInt q;
	q.scanQInt(b, 10);
	q.printQInt(16);
	
	q.scanQInt(c, 2);
	q.printQInt(10);

	return 0;
}