#ifndef INTEL_HEX_FILE_LOADER_H
#define INTEL_HEX_FILE_LOADER_H

#include "avremu_defs.h"
#include "IMemoryLoader.h"

namespace avremu
{
	class AVREMU_DLL IntelHexFileLoader : public IMemoryLoader
	{
	public:
		IntelHexFileLoader(const char * file_path);
		~IntelHexFileLoader();
		// IMemoryLoader interface
	public:
		u8 writeMemory(u8 *pointer,u32 max_size);
		char *_file_path;
	};

} 

#endif 
