#pragma once

#include "../Types.h"

namespace cpu
{

struct IDTDescriptor
{
    ushort offset_1; // offset bits 0..15
    ushort selector; // a code segment selector in GDT or LDT
    byte zero;       // unused, set to 0
    byte type_attr;  // type and attributes, see below
    ushort offset_2; // offset bits 16..31
} __attribute__((packed));

class CPUSystem
{
    CPUSystem(const& CPUSystem) = delete;
    CPUSystem& operator=(const& CPUSystem) = delete;

    static void DefaultInterruptHandle();

	IDTDescriptor* idtTable;

  public:
    static const uint IDT_ADDRESS = 0x1'00'00'00; //16 MB
	static const uint IDT_COUNT = 256;
    static const uint IDT_SIZE =  IDT_COUNT * sizeof(IDTDescriptor);

    CPUSystem();
    ~CPUSystem();

    void Initialize();
	void SetInterruptGate(byte gate, void* function);
};

}