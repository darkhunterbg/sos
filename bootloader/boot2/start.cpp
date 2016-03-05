//DO NOT INCLUDE ANYTHING BEFORE START
//OR I'LL HUNT YOU DOWN

//#include "memory.h"
#include "vga.h"
#include "disk.h"
#include "io.h"
#include "utils.h"
#include "pe.h"

void boot2();
void PrintDiskInfo(DiskService&, VgaService&);
void ShowSuccess(const char* msg, VgaService& vgaService);
void ShowFailed(const char* msg, VgaService& vgaService);

int start()
{
    boot2();
    return 0;
}

static const uint kernel =		0x10'00'00;			//1 MB
static const uint kernelFile =	0x80'00'00;	//8 MB

void boot2()
{
    // MemoryService memoryService;
    DiskService diskService;
    VgaService vgaService;

    vgaService.ClearScreen(0x00);

    //  vgaService.SetCursorColor(0x07);
    //  vgaService.SetCursorPos(16, 3);

    /* vgaService.Print("+-----------------------------------------+");
    vgaService.SetCursorPos(16, 4);
    vgaService.Print("|    SOS 32 Bit C++ Kernel Executing!     |");
    vgaService.SetCursorPos(16, 5);
    vgaService.Print("+-----------------------------------------+");

    vgaService.SetCursorPos(15, 10);
    vgaService.SetCursorColor(0x0F);
    vgaService.Print("I am preparing to load... Hold on, please... :)");

	vgaService.SetCursorPos(0, 12);*/

    diskService.DetectPrimaryDisk();
    diskService.DisableInterrups();

    char dir[] = "SOS";
    char file[] = "KERNEL";
    char ext[] = "SYS";
    char error[] = "SOS/KERNEL.SYS not found!";

    long dirCluster = diskService.GetDirectoryCluster(0, dir, 3);
    long fileCluster = diskService.GetFileCluster(dirCluster, file, 6, ext);
    if(fileCluster < 0)
	{
	    vgaService.Print(error);
	}
    else
	{
	    diskService.LoadFile(fileCluster, (void*)kernelFile);

	    ImageDosHeader* image = (ImageDosHeader*)kernelFile;
	    ImageNtHeader* headers = (ImageNtHeader*)(kernelFile + image->lfanew);
	    //uint entryPoint = headers->optionalHeader.addressOfEntryPoint;
	    //uint base = headers->optionalHeader.imageBase;

	    uint dataDirectoriesSize = headers->optionalHeader.numberOfRvaAndSizes * sizeof(ImageDataDirectory);
	    ImageSectionHeader* sections = (ImageSectionHeader*)((uint)headers + sizeof(ImageNtHeader) + dataDirectoriesSize);

	    for(int i = 0; i < headers->fileHeader.numberOfSections; ++i)
		{
		    ImageSectionHeader& section = sections[i];

		    uint offset = section.virtualAddress - headers->optionalHeader.addressOfEntryPoint;

		    utils::Copy((void*)(section.pointerToRawData + kernelFile),
		                (void*)(kernel + offset),
		                section.sizeOfRawData);
		}

	    typedef int (*KernelStart)();

	    KernelStart kernelStart = (KernelStart)(kernel);

	    kernelStart();
	}
    //vgaService.Print(static_cast<uint>(diskService.GetBootRecord().reservedSectorsCount));

    //byte* buffer = static_cast<byte*>(memoryService.Allocate(sizeof(byte)* DiskService::SECTOR_SIZE_BYTES));

    //diskService.ReadFromHDD(8216,1 ,buffer);

    //vgaService.Print("\nRead complete!");

    //buffer[11] = '\0';

    //vgaService.SetCursorPos(0, 12);
    //vgaService.Print(reinterpret_cast<char*>(buffer));

    /* byte a = 0x00;
    byte b = 0x10;
    while(true)
	{
	    uint x = 0;
	    vgaService.SetCursorColor(b);
	    byte c = a;
	    a = b;
	    b = c;
	    for(uint i = 0; i < VgaService::COLUMNS; ++i)
		{
		    for(uint j = 0; j < 40000; ++j)
			{
			    vgaService.SetCursorPos(x, 22);
			}
		    vgaService.Print(' ');
		    ++x;
		}
	}*/
}

/*void PrintDiskInfo(DiskService& diskService, VgaService& vgaService)
{
    const FAT32BootRecord& bootRecord = diskService.GetBootRecord();
    const FAT32ExtendedBootRecord& extendedRecord = diskService.GetExtendedBootRecord();

    vgaService.SetCursorPos(0, 10);
    vgaService.SetCursorColor(0x0B);
    vgaService.Print("OEM: ");
    vgaService.Print(bootRecord.oem);
    vgaService.Print(" Label: ");
    vgaService.Print(extendedRecord.volumeLabel, 11);
    vgaService.Print(" Identifier: ");
    vgaService.Print(extendedRecord.identifier, 8);
}*/
