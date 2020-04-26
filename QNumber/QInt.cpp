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
	bool flag=0;
	
	if (src.isNegative())
	{
		src = QInt::inverseTwoComplement(src);
		flag=1;
	}

	for (int i = 0; i < BIT_IN_QINT; i++)
	{
		if (BUtils::getBit(src.data, i) == 1)
		{
			result = SUtils::addTwoPositiveIntegerString(result, SUtils::powerOfTwo(i));
		}
	}

	if (flag==1)
	{
		result = "-" + result;
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
	QInt result;
	QInt num=other;
	int carry=0;
	int temp=0;

	for (int i = 0; i < BIT_IN_QINT; i++)
	{
		temp = BitUtils::getBit(this->data, i) + BitUtils::getBit(num.data, i) + carry;
		if ( temp % 2 == 1)
		{
			BitUtils::setBit(result.data,i);
		}
		carry=temp/2;
	}

	return result;
}

QInt QInt::operator-(const QInt& other)
{
	QInt result;
	QInt beminused;

	beminused = this->convertToTwoComplement(other);

	result = (*this) + beminused;

	return result;
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
	if (((*this) - other).isNegative())
	{
		return false;
	}

	return true;
}

bool QInt::operator<(const QInt& other)
{
	if (((*this) - other).isNegative())
	{
		return true;
	}
	
	return false;
}

bool QInt::operator==(const QInt& other)
{
	for( int i = 0; i < TOTAL_BLOCK; i++)
	{
		if (this->data[i] != other.data[i])
		{
			return false;
		}
	}
	return true;
}

bool QInt::operator!=(const QInt& other)
{
	return ((*this) == other) ? false : true;
}

bool QInt::operator>=(const QInt& other)
{
	return ((*this) < other) ? false : true;
}

bool QInt::operator<=(const QInt& other)
{
	return ((*this) > other) ? false : true;
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

QInt QInt::operator&(const QInt& other)
{
	return QInt();
}

QInt QInt::operator|(const QInt& other)
{
	return QInt();
}

QInt QInt::operator^(const QInt& other)
{
	return QInt();
}

QInt QInt::operator~() const
{
	QInt result;
	
	for ( int i = 0; i < TOTAL_BLOCK; i++)
	{
		result.data[i] = ~data[i];
	}

	return result;
}

QInt QInt::operator>>(const int& offset)
{
	return QInt();
}

QInt QInt::operator<<(const int& offset)
{
	return QInt();
}

QInt& QInt::rol()
{
	// TODO: insert return statement here
	return *this;
}

QInt& QInt::ror()
{
	// TODO: insert return statement here
	return *this;
}