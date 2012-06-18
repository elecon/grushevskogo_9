//******************************************************************************
//*
//*                    Single-Chip Microcontroller
//*                    Real-Time Operation System
//*
//*                 Main Declarations And Definitions
//*
//*      Version 1.10
//*
//*      Copyright (c) 2003, Harry E. Zhurov
//*
//*      $Revision: 1.2 $
//*      $Date: 2003/12/03 15:28:38 $
//*
//------------------------------------------------------------------------------

#ifndef scmRTOS_H
#define scmRTOS_H

#include <stddef.h>
#include "../Lib/AVR-GCC/COMMDEFS.H"
#include "../Lib/AVR-GCC/USRLIB.H"
#include "scmRTOS_defs.h"

//------------------------------------------------------------------------------
#ifdef scmRTOS_SYSTIMER_HOOK_ENABLE
void  SystemTimerUserHook();
#endif

#ifdef scmRTOS_START_HOOK_ENABLE
void  SystemStartUserHook();
#endif
//------------------------------------------------------------------------------

//==============================================================================
extern "C" void OS_Start(TStackItem* sp);
extern "C" void OS_ContextSwitcher(TStackItem** Curr_SP, TStackItem* Next_SP);
extern "C" word OS_ISR_ProcessStackSave(TStackItem** Curr_SP);
extern "C" void OS_ISR_Exit_ContextRestorer(TStackItem* Next_SP);
//==============================================================================


//-----------------------------------------------------------------------------
//
//
//     NAME       :   OS
//
//     PURPOSE    :   Namespace for all OS stuff
//
//     DESCRIPTION:   Includes:  Kernel,
//                               Processes,
//                               Mutexes,
//                               Event Flags,
//                               Channels,
//                               Mail Boxes
//
class OS
{
public:
    class Kernel;
    class TProcess;
    class TISR_Wrapper;
    class TEventFlag;
    class TMutex;
    class TChannel;
    class TMailBox;

private:
    class MemoryManager;

public:

    #ifdef scmRTOS_MEMORY_MANAGER_ENABLE
        friend void* operator new(size_t sz);
        friend void  operator delete(void* p);
    #endif

    #if scmRTOS_PROCESS_COUNT < 8
        typedef byte TProcessMap;
    #else
        typedef word TProcessMap;
    #endif

    static void Run() { Kernel::Run(); }

    static void LockSystemTimer()   { Kernel::LockSystemTimer();   }
    static void UnlockSystemTimer() { Kernel::UnlockSystemTimer(); }

    static void WakeUpProcess(TProcess& p)      { Kernel::WakeUpProcess(p);      }
    static void ForceWakeUpProcess(TProcess& p) { Kernel::ForceWakeUpProcess(p); }

    static bool IsProcessSleeping(const TProcess& p)  { return Kernel::IsProcessSleeping(p);  }
    static bool IsProcessSuspended(const TProcess& p) { return Kernel::IsProcessSuspended(p); }

    #ifdef scmRTOS_SYSTEM_TICKS_ENABLE
    static byte GetTickCount()  { TCritSec cs; return Kernel::SysTickCount; }
    static byte GetTick200ms()   { TCritSec cs; return Kernel::SysTick200ms; }
    static byte GetTick1s() { TCritSec cs; return Kernel::SysTick1s; }
    #endif

private:
    static void SetPrioTag(TProcessMap& pm, byte pr) { pm |=  Kernel::PrioMaskTable[pr]; }
    static void ClrPrioTag(TProcessMap& pm, byte pr) { pm &= ~Kernel::PrioMaskTable[pr]; }

    inline static byte GetHighPriority(TProcessMap pm);

public:
    //------------------------------------------------------------------------
    //
    //     NAME       :   Kernel
    //
    //     PURPOSE    :   Implements kernel-level operations such as
    //                    process management, process-level scheduling,
    //                    ISR-level scheduling, system timing.
    //
    //     DESCRIPTION:
    //
    //
    class Kernel
    {
        friend class OS;
        friend class TProcess;
        friend class TISR_Wrapper;
        friend class TMutex;
        friend class TEventFlag;
        friend class TChannel;
        friend class TMailBox;
        friend class MemoryManager;

        friend void OS_SystemTimer_ISR();
        //-----------------------------------------------------------
        //
        //      Data
        //
    private:
        static byte CurProcPriority;
        static TProcessMap ReadyProcessMap;
        static OS::TProcess* ProcessTable[scmRTOS_PROCESS_COUNT+1];
        static byte ISR_NestCount;
        static const TProcessMap PrioMaskTable[scmRTOS_PROCESS_COUNT+1];

