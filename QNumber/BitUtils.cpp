#include "BitUtils.h"

void BitUtils::setBit(int data[], int i, bool value)
{
	if (i < 0 || i > BIT_IN_QINT - 1)
	{
		throw "Bit out of bounds";
	}

	int block = TOTAL_BLOCK - 1 - i / BIT_IN_BLOCK;
	int offset = i % BIT_IN_BLOCK;

	if (value)
	{
		data[block] = data[block] | (1 << offset);
	}
	else
	{
		data[block] = data[block] & ~(1 << offset);
	}
}

bool BitUtils::getBit(int data[], int i)
{
	if (i < 0 || i > BIT_IN_QINT - 1)
	{
		throw "Bit out of bounds";
	}

	int block = TOTAL_BLOCK - 1 - i / BIT_IN_BLOCK;
	int offset = i % BIT_IN_BLOCK;

	return (data[block] >> offset) & 1;
}
