#pragma once
#include "../Types.h"
#include "ATAController.h"

namespace fs
{
class FileSystem
{
    FileSystem(const& FileSystem) = delete;
    FileSystem& operator=(const& FileSystem) = delete;
	
	private:
	ATAController* ataController = nullptr;
	
	public :
	FileSystem();
	~FileSystem();
	
	ATAController& GetATAController();
};
}
