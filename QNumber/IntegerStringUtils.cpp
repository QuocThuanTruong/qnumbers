#include "IntegerStringUtils.h"
#include "QInt.h"
#include "QFloat.h"

/**
 *	Ham convertDecToBin - Hàm chuyển dổi chuỗi thập phân sang chuỗi nhị phân
 *	@param	 string		Chuỗi thập phân cần chuyển
 *	@return	 string		Chuỗi nhị phân kết quả
 */
string IntegerStringUtils::convertDecToBin(string srcDec)
{
	string result;
	string tempDec = srcDec;

	if (isNegative(tempDec))					//Nếu chuỗi đã cho âm --> xóa đi '-' trước chuỗi
	{
		tempDec.erase(tempDec.begin());
	}

	while (tempDec != "")
	{
		result = (char)((tempDec.back() - '0') % 2 + '0') + result;			// Ghi phần dư chuỗi chia cho 2 vào chuỗi kết quả
		tempDec = divideDecStringByTwo(tempDec);							// Lấy chuỗi chia nguyên cho 2 để tiếp tục chuyển cho đến khi hết chuỗi
	}

	if (isNegative(srcDec))								// Nếu chuỗi ban đầu âm
	{
		QInt temp(result, 10);							// Chuyển chuỗi kết quả sang QInt	
		temp = QInt::convertToTwoComplement(temp);		// Chuyển QInt sang dạng bù 2
		result = QInt::convertQIntToBin(temp);			// Chuyển QInt bù 2 sang chuỗi nhị phân
	}													

	return result;
}

string IntegerStringUtils::convertHexToBin(string srcHex)
{
	string result;

	for (int i = 0; i < srcHex.size(); i++)
	{
		switch (toupper(srcHex[i]))
		{
		case '0':
			result += "0000";
			break;
		case '1':
			result += "0001";
			break;
		case '2':
			result += "0010";
			break;
		case '3':
			result += "0011";
			break;
		case '4':
			result += "0100";
			break;
		case '5':
			result += "0101";
			break;
		case '6':
			result += "0110";
			break;
		case '7':
			result += "0111";
			break;
		case '8':
			result += "1000";
			break;
		case '9':
			result += "1001";
			break;
		case 'A':
			result += "1010";
			break;
		case 'B':
			result += "1011";
			break;
		case 'C':
			result += "1100";
			break;
		case 'D':
			result += "1101";
			break;
		case 'E':
			result += "1110";
			break;
		case 'F':
			result += "1111";
			break;
		}
	}

	return result;
}

string IntegerStringUtils::convertBinToHex(string src)
{
	string result;
	string block4Bits;

	while ((src.size() % 4) != 0)
	{
		src = '0' + src;
	}

	for (int i = 0; i < src.size(); i++)
	{
		block4Bits += src[i];

		if ((i + 1) % 4 == 0)
		{
			if (block4Bits == "0000")
			{
				result += '0';
			}
			else if (block4Bits == "0001")
			{
				result += '1';
			}
			else if (block4Bits == "0010")
			{
				result += '2';
			}
			else if (block4Bits == "0011")
			{
				result += '3';
			}
			else if (block4Bits == "0100")
			{
				result += '4';
			}
			else if (block4Bits == "0101")
			{
				result += '5';
			}
			else if (block4Bits == "0110")
			{
				result += '6';
			}
			else if (block4Bits == "0111")
			{
				result += '7';
			}
			else if (block4Bits == "1000")
			{
				result += '8';
			}
			else if (block4Bits == "1001")
			{
				result += '9';
			}
			else if (block4Bits == "1010")
			{
				result += 'A';
			}
			else if (block4Bits == "1011")
			{
				result += 'B';
			}
			else if (block4Bits == "1100")
			{
				result += 'C';
			}
			else if (block4Bits == "1101")
			{
				result += 'D';
			}
			else if (block4Bits == "1110")
			{
				result += 'E';
			}
			else if (block4Bits == "1111")
			{
				result += 'F';
			}

			block4Bits.clear();
		}
	}

	return result;
}

string IntegerStringUtils::convertFractionPartToBin(string srcFrac)
{
	int count = 0;
	string result = "";

	while (count < BIT_IN_SIGNIFICAND)
	{
		bool equalZero = true;
		string newFrac = SUtils::mulOfPositiveIntegerAndTwo(srcFrac);

		if (newFrac.size() > srcFrac.size())
		{
			result += '1';
			srcFrac = newFrac.substr(1, srcFrac.size());
		}
		else
		{
			result += '0';
			srcFrac = newFrac;
		}

		for (int i = 0; i < srcFrac.size(); i++)
		{
			if (srcFrac[i] != '0')
			{
				equalZero = false;
				break;
			}
		}

		if (equalZero)
		{
			break;
		}
	}

	return result;
}


string IntegerStringUtils::divideDecStringByTwo(const string& divisor)
{
	string result;
	int curDivisor = 0;

	for (int i = 0; i < divisor.size(); i++)
	{
		curDivisor = curDivisor * 10 + (divisor[i] - '0');

		if (curDivisor >= 2)						// Nếu số chia hiện tại có thể chia cho 2
		{
			result += (curDivisor / 2) + '0';		// Ghi phần nguyên phép chia vào kết quả
			curDivisor = curDivisor % 2;			// Lấy phần dư của phép chia trên để tiếp tục chia nếu divisor còn chữ số 
		}
		else if (i != 0) {							// Nếu số chia hiện tại không thể chia cho 2 và KHÔNG nằm ở vị trí đầu thì ta viết 0 vào kết quả
			result += '0';							// (vì 0 nằm ở vị trí đầu thì không có ý nghĩa VD: 0911 = 911)
		}
	}

	return result;
}

bool IntegerStringUtils::isNegative(const string& src)
{
	return (src[0] == '-') ? true : false;
}

string IntegerStringUtils::addTwoPositiveIntegerString(string srcA, string srcB)
{
	int lenA, lenB;
	int carry = 0;
	string result = "";

	if (srcA.size() < srcB.size())
	{
		swap(srcA, srcB);
	}

	lenA = srcA.size();
	lenB = srcB.size();

	for (int i = 0; i < lenB; i++)
	{
		int sum = (srcB[lenB - i - 1] - '0') + (srcA[lenA - i - 1] - '0') + carry;
		result = (char)(sum % 10 + '0') + result;
		carry = sum / 10;
	}

	for (int i = 0; i < lenA - lenB; i++)
	{
		int sum = (srcA[lenA - lenB - i - 1] - '0') + carry;
		result = (char)(sum % 10 + '0') + result;
		carry = sum / 10;
	}

	if (carry != 0)
	{
		result = (char)(carry + '0') + result;
	}

	return result;
}

string IntegerStringUtils::mulOfPositiveIntegerAndTwo(string src)
{
	int carry = 0;
	string result = "";

	for (int i = src.size() - 1; i >= 0; i--)
	{
		int mul = (src[i] - '0') * 2 + carry;
		result = (char)(mul % 10 + '0') + result;
		carry = mul / 10;
	}

	if (carry != 0)
	{
		result = (char)(carry + '0') + result;
	}

	return result;
}

string IntegerStringUtils::powerOfTwo(unsigned int exp)
{
	string result = "";
	unsigned int newExp = (exp > SIZE_INT32 - 1) ? SIZE_INT32 - 1 : exp;

	result = to_string((unsigned int)pow(2, newExp));

	for (int i = newExp + 1; i <= exp; i++)
	{
		result = mulOfPositiveIntegerAndTwo(result);
	}

	return result;
}