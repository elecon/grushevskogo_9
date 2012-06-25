//******************************************************************************
//*
//*              Single-Chip Microcontroller
//*              Real-Time Operation System
//*
//*           Declarations & Macro Definitions
//*
//*                     AVR-GCC
//*
//*      Version 1.10
//*
//*      Copyright (c) 2003, Harry E. Zhurov
//*
//*      $Revision: 1.2 $
//*      $Date: 2003/06/24 09:56:16 $
//*
//------------------------------------------------------------------------------

#ifndef scmRTOS_AVR_H
#define scmRTOS_AVR_H


#include "../../Lib/AVR-GCC/COMMDEFS.H"
#include <compat/ina90.h>
#include <avr/io.h>

//-----------------------------------------------------------------------------
//
//    Target specific types
//
//
typedef byte TStackItem;
typedef byte TStatusReg;
//#define Uart0Rx_ISR SIG_UART0_RECV
//#define Uart0Tx_ISR SIG_UART0_TRANS
//#define Uart1Rx_ISR SIG_UART1_RECV
//#define Uart1Tx_ISR SIG_UART1_TRANS
	#define Uart0Rx_ISR USART0_RX_vect
	#define Uart0Tx_ISR USART0_TX_vect
	#define Uart1Rx_ISR USART1_RX_vect
	#define Uart1Tx_ISR USART1_TX_vect
	#define Uart2Rx_ISR USART2_RX_vect
	#define Uart2Tx_ISR USART2_TX_vect

//-----------------------------------------------------------------------------
//
//    Configuration macros
//
//
//#define COMPILER_SUPPORTS_OS_INTERRUPTS

#define OS_PROCESS

#define INLINE __attribute__ ((always_inline))

#define MCU_ENABLE_INTERRUPT()   _SEI()
#define MCU_DISABLE_INTERRUPT()  _CLI()

#ifdef  COMPILER_SUPPORTS_OS_INTERRUPTS
#define OS_INTERRUPT __attribute__ ((signal)) __attribute__ ((naked))
#else
#define OS_INTERRUPT extern "C"  __attribute__ ((signal)) __attribute__ ((naked))
#endif



//-----------------------------------------------------------------------------
//
//    System Timer
//
#define OS_SystemTimer_ISR SIG_OVERFLOW0
#if (__AVR_ATmega1281__||__AVR_ATmega1280__) //MRTP_4_s
	#define LOCK_SYSTEM_TIMER()    ( TIMSK0 &= ~(1 << TOIE0) )
	#define UNLOCK_SYSTEM_TIMER()  ( TIMSK0 |=  (1 << TOIE0) )
#endif
#if (__AVR_ATmega128__)  //for MRTP_4
	#define LOCK_SYSTEM_TIMER()    ( TIMSK &= ~(1 << TOIE0) )
	#define UNLOCK_SYSTEM_TIMER()  ( TIMSK |=  (1 << TOIE0) )
#endif

OS_INTERRUPT void OS_SystemTimer_ISR();
//-----------------------------------------------------------------------------

#ifndef ENABLE_BIT_DEFINITIONS
#define ENABLE_BIT_DEFINITIONS
#endif
//-----------------------------------------------------------------------------

#ifdef scmRTOS_IDLE_HOOK_ENABLE
void IdleProcessUserHook();
#endif

//-----------------------------------------------------------------------------
//
//     The Critital Section Wrapper
//
//
class TCritSec
{
public:
    TCritSec () : StatusReg(SREG) { _CLI(); }
    ~TCritSec() { SREG = StatusReg; }

private:
    TStatusReg StatusReg;

};
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
//    System Timer start macro
//
//    Timer/Counter0 is used as System Timer. Precaler = 64
//
//
#if (__AVR_ATmega128__)  //for MRTP_4
	#define  START_SYSTEM_TIMER() \
		TCCR0 = 0x04;           \
		TIMSK |=  (1 << TOIE0)
#endif
#if (__AVR_ATmega1280__||__AVR_ATmega1281__) //for MK_035
	#define  START_SYSTEM_TIMER() \
		TCCR0B =  (1 << CS01) | (1 << CS00) ;	\
		TIMSK0 |= (1 << TOIE0);
#endif

//-----------------------------------------------------------------------------
//
//    Target platform specific actions.
//
//    There are no actions for AVR
//
//
//#define EXECUTE_PLATFORM_SPECIFIC_STUFF()

//#define SPL   0x3d
//#define SPH   0x3e
//#define SREG  0x3f
//#define RAMPZ 0x3b



#if defined(AVRm103) || defined(AVRm128)

