#include "IntegerStringUtils.h"
#include "BitUtils.h"
#include "QFloat.h"
#include "QInt.h"

int main()
{
	//TODO: Test here Nếu test ở đây thì qua bên Main.cpp bấm Ctrl A, xong bấm Ctrl K rồi bấm Ctrl C --> comment nó lại
	//Unlock comment: Ctrl A , Ctrl K, Ctrl U
	//Hướng dẫn test số thực

	/*QFloat a;
	a.scanQFloat("12.8275453", 10);
	a.printQFloat(10);
	a.printQFloat(2);*/

	QInt a;
	a.scanQInt("1234", 10);
	a.printQInt(2);

	a.ror(3);
	a.printQInt(2);

	return 0;
}