#include "IOPortDevice.h"

using namespace avremu;

IOPortDevice::IOPortDevice():
    _input(0),
    _output(0)
{
    memset(_name,0,100);
    strcpy_s(_name,"unknown");
}

IOPortDevice::IOPortDevice(const char *name):
    _input(0),
    _output(0)
{
    strcpy_s(_name,name);
}

IOPortDevice::~IOPortDevice()
{}

u8 IOPortDevice::getOutput()
{
    return _output;
}

void IOPortDevice::setInput(u8 in)
{
    _input = in;
}

u8 IOPortDevice::getOutput(u8 bit)
{
    return (_output & (1<<bit)) != 0;
}

void IOPortDevice::setInput(u8 bit, u8 v)
{
    _input = (_input & ~(1<<bit)) | v<<bit;
}

const char *IOPortDevice::dupm()
{
    return 0;
}

u8 IOPortDevice::update()
{
 u8 DDR_bit = 0;
 u8 PORT_bit = 0;
 u8 In_bit = 0;
 u8 Pin_bit = 0;
 for(u8 bit=0;bit<8;bit++)
 {
     DDR_bit = ((*DDR_reg) & (1<<bit)) != 0;
     PORT_bit = ((*PORT_reg) & (1<<bit)) != 0;
     In_bit = ((_input) & (1<<bit)) != 0;

     if(DDR_bit == 0)
     {
        Pin_bit = In_bit;
     }
     else //!= 0
     {
         Pin_bit = PORT_bit;
     }

     (*PIN_reg) = ((*PIN_reg) & ~(1<<bit)) | Pin_bit<<bit;
 }
 if(_output != (*PIN_reg))
 {
     _output = (*PIN_reg);
    _callback_container.callback(this,IOPORT_CHANGE);
 }
 return Success;
}

PheripheralCallbackContainer *IOPortDevice::getCallbackContainer()
{
    return &_callback_container;
}

const char *IOPortDevice::getName()
{
    return _name;
}
