#include "QFloat.h"
/**
 *	Constructor QFloat - Hàm khởi tạo mặc định QFloat = 0
 *	@param	 none
 *	@return	 none
 */
QFloat::QFloat()
{
	for (int i = 0; i < TOTAL_BLOCK; i++)
	{
		this->data[i] = 0;
	}
}

/**
 *	Constructor QFloat - Hàm khởi tạo QFloat từ chuỗi số truyền vào với cơ số thích hợp
 *	@param	 const string&		Chuỗi số cần chuyển thành QInt
 *	@param	 const int			Hệ cơ số của chuỗi
 *	@return	 none
 */
QFloat::QFloat(const string& src, const int base)
{
	switch (base)										// Gọi hàm chuyển với hệ cơ số tương ứng
	{
	case 2:
		*this = QFloat::convertBinToQFloat(src);
		break;
	case 10:
		*this = QFloat::convertDecToQFloat(src);
		break;
	}
}

/**
 *	Destructor QFloat - Hàm hủy mặc định
 *	@param	 none
 *	@return	 none
 */
QFloat::~QFloat()
{
}

/**
 *	Hàm scanQFloat - Hàm nhập QFloat từ chuỗi với hệ cơ số tương ứng
 *	@param	 const string&		Chuỗi cần chuyển
 *	@param	 const int			Hệ cơ số của chuỗi
 *	@return	 none
 */
void QFloat::scanQFloat(const string& src, const int base)
{
	switch (base)
	{
	case 2:
		*this = QFloat::convertBinToQFloat(src);
		break;
	case 10:
		*this = QFloat::convertDecToQFloat(src);
		break;
	}
}

/**
 *	Hàm printQFloat - Hàm nhập xuất QFloat theo hệ cơ số tương ứng
 *	@param	 const int			Hệ cơ số cần xuất
 *	@return	 none
 */
void QFloat::printQFloat(const int base)
{
	switch (base)
	{
	case 2:
		cout << QFloat::convertQFloatToBin(*this) << endl;
		break;
	case 10:
		cout << QFloat::convertQFloatToDec(*this) << endl;
		break;
	}
}

/**
 *	Ham convertDecToQFloat - Hàm chuyển đổi chuỗi thập phân sang số QFloat
 *	@param	 string		Chuỗi thập phân cần chuyển
 *	@return	 QFloat	    Số QFloat 
 */
