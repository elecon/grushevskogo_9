//******************************************************************************
//
//      Common type definitions
//
//      Version 2.0
//
//      Copyright (c) 1998-2003, Harry E. Zhurov
//
//      $Revision: 1.2 $
//      $Date: 2003/05/05 16:09:12 $
//
//------------------------------------------------------------------------------

#ifndef COMMONDEFS_HEADER
#define COMMONDEFS_HEADER


#define MAXBYTE  0xffU
#define MAXSBYTE 0x7f
#define MAXWORD  0xffffU
#define MAXINT   0x7fff

#ifndef __IAR_SYSTEMS_ASM__

typedef unsigned char byte;
typedef signed char   sbyte;
typedef unsigned int  word;
typedef unsigned long dword;

//------------------------------------------------------------------------------
//                 Macro
//
#define SetPins(Name)    portreg##Name |= pinmask##Name
#define ClearPins(Name)  portreg##Name &= ~pinmask##Name
#define TogglePins(Name) portreg##Name ^= pinmask##Name

#define SetPin(Name)    portreg##Name |= (1 << pinnum##Name)
#define ClearPin(Name)  portreg##Name &= ~(1 << pinnum##Name)
#define TogglePin(Name) portreg##Name ^= (1 << pinnum##Name)


#define TestPin(Name)   (pinreg##Name & (1 << pinnum##Name))
#define TestPinN(Name)   (~pinreg##Name & (1 << pinnum##Name))


// Macro SetBit(Reg, Bit) is (Reg |= (1 << Bit))
#define SetBit(Reg, Bit)    (Reg |= (1 << Bit))
// Macro ClearBit(Reg, Bit) is (Reg &= ~(1 << Bit))
#define ClearBit(Reg, Bit)  (Reg &= ~(1 << Bit))
#define ToggleBit(Reg, Bit) (Reg ^= (1 << Bit))
#define TestBit(Reg, Bit)   (Reg & (1 << Bit))

#define ClearFlag(Reg, Bit) (Reg |= (1 << Bit))


#define SetBits(Reg, mask)    (Reg |= mask)
#define ClearBits(Reg, mask)    (Reg &= ~mask)
#define ToggleBits(Reg, mask)    (Reg ^= mask)



#endif // __IAR_SYSTEMS_ASM__



#endif // COMMONDEFS_HEADER

//-----------------------------------------------------------------------------

/*============================================================================*/

