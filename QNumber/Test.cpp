#include "IntegerStringUtils.h"
#include "BitUtils.h"
#include "QInt.h"

int main()
{
	string a = "5579";
	string b = "240";
	string c = "11110111";

	QInt q;
	q.scanQInt(b, 10);
	q.printQInt(2);

	q.scanQInt(c, 2);
	q.printQInt(10);

	return 0;
}