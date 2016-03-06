#pragma once

#include "../Types.h"

namespace cpu
{
extern "C" void LoadIDT();

struct IDTDescr
{
    ushort offset_1; // offset bits 0..15
    ushort selector; // a code segment selector in GDT or LDT
    byte zero;       // unused, set to 0
    byte type_attr;  // type and attributes, see below
    ushort offset_2; // offset bits 16..31
};

struct idt_ptr
{
    ushort size;
    uint address;
} __attribute__((packed));

}
