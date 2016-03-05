#pragma once

#include "../types.h"

namespace memory
{
	class MemorySystem
	{
		MemorySystem(const& MemoryManager) = delete;
		MemorySystem& operator=(const& MemoryManager) = delete;
		
		
		//Sice this object will be the first 
		//It will be directly loaded in memory
		//Do not rely on anything to be auto-initialize
		//Use Initialize() for that
		MemorySystem() = delete;
		~MemorySystem() = delete;
		
	public:
		void Initialize();
		
		void DetectMemory();
	};
}
