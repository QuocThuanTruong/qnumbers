#ifndef _BIT_UTILS_H
#define _BIT_UTILS_H

#define BIT_IN_BLOCK 32
#define TOTAL_BLOCK 4
#define BIT_IN_QNUMS 128

class BitUtils
{
public:
	static void setBit(int[], int i, bool value = 1);
	static bool getBit(int[], int i);
};
#endif // !_BIT_UTILS_H
