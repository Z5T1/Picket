#pragma once

#include <stdint.h>

/**
First off, note that varints are sent as actual bytes, not strings of
the characters 1 and 0.

For an unsigned varint, I believe the following will decode it for you,
assuming you've got the varint data in a buffer pointed to by data.
This example function returns the number of bytes decoded in the
reference argument int decoded_bytes.
*/
uint64_t decode_unsigned_varint( const uint8_t *const data, int* decoded_bytes );

int64_t decode_signed_varint( const uint8_t *const data, int* decoded_bytes );

int decode_varint(char* data, int* decoded_bytes);
