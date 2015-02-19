#ifndef I_OPCODE_INTERPRETER_H
#define I_OPCODE_INTERPRETER_H

#include "avremu_defs.h"
#include "Opcode.h"

namespace avremu{ class AVRMicrocontroller; }

namespace avremu
{
	class AVREMU_DLL IOpcodeInterpreter
	{
	public:
		IOpcodeInterpreter(){}
		virtual ~IOpcodeInterpreter() {}

		virtual Opcode* interpret(u8* opcode_pointer, AVRMicrocontroller * uctrl) = 0;
		virtual void release(Opcode ** opcode) = 0;

		virtual Opcode* createNOPOpcode(u8 * mem_loc) = 0;
	};
}
#endif
