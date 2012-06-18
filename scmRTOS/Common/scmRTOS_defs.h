//******************************************************************************
//*
//*                   Single-Chip Microcontroller
//*                   Real-Time Operation System
//*
//*                  Macros And Common Definitions
//*
//*      Version 1.10
//*
//*      Copyright (c) 2003, Harry E. Zhurov
//*
//*      $Revision: 1.2 $
//*      $Date: 2003/06/24 09:54:09 $
//*
//------------------------------------------------------------------------------


#ifndef scmRTOS_DEFS_H
#define scmRTOS_DEFS_H

#include "../Lib/AVR-GCC/COMMDEFS.H"
//#include "../../Src/scmRTOS_config.h"
#include "../Target/AVR-GCC/OS_Target.h"

//------------------------------------------------------------------------------
#define scmRTOS_SYSTEM_TICKS_ENABLE //CAM prudymav
//-----------------------------------------------------------------------------
//
//
//   Macro for Process Type definition
//
//
#ifndef SEPARATE_RETURN_STACK

#define DefineProcess(Name, StkSz)                                               \
class Name : public OS::TProcess                                                 \
{                                                                                \
public:                                                                          \
    Name(TPriority pr) : OS::TProcess(&Stack[StkSz/sizeof(TStackItem)]           \
                                    , pr                                         \
                                    , (void (*)())Exec)                          \
    {                                                                            \
    }                                                                            \
    OS_PROCESS static void Exec();                                               \
                                                                                 \
private:                                                                         \
    TStackItem Stack[StkSz/sizeof(TStackItem)];                                  \
                                                                                 \
}

#else

#define DefineProcess(Name, StkSz, RStkSz)                                       \
class Name : public OS::TProcess                                                 \
{                                                                                \
public:                                                                          \
    Name(TPriority pr) : OS::TProcess(&Stack[StkSz/sizeof(TStackItem)]           \
                                    , &RStack[RStkSz/sizeof(TStackItem)]         \
                                    , pr                                         \
                                    , (void (*)())Exec)                          \
    {                                                                            \
    }                                                                            \
    OS_PROCESS static void Exec();                                               \
                                                                                 \
private:                                                                         \
    TStackItem Stack [StkSz/sizeof(TStackItem)];                                 \
    TStackItem RStack[RStkSz/sizeof(TStackItem)];                                \
                                                                                 \
}


#endif
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
//
//   Macro for Channel Type definition
//
//
#define DefineChannel(Name, Capacity)                                            \
class Name : public OS::TChannel                                                 \
{                                                                                \
public:                                                                          \
    Name() : OS::TChannel(buf, sizeof(buf)) { }                                  \
                                                                                 \
private:                                                                         \
    byte buf[Capacity];                                                          \
                                                                                 \
}


//-----------------------------------------------------------------------------
//
//
//   Macro for MailBox Type definition
//
//

#ifdef scmRTOS_MAIL_BOXES_ENABLE

#define DefineMailBox(Name, MessageType)                                     \
class Name : public OS::TMailBox                                             \
{                                                                            \
public:                                                                      \
    bool CreateMessage() { Msg = new MessageType; return Msg; }              \
    void DeleteMessage() { Clear(); delete Msg; Msg = 0; }                   \
    MessageType* operator->() { return Msg; }                                \
                                                                             \
private:                                                                     \
    MessageType* Msg;                                                        \
}

#endif // scmRTOS_MAIL_BOXES_ENABLE

//-----------------------------------------------------------------------------
//
//    Priority type definition
//
//
//
#if scmRTOS_PROCESS_COUNT   == 1
    enum TPriority { pr0,  pr1 };
    #define IDLE_PRIORITY pr1

#elif scmRTOS_PROCESS_COUNT == 2
    enum TPriority { pr0,  pr1,  pr2 };
    #define IDLE_PRIORITY pr2

#elif scmRTOS_PROCESS_COUNT == 3
    enum TPriority { pr0,  pr1,  pr2,  pr3 };
    #define IDLE_PRIORITY pr3

#elif scmRTOS_PROCESS_COUNT == 4
    enum TPriority { pr0,  pr1,  pr2,  pr3, pr4 };
    #define IDLE_PRIORITY pr4

#elif scmRTOS_PROCESS_COUNT == 5
    enum TPriority { pr0,  pr1,  pr2,  pr3, pr4,  pr5 };
    #define IDLE_PRIORITY pr5

#elif scmRTOS_PROCESS_COUNT == 6
    enum TPriority { pr0,  pr1,  pr2,  pr3, pr4,  pr5,  pr6 };
    #define IDLE_PRIORITY pr6

#elif scmRTOS_PROCESS_COUNT == 7
    enum TPriority { pr0,  pr1,  pr2,  pr3, pr4,  pr5,  pr6, pr7 };
    #define IDLE_PRIORITY pr7

#elif scmRTOS_PROCESS_COUNT == 8
    enum TPriority { pr0,  pr1,  pr2,  pr3, pr4,  pr5,  pr6, pr7, pr8 };
    #define IDLE_PRIORITY pr8

#elif scmRTOS_PROCESS_COUNT == 9
    enum TPriority { pr0,  pr1,  pr2,  pr3, pr4,  pr5,  pr6,  pr7, pr8, pr9 };
    #define IDLE_PRIORITY pr9

#elif scmRTOS_PROCESS_COUNT == 10
    enum TPriority { pr0,  pr1,  pr2,  pr3, pr4,  pr5,  pr6,  pr7, pr8,  pr9, pr10 };
    #define IDLE_PRIORITY pr10

#elif scmRTOS_PROCESS_COUNT == 11
    enum TPriority { pr0,  pr1,  pr2,  pr3, pr4,  pr5,  pr6,  pr7, pr8,  pr9, pr10, pr11 };
    #define IDLE_PRIORITY pr11

#elif scmRTOS_PROCESS_COUNT == 12
    enum TPriority { pr0,  pr1,  pr2,  pr3, pr4,  pr5,  pr6,  pr7, pr8,  pr9, pr10, pr11, pr12 };
    #define IDLE_PRIORITY pr12

#elif scmRTOS_PROCESS_COUNT == 13
    enum TPriority { pr0,  pr1,  pr2,  pr3, pr4,  pr5,  pr6,  pr7, pr8,  pr9, pr10, pr11, pr12, pr13 };
    #define IDLE_PRIORITY pr13

#elif scmRTOS_PROCESS_COUNT == 14
    enum TPriority { pr0,  pr1,  pr2,  pr3, pr4,  pr5,  pr6,  pr7, pr8,  pr9, pr10, pr11, pr12, pr13, pr14 };
    #define IDLE_PRIORITY pr14

#elif scmRTOS_PROCESS_COUNT == 15
    enum TPriority { pr0,  pr1,  pr2,  pr3, pr4,  pr5,  pr6,  pr7, pr8,  pr9, pr10, pr11, pr12, pr13, pr14, pr15 };
    #define IDLE_PRIORITY pr15

#else
    #error "Invalid Process Count specification! Must be from 0 to 15."

#endif // scmRTOS_DEFS_PROC_COUNT
//-----------------------------------------------------------------------------



#endif // scmRTOS_DEFS_H
