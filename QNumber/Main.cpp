#define _CRT_SECURE_NO_WARNINGS
#include "IntegerStringUtils.h"
#include "BitUtils.h"
#include "QFloat.h"
#include "QInt.h"
#include <vector>
#include <sstream>


/**
 *	Hàm processQInt - Hàm xử lý số QInt
 *	@param	  string 		Chuỗi cần xử lý
 *	@return	 none
 */
void processQInt(string strIn)
{
	vector<string> unaryOperator = { "~" }; // toán tử 1 ngôi
	vector<string> binaryOperator = { "+","-","*","/","<",">","==","<=",">=","=","&","|","^","<<",">>","rol","ror" }; // toán tử 2 ngôi

	int operatorType = 0;  // số ngôi
	int paraCount = 1; // số lượng tham số

	// đếm số lượng tham số
	for (int i = 0; i < strIn.size(); i++)
	{
		if (strIn[i] == ' ')
		{
			paraCount++;
		}
	}

	// Tìm toán tử 1 ngôi
	for (int i = 0; i < unaryOperator.size(); i++)
	{
		if (strIn.find(unaryOperator[i], 0) != string::npos)
		{
			operatorType = 1;
			break;
		}
	}

	// Tìm toán tử 2 ngôi
	for (int i = 0; i < binaryOperator.size(); i++)
	{
		if (strIn.find(binaryOperator[i], 0) != string::npos)
		{
			operatorType = 2;
			break;
		}
	}
	// Nếu không có toán tử thì mặc định là 0

	string p1, p2, opr, termA, termB;

	stringstream ssIn;
	ssIn << strIn;

	// lấy ra chỉ thị 1 ( cơ số 1 )
	ssIn >> p1;

	// Kiểm tra có chứa chỉ thị p2 không
	if (paraCount - operatorType == 3)
	{
		// có thì lấy ra
		ssIn >> p2;
	}
	else
	{
		// không có thì cho chỉ thị 2 ( cơ số 2 ) = chỉ thị 1
		p2 = p1;
	}

	// kiểm tra loại toán tử
	opr = ""; // để lưu loại toán tử
	switch (operatorType)
	{
	case 0: // không có toán tử 
		ssIn >> termA;
		break;
	case 1: // toán tử 1 ngôi
		ssIn >> opr >> termA;
		break;
	case 2: // toán tử 2 ngôi
		ssIn >> termA >> opr >> termB;
		break;
	}

	// Thực hiện các phép tính
	QInt A, B;
	int base1 = stoi(p1);    //	chuyển các chỉ thị ( cơ số ) về int
	int base2 = stoi(p2);

	try
	{
		A.scanQInt(termA, base1);
		// Toán tử không ngôi ( chuyển đổi cơ số )
		if (opr == "")
		{
			A.printQInt(base2);
		}

		// Toán tử 1 ngôi
		else if (opr == "~")
		{
			(~A).printQInt(base2);
		}

		// Toán tử 2 ngôi
		else if (opr == "+")
		{
			B.scanQInt(termB, base1);
			(A + B).printQInt(base2);
		}
		else if (opr == "-")
		{
			B.scanQInt(termB, base1);
			(A - B).printQInt(base2);
		}
		else if (opr == "*")
		{
			B.scanQInt(termB, base1);
			(A * B).printQInt(base2);
		}
		else if (opr == "/")
		{
			B.scanQInt(termB, base1);
			(A / B).printQInt(base2);
		}
		else if (opr == "<")
		{
			B.scanQInt(termB, base1);
			cout << ((A < B) ? "TRUE" : "FALSE");
		}
		else if (opr == ">")
		{
			B.scanQInt(termB, base1);
			cout << ((A > B) ? "TRUE" : "FALSE");
		}
		else if (opr == "<=")
		{
			B.scanQInt(termB, base1);
			cout << ((A <= B) ? "TRUE" : "FALSE");
		}
		else if (opr == ">=")
		{
			B.scanQInt(termB, base1);
			cout << ((A >= B) ? "TRUE" : "FALSE");
		}
		else if (opr == "==")
		{
			B.scanQInt(termB, base1);
			cout << ((A == B) ? "TRUE" : "FALSE");
		}

		else if (opr == "&")
		{
			B.scanQInt(termB, base1);
			(A & B).printQInt(base2);
		}
		else if (opr == "|")
		{
			B.scanQInt(termB, base1);
			(A | B).printQInt(base2);
		}
		else if (opr == "^")
		{
			B.scanQInt(termB, base1);
			(A ^ B).printQInt(base2);
		}
		else if (opr == "<<")
		{
			int num = stoi(termB);
			(A << num).printQInt(base2);
		}
		else if (opr == ">>")
		{
			int num = stoi(termB);
			(A >> num).printQInt(base2);
		}
		else if (opr == "rol")
		{
			int num = stoi(termB);
			(A.rol(num)).printQInt(base2);
		}
		else if (opr == "ror")
		{
			int num = stoi(termB);
			(A.ror(num)).printQInt(base2);
		}
	}
	catch (const char* msg)
	{
		cout << msg;
	}
	cout << endl;
}

/**
 *	Hàm processQFloat - Hàm xử lý số QFloat
 *	@param	  string 		Chuỗi cần xử lý
 *	@return	 none
 */
void processQFloat(string strIn)
{

	string p1, p2, strP; // chỉ thị p1, p2 số cần xử lý ( dạng string )

	stringstream ssIn;

	ssIn << strIn;

	ssIn >> p1 >> p2 >> strP; // lấy ra các giá trị

	// chuyển các chỉ thị về số nguyên
	int base1 = stoi(p1);
	int base2 = stoi(p2);

	QFloat A;

	try
	{
		A.scanQFloat(strP, base1);
		A.printQFloat(base2);
	}
	catch (const char* msg)
	{
		cout << msg;
	}
	cout << endl;
}

int main(int argc, char* argv[])
{
	string inPath, outPath;
	if (argc != 3)
	{
		cout << "Syntax error!";
		return 0;
	}
	else
	{
		inPath = string(argv[1]);
		outPath = string(argv[2]);

		freopen(inPath.c_str(), "r", stdin);
		freopen(outPath.c_str(), "w", stdout);

		/*while (!cin.eof())
		{
			string strIn;
			getline(cin, strIn);
			processQInt(strIn);
		}*/

		while (!cin.eof())
		{
			string strIn;
			getline(cin, strIn);
			processQFloat(strIn);
		}
	}
	return 0;
}