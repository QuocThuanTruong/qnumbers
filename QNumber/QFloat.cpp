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

QFloat QFloat::convertDecToQFloat(const string& src)
{
	QFloat result;
	int pos0;
	int pos;
	string inPartDec;
	string fracPartDec;
	string inPartBin;
	string fracPartBin;

    if (src=="0") return result;
	else
	{
		if (src[0] == '-')
		{
			src.erase(0, 1);
		}
	}

	pos0 = src.find_first_of('.',0);
	if (pos0 == string::npos)
	{
		src += '.0';
	}

	pos = src.find_first_of('.', 0);
	inPartDec = src.substr(0, pos - 1);
	fracPartDec = src.substr(pos + 1);

	if (inPartDec != "0")
	{
		inPartBin = SUtils::convertDecToBin(inPartDec);
		fracPartBin = SUtils::convertFractionPartToBin(fracPartDec);


	}


	return QFloat();
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