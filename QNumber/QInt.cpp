#include "QInt.h"

/**
 *	Constructor QInt - Hàm khởi tạo mặc định QInt = 0
 *	@param	 none
 *	@return	 none
 */
QInt::QInt()
{
	for (int i = 0; i < TOTAL_BLOCK; i++)		//Khởi tạo mỗi block bằng 0
	{
		this->data[i] = 0;
	}
}

/**
 *	Constructor QInt - Hàm khởi tạo QInt từ chuỗi số truyền vào với cơ số thích hợp
 *	@param	 const string&		Chuỗi số cần chuyển thành QInt
 *	@param	 const int			Hệ cơ số của chuỗi
 *	@return	 none
 */ 
QInt::QInt(const string& src, const int base)
{
	switch (base)
	{
	case 2:
		*this = QInt::convertBinToQInt(src);
		break;
	case 10:
		*this = QInt::convertDecToQInt(src);
		break;
	case 16:
		*this = QInt::convertHexToQInt(src);
		break;
	}

}

QInt::~QInt()
{
}

void QInt::scanQInt(const string& src, const int base)
{
	switch (base)
	{
	case 2:
		*this = QInt::convertBinToQInt(src);
		break;
	case 10:
		*this = QInt::convertDecToQInt(src);
		break;
	case 16:
		*this = QInt::convertHexToQInt(src);
		break;
	}
}

void QInt::printQInt(const int base)
{
	switch (base)
	{
	case 2:
		cout << QInt::convertQIntToBin(*this) << endl;
		break;
	case 10:
		cout << QInt::convertQIntToDec(*this) << endl;
		break;
	case 16:
		cout << QInt::convertQIntToHex(*this) << endl;
		break;
	}
}

string QInt::convertQIntToBin(QInt src)
{
	string result = "";

	for (int i = 0; i < BIT_IN_QINT; i++)
	{
		result = (char)(BUtils::getBit(src.data, i) + '0') + result;
	}

	while (result[0] == '0' && result.size() > 1)
	{
		result.erase(0, 1);
	}

	return result;
}

string QInt::convertQIntToDec(QInt src)
{
	string srcBin;
	string result = "0";

	if (src.isNegative())
	{
		src = QInt::inverseTwoComplement(src);
	}

	for (int i = 0; i < BIT_IN_QINT; i++)
	{
		if (BUtils::getBit(src.data, i) == 1)
		{
			result = SUtils::addTwoPositiveIntegerString(result, SUtils::powerOfTwo(i));
		}
	}

	return result;
}

string QInt::convertQIntToHex(QInt src)
{
	return SUtils::convertBinToHex(QInt::convertQIntToBin(src));
}

QInt QInt::convertBinToQInt(const string& src)
{
	QInt result;

	for (int i = 0; i < src.size(); i++)
	{
		if (src[i] == '1')
		{
			BUtils::setBit(result.data, src.size() - i - 1);
		}
	}

	return result;
}

QInt QInt::convertDecToQInt(const string& src)
{
	return QInt::convertBinToQInt(SUtils::convertDecToBin(src));
}

QInt QInt::convertHexToQInt(const string& src)
{
	return QInt::convertBinToQInt(SUtils::convertHexToBin(src));
}

bool QInt::isNegative()
{
	return BUtils::getBit(this->data, BIT_IN_QINT - 1);
}

bool QInt::equalZero()
{
	for (int i = 0; i < TOTAL_BLOCK; i++)
	{
		if (this->data[i] != 0)
		{
			return false;
		}
	}

	return true;
}

QInt QInt::convertToTwoComplement(QInt src)
{
	return ~src + QInt("1", 10);
}

QInt QInt::inverseTwoComplement(QInt src)
{
	return ~(src - QInt("1", 10));
}

QInt QInt::operator+(const QInt& other)
{
	return QInt();
}

QInt QInt::operator-(const QInt& other)
{
	return QInt();
}

