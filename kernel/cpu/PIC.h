#pragma once
#include "../Types.h"

namespace cpu
{

enum class PICIOPort : byte
{
    PICIO_MASTER_COMMAND = 0x20,
    PICIO_MASTER_DATA = 0x21,

    PICIO_SLAVE_COMMAND = 0xA0,
    PICIO_SLAVE_DATA = 0xA1,
};

enum class PICCommand : byte
{
    PICC_ICW4 = 0x01,       /* ICW4 (not) needed */
    PICC_SINGLE = 0x02,     /* Single (cascade) mode */
    PICC_INTERVAL4 = 0x04,  /* Call address interval 4 (8) */
    PICC_LEVEL = 0x08,      /* Level triggered (edge) mode */
    PICC_INITIALIZE = 0x10, /* Initialization - required! */
    PICC_EOI = 0x20,        /* End of Interrupt - required! */
};

//Programmable Interrupt Controller
class PIC
{
    PIC(const& PIC) = delete;
    PIC& operator=(const& PIC) = delete;

  private:
    void Initialize();

  public:
    static const uint MASTER_VECTOR_OFFSET = 0x20;
    static const uint SLAVE_VECTOR_OFFSET = 0x28;

    PIC();
    ~PIC();

    void SendEOI(byte irq);
};
}