        #ifdef scmRTOS_SYSTEM_TICKS_ENABLE
        static byte SysTickCount;
		static byte SysTick200ms;
		static byte SysTick1s;
        #endif


    #ifdef COMPILER_SUPPORTS_OS_INTERRUPTS
    private:
    #else
    public:
    #endif

        INLINE static word ISR_Enter()
        {
            if(ISR_NestCount++ == 0)
            {
                TStackItem** Curr_SP_addr = &(ProcessTable[CurProcPriority]->StackPointer);
                return OS_ISR_ProcessStackSave(Curr_SP_addr);
            }
            else
                return 0;
        }
        static void ISR_Exit();

    private:
        INLINE static inline bool RegisterProcess(TProcess* p);


        static void Scheduler();
        static void SetProcessReady  (byte pr) { SetPrioTag(ReadyProcessMap, pr); }
        static void SetProcessUnready(byte pr) { ClrPrioTag(ReadyProcessMap, pr); }
        static void SystemTimer();

        static void Run();
        static void LockSystemTimer()   { TCritSec cs; LOCK_SYSTEM_TIMER();   }
        static void UnlockSystemTimer() { TCritSec cs; UNLOCK_SYSTEM_TIMER(); }
        static void WakeUpProcess(TProcess& p);
        static void ForceWakeUpProcess(TProcess& p);
        static bool IsProcessSleeping(const TProcess& p)  { TCritSec cs; if(p.Timeout) return true; else return false; }
        static bool IsProcessSuspended(const TProcess& p) { TCritSec cs; if(ReadyProcessMap & PrioMaskTable[p.Priority]) return false; else return true; }
    };

    #ifdef COMPILER_SUPPORTS_OS_INTERRUPTS
    //-------------------------------------------------------------------------
    //
    //      NAME       :   ISR Wrapper
    //
    //      PURPOSE    :   Implements common actions on enter and exit of
    //                     interrupts under the OS
    //
    //      DESCRIPTION:
    //
    //
    class TISR_Wrapper
    {
    public:
        INLINE  TISR_Wrapper()   { OS_ISR_ENTER(); }
        INLINE  ~TISR_Wrapper()  { OS_ISR_EXIT();  }

    };
    #endif // COMPILER_SUPPORTS_OS_INTERRUPTS


public:
    //-------------------------------------------------------------------------
    //
    //      NAME       :   Process
    //
    //      PURPOSE    :   Implements base class-type for application processes
    //
    //      DESCRIPTION:
    //
    //
    class TProcess
    {
        friend class OS;
        friend class Kernel;
        friend class TEventFlag;
        friend class TMutex;
        friend class TMailBox;

    public:
        #ifndef SEPARATE_RETURN_STACK
            TProcess( TStackItem* Stack, TPriority pr, void (*exec)() );
        #else
            TProcess( TStackItem* Stack, TStackItem* RStack, TPriority pr, void (*exec)() );
        #endif

        static void Sleep(word timeout = 0);

    protected:
        TStackItem* StackPointer;
        word Timeout;
        TPriority Priority;

    };
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    //
    //       NAME       :   Mutex
    //
    //       PURPOSE    :   Binary semaphore for support of mutual exclusion
    //
    //       DESCRIPTION:
    //
    //
    class TMutex
    {
    public:
        TMutex() : ProcessMap(0), Value(mvUnlocked) { }
        void Lock();
        void Unlock();

        INLINE void LockSoftly()     { TCritSec cs; if(Value == mvLocked) return; else Lock(); }
        INLINE bool IsLocked() const { TCritSec cs; if(Value == mvLocked) return true; else return false; }

    private:
        TProcessMap ProcessMap;
        enum TValue { mvLocked = 1, mvUnlocked = 0 } Value; // prefix 'mv' means: "Mutex Value"

    };
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    //
    //       NAME       : Event Flag
    //
    //       PURPOSE    : Intended for processes synchronization and
    //                    event notification one (or more) process by another
    //
    //       DESCRIPTION:
    //
    //
    class TEventFlag
    {
        enum TValue { efOn = 1, efOff= 0 }; // prefix 'ef' means: "Event Flag"

    public:
        TEventFlag(TValue init_val = efOff) : ProcessMap(0), Value(init_val) { }

        bool Wait(word timeout = 0);
        void Signal();
        void Clear() { TCritSec cs; Value = efOff; }