//-----------------------------------------------------------------------------
//
//    Save Context macro.
//
//    Used when ISR enter occures
//
//
#define  SAVE_CONTEXT()                              \
               asm("mov   r5,r16");                  \
               asm("in    r16,0x3f");  /*  SREG */   \
               asm("sbr   r16,0x80");  /* I = 1 */   \
               asm("push  r16");                     \
                                                     \
               asm("in    r4,0x3e");   /*  SPH */    \
               asm("push  r4");                      \
               asm("in    r4,0x3d");   /*  SPL */    \
               asm("push  r4");                      \
                                                     \
               asm("push  r0");                      \
               asm("push  r1");                      \
               asm("push  r2");                      \
               asm("push  r3");                      \
               asm("push  r5");     /*r5 <- r16*/    \
               asm("push  r17");                     \
               asm("push  r18");                     \
               asm("push  r19");                     \
               asm("push  r20");                     \
               asm("push  r21");                     \
               asm("push  r22");                     \
               asm("push  r23");                     \
               asm("push  r24");                     \
               asm("push  r25");                     \
               asm("push  r26");                     \
               asm("push  r27");                     \
               asm("push  r28");                     \
               asm("push  r29");                     \
               asm("push  r30");                     \
               asm("push  r31");                     \
                                                     \
               asm("in    r4,0x3b");   /* RAMPZ */   \
               asm("push  r4")

//-----------------------------------------------------------------------------
//
//    Restore Context macro.
//
//    Used when processor exits from nested interrupt
//
//
#define  RESTORE_CONTEXT()                          \
               asm("pop  r4");                      \
               asm("out  0x3b,r4");   /* RAMPZ */   \
                                                    \
               asm("pop  r31");                     \
               asm("pop  r30");                     \
               asm("pop  r29");                     \
               asm("pop  r28");                     \
               asm("pop  r27");                     \
               asm("pop  r26");                     \
               asm("pop  r25");                     \
               asm("pop  r24");                     \
               asm("pop  r23");                     \
               asm("pop  r22");                     \
               asm("pop  r21");                     \
               asm("pop  r20");                     \
               asm("pop  r19");                     \
               asm("pop  r18");                     \
               asm("pop  r17");                     \
               asm("pop  r16");                     \
               asm("pop  r3");                      \
               asm("pop  r2");                      \
               asm("pop  r1");                      \
               asm("pop  r0");                      \
                                                    \
               asm("pop  r4");                      \
               asm("out  0x3d,r4");  /*  SPL */     \
               asm("pop  r4");                      \
               asm("out  0x3e,r4");  /*  SPH */     \
                                                    \
               asm("pop  r4");                      \
               asm("out  0x3f,r4")   /* SREG */


#else   //  non mega103 and mega128 AVRs

//-----------------------------------------------------------------------------
//
//    Save Context macro.
//
//    Used when ISR enter occures
//
//
#define  SAVE_CONTEXT()                              \
               asm("mov   r5,r16");                  \
               asm("in    r16,0x3f");  /*  SREG */   \
               asm("sbr   r16,0x80");  /* I = 1 */   \
               asm("push  r16");                     \
                                                     \
               asm("push  r0");                      \
               asm("push  r1");                      \
               asm("push  r2");                      \
               asm("push  r3");                      \
               asm("push  r5");     /*r5 <- r16*/    \
               asm("push  r17");                     \
               asm("push  r18");                     \
               asm("push  r19");                     \
               asm("push  r20");                     \
               asm("push  r21");                     \
               asm("push  r22");                     \
               asm("push  r23");                     \
               asm("push  r24");                     \
               asm("push  r25");                     \
               asm("push  r26");                     \
               asm("push  r27");                     \
               asm("push  r28");                     \
               asm("push  r29");                     \
               asm("push  r30");                     \
               asm("push  r31")


//-----------------------------------------------------------------------------
//
//    Restore Context macro.
//
//    Used when processor exits from nested interrupt
//
//
#define  RESTORE_CONTEXT()                          \
               asm("pop  r31");                     \
               asm("pop  r30");                     \
               asm("pop  r29");                     \
               asm("pop  r28");                     \
               asm("pop  r27");                     \
               asm("pop  r26");                     \
               asm("pop  r25");                     \
               asm("pop  r24");                     \
               asm("pop  r23");                     \
               asm("pop  r22");                     \
               asm("pop  r21");                     \
               asm("pop  r20");                     \
               asm("pop  r19");                     \
               asm("pop  r18");                     \
               asm("pop  r17");                     \
               asm("pop  r16");                     \
               asm("pop  r3");                      \
               asm("pop  r2");                      \
               asm("pop  r1");                      \
               asm("pop  r0");                      \
                                                    \
               asm("pop  r4");                      \
               asm("out  0x3f,r4");   /* SREG */    \
               asm("ret")


#endif // AVRm103 || AVRm128
//-----------------------------------------------------------------------------
//
//
//	   ISR Enter/Exit macros
//
//
#define OS_ISR_ENTER()  \
        SAVE_CONTEXT(); \
        word addr = OS::Kernel::ISR_Enter(); if(addr) SP = addr

#define OS_ISR_EXIT()           \
        OS::Kernel::ISR_Exit(); \
        RESTORE_CONTEXT()
//-----------------------------------------------------------------------------


#endif // scmRTOS_AVR_H
