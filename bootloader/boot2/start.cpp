//DO NOT INCLUDE ANYTHING BEFORE START
//OR I'LL HUNT YOU DOWN

//#include "memory.h"
#include "vga.h"
#include "disk.h"
#include "io.h"
#include "utils.h"
#include "pe.h"



static const uint kernel =		0x10'00'00;			//1 MB
static const uint kernelFile =	0x01'00'00'00;	//16 MB

int start()
{
    DiskService diskService;
    VgaService vgaService;

    vgaService.ClearScreen(0x00);


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

		goto *(void*)(kernel);
	}
	
	return 1;
   
}