        INLINE bool IsSignaled() { TCritSec cs; if(Value == efOn) return true; else return false; }

    private:
        TProcessMap ProcessMap;
        TValue Value;

    };
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
    //
    //       NAME       :  Channel
    //
    //       PURPOSE    :  Byte-wide data channel for transfering of "raw" data
    //
    //       DESCRIPTION:
    //
    //
    class TChannel
    {
    public:
        TChannel(byte* buf, byte size) : Cbuf(buf, size) { }
        void Push(byte x);
        byte Pop();
        void Write(const byte* data, const byte count);
        void Read(byte* const data, const byte count);

        INLINE byte GetCount() const { TCritSec cs; return Cbuf.get_count(); }

    private:
        TProcessMap PushersProcessMap;
        TProcessMap PopersProcessMap;
        TCbuf Cbuf;

    private:
        void CheckWaiters(TProcessMap pm);
    };
    //-------------------------------------------------------------------------

public:

#ifdef scmRTOS_MAIL_BOXES_ENABLE

#ifndef scmRTOS_MEMORY_MANAGER_ENABLE
#error "Memory manager must be enabled for using of MailBoxes!"
#endif  // scmRTOS_MEMORY_MANAGER_ENABLE

    //-------------------------------------------------------------------------
    //
    //       NAME       :  Mail Box
    //
    //       PURPOSE    :  Base class for user defined mailboxes
    //
    //       DESCRIPTION:
    //
    //
    class TMailBox
    {
    public:
        TMailBox() : ProcessMap(0), NonEmpty(false) { }
        void SendMessage();

        INLINE bool IsNonEmpty() const { TCritSec cs; return NonEmpty; }
        bool WaitMessage(word timeout = 0);

    protected:
        void Clear() { TCritSec cs; NonEmpty = false; }

    private:
        TProcessMap ProcessMap;
        bool NonEmpty;

    };
    //-------------------------------------------------------------------------
#endif // scmRTOS_MAIL_BOXES_ENABLE

private:

#ifdef scmRTOS_MEMORY_MANAGER_ENABLE

#if scmRTOS_MEM_BLOCK_SIZE < 1
#error "Memory block size must be greater 0!"
#endif // scmRTOS_MEM_BLOCK_SIZE

#if scmRTOS_MEM_POOL_CAPACITY < 1
#error "Memory pool must contain at least one memory block: macro 'MEM_POOL_CAPACITY' >= 1!"
#endif // scmRTOS_MEM_POOL_CAPACITY

    typedef byte TMemoryBlock[scmRTOS_MEM_BLOCK_SIZE];

    //-------------------------------------------------------------------------
    //
    //       NAME       :  Memory Manager
    //
    //       PURPOSE    :  Perform memory block allocation/deallocation
    //                     Memory block size and available blocks number
    //                     are set at configuring
    //
    //       DESCRIPTION:
    //
    //
    class MemoryManager
    {
    public:
        static void Init();
        static void* operator new(size_t sz);
        static void  operator delete(void* p);

    public:
        static TMemoryBlock   MemoryPool[scmRTOS_MEM_POOL_CAPACITY];
        static TMemoryBlock*  MemBlockTable[scmRTOS_MEM_POOL_CAPACITY];
        static TProcessMap    ProcessMap;

        static byte  First;
        static byte  Last;
        static byte  AvailableCount;
    };
#endif // MEMORY_MANAGER_ENABLE

};

//==============================================================================
byte OS::GetHighPriority(TProcessMap pm)
{
    byte pr = 0;

    while( !(pm & 0x0001) )
    {
        pr++;
        pm >>= 1;
    }
    return pr;
}
//-----------------------------------------------------------------------------
bool OS::Kernel::RegisterProcess(TProcess* p)
{
    TProcess* proc = ProcessTable[p->Priority];

    if(!proc)
    {
        ProcessTable[p->Priority] = p;
        SetProcessReady(p->Priority);
        return true;
    }
    else
    {
        return false;
    }
}
//-----------------------------------------------------------------------------

#ifdef scmRTOS_MEMORY_MANAGER_ENABLE
inline void* operator new(size_t sz)  { return OS::MemoryManager::operator new(sz); }
inline void  operator delete(void* p) { OS::MemoryManager::operator delete(p);      }
#endif // scmRTOS_MEMORY_MANAGER_ENABLE

//-----------------------------------------------------------------------------


#endif // scmRTOS_H
