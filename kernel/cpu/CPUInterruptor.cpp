#include "CPUInterruptor.h"
#include "CPUSystem.h"
#include "PIC.h"
#include "../SystemProvider.h"

extern "C" void load_idt();
extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

namespace cpu
{

CPUExceptionHandler exceptionHandler = nullptr;
IRQHandler* irqHandlers = nullptr;

const char* exceptionsMessages[] =
    {
        "Divided By Zero",
        "Debug",
        "Non Maskable Interrupt",
        "Breakpoint",
        "Overflow",
        "Bound Range Exceeded",
        "Invalid Opcode",
        "Device Not Available",
        "Double Fault",
        "Coprocessor Segment Overrun",
        "Invalid Task Segment Section",
        "Segment Not Present",
        "Stack-Segment Fault",
        "General Protection Fault",
        "Page Fault",
        "Unknown",
        "x87 Floating-Point Exception",
        "Aligment Check",
        "Machine Check",
        "SIMD Floating-Point Exception",
        "Virtualization Exception",
        "Unkown",
        "Unkown",
        "Unkown",
        "Unkown",
        "Unkown",
        "Unkown",
        "Unkown",
        "Unkown",
        "Unkown",
        "Security Exception"
        "Unkown",
};

CPUInterruptor::CPUInterruptor()
{
    irqHandlers = new IRQHandler[16];
}

CPUInterruptor::~CPUInterruptor()
{
    delete[] irqHandlers;
}

void CPUInterruptor::LoadIDT()
{
    idtTable = (IDTDescriptor*)IDT_ADDRESS;

    IDTAttributes attributes = (IDTAttributes)0b10001110;

    SetInterruptGate(0, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr0);
    SetInterruptGate(1, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr1);
    SetInterruptGate(2, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr2);
    SetInterruptGate(3, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr3);
    SetInterruptGate(4, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr4);
    SetInterruptGate(5, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr5);
    SetInterruptGate(6, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr6);
    SetInterruptGate(7, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr7);
    SetInterruptGate(8, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr8);
    SetInterruptGate(9, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr9);
    SetInterruptGate(10, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr10);
    SetInterruptGate(11, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr11);
    SetInterruptGate(12, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr12);
    SetInterruptGate(13, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr13);
    SetInterruptGate(14, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr14);
    SetInterruptGate(15, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr15);
    SetInterruptGate(16, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr16);
    SetInterruptGate(17, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr17);
    SetInterruptGate(18, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr18);
    SetInterruptGate(19, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr19);
    SetInterruptGate(20, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr20);
    SetInterruptGate(21, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr21);
    SetInterruptGate(22, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr22);
    SetInterruptGate(23, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr23);
    SetInterruptGate(24, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr24);
    SetInterruptGate(25, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr25);
    SetInterruptGate(26, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr26);
    SetInterruptGate(27, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr27);
    SetInterruptGate(28, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr28);
    SetInterruptGate(29, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr29);
    SetInterruptGate(30, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr30);
    SetInterruptGate(31, (ushort)GDTSegmentType::GDTST_CODE, attributes, isr31);

    SetInterruptGate(0 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq0);
    SetInterruptGate(1 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq1);
    SetInterruptGate(2 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq2);
    SetInterruptGate(3 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq3);
    SetInterruptGate(4 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq4);
    SetInterruptGate(5 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq5);
    SetInterruptGate(6 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq6);
    SetInterruptGate(7 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq7);
    SetInterruptGate(8 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq8);
    SetInterruptGate(9 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq9);
    SetInterruptGate(10 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq10);
    SetInterruptGate(11 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq11);
    SetInterruptGate(12 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq12);
    SetInterruptGate(13 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq13);
    SetInterruptGate(14 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq14);
    SetInterruptGate(15 + PIC::MASTER_VECTOR_OFFSET, (ushort)GDTSegmentType::GDTST_CODE, attributes, irq15);

    load_idt();
}

void CPUInterruptor::SetInterruptGate(byte gate, ushort segment, IDTAttributes attributes, InterruptServiceRoutine routine)
{

    idtTable[gate] = {
        (ushort)(((uint)routine) & 0xFFFF),
        segment,
        0,
        attributes,
        (ushort)(((uint)routine >> 16) & 0xFFFF),
    };
}

void CPUInterruptor::SetExceptionHandler(CPUExceptionHandler handler)
{
    exceptionHandler = handler;
}
void CPUInterruptor::SetIRQHandler(IRQType i, IRQHandler routine)
{

	irqHandlers[(byte)i] = routine;
}

void _fault(CPUExceptionData* d)
{
    if(exceptionHandler)
	{
	    CPUException ex = {exceptionsMessages[d->int_no], d};
	    exceptionHandler(ex);
	}
    else
	asm("hlt");
}

void _trap(CPUExceptionData* d)
{
    if(exceptionHandler)
	{
	    CPUException ex = {exceptionsMessages[d->int_no], d};
	    exceptionHandler(ex);
	}
    else
	asm("hlt");
}

void _abort(CPUExceptionData* d)
{
    if(exceptionHandler)
	{
	    CPUException ex = {exceptionsMessages[d->int_no], d};
	    exceptionHandler(ex);
	}
    else
	asm("hlt");
}

void _irq(uint irq)
{

	IRQHandler handler = irqHandlers[irq];
	if(handler != nullptr)
	{
		handler(*SystemProvider::instance);
	}
	else
	    asm("hlt");
}
}
