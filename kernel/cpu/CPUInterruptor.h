#pragma once
#include "../Types.h"

namespace cpu
{

enum class IDTAttributes : byte
{

};

struct IDTDescriptor
{
    ushort isrLow;           // offset bits 0..15
    ushort segment;          // a code segment selector in GDT or LDT
    byte zero;               // unused, set to 0
    IDTAttributes type_attr; // type and attributes
    ushort isrHigh;          // offset bits 16..31
} __attribute__((packed));

typedef void (*InterruptServiceRoutine)();

struct CPUExceptionData
{
    uint gs, fs, es, ds;                         /* pushed the segs last */
    uint edi, esi, ebp, esp, ebx, edx, ecx, eax; /* pushed by 'pusha' */

    uint int_no, err_code;             /* our 'push byte #' and ecodes do this */
    uint eip, cs, eflags, useresp, ss; /* pushed by the processor automatically */
};

struct CPUException
{
    const char* exceptionMessage;
    CPUExceptionData* exceptionData;
};

typedef void (*CPUExceptionHandler)(const CPUException& ex);

class CPUInterruptor
{
    CPUInterruptor(const& CPUInterruptor) = delete;
    CPUInterruptor& operator=(const& CPUInterruptor) = delete;

  private:
    IDTDescriptor* idtTable;

    void SetInterruptGate(byte gate, ushort segment, IDTAttributes attributes, InterruptServiceRoutine routine);

  public:
    static const uint IDT_ADDRESS = 0x1'00'00'00; //16 MB
    static const uint IDT_COUNT = 256;
    static const uint IDT_SIZE = IDT_COUNT * sizeof(IDTDescriptor);
    static const uint EXCEPTIONS_COUNT = 32;

    CPUInterruptor();
    ~CPUInterruptor();

    void LoadIDT();
    void SetExceptionHandler(CPUExceptionHandler handler);
    void SetIRQHandler(byte irq, InterruptServiceRoutine routine);
};

extern "C" void _fault(CPUExceptionData*);
extern "C" void _abort(CPUExceptionData*);
extern "C" void _trap(CPUExceptionData*);
}
