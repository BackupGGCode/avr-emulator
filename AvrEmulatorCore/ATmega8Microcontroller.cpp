#include "ATmega8Microcontroller.h"

//#include "StandardAVROpcodeInterpreter.h"
#include "IOPortDevice.h"

using namespace avremu;

Atmega8Microcontroller::Atmega8Microcontroller(IOpcodeInterpreter *interp):
    AVRMicrocontroller(interp)
{
    _program_counter_bytes = 2;
	_flash_program_size = 8*1024;
    _SRAM_size          = 1119; // SRAM = 1024 + (32+64) general and io registers
    _DATA_size          = 1024;
    _general_registers_size = 32;
    _io_registers_size      = 64;

    _flash_program      = new u8[_flash_program_size];
    _SRAM               = new u8[_SRAM_size]; 
    _general_registers  = _SRAM;
    _io_registers       = _SRAM + _general_registers_size;
    _DATA               = _SRAM + _general_registers_size + _io_registers_size;

    _SREG_addr = _io_registers + 0x3F;
    _SPH_addr  = _io_registers + 0x3E;
    _SPL_addr  = _io_registers + 0x3D;

	_opcodes = new Opcode*[_flash_program_size];

	for(u32 i=0;i<_flash_program_size;i++)
		_opcodes[i] = 0;

    _peripherals_count = 3;
    _peripherals = new IPeripheralDevice*[3];
	
    portB  = new IOPortDevice("PortB");
    _peripherals[0] = portB;
    portB->PIN_reg = _io_registers + 0x16;
    portB->DDR_reg = _io_registers + 0x17;
    portB->PORT_reg = _io_registers + 0x18;
    portB->SFIOR_reg = _io_registers + 0x30;
    portB->_PUD_bit = 2;

    portC = new IOPortDevice("PortC");
    _peripherals[1] = portC;
    portC->PIN_reg = _io_registers + 0x13;
    portC->DDR_reg = _io_registers + 0x14;
    portC->PORT_reg = _io_registers + 0x15;
    portC->SFIOR_reg = _io_registers + 0x30;
    portC->_PUD_bit = 2;

    portD = new IOPortDevice("PortD");
    _peripherals[2] = portD;
    portD->PIN_reg = _io_registers + 0x10;
    portD->DDR_reg = _io_registers + 0x11;
    portD->PORT_reg = _io_registers + 0x12;
    portD->SFIOR_reg = _io_registers + 0x30;
    portD->_PUD_bit = 2;
	
    reset();
}

void Atmega8Microcontroller::reset()
{
    memset(_SRAM,0,1119); // RAM + registers
    _instruction_counter = 0;
    _waitCycles = 0;
    _PC = 0;
    _cycle_counter = 0;

	for(u32 i=0; i<_flash_program_size; i++)
	{
		if(_opcodes[i] != 0)
			_interpreter->release(_opcodes + i);
	}
}
