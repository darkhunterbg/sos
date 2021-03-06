##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=kernel
ConfigurationName      :=Debug
WorkspacePath          := "D:\SOS\sos"
ProjectPath            := "D:\SOS\sos\kernel"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=dark_hunter
Date                   :=17/03/2016
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
OutputFile             :=../Build/Debug/SOS/kernel.sys
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="kernel.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/MinGW/bin/windres.exe
LinkOptions            :=  @"asmobjects.txt" -Wl, -Ttext=0x100000 -nostdlib
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
CXXFLAGS :=  -pedantic-errors -O0 -ansi -pedantic -W -std=c++14 -Wall -fno-rtti -fno-exceptions -mno-sse -mno-sse2 -nostdlib $(Preprocessors)
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
Objects0=$(IntermediateDirectory)/kernel.cpp$(ObjectSuffix) $(IntermediateDirectory)/SystemProvider.cpp$(ObjectSuffix) $(IntermediateDirectory)/memory_MemorySystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/vga_VGATextSystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/vga_DefaultVGADriver.cpp$(ObjectSuffix) $(IntermediateDirectory)/cpu_CPUSystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/cpu_PIC.cpp$(ObjectSuffix) $(IntermediateDirectory)/cpu_CPUInterruptor.cpp$(ObjectSuffix) $(IntermediateDirectory)/input_KeyboardSystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/input_PS2Controller.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/fs_FileSystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/fs_ATAController.cpp$(ObjectSuffix) 



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
	
	..\Tools\verify-build ../Build/Debug/ -kernel
	
	
	'C:\Program Files\OSFMount'/OSFMount.com -a -t file -m I: -f 'D:\SOS\vm\disk.img' -o rw
	xcopy ..\Build\Debug\sos\kernel.sys I:\sos\kernel.sys* /f /y
	'C:\Program Files\OSFMount'/OSFMount.com -D -m I:
	@echo Done

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:
	@echo Executing Pre Build commands ...
	pre.bat
	'C:\NASM'/nasm -f elf ./cpu/idt.asm -o ./Debug/cpu_idt.asm.o
	'C:\NASM'/nasm -f elf ./io.asm -o ./Debug/io.asm.o
	
	@echo Done


##
## Objects
##
$(IntermediateDirectory)/kernel.cpp$(ObjectSuffix): kernel.cpp $(IntermediateDirectory)/kernel.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/kernel/kernel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/kernel.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/kernel.cpp$(DependSuffix): kernel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/kernel.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/kernel.cpp$(DependSuffix) -MM "kernel.cpp"

$(IntermediateDirectory)/kernel.cpp$(PreprocessSuffix): kernel.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/kernel.cpp$(PreprocessSuffix) "kernel.cpp"

$(IntermediateDirectory)/SystemProvider.cpp$(ObjectSuffix): SystemProvider.cpp $(IntermediateDirectory)/SystemProvider.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/kernel/SystemProvider.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SystemProvider.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SystemProvider.cpp$(DependSuffix): SystemProvider.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SystemProvider.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SystemProvider.cpp$(DependSuffix) -MM "SystemProvider.cpp"

$(IntermediateDirectory)/SystemProvider.cpp$(PreprocessSuffix): SystemProvider.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SystemProvider.cpp$(PreprocessSuffix) "SystemProvider.cpp"

$(IntermediateDirectory)/memory_MemorySystem.cpp$(ObjectSuffix): memory/MemorySystem.cpp $(IntermediateDirectory)/memory_MemorySystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/kernel/memory/MemorySystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/memory_MemorySystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/memory_MemorySystem.cpp$(DependSuffix): memory/MemorySystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/memory_MemorySystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/memory_MemorySystem.cpp$(DependSuffix) -MM "memory/MemorySystem.cpp"

$(IntermediateDirectory)/memory_MemorySystem.cpp$(PreprocessSuffix): memory/MemorySystem.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/memory_MemorySystem.cpp$(PreprocessSuffix) "memory/MemorySystem.cpp"

$(IntermediateDirectory)/vga_VGATextSystem.cpp$(ObjectSuffix): vga/VGATextSystem.cpp $(IntermediateDirectory)/vga_VGATextSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/kernel/vga/VGATextSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/vga_VGATextSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/vga_VGATextSystem.cpp$(DependSuffix): vga/VGATextSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/vga_VGATextSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/vga_VGATextSystem.cpp$(DependSuffix) -MM "vga/VGATextSystem.cpp"

$(IntermediateDirectory)/vga_VGATextSystem.cpp$(PreprocessSuffix): vga/VGATextSystem.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/vga_VGATextSystem.cpp$(PreprocessSuffix) "vga/VGATextSystem.cpp"

$(IntermediateDirectory)/vga_DefaultVGADriver.cpp$(ObjectSuffix): vga/DefaultVGADriver.cpp $(IntermediateDirectory)/vga_DefaultVGADriver.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/kernel/vga/DefaultVGADriver.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/vga_DefaultVGADriver.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/vga_DefaultVGADriver.cpp$(DependSuffix): vga/DefaultVGADriver.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/vga_DefaultVGADriver.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/vga_DefaultVGADriver.cpp$(DependSuffix) -MM "vga/DefaultVGADriver.cpp"

