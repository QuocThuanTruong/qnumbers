#include "BitUtils.h"

/**
 *	setBit - Hàm set giá trị cho bit thứ i (tính từ 0 và phải sang)
 *	@param	 int[]		dãy bit cần thiết lập giá trị
 *	@param	 int		vị trí của bit thứ i
 *	@param	 bool		giá trị cần set
 *	@return	 none
 */
void BitUtils::setBit(int data[], int i, bool value)
{
	if (i < 0 || i > BIT_IN_QNUMS - 1)					// Nếu vị trí không hợp lệ
	{
		throw "Bit out of bounds";
	}

	int block = TOTAL_BLOCK - 1 - i / BIT_IN_BLOCK;		// Tính block chứ vị trí cần set
	int offset = i % BIT_IN_BLOCK;						// Vị trí của bit trong block

	if (value)											// Nếu là bit 1
	{
		data[block] = data[block] | (1 << offset);		// Bật bit tại vị trí cần set
	}
	else												// Ngược lại bit 0
	{
		data[block] = data[block] & ~(1 << offset);		// Tắt bit tại vị trí cần set
	}
}

/**
 *	setBit - Hàm get giá trị cho bit thứ i (tính từ 0 và phải sang)
 *	@param	 int[]		dãy bit cần lấy giá trị
 *	@param	 int		vị trí của bit thứ i
 *	@return	 none
 */
bool BitUtils::getBit(int data[], int i)
{
	if (i < 0 || i > BIT_IN_QNUMS - 1)					// Nếu vị trí không hợp lệ
	{
		throw "Bit out of bounds";
	}

	int block = TOTAL_BLOCK - 1 - i / BIT_IN_BLOCK;		// Tính block chứ vị trí cần set
	int offset = i % BIT_IN_BLOCK;						// Vị trí của bit trong block

	return (data[block] >> offset) & 1;					// Lấy bit ra và trả về
}
