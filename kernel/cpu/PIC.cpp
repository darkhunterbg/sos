#include "PIC.h"
#include "CPUSystem.h"
#include "../io.h"

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

namespace cpu
{

CPUExceptionHandler exceptionHandler = nullptr;
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

PIC::PIC()
{
    Initialize();
}

PIC::~PIC()
{
}

void PIC::Initialize()
{
    byte a1, a2;

    //Save masks
    a1 = inb((byte)PICIOPort::PICIO_MASTER_DATA);
    a2 = inb((byte)PICIOPort::PICIO_SLAVE_DATA);

    //Start initialization
    outb((byte)PICIOPort::PICIO_MASTER_COMMAND, (byte)PICCommand::PICC_INITIALIZE + (byte)PICCommand::PICC_ICW4);
    outb((byte)PICIOPort::PICIO_SLAVE_COMMAND, (byte)PICCommand::PICC_INITIALIZE + (byte)PICCommand::PICC_ICW4);

    //Set vector offsets
    outb((byte)PICIOPort::PICIO_MASTER_DATA, MASTER_VECTOR_OFFSET);
    outb((byte)PICIOPort::PICIO_SLAVE_DATA, SLAVE_VECTOR_OFFSET);

    //Tell Master there is slave at IRQ2 (0000 0100)
    outb((byte)PICIOPort::PICIO_MASTER_DATA, 0b00000100);
    //Tell Salve it has cascade identity (0000 0010)
    outb((byte)PICIOPort::PICIO_SLAVE_DATA, 0b00000010);

    //8086/88 (MCS-80/85) mode
    outb((byte)PICIOPort::PICIO_MASTER_DATA, 0x01);
    outb((byte)PICIOPort::PICIO_SLAVE_DATA, 0x01);

    //Restore masks
    outb((byte)PICIOPort::PICIO_MASTER_DATA, a1);
    outb((byte)PICIOPort::PICIO_SLAVE_DATA, a2);
}

void PIC::SendEOI(byte irq)
{
    if(irq >= 8)
	outb((byte)PICIOPort::PICIO_SLAVE_COMMAND, (byte)PICCommand::PICC_EOF);
	
    outb((byte)PICIOPort::PICIO_MASTER_COMMAND, (byte)PICCommand::PICC_EOF);
}

void PIC::LoadIDT()
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

    load_idt();
}

void PIC::SetInterruptGate(byte gate, ushort segment, IDTAttributes attributes, InterruptServiceRoutine routine)
{

    idtTable[gate] = {
        (ushort)(((uint)routine) & 0xFFFF),
        segment,
        0,
        attributes,
        (ushort)(((uint)routine >> 16) & 0xFFFF),
    };
}

void PIC::SetExceptionHandler(CPUExceptionHandler handler)
{
    exceptionHandler = handler;
}

void PIC::SetIRQHandler(byte gate, InterruptServiceRoutine routine)
{

    IDTAttributes attributes = (IDTAttributes)0b10001110;
    SetInterruptGate(gate, (ushort)GDTSegmentType::GDTST_CODE, attributes, routine);
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
}