QFloat QFloat::convertDecToQFloat(const string& src)
{
	int posOfDot;
	int exp = 0;
	QFloat result;
	string intPartDec;
	string fracPartDec;
	string intPartBin;
	string fracPartBin;
	string srcExpBin;
	string srcSignificandBin = "";
	string srcDec = src;

	if (srcDec == "0")												// Nếu số đã cho là 0 thì trả về kết quả
	{
		return result;
	}
	else
	{
		if (srcDec[0] == '-')										// Xét dấu, nếu âm thì setbit dấu = 1 là bit thứ 127 và bỏ đi
		{
			BUtils::setBit(result.data, BIT_IN_QFLOAT - 1);
			srcDec.erase(0, 1);
		}
	}

	if (srcDec.find('.', 0) == string::npos)
	{
		srcDec += ".0";												// Nếu không tồn tại phần thập phân thì thêm .0 vào
	}

	posOfDot = srcDec.find('.', 0);
	intPartDec = srcDec.substr(0, posOfDot);
	fracPartDec = srcDec.substr(posOfDot + 1, srcDec.size() - posOfDot - 1);

	if (intPartDec != "0")																// Trường hợp 1: Phần nguyên là 0
	{
		intPartBin = SUtils::convertDecToBin(intPartDec);								// Chuyển phần nguyên về nhị phân
		fracPartBin = SUtils::convertFractionPartToBin(fracPartDec);				    // Chuyển phần thập phân về nhị phân

		if (fracPartBin.find('.', 0) != string::npos)									// Nếu phần phân số làm tròn tràn lên phần thập phân thì lây phần thập phân + thêm 1	
		{
			fracPartBin = fracPartBin.substr(2, BIT_IN_SIGNIFICAND);					// Lấy phần phân số
			intPartBin = QInt::convertQIntToBin(QInt(intPartBin, 2) + QInt("1", 10));	// VD: 1010.1111 -> Làm tròn 1011.0000
		}
	
		exp = intPartBin.size() - 1;			
		
		if (exp > BIAS)																	// Tránh tràn số ( vì mũ dương lớn nhất là BIAS) ->  Đây là số Inf
		{
			exp = BIAS;
		}

		if (exp == 0)																	// Trường hợp mũ  = 0
		{
			srcSignificandBin = fracPartBin;											// Không cần dịch, chuổi Significand ( định trị ) chính là phần nhị phân phía sau
		}
		else																			// Ngược lại thì chuỗi Significand = phần nhị phân của phần nguyên ( bỏ đi 1 ở đầu ) + phần nhị phân của phần thập phân
		{
			srcSignificandBin = intPartBin.substr(1, exp) + fracPartBin;
		}

		exp = exp + BIAS;																// Chuyển số mũ về số quá K
	}
	else																				// Trường hợp 2: Phần nguyên là 0
	{
		while (exp < BIAS - 1)															// Tìm số 1 đầu tiên để đưa về dạng 1.F * 2^E nếu exp > BIAS - 1 thì nó là số không thể chuẩn hóa -> Dạng 0.F*2^-16382
		{
			exp++;
			string newFracDec = SUtils::mulOfPositiveIntegerAndTwo(fracPartDec);		// Chuỗi tạm bằng chuỗi hiện tại nhân cho 2 

			if (newFracDec.size() > fracPartDec.size())									// So sánh 2 chuỗi, khi mà chuỗi tạm > chuỗi hiện tại (tức là số thập phân khi nhân > 1) 																					
			{																			// thì ta lấy phần sau làm chuỗi hiện tạiví dụ chuỗi hiện tại là 75 -> chuỗi tạm = 75*2=150 ->size lớn hơn chuỗi hiện tại 
				fracPartDec = newFracDec.substr(1, fracPartDec.size());					// -> tức là > 1 (150 = 1.5) -> lấy 50 làm chuỗi hiện tại
				break;
			}
			else																		// Ngược lại lấy gán thằng tạm cho thằng hiện tại khi chưa vượt quá 1
			{
				fracPartDec = newFracDec; 
			}
		}
		
		srcSignificandBin = SUtils::convertFractionPartToBin(fracPartDec);				// Chuyển phần định trị về nhị phân

		if (srcSignificandBin.find('.', 0) != string::npos)								// Nếu làm tròn lên tràn qua phần thập phân thì mũ + 1
		{
			exp++;
			srcSignificandBin = srcSignificandBin.substr(2, BIT_IN_SIGNIFICAND);		// Bỏ phần thập phân bị tràn VD: 0.11 làm tròn lên là 1.00 ta tăng mũ, và phần phân số sẽ là 00
		}

		exp = (exp == BIAS - 1) ? BIAS - 1 - exp : BIAS - exp;							// Chuyển số mũ về số quá K nếu là số không chuẩn hóa thì mũ = 0
	}

	srcExpBin = SUtils::convertDecToBin(to_string(exp));								// Chuyển phần mũ về dạng nhị phân

	while (srcExpBin.size() < BIT_IN_EXP)												// Nếu số mũ chưa đầy 15 số thì phải thêm 0 vào trước để đủ 15 số
	{
		srcExpBin = '0' + srcExpBin;
	}

	if (srcSignificandBin.size() > BIT_IN_SIGNIFICAND)									// Nếu phần định trị lớn hơn 112 bits thì chỉ lấy 112 bits
	{
		srcSignificandBin = srcSignificandBin.substr(0, BIT_IN_SIGNIFICAND);
	}

	for (int i = 0; i < srcExpBin.size(); i++)											// Set bit cho phần mũ
	{
		if (srcExpBin[i] == '1')
		{
			BUtils::setBit(result.data, (BIT_IN_QFLOAT - 1) - 1 - i);
		}
	}

	for (int i = 0; i < srcSignificandBin.size(); i++)									// Set bit cho phần định trị
	{
		if (srcSignificandBin[i] == '1')
		{
			BUtils::setBit(result.data, BIT_IN_SIGNIFICAND - 1 - i);
		}
	}

	return result;
}

/**
 *	Hàm convertBinToQFloat - Hàm chuyển chuỗi nhị phân sang QFloat
 *	@param	 const string&		Chuỗi nhị phân cần chuyển
 *	@return	 QFloat				Số QFloat kết quả
 */
QFloat QFloat::convertBinToQFloat(const string& src)
{
	QFloat result;													// result mặc định toàn bit 0

	for (int i = 0; i < src.size(); i++)							// Duyệt chuỗi và set bit tương ứng cho QInt (chỉ set bit 1)
	{
		if (src[i] == '1')
		{
			BUtils::setBit(result.data, src.size() - i - 1);
		}
	}

	return result;
}

/**
 *	Hàm convertQFloatToDec - Hàm chuyển QFloat sang chuỗi thập phân
 *	@param	 QFloat		Số QFloat cần chuyển
 *	@return	 string		Chuỗi thập phân
 */
