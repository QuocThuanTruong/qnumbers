#include "QFloat.h"

QFloat::QFloat()
{
	for (int i = 0; i < TOTAL_BLOCK; i++)
	{
		this->data[i] = 0;
	}
}

QFloat::QFloat(const string& src, const int base)
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

QFloat::~QFloat()
{
}

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
 *	Ham convertDecToQFloat - Hàm chuyển đổi chuỗi thập phân sang số QFloat ( số chấm động chính xác cao )
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

	if (srcDec == "0")                         // Nếu chuỗi là 0 -> trả về dãy bit toàn 0  
	{
		return result;
	}
	else
	{
		if (srcDec[0] == '-')                 // Xét dấu, nếu âm thì setbit dấu = 1 là bit thứ 127 và bỏ đi
		{
			srcDec.erase(0, 1);
		}
	}

	if (srcDec.find('.', 0) == string::npos)  // Tìm vị trí ngăn cách phần nguyên và phần thật phân
	{
		srcDec += ".0";                       // Nếu không tồn tại phần thập phân thì thêm .0 vào
	}

	posOfDot = srcDec.find('.', 0);          // Vị trí chia phần nguyên và thập phân ( dấu . )
	intPartDec = srcDec.substr(0, posOfDot); // Phần nguyên
	fracPartDec = srcDec.substr(posOfDot + 1, srcDec.size() - posOfDot - 1);  // Phần thập phân

	if (intPartDec != "0")                   // Trường hợp 1: Phần nguyên là 0
	{
		intPartBin = SUtils::convertDecToBin(intPartDec);   // Chuyển phần nguyên về nhị phân
		fracPartBin = SUtils::convertFractionPartToBin(fracPartDec);  // Chuyển phần thập phân về nhị phân

		exp = intPartBin.size() - 1;  // Số mũ

		if (exp > BIAS)     // Tránh tràn số ( BIAS là miền giá trị = 2^(15-1)-1
		{
			exp = BIAS;
		}

		if (exp == 0)    // Trường hợp mũ  = 0
		{
			srcSignificandBin = fracPartBin; // Không cần dịch, chuổi Significand ( định trị ) chính là phần nhị phân phía sau
		}
		else
		{
			// Ngược lại thì chuỗi Significand = phần nhị phân của phần nguyên ( bỏ đi 1 ở đầu ) + phần nhị phân của phần thập phân
			srcSignificandBin = intPartBin.substr(1, exp) + fracPartBin;
		}

		exp = exp + BIAS;   // Chuyển số mũ về số quá K
	}
	else      // Trường hợp 2: Phần nguyên là 0
	{
		// Tìm số 1 đầu tiên để đưa về dạng 1.F * 2^E
		while (exp < BIAS) 
		{
			exp++;
			string newFracDec = SUtils::mulOfPositiveIntegerAndTwo(fracPartDec); // Chuỗi tạm bằng chuỗi hiện tại nhân cho 2 

			if (newFracDec.size() > fracPartDec.size()) // So sánh 2 chuỗi, khi mà chuỗi tạm > chuỗi hiện tại tức > 1 
				                                       //thì ta lấy phần sau làm chuỗi hiện tại
			{                                         // ví dụ chuỗi hiện tại là 75 -> chuỗi tạm = 75*2=150 ->size lớn hơn chuỗi hiện tại 
				fracPartDec = newFracDec.substr(1, fracPartDec.size());  // -> tức là > 1 -> lấy 50 làm chuỗi hiện tại
				break;
			}
			else            // Ngược lại lấy gán thằng tạm cho thằng hiện tại khi chưa vượt quá 1
			{
				fracPartDec = newFracDec;  
			}
		}

		exp = BIAS - exp; // Đưa mũ về số quá K (- exp bởi vì mũ tìm được là dương nhưng dịch số qua trái thì phải nhân cho số mũ âm )
		srcSignificandBin = SUtils::convertFractionPartToBin(fracPartDec); // Chuyển về nhị phân
	}

	srcExpBin = SUtils::convertDecToBin(to_string(exp)); // chuyển số mũ về nhị phân

	// Nếu số mũ chưa đầy 15 số thì phải thêm 0 vào trước để đủ 15 số
	while (srcExpBin.size() < BIT_IN_EXP) 
	{
		srcExpBin = '0' + srcExpBin;
	}

	// Nếu phần định trị lớn hơn 112 bits thì chỉ lấy 112 bits
	if (srcSignificandBin.size() > BIT_IN_SIGNIFICAND)
	{
		srcSignificandBin = srcSignificandBin.substr(0, BIT_IN_SIGNIFICAND);
	}

	// Set bit cho phần mũ
	for (int i = 0; i < srcExpBin.size(); i++)
	{
		if (srcExpBin[i] == '1')
		{
			BUtils::setBit(result.data, (BIT_IN_QFLOAT - 1) - 1 - i);
		}
	}

	// Set bit cho phần định trị
	for (int i = 0; i < srcSignificandBin.size(); i++)
	{
		if (srcSignificandBin[i] == '1')
		{
			BUtils::setBit(result.data, BIT_IN_SIGNIFICAND - 1 - i);
		}
	}

	return result;
}

QFloat QFloat::convertBinToQFloat(const string& src)
{
	QFloat result;

	for (int i = 0; i < src.size(); i++)
	{
		if (src[i] == '1')
		{
			BUtils::setBit(result.data, src.size() - i - 1);
		}
	}

	return result;
}

string QFloat::convertQFloatToDec(QFloat src)
{
	return string();
}

string QFloat::convertQFloatToBin(QFloat src)
{
	string result = "";

	for (int i = 0; i < BIT_IN_QFLOAT; i++)
	{
		result = (char)(BUtils::getBit(src.data, i) + '0') + result;
	}

	return result;
}