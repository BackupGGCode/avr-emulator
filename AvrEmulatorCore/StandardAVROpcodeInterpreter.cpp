#include "StandardAVROpcodeInterpreter.h"
#include "StandardAVROpcodeInterpreter_Functions.h"

using namespace avremu;

StandardAVROpcodeInterpreter::StandardAVROpcodeInterpreter()
{}

StandardAVROpcodeInterpreter::~StandardAVROpcodeInterpreter(){}

Opcode* StandardAVROpcodeInterpreter::interpret(u8* opcode_pointer, AVRMicrocontroller * ucontroller)
{

	Opcode * oc = new Opcode;
	
	oc->code = OPC_NOP;
	oc->cycles = 1;
	oc->memory_location = 0;
	oc->params = 0;
	oc->params_count = 0;
	oc->raw_opcode_length = 1;
	oc->exec = StandardOpcodeFnc::opc_nop;
	addDumpString(oc,"nop");

	return oc;
}

Opcode* StandardAVROpcodeInterpreter::createNOPOpcode(u8 *memory_loc)
{
	Opcode * oc = new Opcode;
	
	oc->code = OPC_NOP;
	oc->cycles = 1;
	oc->memory_location = memory_loc;
	oc->params = 0;
	oc->params_count = 0;
	oc->raw_opcode_length = 1;
	oc->exec = StandardOpcodeFnc::opc_nop;
	addDumpString(oc,"nop");

	return oc;
}

void StandardAVROpcodeInterpreter::release(Opcode ** opcode)
{
	Opcode * oc = *opcode;
	if(oc->dump != 0) delete[] oc->dump;
	if(oc->params != 0) delete[] oc->params;
	delete oc;
	*opcode = 0;
}

void StandardAVROpcodeInterpreter::addDumpString(Opcode * opc, const char * str)
{
	if(str == 0)
		opc->dump = 0;
	else
	{

		u32 str_length = strlen(str);
		opc->dump = new char[str_length + 1];
		memcpy_s((void*)opc->dump, str_length, str, str_length);
		opc->dump[str_length];
	}
}