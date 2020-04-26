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
	q.printQInt(10);
	
	q.scanQInt(c, 2);
	q.printQInt(10);

	QInt add1;
	QInt add2;
	QInt kq;
	a="1";
	b="16";
	add1.scanQInt(a, 10);
	add2.scanQInt(b, 10);
	/*
	if(add1>add2)
		cout<<"lon hon\n";
	if(add1<add2)
		cout<<"nho hon\n";
	*/
	kq = add1 - add2;
	//kq=kq-add1;
	kq.printQInt(10);
	

	return 0;
}