#ifndef I_MEMORY_LOADER_H
#define I_MEMORY_LOADER_H

#include "avremu_defs.h"

namespace avremu
{

class AVREMU_DLL IMemoryLoader
{
public:
	IMemoryLoader(){}
	virtual ~IMemoryLoader(){}

    virtual u8 writeMemory(u8 *pointer,u32 max_size) = 0;
};

} 

#endif 
