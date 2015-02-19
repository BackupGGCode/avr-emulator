#ifndef ATMEGA_8_MICTROCONTROLLER_H
#define ATMEGA_8_MICTROCONTROLLER_H

#include "avremu_defs.h"
#include "AVRMicrocontroller.h"
#include "IOPortDevice.h"

namespace avremu
{
class AVREMU_DLL Atmega8Microcontroller : public AVRMicrocontroller
{
public:
    Atmega8Microcontroller(IOpcodeInterpreter * opcodeInterpreter );
	~Atmega8Microcontroller(){}

    void reset();

    IOPortDevice * portB;
    IOPortDevice * portC;
    IOPortDevice * portD;
};

typedef Atmega8Microcontroller Atmega8M;
} //namespace avrsim


#endif