#include "varint.h"

int decode_varint(char* data, int* decoded_bytes) {
	int i = -1;
	int value = 0;
	
	do {
		char byte;
		i++;
		
		byte = data[i] & 0x7F;
		value += byte << (7*i);
	} while (data[i] & 0x80 != 0);
	
	*decoded_bytes = i;
	return value;
}

uint64_t decode_unsigned_varint( const uint8_t *const data, int* decoded_bytes )
{
    int i = 0;
    uint64_t decoded_value = 0;
    int shift_amount = 0;

    do 
    {
        decoded_value |= (uint64_t)(data[i] & 0x7F) << shift_amount;     
        shift_amount += 7;
    } while ( (data[i++] & 0x80) != 0 );

    *decoded_bytes = i;
    return decoded_value;
}

int64_t decode_signed_varint( const uint8_t *const data, int* decoded_bytes )
{
    uint64_t unsigned_value = decode_unsigned_varint(data, decoded_bytes);
    return (int64_t)( unsigned_value & 1 ? ~(unsigned_value >> 1) 
                                         :  (unsigned_value >> 1) );
}



uint8_t ex_p300[] = { 0xAC, 0x02 };
uint8_t ex_n1  [] = { 0x01 };