string QFloat::convertQFloatToDec(QFloat src)
{
	int exp;
	int posOfLastOne;
	string result;
	string intPartBin;
	string fracPartBin;
	string intPartDec;
	string fracPartDec;
	string srcBin = QFloat::convertQFloatToBin(src);									// Chuyển QFloat sang chuỗi nhị phân
	string srcSign = (srcBin[0] == '1') ? "-" : "";										// Xét dấu cho chuỗi nhị phân đã chuyển
	string srcExpBin = srcBin.substr(1, BIT_IN_EXP);									// Lấy phần mũ exp
	string srcSignificandBin = srcBin.substr(BIT_IN_EXP + 1, BIT_IN_SIGNIFICAND);		// Lấy phần định trị significand

	if (QFloat::isZero(srcExpBin, srcSignificandBin))									// Trả về "0" nếu số đã cho là 0
	{
		return "0";
	}

	if (QFloat::isInfinity(srcExpBin, srcSignificandBin))								// Trả về "Inf" nếu số đã cho là vô cực
	{
		return "Inf";
	}

	if (QFloat::isNaN(srcExpBin, srcSignificandBin))									// Trả về "NaN" nếu số đã cho không phải là số
	{
		return "NaN";
	}

	if (QFloat::isDernomalized(srcExpBin, srcSignificandBin) == true)					// Nếu là số không chuẩn hóa thì đưa về dạng 0.F*2^-16382
	{
		exp = stoi(srcExpBin, nullptr, 2) - (BIAS - 1);									// Theo IEEE 754 Exp min = -16382
		intPartBin = "0";
	}
	else																				// Nếu là số chuẩn hóa thì có dạng 1.F*2^E
	{
		exp = stoi(srcExpBin, nullptr, 2) - BIAS;
		intPartBin = "1";
	}

	fracPartBin = srcSignificandBin;													// Phần phân số ở dạng nhị phân

	while (exp != 0)																	// Dời dấu chấm động (làm cho exp == 0)
	{
		if (exp < 0)																	// Nếu mũ âm thì dời dấu chấm sang trái
		{
			if (intPartBin.size() > 0)													// Dời phần nguyên sang phần phân số
			{
				fracPartBin = intPartBin[intPartBin.size() - 1] + fracPartBin;
				intPartBin.erase(intPartBin.size() - 1, 1);
			}
			else																		// Nếu phần nguyên đã hết thì chèn 0 vào đầu phần phân số
			{
				fracPartBin = '0' + fracPartBin;
			}
			exp++;																		
		}
		else																			// Ngược lại mũ dương thì dời dấu chấm sang phải
		{
			if (fracPartBin.size() > 0)													// Dời phần phân số sang phần nguyên
			{
				intPartBin += fracPartBin[0];
				fracPartBin.erase(0, 1);
			}
			else																		// Nếu phần âm đã hết thì phần nguyên thêm 0 vào phía sau 
			{
				intPartBin += '0';
			}
			exp--;
		}
	}

	if (intPartBin.size() == 0)															// Nếu phần nguyên hết thì thêm 0 vào, tức là 0.xxx
	{
		intPartBin += '0';
	}

	if (fracPartBin.size() == 0)														// Nếu phần phân số hết thì thêm 0 vào, tức là xxx.0
	{
		fracPartBin += '0';
	}

	intPartDec = QInt::convertQIntToDec(QInt(intPartBin, 2));							// Chuyển phần nguyên về thập phân

	posOfLastOne = fracPartBin.find_last_of('1');										// Tìm số 1 cuối cùng ở phần phân số để chuyển về thập phân

	if (posOfLastOne != string::npos)													// Nếu tìm đuọc thì bắt đầu chuyển theo công thức dựa vào ví dụ sau
	{																					// 0.1011 -> Dec, lấy 0.5(1 + 0) = 0.5 -> 0.5(1 + 0.5) = 0.75 -> 0.5(0 + 0.75) = 0.375 -> 0.5(1 + 0.375) = 0.6875
		fracPartDec = "";																// Bắt đầu là				  0

		for (int i = posOfLastOne; i >= 0; i--)											// Duyệt các số tiếp theo đến đầu chuỗi
		{																				// Độ dài thực tế khi nhân 2 số thực: VD: 5(0.5) x 5(0.5) = 25(0.25) -> expectedLen = 2
			int expectedLen = posOfLastOne - i + 1;										// Độ dài tăng lên 1 mỗi lần lặp vì ta nhân thêm 0.5 cho nó:  5 x 25 = 125 -> expectedLen = 3
																						
			if (fracPartBin[i] == '1')													// Nếu là bit 1 thì ta cộng 1 + phần phân số đã nhân phía trước như ví dụ
			{
				fracPartDec = '1' + fracPartDec;
			}

			fracPartDec = SUtils::mulOfPositiveIntegerAndFive(fracPartDec);				// Nhân phần phân số cho 5 (0.5)

			for (int i = 0; i < expectedLen - fracPartDec.size(); i++)					// Nếu chuỗi kết quả < expectedLen, ta thêm 0 và đầu vì nếu tính theo số thực: 0.5 x 0.125 = 0.0625
			{																			// Nhưng khi tính ở đây ta chỉ lấy 5 x 125 = 625 -> thiếu số 0
				fracPartDec = '0' + fracPartDec;										 
			}
		}

		fracPartDec = '.' + fracPartDec;												// Thêm dấu '.' ở đầu chuỗi
	}
	else
	{
		fracPartDec = "";																// Không tìm được số '1' -> phần phân số không có (xxx.0)
	}

	result = srcSign + intPartDec + fracPartDec;										// Kết quả sẽ là tổng của dấu + phần nguyên + phần phân số

	return result;
}

