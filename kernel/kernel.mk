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
CXXFLAGS :=  -pedantic-errors -ansi -pedantic -W -std=c++14 -Wall -fno-rtti -fno-exceptions -mno-sse -mno-sse2  -nostdlib  -O0  $(Preprocessors)
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
Objects0=$(IntermediateDirectory)/kernel.cpp$(ObjectSuffix) $(IntermediateDirectory)/memory_MemorySystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/vga_VGATextSystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/vga_DefaultVGADriver.cpp$(ObjectSuffix) 



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


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


