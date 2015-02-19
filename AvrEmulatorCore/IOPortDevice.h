#ifndef I_OPORT_DEVICE_H
#define I_OPORT_DEVICE_H

#include "avremu_defs.h"
#include "IPeripheralDevice.h"

namespace avremu
{

#define IOPORT_CHANGE 0x01

class AVREMU_DLL IOPortDevice : public IPeripheralDevice
{
public:
    IOPortDevice();
    IOPortDevice(const char * name);
    ~IOPortDevice();

    u8* DDR_reg;
    u8* PORT_reg;
    u8* PIN_reg;
    u8* SFIOR_reg;
    u8  _PUD_bit;

    u8  getOutput();
    void setInput(u8);

    u8  getOutput(u8 bit);
    void setInput(u8 bit, u8);

    // IPeripheral interface
public:
    const char *dupm();
    u8 update();
	PheripheralCallbackContainer    *getCallbackContainer();
    const char *getName();
private:
    u8 _input;
    u8 _output;
    PheripheralCallbackContainer    _callback_container;
    char _name[100];
};
}//namespace avrsim
#endif // IOPortDevice_H
