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

string QFloat::convertFractionPartToBin(string srcFrac)
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