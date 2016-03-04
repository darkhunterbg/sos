#pragma once

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned short ushort;

inline constexpr bool _assert_types()
{
    static_assert(sizeof(uint) == 4, "UINT is not 4 bytes!");
    static_assert(sizeof(ushort) == 2, "USHORT is not 4 bytes!");
    static_assert(sizeof(byte) == 1, "BYTE is not 1 bytes!");
    static_assert(sizeof(void*) == 4, "Pointer is not 4 bytes!");

    return true;
}
