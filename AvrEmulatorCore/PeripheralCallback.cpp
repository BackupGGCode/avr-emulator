#include "PeripheralCallback.h"

using namespace avremu;


PheripheralCallbackContainer::PheripheralCallbackContainer():
    _container(new PheripheralCallback*[0]),
    _count(0)
{}

PheripheralCallbackContainer::~PheripheralCallbackContainer()
{
    SAFE_DELETE_ARR(_container);
}

void PheripheralCallbackContainer::add(PheripheralCallback * c)
{
    for(u32 i=0;i<_count;i++)
    {
        if(_container[i] == c)
            return;
    }

    PheripheralCallback ** tmp_containter = new PheripheralCallback*[_count+1];
    memcpy(tmp_containter,_container,sizeof(PheripheralCallback*)*_count);
    //sizeof(Callback*) = 4

    tmp_containter[_count] = c;
    delete[] _container;
    _container = tmp_containter;
    _count++;
}

void PheripheralCallbackContainer::remove(PheripheralCallback * c)
{
    for(u32 i=0;i<_count;i++)
    {
        if(_container[i] == c)
        {
            PheripheralCallback ** _new_container = new PheripheralCallback*[_count-1];
            memcpy(_new_container,_container,sizeof(PheripheralCallback*)*i);
            memcpy(_new_container + i,_container + (i+1),sizeof(PheripheralCallback*)*(_count - (i+1)));
            delete[] _container;
            _container = _new_container;
            _count--;
            return;
        }
    }

    return;
}

u32 PheripheralCallbackContainer::getCount()
{
    return _count;
}

void PheripheralCallbackContainer::callback(IPeripheralDevice *sender, u8 type)
{
    for(u32 i=0;i<_count;i++)
    {
        _container[i]->onCallback(sender,type);
    }
}
