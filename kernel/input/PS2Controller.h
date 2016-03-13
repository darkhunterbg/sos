#pragma once
#include "../Types.h"

namespace input
{
enum class PS2IOPort : byte
{
    PS2IOP_DATA = 0x60,
    PS2IOP_STATUS_COMMAND = 0x64,
};

enum class PS2Status : byte
{
    PS2S_OUTPUT_FULL = 1,
    PS2S_INPUT_FULL = 2,
    PS2S_SYSTEM = 4,
    PS2S_CONTROLLER = 8,
    PS2S_TIMEOUT_ERROR = 64,
    PS2S_PARITY_ERROR = 128,
};

enum class PS2Configuration : byte
{
    PS2C_INTERRUPT_FIRST = 1,
    PS2C_INTERRUPT_SECOND = 2,
    PS2C_SYSTEM = 4,
    PS2C_ZERO = 8,
    PS2C_CLOCK_FIRST = 16,
    PS2C_CLOCK_SECOND = 32,
    PS2C_TRANSLATION_FIRST = 64,
    PS2C_ZERO2 = 128,
};

enum class PS2Output : byte
{
    PS2O_SYSTEM_RESET = 1,
    PS2O_A20 = 2,
    PS2O_CLOCK_SECOND = 4,
    PS2O_DATA_SECOND = 8,
    PS2O_OUTPUT_FULL_FIRST = 16,
    PS2O_OUTPUT_FULL_SECOND = 32,
    PS2O_CLOCK_FIRST = 64,
    PS2O_DATA_FIRST = 128,
};

enum class PS2Command : byte
{
    PS2C_READ_BYTE_0 = 0x20,
    PS2C_WRITE_BYTE_0 = 0x60,

    PS2C_DISABLE_SECOND = 0xA7,
    PS2C_ENABLE_SECOND = 0xA8,

    PS2C_TEST_CONTROLLER = 0xAA,
    PS2C_TEST_FIRST = 0xAB,
    PS2C_DISABLE_FIRST = 0xAD,
    PS2C_ENABLE_FIRST = 0xAE,
	
	PS2C_IDENTITY = 0xF2,
};

class PS2Controller
{
    PS2Controller(const& PS2Controller) = delete;
    PS2Controller& operator=(const& PS2Controller) = delete;

  public:
    byte config;
    byte status;
	
    PS2Controller();
    ~PS2Controller();
};
}
