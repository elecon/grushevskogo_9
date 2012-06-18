//******************************************************************************
//
//      USER LIBRARY TYPE DEFINITIONS
//
//      Version 1.1
//
//      Copyright (c) 2001-2003, Harry E. Zhurov
//
//      $Revision: 1.1.1.1 $
//      $Date: 2003/04/24 15:31:50 $
//
//------------------------------------------------------------------------------

#ifndef USRLIB_H
#define USRLIB_H

#include "COMMDEFS.H"


byte get_checksum(const byte* ptr, const byte count);
inline byte abs(sbyte x) { if(x < 0) return -x; else return x;}

extern "C" void bin2BCD16(word num, byte* Buf);

//------------------------------------------------------------------------------
//     The Circular Buffer
//
class TCbuf
{
public:
    TCbuf(byte* const Address, const byte Size);
    bool write(const byte* data, const byte Count);
    void read(byte* const data, const byte Count);
    byte get_count() const { return count; }
    byte get_free_size() const { return size - count; }
    byte get_byte(const byte index) const;
    void clear() { count = 0; last = first; }
    bool put(const byte item);
    byte get();

private:
   //------------------------------------------------------------------------------
   //
   //  DESCRIPTON: For internal purposes
   //
    void push(const byte item); // Use this function with care - it doesn't perform free size check
    byte pop();                 // Use this function with care - it doesn't perform count check
   //------------------------------------------------------------------------------

private:
    byte* buf;
    byte  size;
    byte  count;
    byte  first;
    byte  last;
};
//------------------------------------------------------------------------------
#endif // USRLIB_H
