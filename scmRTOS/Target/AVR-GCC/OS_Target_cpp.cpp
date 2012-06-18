//******************************************************************************
//*
//*              Single-Chip Microcontroller
//*              Real-Time Operation System
//*
//*               Platform Dependent Stuff
//*
//*                       AVR-GCC
//*
//*      Version 1.10
//*
//*      Copyright (c) 2003, Harry E. Zhurov
//*
//*      $Revision: 1.2 $
//*      $Date: 2003/06/24 09:56:16 $
//*
//------------------------------------------------------------------------------


#include <scmRTOS.h>

#if defined(AVRm103) || defined(AVRm128)

#define REGS_COUNT 21     //  18 regs + RAMPZ

#else

#define REGS_COUNT 20     //  18 regs

#endif
//------------------------------------------------------------------------------
//
//
//
//
//
OS::TProcess::TProcess(TStackItem* Stack, TPriority pr, void (*exec)())
    : StackPointer(Stack)
    , Priority(pr)
    , Timeout(0)
{
    Kernel::RegisterProcess(this);

    //---------------------------------------------------------------
    //
    //  Prepare Process Stack Frame
    //
    *(--StackPointer) =   (word)(exec);           // SP (low  byte)
    *(--StackPointer) = ( (word)(exec) >> 8);     // SP (high byte)
    *(--StackPointer) = 0x80;                     // SREG value: I-bit set, enable interrupts
    StackPointer     -= REGS_COUNT + 1;           // emulate saving regs
}
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//
//
//    Idle Process
//
//
//    Context size = 23. 31 - 23 = 8 bytes for process
//    Return stack depth = 10 -> 5 calls
//
DefineProcess(TIdleProcess, 40) IdleProcess(IDLE_PRIORITY);

OS_PROCESS void TIdleProcess::Exec()
{

    for(;;)
    {
        #ifdef scmRTOS_IDLE_HOOK_ENABLE
        IdleProcessUserHook();
        #endif
    }
}

//------------------------------------------------------------------------------
#ifdef COMPILER_SUPPORTS_OS_INTERRUPTS
OS_INTERRUPT void OS_SystemTimer_ISR()
{
    OS::TISR_Wrapper ISR;
    OS::Kernel::SystemTimer();

    #ifdef scmRTOS_SYSTIMER_NEST_INTS_ENABLE
    MCU_ENABLE_INTERRUPT();
    #endif

    #ifdef scmRTOS_SYSTIMER_HOOK_ENABLE
    SystemTimerUserHook();
    #endif
}
#else
OS_INTERRUPT void OS_SystemTimer_ISR()
{
    OS_ISR_ENTER();
    OS::Kernel::SystemTimer();

    #ifdef scmRTOS_SYSTIMER_NEST_INTS_ENABLE
    MCU_ENABLE_INTERRUPT();
    #endif

    #ifdef scmRTOS_SYSTIMER_HOOK_ENABLE
    SystemTimerUserHook();
    #endif

    OS_ISR_EXIT();
}
#endif // COMPILER_SUPPORTS_OS_INTERRUPTS
//------------------------------------------------------------------------------

