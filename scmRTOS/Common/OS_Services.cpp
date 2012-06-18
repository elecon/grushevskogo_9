//******************************************************************************
//*
//*              Single-Chip Microcontroller
//*              Real-Time Operation System
//*
//*               OS services definitions
//*
//*      Version 1.10
//*
//*      Copyright (c) 2003, Harry E. Zhurov
//*
//*      $Revision: 1.1.1.1 $
//*      $Date: 2003/04/24 15:31:50 $
//*
//------------------------------------------------------------------------------

#include "scmRTOS.h"

//------------------------------------------------------------------------------
//
//
//      Event Flag
//
//
bool OS::TEventFlag::Wait(word timeout)
{
    TCritSec cs;

    if(Value == efOn)
    {
        Value = efOff;
        return true;
    }
    else
    {
        SetPrioTag(ProcessMap, Kernel::CurProcPriority);              // put current process to wait map
        ClrPrioTag(Kernel::ReadyProcessMap, Kernel::CurProcPriority); // remove current process from ready map


        TProcess* p = Kernel::ProcessTable[Kernel::CurProcPriority];
        p->Timeout = timeout;
        Kernel::Scheduler();

        ClrPrioTag(ProcessMap, Kernel::CurProcPriority);  // remove current process from wait list
        Value = efOff;


        word t = p->Timeout; p->Timeout = 0;

        if(timeout == 0)
            return true;

        if(t)
            return true;
        else
            return false;
    }
}
//------------------------------------------------------------------------------
void OS::TEventFlag::Signal()
{
    TCritSec cs;

    Value = efOn;
    OS::Kernel::ReadyProcessMap |= ProcessMap; // place all waiting processes to ready map

    Kernel::Scheduler();
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
//
//      Mutex
//
//
void OS::TMutex::Lock()
{
    TCritSec cs;

    if(Value == mvLocked)
    {
        SetPrioTag(ProcessMap, Kernel::CurProcPriority);              // mutex already locked by another process, put current process to wait map
        ClrPrioTag(Kernel::ReadyProcessMap, Kernel::CurProcPriority); // remove current process from ready map

        Kernel::Scheduler();
    }
    Value = mvLocked;   // mutex has been successfully locked
}
//------------------------------------------------------------------------------
void OS::TMutex::Unlock()
{
    TCritSec cs;

    Value = mvUnlocked;
    if(ProcessMap)
    {
        byte pr = GetHighPriority(ProcessMap);
        ClrPrioTag(ProcessMap, pr);                  // remove next ready process from wait map
        SetPrioTag(OS::Kernel::ReadyProcessMap, pr); // place next process to ready map
        Kernel::Scheduler();
    }
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
//
//      Channel
//
//
void OS::TChannel::CheckWaiters(TProcessMap pm)
{
    if(pm)
    {
        byte pr = GetHighPriority(pm);
        ClrPrioTag(pm, pr);                           // remove next ready process from wait map
        SetPrioTag(OS::Kernel::ReadyProcessMap, pr);  // place next process to ready map
        Kernel::Scheduler();
    }
}
//------------------------------------------------------------------------------
void OS::TChannel::Push(byte x)
{
    TCritSec cs;

    if(Cbuf.get_free_size())
    {
        Cbuf.put(x);
        CheckWaiters(PopersProcessMap);
    }
    else
    {
        SetPrioTag  (PushersProcessMap, Kernel::CurProcPriority);     // channel is full, put current process to wait map
        ClrPrioTag(Kernel::ReadyProcessMap, Kernel::CurProcPriority); // remove current process from ready map
        Kernel::Scheduler();
        Cbuf.put(x);
        CheckWaiters(PopersProcessMap);
    }
}
//------------------------------------------------------------------------------
byte OS::TChannel::Pop()
{
    TCritSec cs;
    byte x;

    if(Cbuf.get_count())
    {
        x = Cbuf.get();
        CheckWaiters(PushersProcessMap);
        return x;
    }
    else
    {
        SetPrioTag(PopersProcessMap, Kernel::CurProcPriority);        // channel is empty, put current process to wait map
        ClrPrioTag(Kernel::ReadyProcessMap, Kernel::CurProcPriority); // remove current process from ready map
        Kernel::Scheduler();
        x = Cbuf.get();
        CheckWaiters(PushersProcessMap);
        return x;
    }
}
//------------------------------------------------------------------------------
void OS::TChannel::Write(const byte* data, const byte count)
{
    TCritSec cs;

    while(Cbuf.get_free_size() < count)
    {
        SetPrioTag(PushersProcessMap, Kernel::CurProcPriority);       // channel has not enough space, put current process to wait map
        ClrPrioTag(Kernel::ReadyProcessMap, Kernel::CurProcPriority); // remove current process from ready map
        Kernel::Scheduler();
    }

    Cbuf.write(data, count);
    CheckWaiters(PopersProcessMap);
}
//------------------------------------------------------------------------------
void OS::TChannel::Read(byte* const data, const byte count)
{
    TCritSec cs;

    while(Cbuf.get_count() < count)
    {
        SetPrioTag(PopersProcessMap, Kernel::CurProcPriority);        // channel doesn't contain enough data, put current process to wait map
        ClrPrioTag(Kernel::ReadyProcessMap, Kernel::CurProcPriority); // remove current process from ready map
        Kernel::Scheduler();
    }

    Cbuf.read(data, count);
    CheckWaiters(PushersProcessMap);
}
//------------------------------------------------------------------------------


#ifdef scmRTOS_MEMORY_MANAGER_ENABLE

#ifdef scmRTOS_MAIL_BOXES_ENABLE

//------------------------------------------------------------------------------
//
//
//      Mail Box
//
//

void OS::TMailBox::SendMessage()
{
    TCritSec cs;

    NonEmpty = true;
    if(ProcessMap)
    {
        byte pr = GetHighPriority(ProcessMap);
        ClrPrioTag(ProcessMap, pr);                  // remove next ready process from wait map
        SetPrioTag(OS::Kernel::ReadyProcessMap, pr); // place next process to ready map
        Kernel::Scheduler();
    }
}
//------------------------------------------------------------------------------
bool OS::TMailBox::WaitMessage(word timeout)
{
    TCritSec cs;

    if(NonEmpty)
    {
        return true;
    }
    else
    {
        SetPrioTag(ProcessMap, Kernel::CurProcPriority);              // put current process to wait map
        ClrPrioTag(Kernel::ReadyProcessMap, Kernel::CurProcPriority); // remove current process from ready map

        TProcess* p = Kernel::ProcessTable[Kernel::CurProcPriority];
        p->Timeout = timeout;
        Kernel::Scheduler();

        ClrPrioTag(ProcessMap, Kernel::CurProcPriority);  // remove current process from wait list

        word t = p->Timeout;

        p->Timeout = 0;
        if(t)
            return true;
        else
            return false;
    }
}
//------------------------------------------------------------------------------
#endif // scmRTOS_MAIL_BOXES_ENABLE


//------------------------------------------------------------------------------
//
//
//      Memory Manager
//
//

OS::TMemoryBlock  OS::MemoryManager::MemoryPool[scmRTOS_MEM_POOL_CAPACITY];
OS::TMemoryBlock* OS::MemoryManager::MemBlockTable[scmRTOS_MEM_POOL_CAPACITY];
OS::TProcessMap   OS::MemoryManager::ProcessMap;
byte OS::MemoryManager::First = 0;
byte OS::MemoryManager::Last  = scmRTOS_MEM_POOL_CAPACITY-1;
byte OS::MemoryManager::AvailableCount = scmRTOS_MEM_POOL_CAPACITY;

//------------------------------------------------------------------------------
void* OS::MemoryManager::operator new(size_t sz)
{
    TCritSec cs;

    if(sz > scmRTOS_MEM_BLOCK_SIZE)
        return 0;

    if(AvailableCount == 0)
    {
        SetPrioTag(ProcessMap, Kernel::CurProcPriority);              // there is no available memory block, put current process to wait map
        ClrPrioTag(Kernel::ReadyProcessMap, Kernel::CurProcPriority); // remove current process from ready map

        Kernel::Scheduler();
    }

    AvailableCount--;
    void* p = MemBlockTable[First++];
    if(First == scmRTOS_MEM_POOL_CAPACITY)
        First = 0;

    return p;
}
//------------------------------------------------------------------------------
void OS::MemoryManager::operator delete(void* p)
{
    TCritSec cs;

    MemBlockTable[Last++] = (TMemoryBlock*)p;
    p = 0;

    if(Last == scmRTOS_MEM_POOL_CAPACITY)
        Last = 0;

    AvailableCount++;
    if(ProcessMap)
    {
        byte pr = GetHighPriority(ProcessMap);
        ClrPrioTag(ProcessMap, pr);                  // remove next ready process from wait map
        SetPrioTag(OS::Kernel::ReadyProcessMap, pr); // place next process to ready map
        Kernel::Scheduler();
    }
}
//------------------------------------------------------------------------------
//#pragma optimize=z
void OS::MemoryManager::Init()
{
    for(byte i = 0; i < scmRTOS_MEM_POOL_CAPACITY; i++)
    {
        MemBlockTable[i] = &MemoryPool[i];
    }
}
//------------------------------------------------------------------------------

#endif  // scmRTOS_MEMORY_MANAGER_ENABLE

//------------------------------------------------------------------------------

