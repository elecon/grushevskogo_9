//******************************************************************************
//
//      User Library Source
//
//      Version 1.2
//
//      Copyright (c) 2001-2003, Harry E. Zhurov
//
//      $Revision: 1.1.1.1 $
//      $Date: 2003/04/24 15:31:50 $
//
//------------------------------------------------------------------------------

#include "USRLIB.H"
#include "COMMDEFS.H"


//-----------------------------------------------------------------------------
byte get_checksum(const byte* ptr, const byte count)
{
    byte checksum = 0;

    for(sbyte i = count; --i >= 0;) checksum ^= *(ptr++);
    return checksum;
}
//------------------------------------------------------------------------------
//
//    Circular buffer function-member description
//
//
//
TCbuf::TCbuf(byte* const Address, const byte Size) :
        buf(Address),
        size(Size),
        first(0),
        last(0),
    count(0)
{
}
//------------------------------------------------------------------------------
bool TCbuf::write(const byte* data, const byte Count)
{
    if( Count > (size - count) )
        return false;

    for(byte i = 0; i < Count; i++)
        push(*(data++));

    return true;
}
//------------------------------------------------------------------------------
void TCbuf::read(byte* data, const byte Count)
{
    byte N = Count <= count ? Count : count;

    for(byte i = 0; i < N; i++)
        data[i] = pop();
}
//------------------------------------------------------------------------------
byte TCbuf::get_byte(const byte index) const
{
    byte x = first + index;

    if(x < size)
        return buf[x];
    else
        return buf[x - size];
}

//------------------------------------------------------------------------------
bool TCbuf::put(const byte item)
{
    if(count == size)
        return false;

    push(item);
    return true;
}
//------------------------------------------------------------------------------
byte TCbuf::get()
{
    if(count)
        return pop();
    else
        return 0;
}
//------------------------------------------------------------------------------
//
//  DESCRIPTON: For internal purposes
//              Use this function with care - it doesn't perform free size check
//
void TCbuf::push(const byte item)
{
    buf[last] = item;
    last++;
    count++;

    if(last == size)
        last = 0;
}
//------------------------------------------------------------------------------
//
//  DESCRIPTON: For internal purposes
//              Use this function with care - it doesn't perform count check
//
byte TCbuf::pop()
{
    byte item = buf[first];

    count--;
    first++;
    if(first == size)
        first = 0;

    return item;
}
//------------------------------------------------------------------------------
