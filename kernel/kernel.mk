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
Date                   :=05/03/2016
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
LinkOptions            :=  -s @"asmobjects.txt" -Wl,-Ttext=0x20000 -nostdlib
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
CXXFLAGS :=  -pedantic-errors -ansi -pedantic -W -std=c++14 -Wall -nostdlib -fno-rtti -fno-exceptions -mno-sse -mno-sse2  -O0  $(Preprocessors)
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
Objects0=$(IntermediateDirectory)/start.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/start.cpp$(ObjectSuffix): start.cpp $(IntermediateDirectory)/start.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/SOS/sos/kernel/start.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/start.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/start.cpp$(DependSuffix): start.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/start.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/start.cpp$(DependSuffix) -MM "start.cpp"

$(IntermediateDirectory)/start.cpp$(PreprocessSuffix): start.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/start.cpp$(PreprocessSuffix) "start.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


