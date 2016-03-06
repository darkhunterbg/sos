##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=bootloader
ConfigurationName      :=Debug
WorkspacePath          := "D:\SOS\sos"
ProjectPath            := "D:\SOS\sos\bootloader"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=dark_hunter
Date                   :=06/03/2016
CodeLitePath           :="C:\Program Files\CodeLite"
LinkerName             :=C:/MinGW/bin/g++.exe
SharedObjectLinkerName :=C:/MinGW/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=./Debug/boot2.exe
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="bootloader.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/MinGW/bin/windres.exe
LinkOptions            :=  -s @"asmobjects.txt" -Wl,-Ttext=0x10000 -nostdlib
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/MinGW/bin/ar.exe rcu
CXX      := C:/MinGW/bin/g++.exe
CC       := C:/MinGW/bin/gcc.exe
CXXFLAGS :=  -O0 -ansi -W -std=c++14 -Wall -nostdlib -fno-rtti -fno-exceptions -mno-sse -mno-sse2 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/MinGW/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Disk:='D:\SOS\vm\disk.img'
SFKDir:='C:\tools'
NASMDir:='C:\NASM'
OSFMountDir:='C:\Program Files\OSFMount'
DiskMountPoint:=I:
BootLoaderOffset:=90
BootLoaderSize:=422
Objects0=$(IntermediateDirectory)/boot2_start.cpp$(ObjectSuffix) $(IntermediateDirectory)/boot2_vga.cpp$(ObjectSuffix) $(IntermediateDirectory)/boot2_disk.cpp$(ObjectSuffix) $(IntermediateDirectory)/boot2_utils.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	objcopy -O binary -j .text ./Debug/boot2.exe ../Build/Debug/boot2.bin
	
	..\Tools\verify-build ../Build/Debug/
	
	'C:\Program Files\OSFMount'/OSFMount.com -a -t file -m I: -f 'D:\SOS\vm\disk.img' -o rw
	xcopy ..\Build\Debug\boot2.bin I:\boot2.bin* /f /y
	'C:\Program Files\OSFMount'/OSFMount.com -D -m I:
	'C:\tools'/sfk partcopy ../Build/Debug/boot1.bin 0 $(BootLoaderSize) 'D:\SOS\vm\disk.img' $(BootLoaderOffset) -yes
	@echo Done

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:
	@echo Executing Pre Build commands ...
	pre.bat
	'C:\NASM'/nasm -f bin boot1.asm -o ../Build/Debug/boot1.bin
	'C:\NASM'/nasm -f elf ./boot2/io.asm -o ./Debug/boot2_io.asm.o
	@echo Done


##
## Objects
##
$(IntermediateDirectory)/boot2_start.cpp$(ObjectSuffix): boot2/start.cpp $(IntermediateDirectory)/boot2_start.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/bootloader/boot2/start.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/boot2_start.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/boot2_start.cpp$(DependSuffix): boot2/start.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/boot2_start.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/boot2_start.cpp$(DependSuffix) -MM "boot2/start.cpp"

$(IntermediateDirectory)/boot2_start.cpp$(PreprocessSuffix): boot2/start.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/boot2_start.cpp$(PreprocessSuffix) "boot2/start.cpp"

$(IntermediateDirectory)/boot2_vga.cpp$(ObjectSuffix): boot2/vga.cpp $(IntermediateDirectory)/boot2_vga.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/bootloader/boot2/vga.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/boot2_vga.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/boot2_vga.cpp$(DependSuffix): boot2/vga.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/boot2_vga.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/boot2_vga.cpp$(DependSuffix) -MM "boot2/vga.cpp"

$(IntermediateDirectory)/boot2_vga.cpp$(PreprocessSuffix): boot2/vga.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/boot2_vga.cpp$(PreprocessSuffix) "boot2/vga.cpp"

$(IntermediateDirectory)/boot2_disk.cpp$(ObjectSuffix): boot2/disk.cpp $(IntermediateDirectory)/boot2_disk.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/bootloader/boot2/disk.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/boot2_disk.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/boot2_disk.cpp$(DependSuffix): boot2/disk.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/boot2_disk.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/boot2_disk.cpp$(DependSuffix) -MM "boot2/disk.cpp"

$(IntermediateDirectory)/boot2_disk.cpp$(PreprocessSuffix): boot2/disk.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/boot2_disk.cpp$(PreprocessSuffix) "boot2/disk.cpp"

$(IntermediateDirectory)/boot2_utils.cpp$(ObjectSuffix): boot2/utils.cpp $(IntermediateDirectory)/boot2_utils.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/bootloader/boot2/utils.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/boot2_utils.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/boot2_utils.cpp$(DependSuffix): boot2/utils.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/boot2_utils.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/boot2_utils.cpp$(DependSuffix) -MM "boot2/utils.cpp"

$(IntermediateDirectory)/boot2_utils.cpp$(PreprocessSuffix): boot2/utils.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/boot2_utils.cpp$(PreprocessSuffix) "boot2/utils.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


