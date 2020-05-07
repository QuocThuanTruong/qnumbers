#include "QFloat.h"
#include "QInt.h"
#include <sstream>

#pragma warning(disable : 4996)

/**
 *	Hàm executeQInt - Hàm xử lý số QInt
 *	@param	  string 		Chuỗi cần xử lý
 *	@return	  none
 */
void executeQInt(string srcQInt)
{
	string p1;
	string p2;
	string firstNum;
	string secondNum;
	string _operator = "";
	stringstream lineProcessing;

	QInt firstQNum;
	QInt secondQNum;
	int base_1;
	int base_2;

	const int uOpSize = 1;
	string uOperator[] = { "~" };																								// Toán tử 1 ngôi
	const int bOpSize = 17;
	string bOperator[] = { "+", "-", "*", "/", "<", ">", "==", "<=", ">=", "=", "&", "|", "^", "<<", ">>", "rol", "ror" };		// Toán tử 2 ngôi

	int operatorType = 0;								// Loại toán tử
	int paramCount = 1;									// Số lượng tham số

	for (int i = 0; i < srcQInt.size(); i++)			// Đếm số lượng tham số dựa vào đếm dấu space
	{
		if (srcQInt[i] == ' ')
		{
			paramCount++;
		}
	}

	for (int i = 0; i < uOpSize; i++)					// Tìm toán tử 1 ngôi có trong mảng quy định
	{
		if (srcQInt.find(uOperator[i], 0) != string::npos)
		{
			operatorType = 1;
			break;
		}
	}

	for (int i = 0; i < bOpSize; i++)					// Tìm toán tử 2 ngôi có trong mảng quy định
	{
		if (srcQInt.find(bOperator[i], 0) != string::npos)
		{
			operatorType = 2;
			break;
		}
	}													// Nếu không có toán tử thì mặc định là 0

	lineProcessing << srcQInt;							// Đọc dữ liệu vào bộ đệm

	lineProcessing >> p1;								// Lấy chỉ thị p1 

	if (paramCount - operatorType == 3)					// Lấy chỉ thị p2 nếu có
	{													// VD: 2 10 1011 -> paramCount(3) - operatorType(0) = 3 -> Có p2
		lineProcessing >> p2;							// VD: 
	}
	else												// Không thì cho p2 và p1 là như nhau tức là 2 nhập vào hệ cơ số X và xuất ra hệ cơ số X
	{
		p2 = p1;
	}

	switch (operatorType)								// Kiểm tra loại toán tử
	{
	case 0:												// Không có toán tử -> Lấy số đầu để chuyển cơ số
		lineProcessing >> firstNum;
		break;
	case 1:												// Toán tử 1 ngôi -> lấy toán tử rồi đến số cần tính
		lineProcessing >> _operator >> firstNum;
		break;
	case 2:												// Toán tử 2 ngôi -> lấy số đầu > toán tử > số sau
		lineProcessing >> firstNum >> _operator >> secondNum;
		break;
	}

	 base_1 = stoi(p1);									// Chuyển đổi p1, p2 sang số nguyên
	 base_2 = stoi(p2);

	try
	{
		firstQNum.scanQInt(firstNum, base_1);
		
		if (_operator == "")							// Chuyển đổi cơ số và xuất ra
		{
			firstQNum.printQInt(base_2);
		}
		else if (_operator == "~")						// Tính NOT bit và xuất ra
		{
			(~firstQNum).printQInt(base_2);
		}
		else if (_operator == "+")						// Tính + và xuất kết quả
		{
			secondQNum.scanQInt(secondNum, base_1);
			(firstQNum + secondQNum).printQInt(base_2);
		}
		else if (_operator == "-")						// Tính - và xuất kết quả
		{
			secondQNum.scanQInt(secondNum, base_1);
			(firstQNum - secondQNum).printQInt(base_2);
		}
		else if (_operator == "*")						// Tính * và xuất kết quả
		{
			secondQNum.scanQInt(secondNum, base_1);
			(firstQNum * secondQNum).printQInt(base_2);
		}
		else if (_operator == "/")						// Tính / và xuất kết quả
		{
			secondQNum.scanQInt(secondNum, base_1);
			(firstQNum / secondQNum).printQInt(base_2);
		}
		else if (_operator == "<")						// So sánh < và xuất kết quả
		{
			secondQNum.scanQInt(secondNum, base_1);
			cout << ((firstQNum < secondQNum) ? "true" : "false") << endl;
		}
		else if (_operator == ">")						// So sánh > và xuất kết quả
		{
			secondQNum.scanQInt(secondNum, base_1);
			cout << ((firstQNum > secondQNum) ? "true" : "false") << endl;
		}
		else if (_operator == "<=")						// So sánh <= và xuất kết quả
		{
			secondQNum.scanQInt(secondNum, base_1);
			cout << ((firstQNum <= secondQNum) ? "true" : "false") << endl;
		}
		else if (_operator == ">=")						// So sánh >= và xuất kết quả
		{
			secondQNum.scanQInt(secondNum, base_1);
			cout << ((firstQNum >= secondQNum) ? "true" : "false") << endl;
		}
		else if (_operator == "==")						// So sánh == và xuất kết quả
		{
			secondQNum.scanQInt(secondNum, base_1);
			cout << ((firstQNum == secondQNum) ? "true" : "false") << endl;
		}
		else if (_operator == "&")						// Tính AND bit và xuất ra kết quả
		{
			secondQNum.scanQInt(secondNum, base_1);
			(firstQNum & secondQNum).printQInt(base_2);
		}
		else if (_operator == "|")						// Tính OR bit và xuất ra kết quả
		{
			secondQNum.scanQInt(secondNum, base_1);
			(firstQNum | secondQNum).printQInt(base_2);
		}
		else if (_operator == "^")						// Tính XOR bit và xuất ra kết quả
		{
			secondQNum.scanQInt(secondNum, base_1);
			(firstQNum ^ secondQNum).printQInt(base_2);
		}
		else if (_operator == "<<")						// Tính SHL bit và xuất ra kết quả
		{
			int num = stoi(secondNum);
			(firstQNum << num).printQInt(base_2);
		}
		else if (_operator == ">>")						// Tính SHR bit và xuất ra kết quả
		{
			int num = stoi(secondNum);
			(firstQNum >> num).printQInt(base_2);
		}
		else if (_operator == "rol")					// Tính ROL bit và xuất ra kết quả
		{
			int num = stoi(secondNum);
			(firstQNum.rol(num)).printQInt(base_2);
		}
		else if (_operator == "ror")					// Tính ROR bit và xuất ra kết quả
		{
			int num = stoi(secondNum);
			(firstQNum.ror(num)).printQInt(base_2);
		}
	}
	catch (const char* msg)
	{
		cout << msg;
	}
}