$(IntermediateDirectory)/vga_DefaultVGADriver.cpp$(PreprocessSuffix): vga/DefaultVGADriver.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/vga_DefaultVGADriver.cpp$(PreprocessSuffix) "vga/DefaultVGADriver.cpp"

$(IntermediateDirectory)/cpu_CPUSystem.cpp$(ObjectSuffix): cpu/CPUSystem.cpp $(IntermediateDirectory)/cpu_CPUSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/kernel/cpu/CPUSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cpu_CPUSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cpu_CPUSystem.cpp$(DependSuffix): cpu/CPUSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cpu_CPUSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/cpu_CPUSystem.cpp$(DependSuffix) -MM "cpu/CPUSystem.cpp"

$(IntermediateDirectory)/cpu_CPUSystem.cpp$(PreprocessSuffix): cpu/CPUSystem.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cpu_CPUSystem.cpp$(PreprocessSuffix) "cpu/CPUSystem.cpp"

$(IntermediateDirectory)/cpu_PIC.cpp$(ObjectSuffix): cpu/PIC.cpp $(IntermediateDirectory)/cpu_PIC.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/kernel/cpu/PIC.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cpu_PIC.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cpu_PIC.cpp$(DependSuffix): cpu/PIC.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cpu_PIC.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/cpu_PIC.cpp$(DependSuffix) -MM "cpu/PIC.cpp"

$(IntermediateDirectory)/cpu_PIC.cpp$(PreprocessSuffix): cpu/PIC.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cpu_PIC.cpp$(PreprocessSuffix) "cpu/PIC.cpp"

$(IntermediateDirectory)/cpu_CPUInterruptor.cpp$(ObjectSuffix): cpu/CPUInterruptor.cpp $(IntermediateDirectory)/cpu_CPUInterruptor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/kernel/cpu/CPUInterruptor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cpu_CPUInterruptor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cpu_CPUInterruptor.cpp$(DependSuffix): cpu/CPUInterruptor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cpu_CPUInterruptor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/cpu_CPUInterruptor.cpp$(DependSuffix) -MM "cpu/CPUInterruptor.cpp"

$(IntermediateDirectory)/cpu_CPUInterruptor.cpp$(PreprocessSuffix): cpu/CPUInterruptor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cpu_CPUInterruptor.cpp$(PreprocessSuffix) "cpu/CPUInterruptor.cpp"

$(IntermediateDirectory)/input_KeyboardSystem.cpp$(ObjectSuffix): input/KeyboardSystem.cpp $(IntermediateDirectory)/input_KeyboardSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/kernel/input/KeyboardSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/input_KeyboardSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/input_KeyboardSystem.cpp$(DependSuffix): input/KeyboardSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/input_KeyboardSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/input_KeyboardSystem.cpp$(DependSuffix) -MM "input/KeyboardSystem.cpp"

$(IntermediateDirectory)/input_KeyboardSystem.cpp$(PreprocessSuffix): input/KeyboardSystem.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/input_KeyboardSystem.cpp$(PreprocessSuffix) "input/KeyboardSystem.cpp"

$(IntermediateDirectory)/input_PS2Controller.cpp$(ObjectSuffix): input/PS2Controller.cpp $(IntermediateDirectory)/input_PS2Controller.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/kernel/input/PS2Controller.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/input_PS2Controller.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/input_PS2Controller.cpp$(DependSuffix): input/PS2Controller.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/input_PS2Controller.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/input_PS2Controller.cpp$(DependSuffix) -MM "input/PS2Controller.cpp"

$(IntermediateDirectory)/input_PS2Controller.cpp$(PreprocessSuffix): input/PS2Controller.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/input_PS2Controller.cpp$(PreprocessSuffix) "input/PS2Controller.cpp"

$(IntermediateDirectory)/fs_FileSystem.cpp$(ObjectSuffix): fs/FileSystem.cpp $(IntermediateDirectory)/fs_FileSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/kernel/fs/FileSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/fs_FileSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fs_FileSystem.cpp$(DependSuffix): fs/FileSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/fs_FileSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/fs_FileSystem.cpp$(DependSuffix) -MM "fs/FileSystem.cpp"

$(IntermediateDirectory)/fs_FileSystem.cpp$(PreprocessSuffix): fs/FileSystem.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/fs_FileSystem.cpp$(PreprocessSuffix) "fs/FileSystem.cpp"

$(IntermediateDirectory)/fs_ATAController.cpp$(ObjectSuffix): fs/ATAController.cpp $(IntermediateDirectory)/fs_ATAController.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/kernel/fs/ATAController.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/fs_ATAController.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/fs_ATAController.cpp$(DependSuffix): fs/ATAController.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/fs_ATAController.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/fs_ATAController.cpp$(DependSuffix) -MM "fs/ATAController.cpp"

$(IntermediateDirectory)/fs_ATAController.cpp$(PreprocessSuffix): fs/ATAController.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/fs_ATAController.cpp$(PreprocessSuffix) "fs/ATAController.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


