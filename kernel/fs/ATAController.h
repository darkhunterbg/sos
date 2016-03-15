#pragma once
#include "../Types.h"

class SystemProvider;

namespace fs
{

enum class ATAIOPort : ushort
{
    ATAIOP_DATA = 0x01F0,
    ATAIOP_FEATURE_ERROR = 0x01F1,
    ATAIOP_SECTOR_COUNT = 0x01F2,
    ATAIOP_LBA_LOW = 0x01F3,
    ATAIOP_LBA_MID = 0x01F4,
    ATAIOP_LBA_HIGH = 0x01F5,
    ATAIOP_DRIVE_SELECT = 0x01F6,
    ATAIOP_COMMAND_STATUS = 0x01F7,
    ATAIOP_CONTROL_ALT_STATUS = 0x03F6
};
enum class ATAIOCommand : byte
{
    ATAIOC_DRIVE_SELECT = 0xA0,
    ATAIOC_DRIVE_RW = 0x40,
    ATAIOC_READ_LBA48 = 0x20,
    ATAIOC_WRITE_LBA48 = 0x34,
    ATAIOC_FLUSH = 0xE7,
    ATAIOC_IDENTITY = 0xEC,
    ATAIOC_C_NO_INTERRUPTS = 0x02,
    ATAIOC_C_SOFTWARE_RESET = 0x04,
    ATAIOC_C_HOB_READ = 0x80,
};
enum class ATAStatus : byte
{
    ATAS_ERROR = 0x01,
    ATAS_INDEX = 0x02,
    ATAS_DATA_CORRECTED = 0x04,
    ATAS_DATA_REQUEST = 0x08,
    ATAS_OVERLAPPED_SERVICE = 0x10,
    ATAS_DRIVE_FAULT = 0x20,
    ATAS_READY = 0x40,
    ATAS_BUSY = 0x80,
};

class ATAController
{
    ATAController(const& ATAController) = delete;
    ATAController& operator=(const& ATAController) = delete;

  private:
    static void PrimaryHandler(SystemProvider& provider);
    bool Poll();
  public:
    static const uint SECTOR_SIZE = 512;

    ATAController();
    ~ATAController();

    bool Read(ulong startSector, ushort lengthSectors, byte* outBuffer);
	bool Write(ulong startSector, ushort lengthSectors, const byte* buffer);
	
};
}
