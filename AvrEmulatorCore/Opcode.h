#ifndef OPCODE_H
#define OPCODE_H

#include "avremu_defs.h"

namespace avremu {class AVRMicrocontroller;}
namespace avremu
{
	struct Opcode;

	typedef void OPCODE_FUNC(AVRMicrocontroller*, Opcode*);
	
	struct Opcode
	{
			u8 *memory_location;
			u8 raw_opcode_length;

			u32 code;
			u32 *params;
			u8  params_count;

			u8 cycles;

			const char * dump;

			OPCODE_FUNC *exec;
	};

}
#endif
