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

	if (srcDec == "0")
	{
		return result;
	}
	else
	{
		if (srcDec[0] == '-')
		{
			srcDec.erase(0, 1);
		}
	}

	if (srcDec.find('.', 0) == string::npos)
	{
		srcDec += ".0";
	}

	posOfDot = srcDec.find('.', 0);
	intPartDec = srcDec.substr(0, posOfDot);
	fracPartDec = srcDec.substr(posOfDot + 1, srcDec.size() - posOfDot - 1);

	if (intPartDec != "0")
	{
		intPartBin = SUtils::convertDecToBin(intPartDec);
		fracPartBin = SUtils::convertFractionPartToBin(fracPartDec);

		exp = intPartBin.size() - 1;

		if (exp > BIAS - 1)
		{
			exp = BIAS - 1;
		}

		if (exp == 0)
		{
			srcSignificandBin = fracPartBin;
		}
		else
		{
			srcSignificandBin = intPartBin.substr(1, exp) + fracPartBin;
		}

		exp = exp + BIAS;
	}
	else
	{
		while (exp < BIAS)
		{
			exp++;
			string newFracDec = SUtils::mulOfPositiveIntegerAndTwo(fracPartDec);

			if (newFracDec.size() > fracPartDec.size())
			{
				fracPartDec = newFracDec.substr(1, fracPartDec.size());
				break;
			}
			else
			{
				fracPartDec = newFracDec;
			}
		}

		exp = BIAS - exp;
		srcSignificandBin = SUtils::convertFractionPartToBin(fracPartDec);
	}

	srcExpBin = SUtils::convertDecToBin(to_string(exp));
	
	while (srcExpBin.size() < BIT_IN_EXP)
	{
		srcExpBin = '0' + srcExpBin;
	}

	if (srcSignificandBin.size() > BIT_IN_SIGNIFICAND)
	{
		srcSignificandBin = srcSignificandBin.substr(0, BIT_IN_SIGNIFICAND);
	}

	for (int i = 0; i < srcExpBin.size(); i++)
	{
		if (srcExpBin[i] == '1')
		{
			BUtils::setBit(result.data, (BIT_IN_QFLOAT - 1) - 1 - i);
		}
	}

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