#ifndef I_PERIPHERAL_DEVICE_H
#define I_PERIPHERAL_DEVICE_H

#include "avremu_defs.h"

namespace avremu {class IPeripheralDevice;}

#include "PeripheralCallback.h"

namespace avremu
{

class AVREMU_DLL IPeripheralDevice
{
public:
	IPeripheralDevice() {}
	virtual ~IPeripheralDevice() {};

    virtual const char * dupm() = 0;
    virtual u8           update() = 0;
    virtual PheripheralCallbackContainer    *getCallbackContainer() = 0;
    virtual const char * getName() = 0;
};
} //namespace avrsim
#endif // IPERIPHERAL_H
