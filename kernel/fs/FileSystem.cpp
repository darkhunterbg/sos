#include "FileSystem.h"

namespace fs
{
	FileSystem::FileSystem()
	{
		ataController = new ATAController();
	}
	
	FileSystem::~FileSystem()
	{
		delete ataController;
	}
	
	ATAController& FileSystem::GetATAController()
	{
		return *ataController;
	}
}
