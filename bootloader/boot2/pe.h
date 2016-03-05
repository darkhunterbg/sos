#include "types.h"

struct ImageDosHeader
{
    ushort magic;
    ushort cblp;
    ushort cp;
    ushort crlc;
    ushort cparhdr;
    ushort minalloc;
	ushort maxalloc;
	ushort ss;
	ushort sp;
	ushort csum;
	ushort ip;
	ushort cs;
	ushort lfarlc;
	ushort ovno;
	ushort res[4];
	ushort oemid;
	ushort oeminfo;
	ushort res2[10];
	uint lfanew;

} __attribute__((packed));

struct ImageFileHeader
{
	ushort machine;
	ushort numberOfSections;
	uint timeDateStamp;
	uint pointerToSymbolTable;
	uint numberOfSymbols;
	ushort sizeOfOptioanlHeader;
	ushort characteristics;
	
} __attribute__((packed));

struct ImageDataDirectory
{
	uint virtualAddress;
	uint size;
} __attribute__((packed));

struct ImageSectionHeader
{
	char name[8];
	uint virtualSize;
	uint virtualAddress;
	uint sizeOfRawData;
	uint pointerToRawData;
	uint pointerToRelocations;
	uint pointerToLineNumbers;
	ushort numberOfRelocations;
	ushort numberOfLinenumbers;
	uint characteristics;
} __attribute__((packed));

struct ImageOptionalHeader
{
	ushort magic;
	byte majorLinkerVersion;
	byte minorLinkerVersion;
	uint sizeOfCode;
	uint sizeOfInitializedData;
	uint sizeOfUninitializedData;
	uint addressOfEntryPoint;
	uint baseOfCode;
	uint baseOfData;
	uint imageBase;
	uint sectionAlignment;
	uint fileAlignment;
	ushort majorOSVerion;
	ushort minorOSVersion;
	ushort majorImageVersion;
	ushort minorImageVersion;
	ushort majorSubsystemVersion;
	ushort minorSubsystemVersion;
	uint reserved1;
	uint sizeOfImage;
	uint sizeOfHeaders;
	uint checkSum;
	ushort subsystem;
	ushort dllCharacteristics;
	uint sizeOfStackReserve;
	uint sizeOfStackCommit;
	uint sizeOfHeapReserve;
	uint sizeOfHeapCommit;
	uint loaderFlags;
	uint numberOfRvaAndSizes;
} __attribute__((packed));

struct ImageNtHeader
{
	uint signature;
	ImageFileHeader fileHeader;
	ImageOptionalHeader optionalHeader;
	
}__attribute__((packed));