/**
 *	Hàm convertQFloatToBin - Hàm chuyển QFloat sang chuỗi nhị phân
 *	@param	 QFloat		Số QFloat cần chuyển
 *	@return	 string		Chuỗi nhị phân
 */
string QFloat::convertQFloatToBin(QFloat src)
{
	string result = "";

	for (int i = 0; i < BIT_IN_QFLOAT; i++)								// Lấy từng bit ra và gán cho kết quả
	{
		result = (char)(BUtils::getBit(src.data, i) + '0') + result;
	}

	return result;
}

/**
 *	Hàm isZero - Hàm kiểm tra số đã cho có phải là số 0
 *	@param	 string		phần mũ ở dạng nhị phân
 *	@param	 string		phần định trị ở dạng nhị phân
 *	@return	 bool		Kết quả kiểm tra
 */
bool QFloat::isZero(string srcExpBin, string srcSignificandBin)
{
	for (int i = 0; i < srcExpBin.size(); i++)				// Kiểm tra toàn 0 phần mũ
	{
		if (srcExpBin[i] == '1')
		{
			return false;
		}
	}

	for (int i = 0; i < srcSignificandBin.size(); i++)		// Kiểm tra toàn 0 phần định trị
	{
		if (srcSignificandBin[i] == '1')
		{
			return false;
		}
	}

	return true;
}

/**
 *	Hàm isDernomalized - Hàm kiểm tra số đã cho có phải là số không chuẩn hóa
 *	@param	 string		phần mũ ở dạng nhị phân
 *	@param	 string		phần định trị ở dạng nhị phân
 *	@return	 bool		Kết quả kiểm tra
 */
bool QFloat::isDernomalized(string srcExpBin, string srcSignificandBin)
{
	for (int i = 0; i < srcExpBin.size(); i++)			// Kiểm tra toàn 0
	{
		if (srcExpBin[i] == '1')
		{
			return false;
		}
	}

	return (QFloat::isZero(srcExpBin, srcSignificandBin) == true) ? false : true;		// Nếu phần mũ toàn 0 và không phải là số 0 thì là số không chuẩn hóa
}

/**
 *	Hàm isInfinity - Hàm kiểm tra số đã cho có phải là số vô cực
 *	@param	 string		phần mũ ở dạng nhị phân
 *	@param	 string		phần định trị ở dạng nhị phân
 *	@return	 bool		Kết quả kiểm tra
 */
bool QFloat::isInfinity(string srcExpBin, string srcSignificandBin)
{
	for (int i = 0; i < srcExpBin.size(); i++)					// Kiểm tra toàn 1 phần mũ
	{
		if (srcExpBin[i] == '0')
		{
			return false;
		}
	}

	for (int i = 0; i < srcSignificandBin.size(); i++)			// Kiểm tra toàn 1 phần định trị
	{
		if (srcSignificandBin[i] == '1')
		{
			return false;
		}
	}

	return true;
}

/**
 *	Hàm isNaN - Hàm kiểm tra số đã cho có phải là NaN
 *	@param	 string		phần mũ ở dạng nhị phân
 *	@param	 string		phần định trị ở dạng nhị phân
 *	@return	 bool		Kết quả kiểm tra
 */
bool QFloat::isNaN(string srcExpBin, string srcSignificandBin)
{
	for (int i = 0; i < srcExpBin.size(); i++)			// Kiểm tra toàn 1
	{
		if (srcExpBin[i] == '0')
		{
			return false;
		}
	}

	return (QFloat::isInfinity(srcExpBin, srcSignificandBin) == true) ? false : true;		// Nếu phân mũ toàn 1 và không phải là vô cực thì là NaN
}