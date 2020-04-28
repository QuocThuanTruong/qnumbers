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
	QInt temp = src;
	string result = "0";

	if (src.isNegative())
	{
		temp = QInt::inverseTwoComplement(temp);
	}

	for (int i = 0; i < BIT_IN_QINT; i++)
	{
		if (BUtils::getBit(temp.data, i) == 1)
		{
			result = SUtils::addTwoPositiveIntegerString(result, SUtils::powerOfTwo(i));
		}
	}

	if (src.isNegative())
	{
		result = '-' + result;
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
/**
 *	operator+ - Toán tử cộng 2 số QInt
 *	@param	 const QInt&     Số hạng
 *	@return	 QInt            Kết quả sau khi cộng
 */
QInt QInt::operator+(const QInt& other)
{
	QInt result;
	QInt num = other;
	int carry = 0;
	int temp = 0;

	for (int i = 0; i < BIT_IN_QINT; i++)					// Cộng lần lượt các bit và lưu biến nhớ
	{
		temp = BitUtils::getBit(this->data, i) + BitUtils::getBit(num.data, i) + carry;
		if ( temp % 2 == 1)
		{
			BitUtils::setBit(result.data, i);
		}
		carry = temp/2;
	}

	return result;
}
/**
 *	operator- - Toán tử trừ 2 số QInt
 *	@param	 const QInt&    Số bị trừ       
 *	@return	 QInt			Kết quả sau khi trừ          
 */
QInt QInt::operator-(const QInt& other)
{
	return *this + QInt::convertToTwoComplement(other);			// Cộng cho bù 2
}
/**
 *	operator* - Toán tử nhân số QInt
 *	@param	 const QInt&    Thừa số nhân
 *	@return	 QInt			Kết quả sau khi nhân
 */
QInt QInt::operator*(const QInt& other)
{
	QInt result;
	QInt A;
	QInt Q = other;
	bool Q_1 = 0;												
	int k = BIT_IN_QINT;										//k = 128

	if (this->equalZero() || Q.equalZero())						//Một trong 2 mà nhan nhau bang 0 thì return result
	{
		return result;
	}

	while (k > 0)
	{
		bool Q_0 = BitUtils::getBit(Q.data,0);					//lấy Q_0 cua Q

		if (Q_0 == true && Q_1 == false)						//Nếu 2 bit cuối Q_0 =1, Q_1 = 0
		{
			A = A - *this;										//A-M->A
		}

		if (Q_0 == false && Q_1 == true)						//Nếu 2 bit cuối Q_0 =0, Q_1 = 1
		{
			A = A + *this;										//A+M->A
		}
								
		Q_1 = Q_0;												//Shift right[A,Q,Q_1]
		Q = Q >> 1;												//Q shift right
		BitUtils::setBit(Q.data,BIT_IN_QINT - 1,BitUtils::getBit(A.data,0));//Lấy bit phải nhất của A bỏ qua bit trái nhất của Q vì đang dịch phải
		A = A >> 1;												//A shift right
		k--;
	}

	result = Q;													//Gán result = Q và return ket qua
	return result;
}
/**
 *	operator/ - Toán tử chia 2 số QInt
 *	@param	 const QInt&    Số chia
 *	@return	 QInt			Kết quả sau khi chia
 */
QInt QInt::operator/(const QInt& other)
{																// Q/M
	QInt M = other;												// tạo tiến tạm M
	if (M.equalZero())											// Nếu M = 0 , M là số chia
	{
		throw "Division by zero!";
	}
	if ( (M - QInt("1",10)).equalZero() || this->equalZero())	//Nếu số chia M hoặc số bị chia this bằng 0
	{
		return *this;											// return về this
	}

	QInt result;
	QInt A;
	QInt Q = *this;
	int k = BIT_IN_QINT;										//k = 128
	bool isNegative = false;
	bool Q_0 = 0;

	if ((Q.isNegative() && !M.isNegative() || (!Q.isNegative() && M.isNegative())))
	{															//Nếu 2 số trái dấu
		isNegative = true;										
	}															//Ngược lai là false

	if (Q.isNegative())
	{
		QInt::inverseTwoComplement(Q);							//Nếu Q âm thì chuyển về dạng số dương
	}

	if (M.isNegative())
	{
		QInt::inverseTwoComplement(M);							//Nếu M âm thì chuyển về dạng số dương
	}

	while (k > 0)
	{
																//Shift left[A,Q]
		A = A << 1;												//Dịch trái A
		BitUtils::setBit(A.data,0, BitUtils::getBit(Q.data, BIT_IN_QINT-1));//Lấy bit trái nhất của Q bỏ qua  A vì đang dịch trái
		Q = Q << 1;												//Dịch trái Q
		
		A = A - M;												//A-M->A
		if (A.isNegative())										//Nếu A < 0
		{
			A = A + M;											//Q_0 = 0 đã khai báo mặc định ở trên, A+M->A
		}
		else
		{
			Q_0 = 1;
			BitUtils::setBit(Q.data, 0, Q_0);					//set bit 1 cho bit thu 0 cua Q
		}
		k--;
	}

	result = Q;												// kết quả Q là thương A là số dư
	if (isNegative == true)									//Nếu cho kết quả âm thì chuyen qua bu 2
	{
		QInt::convertToTwoComplement(result);
	}

	return result;
}
/**
 *	operator> - Toán tử so sánh lớn hơn
 *	@param	 const QInt&      Số cần so sánh
 *	@return	 bool             Kết quả phép so sánh
 */
bool QInt::operator>(const QInt& other)
{
	if (((*this) - other).isNegative())							//Trừ nhau ra dương thì return true
	{
		return false;
	}

	return true;
}
/**
 *	operator< - Toán tử so sánh bé hơn
 *	@param	 const QInt&      Số cần so sánh
 *	@return	 bool             Kết quả phép so sánh
 */
bool QInt::operator<(const QInt& other)
{
	if (((*this) - other).isNegative())							//Trừ nhau ra âm thì return true
	{
		return true;
	}
	
	return false;
} 
/**
 *	operator== - Toán tử so sánh bằng
 *	@param	 const QInt&      Số cần so sánh
 *	@return	 bool             Kết quả phép so sánh
 */
bool QInt::operator==(const QInt& other)
{
	for( int i = 0; i < TOTAL_BLOCK; i++)						// So sánh lần lượt các block
	{
		if (this->data[i] != other.data[i])
		{
			return false;
		}
	}
	return true;
}
/**
 *	operator!= - Toán tử so sánh khác
 *	@param	 const QInt&		Số cần so sánh
 *	@return	 bool               Kết quả phép so sánh
 */
bool QInt::operator!=(const QInt& other)
{
	return ((*this) == other) ? false : true;
}
/**
 *	operator>=  - Toán tử so sánh lớn hơn hoặc bằng
 *	@param	 const QInt&         Số cần so sánh
 *	@return	 bool                Kết quả phép so sánh
 */
bool QInt::operator>=(const QInt& other)
{
	return ((*this) < other) ? false : true;
}
/**
 *	operator<=  - Toán tử so sánh nhỏ hơn hoặc bằng
 *	@param	 const QInt&       Số cần so sánh
 *	@return	 bool              Kết quả phép so sánh
 */
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


/**
 *	operator & - Toán tử AND
 *	@param	 const QInt&		Số QInt truyền vào để thực hiện phép &	
 *	@return	 QInt				Kết quả sau khi thực hiện phép &
 */ 
QInt QInt::operator&(const QInt& other)
{
	QInt result;

	for (int i = 0; i < TOTAL_BLOCK; i++)							// Duyệt và & bit các block tương ứng
	{
		result.data[i] = this->data[i] & other.data[i];
	}

	return result;
}


/**
 *	operator| - Toán tử OR
 *	@param	 const QInt&		Số QInt truyền vào để thực hiện phép |
 *	@return	 QInt				Kết quả sau khi thực hiện phép |
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
 *	operater - Toán tử XOR 
 *	@param	 const QInt&		Số QInt truyền vào để thực hiện phép ^
 *	@return	 QInt				Lưu lại kết quả sau khi thực hiện phép ^
 */
QInt QInt::operator^(const QInt& other)
{
	QInt result;

	for (int i = 0; i < TOTAL_BLOCK; i++)							// Duyệt và ^ từng block tương ứng
	{
		result.data[i] = this->data[i] ^ other.data[i];
	}

	return result;
}


/**
 *	operator ~ - Toán tử NOT 
 *	@param	 none 
 *	@return	 QInt			Kết quả sau khi thực hiện phép ~
 */
QInt QInt::operator~() const
{
	QInt result;

	for (int i = 0; i < TOTAL_BLOCK; i++)							// Duyệt và ~ bit các block tương ứng
	{
		result.data[i] = ~(this->data[i]);
	}

	return result;
}


/**
 *	operator>> - Toán tử dịch phải
 *	@param	 const int&			Số lượng bit dịch
 *	@return	 QInt				Kết quả sau khi thực hiện phép dịch
 */
QInt QInt::operator>>(const int& offset)
{
	QInt result;													// Tạo 1 dãy bit 0

	for (int i = offset; i < BIT_IN_QINT; i++)						// Duyệt từ vị trí offset đến hết dãy bit
	{
		bool temp = BUtils::getBit(this->data, i);					// Lưu lại bit thứ i của dãy cần dịch
		BUtils::setBit(result.data, i - offset, temp);				// Set bit vừa lưu vào bit thứ i - offset của dãy kết quả
	}

	return result;
}


/**
 *	operator<< - Toán tử dịch trái
 *	@param	 const int&			Số lượng bit dịch
 *	@return	 QInt				Lưu kết quả sau khi thực hiện phép dịch trái
 */
QInt QInt::operator<<(const int& offset)
{
	QInt result;													// Tạo 1 dãy bit 0

	for (int i = offset; i < BIT_IN_QINT; i++)						// Duyệt từ vị trí offset đến hết dãy
	{
		bool temp = BUtils::getBit(this->data, i - offset);			// Lưu bit thứ i - offset của dãy cần dịch trái
		BUtils::setBit(result.data, i, temp);						// Set bit vừa lưu vào bit thứ i của dãy bit kết quả
	}

	return result;
}


/**
 *	Hàm rol - Thực hiện việc xoay trái dãy bit 
 *	@param	 none
 *	@return	 QInt		Lưu kết quả sau khi thực hiện xoay trái dãy bit
 */
QInt& QInt::rol()
{
	bool temp = BUtils::getBit(this->data, BIT_IN_QINT - 1);		// Lưu lại bit trái nhất

	*this = *this << 1;												// Dịch trái dãy bit sang 1 bit
	BUtils::setBit(this->data, 0, temp);							// Set bit trái nhất cho bit thứ 0 của dãy

	return *this;
}


/**
 *	Hàm ror - Thực hiện việc xoay phải dãy bit
 *	@param	 none 
 *	@return	 QInt		Kết quả sau khi thực hiện phép xoay phải
 */
QInt& QInt::ror()
{
	bool temp = BUtils::getBit(this->data, 0);						// Lưu lại bit phải nhất

	*this = *this >> 1;												// Dịch phải dãy bit sang 1 bit
	BUtils::setBit(this->data, BIT_IN_QINT - 1, temp);				// Set bit phải nhất cho bit trái nhất

	return *this;
}
