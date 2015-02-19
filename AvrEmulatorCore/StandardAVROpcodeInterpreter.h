//#ifndef STANDARD_AVR_OPCODE_INTERPRETER_H
//#define STANDARD_AVR_OPCODE_INTERPRETER_H

#include "avremu_defs.h"
#include "IOpcodeInterpreter.h"

namespace avremu
{
	const u32 OPC_NOP = 0x00;

	class AVREMU_DLL StandardAVROpcodeInterpreter : public IOpcodeInterpreter
	{
	public:
		StandardAVROpcodeInterpreter();
		~StandardAVROpcodeInterpreter();

		Opcode* interpret(u8* opcode_pointer, AVRMicrocontroller * uctrl);
		void release(Opcode ** opcode);
		Opcode* createNOPOpcode(u8* memory_loc);
		
	private:
		
		void addDumpString(Opcode * opc, const char * str);
	};

}

//#endif