/**
 *	Hàm executeQFloat - Hàm xử lý số QFloat
 *	@param	  string 		Chuỗi cần xử lý
 *	@return	  none
 */
void executeQFloat(string srcQFloat)
{

	string p1;
	string p2;
	string convertedNum; 
	stringstream ssIn;

	QFloat destNum;

	int base_1;
	int base_2;

	ssIn << srcQFloat;								// Lấy dữ liệu cần xử lí

	ssIn >> p1 >> p2 >> convertedNum;				// Tách 3 thành phần 

	base_1 = stoi(p1);								// Chuyển p1, p2 sang số nguyên
	base_2 = stoi(p2);

	try
	{
		destNum.scanQFloat(convertedNum, base_1);	// Chuyển cơ số và xuất ra
		destNum.printQFloat(base_2);
	}
	catch (const char* msg)
	{
		cout << msg;
	}
}

int main(int argc, char* argv[])
{
	int type;
	string inFile;
	string outFile;

	if (argc != 4)
	{
		cout << "Syntax must be <program.exe> <input file> <output file> <type>";
		return 0;
	}
	else
	{
		inFile = string(argv[1]);								// Lấy đường dẫn file in và out
		outFile = string(argv[2]);
		type = stoi(argv[3]);

		freopen(inFile.c_str(), "r", stdin);					// Mở file thực hiện đọc ghi bằng cách đưa dữ liệu lên bộ đệm nhập xuất chuẩn (cin, cout) rồi xử lí
		freopen(outFile.c_str(), "w", stdout);					// Vì các hàm print QInt QFloat là xuất ra màn hình nên ta điều hướng bộ đệm xuất chuẩn vào file

		cin.seekg(SEEK_SET);									// Đưa con trỏ đọc bộ đệm lên đầu

		if (type == 1)
		{
			while (!cin.eof())									// Xử lí theo loại 1: Số nguyên, 2 số thực
			{
				string srcQInt;
				getline(cin, srcQInt);
				executeQInt(srcQInt);
			}
		}
		else if (type == 2)
		{
			while (!cin.eof())
			{
				string strIn;
				getline(cin, strIn);
				executeQFloat(strIn);
			}
		}

		fcloseall();
	}

	return 0;
}