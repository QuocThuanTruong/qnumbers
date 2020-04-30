#include "IntegerStringUtils.h"
#include "QInt.h"
#include "QFloat.h"

/**
 *	Hàm convertDecToBin - Hàm chuyển dổi chuỗi thập phân sang chuỗi nhị phân
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
		QInt temp(result, 2);							// Chuyển chuỗi kết quả sang QInt	
		temp = QInt::convertToTwoComplement(temp);		// Chuyển QInt sang dạng bù 2
		result = QInt::convertQIntToBin(temp);			// Chuyển QInt bù 2 sang chuỗi nhị phân
	}													

	return result;
}

/**
 *	Hàm convertHexToBin - Hàm chuyển dổi chuỗi thập lục phân sang chuỗi nhị phân
 *	@param	 string		Chuỗi thập lục phân cần chuyển
 *	@return	 string		Chuỗi nhị phân kết quả
 */
string IntegerStringUtils::convertHexToBin(string srcHex)
{
	string result;

	for (int i = 0; i < srcHex.size(); i++)			// Duyệt chuỗi thập lục phân và xét từng giá trị
	{
		switch (toupper(srcHex[i]))					// Gán giá trị nhị phân tương ứng với mã Hex của chuỗi
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

/**
 *	Hàm convertBinToHex - Hàm chuyển dổi chuỗi nhị phân sang thập lục phân
 *	@param	 string		Chuỗi nhị phân cần chuyển
 *	@return	 string		Chuỗi thập lục phân kết quả
 */
string IntegerStringUtils::convertBinToHex(string src)
{
	string result;
	string block4Bits;

	while ((src.size() % 4) != 0)				// Chuẩn hóa chuỗi thành các cụm 4 bit bằng cahcs thêm 0 vào đầu chuỗi 
	{
		src = '0' + src;
	}

	for (int i = 0; i < src.size(); i++)		// Duyệt chuỗi
	{
		block4Bits += src[i];					// Và gán giá trị nhị phân vào block 4 bit

		if ((i + 1) % 4 == 0)					// Nếu đủ block 4 bit thì ta xét giá trị và chuyển thành mã Hex tương ứng
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

			block4Bits.clear();							// Đã chuyển xong, xóa giá trị để nhận block khác
		}
	}

	return result;
}

/**
 *	Hàm convertFractionPartToBin - Hàm chuyển dổi phần thập phân của số thực sang nhị phân
 *	@param	 string		Phần chuỗi thập phân cần chuyển
 *	@return	 string		Chuỗi nhị phân kết quả
 */
string IntegerStringUtils::convertFractionPartToBin(string srcFrac)
{
	int count = 0;															// Biến đếm bit (chỉ lấy đủ 112 bits)
	string result = "";

	while (count < BIT_IN_SIGNIFICAND)										// Lặp lại đến khi đủ 112 bits
	{
		bool equalZero = true;
		string newFrac = SUtils::mulOfPositiveIntegerAndTwo(srcFrac);		// Lấy phần thập phân nhân cho 2

		if (newFrac.size() > srcFrac.size())								// Nếu chiều dài kết quả nhân được lớn hơn chuỗi cũ thì kết quả nhị phân tại bit đó là 1
		{
			result += '1';													// VD: 5 (0.5) x 2 = 10 (1.0) -> 10.size > 5.size
			srcFrac = newFrac.substr(1, srcFrac.size());					// Bỏ 1 đi lấy phần còn lại nhân tiếp
		}
		else																// Ngược lại độ dài chuỗi không thay đổi thì kết quả nhị phân là 0
		{
			result += '0';													// VD: 25 (0.25) x 2 = 50 (0.5)
			srcFrac = newFrac;												// Tiếp tục lấy chuỗi tính được nhân tiếp
		}

		for (int i = 0; i < srcFrac.size(); i++)							// Kiểm tra xem chuỗi tính được có bằng 0 hay không (toàn số 0)
		{
			if (srcFrac[i] != '0')
			{
				equalZero = false;
				break;
			}
		}

		if (equalZero)														// Nếu chuỗi tính được toàn 0 tức là ta tính được kết quả là 1.0 -> Điều kiện dừng
		{
			break;															// VD: 25 x 2 = 50 -> 50 x 2 = 100 (1.0) bỏ 1 đi còn lại 00 -> chuỗi toàn 0 -> Dừng
		}

		count++;
	}

	return result;
}

/**
 *	Hàm divideDecStringByTwo - Hàm chia số nguyên ở dạng thập phan cho 2
 *	@param	 string		Chuỗi số chia
 *	@return	 string		Chuỗi kết quả
 */
string IntegerStringUtils::divideDecStringByTwo(const string& divisor)
{
	string result;
	int curDivisor = 0;

	for (int i = 0; i < divisor.size(); i++)
	{
		curDivisor = curDivisor * 10 + (divisor[i] - '0');

		if (curDivisor >= 2)								// Nếu số chia hiện tại có thể chia cho 2
		{
			result += (curDivisor / 2) + '0';				// Ghi phần nguyên phép chia vào kết quả
			curDivisor = curDivisor % 2;					// Lấy phần dư của phép chia trên để tiếp tục chia nếu divisor còn chữ số 
		}
		else if (i != 0) {									// Nếu số chia hiện tại không thể chia cho 2 và KHÔNG nằm ở vị trí đầu thì ta viết 0 vào kết quả
			result += '0';									// (vì 0 nằm ở vị trí đầu thì không có ý nghĩa VD: 0911 = 911)
		}
	}

	return result;
}

/**
 *	Hàm isNegative - Hàm kiểm tra chuỗi số đã cho có âm hay không
 *	@param	 string		Chuỗi cần kiểm tra
 *	@return	 bool		Kết quả kiểm tra
 */
bool IntegerStringUtils::isNegative(const string& src)
{
	return (src[0] == '-') ? true : false;
}

/**
 *	Hàm addTwoPositiveIntegerString - Hàm cộng hai chuỗi số dương
 *	@param	 string		Chuỗi A
 *	@param	 string		Chuỗi B
 *	@return	 string		Kết quả chuỗi A + B
 */
string IntegerStringUtils::addTwoPositiveIntegerString(string srcA, string srcB)
{
	int lenA, lenB;
	int carry = 0;					
	string result = "";

	if (srcA.size() < srcB.size())						// Nếu chiều dài A < B thì hoán vị vì ta mặc định chiều dài A luôn lớn hơn B
	{
		swap(srcA, srcB);
	}

	lenA = srcA.size();
	lenB = srcB.size();

	for (int i = 0; i < lenB; i++)						// Cộng chuỗi B cho A (vì len A dài hơn)
	{
		int sum = (srcB[lenB - i - 1] - '0') + (srcA[lenA - i - 1] - '0') + carry;		
		result = (char)(sum % 10 + '0') + result;
		carry = sum / 10;
	}

	for (int i = 0; i < lenA - lenB; i++)				// Cộng phần còn lại của chuỗi A cho biến nhớ
	{
		int sum = (srcA[lenA - lenB - i - 1] - '0') + carry;
		result = (char)(sum % 10 + '0') + result;
		carry = sum / 10;
	}

	if (carry != 0)										// Nếu sau khi cộng vẫn còn biến nhớ thì viết nó lên đầu kết quả
	{
		result = (char)(carry + '0') + result;
	}

	return result;
}

/**
 *	Hàm mulOfPositiveIntegerAndTwo - Hàm nhân chuỗi số dương cho 2
 *	@param	 string		Chuỗi cân nhân
 *	@return	 string		Kết quả chuỗi x 2
 */
string IntegerStringUtils::mulOfPositiveIntegerAndTwo(string src)
{
	int carry = 0;
	string result = "";

	for (int i = src.size() - 1; i >= 0; i--)		// Lần luọt nhân 2 cho từng số ở chuỗi A nếu có nhớ thì cộng biến nhớ
	{
		int mul = (src[i] - '0') * 2 + carry;
		result = (char)(mul % 10 + '0') + result;	
		carry = mul / 10;
	}

	if (carry != 0)									// Nếu sau khi nhân vẫn còn biến nhớ thì ghi vào đầu kết quả
	{
		result = (char)(carry + '0') + result;
	}

	return result;
}

/**
 *	Hàm powerOfTwo - Hàm tính 2^exp
 *	@param	 unsigned int 		Số mũ không dấu
 *	@return	 string				Chuỗi kết quả 2^exp
 */
string IntegerStringUtils::powerOfTwo(unsigned int exp)
{
	string result = "";
	unsigned int newExp = (exp > SIZE_INT32 - 1) ? SIZE_INT32 - 1 : exp;	// Nếu mũ lớn hơn phạm vi tính được ta chia mũ thành 2 phần:
																			// Phần new tính được bằng hàm pow và phần còn lại bằng cách cộng dồn cho chính nó x 2
	result = to_string((unsigned int)pow(2, newExp));						// Chọn 31 vì ta có số nguyên không dấu lớn nhất là 2^32 - 1
																			// VD: 2^34 = 2^31x2x2x2
	for (int i = newExp + 1; i <= exp; i++)
	{
		result = mulOfPositiveIntegerAndTwo(result);
	}

	return result;
}

/**
 *	Hàm mulOfPositiveIntegerAndFive - Hàm nhân chuỗi số dương cho 5
 *	@param	 string		Chuỗi cân nhân
 *	@return	 string		Kết quả chuỗi x 5
 */
string IntegerStringUtils::mulOfPositiveIntegerAndFive(string src)
{
	int carry = 0;
	string result = "";

	for (int i = src.size() - 1; i >= 0; i--)			// Lần luọt nhân 5 cho từng số ở chuỗi A nếu có nhớ thì cộng biến nhớ
	{
		int mul = (src[i] - '0') * 5 + carry;
		result = (char)(mul % 10 + '0') + result;
		carry = mul / 10;
	}

	if (carry != 0)										// Nếu sau khi nhân vẫn còn biến nhớ thì ghi vào đầu kết quả
	{
		result = (char)(carry + '0') + result;
	}

	return result;
}
