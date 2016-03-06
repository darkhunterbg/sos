#include "cpu.h"

namespace cpu
{

idt_ptr idtp;

extern "C" void load_idt();

void Interrupt()
{
    asm("hlt");
}

void LoadIDT()
{

    IDTDescr* idt = (IDTDescr*)0x110000;


    //for(int i = 0; i < 255; ++i)
    {
	idt[0x0] = {
	    (ushort)(((uint)&Interrupt) & 0xFFFF),
	    8,
	    0,
	    0b10001110,
	    (ushort)(((uint)&Interrupt >> 16) & 0xFFFF),
	};
    } //
    load_idt();

}
}
