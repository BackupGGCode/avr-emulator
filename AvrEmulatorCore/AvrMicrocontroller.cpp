#include "AvrMicrocontroller.h"

using namespace avremu;

AVRMicrocontroller::AVRMicrocontroller(IOpcodeInterpreter * interp):
    _flash_program(0),_flash_program_size(0),
    _DATA(0),_DATA_size(0),
    _SRAM(0),_SRAM_size(0),
    _general_registers(0),_general_registers_size(0),
    _io_registers(0), _io_registers_size(0),
    _opcodes(0),_interpreter(interp),
    _PC(0),_instruction_counter(0),_waitCycles(0),
    _peripherals(0),_peripherals_count(0),
    _SREG_addr(0),_SPH_addr(0),_SPL_addr(0),
    _cycle_counter(0)
{}

AVRMicrocontroller::~AVRMicrocontroller()
{
    if(_peripherals != 0)
    {
        for(u8 i=0;i<_peripherals_count;i++)
        {
            delete _peripherals[i];
        }
        delete[] _peripherals;
    }

	if(_opcodes != 0)
	{
		for(u32 i=0; i<_flash_program_size; i++)
		{
			if(_opcodes[i] != 0)
				_interpreter->release(&_opcodes[i]);
		}
	}

	SAFE_DELETE_ARR(_opcodes);
	SAFE_DELETE(_interpreter);
	SAFE_DELETE_ARR(_flash_program);
    SAFE_DELETE_ARR(_SRAM);
}

u8 AVRMicrocontroller::processTick(bool debug)
{
    u8 res = Success;
    if(_waitCycles > 0)
        _waitCycles--;
    else
    {
		Opcode * opc = getOpcode();
		if(opc == 0)
		{
			TRACE_PRT(">>> Unknown OPCODE at: %x with code: %x\n", u32(_flash_program + _PC*2) ,*(_flash_program + _PC*2));
			return Error;
		}

        if(debug)
        {
			printf("%X:\t%s\n", _PC, opc->dump);
        }

		opc->exec(this,opc);
        _instruction_counter++;
    }

    for(u32 i=0;i<_peripherals_count;i++)
    {
        _peripherals[i]->update();
    }

    _cycle_counter++;

    return res;
}

Opcode * AVRMicrocontroller::getOpcode()
{
	if(_opcodes[_PC] == 0 )
		_opcodes[_PC] = _interpreter->interpret(_flash_program + _PC*2, this);
	
	return _opcodes[_PC];
}
