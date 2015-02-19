#ifndef PHRERIPHERAL_CALLBACK_H
#define PHRERIPHERAL_CALLBACK_H

#include "avremu_defs.h"
namespace avremu {class PheripheralCallbackContainer;}

#include "IPeripheralDevice.h"

namespace avremu
{
	class AVREMU_DLL PheripheralCallback
	{
	public:
		PheripheralCallback(){}
		virtual ~PheripheralCallback() {}

		virtual void onCallback(IPeripheralDevice *sender, u8 type) = 0;
	};

	class AVREMU_DLL PheripheralCallbackContainer
	{
	public:
		PheripheralCallbackContainer();
		~PheripheralCallbackContainer();

		void add(PheripheralCallback *);
		void remove(PheripheralCallback *);

		PheripheralCallback ** getPtr();
		u32         getCount();

		void        callback(IPeripheralDevice *sender, u8 type);
	private:
		PheripheralCallback ** _container;
		u32         _count;
	};
} 
#endif
