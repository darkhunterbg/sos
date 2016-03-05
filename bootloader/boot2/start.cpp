//DO NOT INCLUDE ANYTHING BEFORE START
//OR I'LL HUNT YOU DOWN

#include "memory.h"
#include "vga.h"
#include "disk.h"
#include "io.h"

void boot2();
void PrintDiskInfo(DiskService&, VgaService&);
void ShowSuccess(const char* msg, VgaService& vgaService);
void ShowFailed(const char* msg, VgaService& vgaService);

int start()
{
    boot2();
    return 0;
}

void boot2()
{
    MemoryService memoryService;
    DiskService diskService;
    VgaService vgaService;
    diskService.vga = &vgaService;

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

    const FAT32BootRecord& bootRecord = diskService.GetBootRecord();
    const FAT32ExtendedBootRecord& extendedRecord = diskService.GetExtendedBootRecord();

    vgaService.SetCursorPos(0, 0);
    diskService.DetectPrimaryDisk();
    diskService.DisableInterrups();

    uint* fatTable = static_cast<uint*>(memoryService.Allocate(sizeof(uint) * 1 * 128));

    diskService.ReadFatTable(fatTable);

    //TODO: calculate fat sector and only read from disk!

    //fat sector = 128 clusters
    for(uint i = extendedRecord.fileSystemInfoSector + 1; i < 1 * 128; ++i)
	{
	    uint rootCluster = fatTable[i];

	    if(fatTable[i] == 0)
		break;

	    // vgaService.Print(fatTable[i]);
	    vgaService.Print(' ');

	    if(rootCluster >= 0x0FFFFFF8)
		{
		    vgaService.Print("DONE");
		    //No more clusters in the chain
		}
	    else if(rootCluster == 0x0FFFFFF7)
		{
		    vgaService.Print("BAD");
		    //Bad cluster
		}
	    else
		{
		    vgaService.Print(rootCluster  - 2);
		    //Next cluster
		}
	}
    vgaService.Print('\n');

    byte buffer[512];
    long root = diskService.GetRootSector();

    uint cluster = 0;


    for(uint j = cluster * 8; j < (cluster + 1) * 8; j++)
	{
	    diskService.ReadFromHDD(root + j, 1, buffer);
	    for(int i = 0; i < 512; ++i)
		vgaService.Print((char)buffer[i]);
	}
    //
    // FAT32Object objects[16];

    //  for(int j = 0; j < bootRecord.clusterSectors; ++j)
    /*{
	    diskService.ReadObjectsFromSector(root  , objects);
	    for(int i = 15; i >= 0; --i)
		{
		    FAT32Object& obj = objects[i];

		    if(obj.attributes == FAT32ObjectAttribte::FAT32OA_LONG_FILE_ENTRY)
			{
			    vgaService.SetCursorColor(0x17);
			    FAT32LongFileEntry& entry = reinterpret_cast<FAT32LongFileEntry&>(obj);

			    vgaService.Print('[');
			    vgaService.Print((uint)entry.order);
			    vgaService.Print(']');

			    vgaService.PrintUTF16(entry.firstChar, 10);
			    vgaService.PrintUTF16(entry.secondChar, 12);
			    vgaService.PrintUTF16(entry.thirdChar, 4);
			}
		    else
			{
			    if((byte)obj.attributes == 0)
				continue;
			    if((byte)obj.attributes & (byte)FAT32ObjectAttribte::FAT32OA_DIRECTORY)
				vgaService.SetCursorColor(0x13);
			    else if((byte)obj.attributes & (byte)FAT32ObjectAttribte::FAT32OA_ARCHIVE)
				vgaService.SetCursorColor(0x14);
			    else
				vgaService.SetCursorColor(0x17);
			    vgaService.Print('\n');
			    vgaService.Print(obj.name, 11);
			    vgaService.Print(' ');
			    vgaService.Print((uint)obj.attributes);
			    vgaService.Print(' ');
			}
		}

		vgaService.Print(objects[i].name);
	    vgaService.Print(' ');
	    vgaService.Print(static_cast<uint>(objects[i].attributes));
	    vgaService.Print(' ');
	    vgaService.Print(objects[i].size);
	    vgaService.Print('\n');
	}
	*/
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

    asm("hlt");
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
