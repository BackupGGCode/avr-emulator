#ifndef AVR_MICROCONTROLLER_H
#define AVR_MICROCONTROLLER_H

#include "avremu_defs.h"

namespace avremu{ class AVRMicrocontroller;}

#include "IOpcodeInterpreter.h"
#include "IMemoryLoader.h"
#include "IPeripheralDevice.h"

namespace avremu
{

class AVREMU_DLL AVRMicrocontroller
{
public:
    virtual ~AVRMicrocontroller();

    u8    processTick(bool debug);

    u8*     _flash_program;     u32 _flash_program_size;
    u8*     _DATA;              u32 _DATA_size;
    u8*     _SRAM;              u32 _SRAM_size;
    u8*     _general_registers; u32 _general_registers_size;
    u8*     _io_registers;      u32 _io_registers_size;
	
	Opcode ** _opcodes;
    IOpcodeInterpreter  *_interpreter;
    virtual void    reset() = 0;

    u32     _PC;
    u32     _instruction_counter;
    u8		_program_counter_bytes;
	s8      _waitCycles;

    IPeripheralDevice **_peripherals;
    u8           _peripherals_count;

    u8*         _SREG_addr;
    u8*         _SPH_addr;
    u8*         _SPL_addr;
    u32         _cycle_counter;
protected:
    AVRMicrocontroller(IOpcodeInterpreter*);

private:
	Opcode * getOpcode();
};

}

#endif