QInt QInt::operator*(const QInt& other)
{
	return QInt();
}

QInt QInt::operator/(const QInt& other)
{
	return QInt();
}

bool QInt::operator>(const QInt& other)
{
	return false;
}

bool QInt::operator<(const QInt& other)
{
	return false;
}

bool QInt::operator==(const QInt& other)
{
	return false;
}

bool QInt::operator!=(const QInt& other)
{
	return false;
}

bool QInt::operator>=(const QInt& other)
{
	return false;
}

bool QInt::operator<=(const QInt& other)
{
	return false;
}

QInt& QInt::operator=(const QInt& other)
{
	if (other.data == this->data)
	{
		return *this;
	}

	for (int i = 0; i < TOTAL_BLOCK; i++)
	{
		this->data[i] = other.data[i];
	}

	return *this;
}


/**
 *	Toán tử AND - &
 *	@param	 const QInt&	số QInt truyền vào để thực hiện phép &	
 *	@return	 QInt			abcxyz
 */
QInt QInt::operator&(const QInt& other)
{
	QInt result;

	for (int i = 0; i < TOTAL_BLOCK; i++)
	{
		result.data[i] = this->data[i] & other.data[i];
	}

	return result;
}


/**
 *	operator| - Toán tử OR
 *	@param	 const QInt&	số QInt truyền vào để thực hiện phép |
 *	@return	 QInt			kết quả sau khi thực hiện phép |
 */
QInt QInt::operator|(const QInt& other)
{
	QInt result;

	for (int i = 0; i < TOTAL_BLOCK; i++)
	{
		result.data[i] = this->data[i] | other.data[i];
	}

	return result;
}


/**
 *	Toán tử XOR - ^
 *	@param	 const QInt& - số QInt truyền vào để thực hiện phép ^
 *	@return	 QInt
 */
QInt QInt::operator^(const QInt& other)
{
	QInt result;

	for (int i = 0; i < TOTAL_BLOCK; i++)
	{
		result.data[i] = this->data[i] ^ other.data[i];
	}

	return result;
}


/**
 *	Toán tử NOT - ~
 *	@param	 none 
 *	@return	 QInt
 */
QInt QInt::operator~() const
{
	QInt result;

	for (int i = 0; i < TOTAL_BLOCK; i++)
	{
		result.data[i] = ~(this->data[i]);
	}

	return result;
}


/**
 *	Toán tử dịch phải - >>
 *	@param	 const int& - số lượng bit dịch
 *	@return	 QInt
 */
QInt QInt::operator>>(const int& offset)
{
	QInt result;

	for (int i = offset; i < BIT_IN_QINT; i++)
	{
		bool temp = BUtils::getBit(this->data, i);
		BUtils::setBit(result.data, i - offset, temp); 
	}

	return result;
}


/**
 *	operator<< - Toán tử dịch trái
 *	@param	 const int&		số lượng bit dịch
 *	@return	 QInt			abxyz
 */
QInt QInt::operator<<(const int& offset)
{
	QInt result;

	for (int i = offset; i < BIT_IN_QINT; i++)
	{
		bool temp = BUtils::getBit(this->data, i - offset);
		BUtils::setBit(result.data, i, temp);
	}

	return result;
}


/**
 *	Hàm rol - Thực hiện việc xoay trái dãy bit 
 *	@param	 none
 *	@return	 QInt	abcxyz
 */
QInt& QInt::rol()
{
	bool temp = BUtils::getBit(this->data, BIT_IN_QINT - 1);

	*this = *this << 1;
	BUtils::setBit(this->data, 0, temp);

	return *this;
}


/**
 *	Toán tử xoay phải
 *	@param	 none 
 *	@return	 QInt
 */
QInt& QInt::ror()
{
	bool temp = BUtils::getBit(this->data, 0);

	*this = *this >> 1;
	BUtils::setBit(this->data, BIT_IN_QINT - 1, temp);

	return *this;
}