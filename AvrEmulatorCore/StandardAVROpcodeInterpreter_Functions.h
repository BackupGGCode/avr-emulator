#ifndef STANDARD_AVR_OPCODE_INTERPRETER_FUNCTIONS_H
#define STANDARD_AVR_OPCODE_INTERPRETER_FUNCTIONS_H

#include "avremu_defs.h"
#include "AvrMicrocontroller.h"
#include "Opcode.h"

namespace avremu
{
	class StandardOpcodeFnc
	{
	public:
		static void opc_nop(AVRMicrocontroller*, Opcode*);
	};
}

#endif