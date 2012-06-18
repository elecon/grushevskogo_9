//******************************************************************************
//*
//*              Single-Chip Microcontroller
//*              Real-Time Operation System
//*
//*                   CONFIGURATION
//*
//*
//*      Version 1.0
//*
//*      Copyright (c) 2003, Harry E. Zhurov
//*
//*      $Revision$
//*      $Date$
//*
//------------------------------------------------------------------------------

#ifndef  scmRTOS_CONFIG_H
#define  scmRTOS_CONFIG_H

//------------------------------------------------------------------------------
//
//    Specify scmRTOS Process Count. Must be less then 15
//
//
#define  scmRTOS_PROCESS_COUNT                  4

//------------------------------------------------------------------------------
//
//    scmRTOS Memory Manager. Allow user to allocate (and to free) memory blocks.
//    Block count and size (bytes) must be specified.
//
//#define  scmRTOS_MEMORY_MANAGER_ENABLED

#define  scmRTOS_MEM_BLOCK_SIZE                 8  // bytes
#define  scmRTOS_MEM_POOL_CAPACITY              8  // block count

//------------------------------------------------------------------------------
//
//    scmRTOS Mail Boxes. Implement inter-process data exchange with structured data.
//
//
//#define  scmRTOS_MAIL_BOXES_ENABLED

//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer Nested Interrupts Enable.
//
//
#define  scmRTOS_SYSTIMER_NEST_INTS_ENABLE

//-----------------------------------------------------------------------------
//
//    scmRTOS System Timer Hook.
//
//
//#define  scmRTOS_SYSTIMER_HOOK_ENABLE

//-----------------------------------------------------------------------------
//
//    scmRTOS Idle Process Hook.
//
//
//#define  scmRTOS_IDLE_HOOK_ENABLE

//-----------------------------------------------------------------------------
//
//    scmRTOS System Start Hook.
//
//
//#define  scmRTOS_START_HOOK_ENABLE

//-----------------------------------------------------------------------------


#endif // scmRTOS_CONFIG_H
