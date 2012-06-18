//******************************************************************************
//*
//*              Single-Chip Microcontroller
//*              Real-Time Operation System
//*
//*                  OS Kernel
//*
//*      Version 1.10
//*
//*      Copyright (c) 2003, Harry E. Zhurov
//*
//*      $Revision: 1.5 $
//*      $Date: 2003/06/24 09:54:09 $
//*
//------------------------------------------------------------------------------

#include "scmRTOS.h"

//------------------------------------------------------------------------------
OS::TProcess* OS::Kernel::ProcessTable[scmRTOS_PROCESS_COUNT+1];
OS::TProcessMap OS::Kernel::ReadyProcessMap;
byte OS::Kernel::CurProcPriority;
byte OS::Kernel::ISR_NestCount;

#ifdef scmRTOS_SYSTEM_TICKS_ENABLE
byte OS::Kernel::SysTickCount;
byte OS::Kernel::SysTick200ms;
byte OS::Kernel::SysTick1s;
#endif


//-----------------------------------------------------------------------------
//
//
//   NAME   :  PrioMaskTable
//
//   PURPOSE:  Table that contains masks of priorites for TProcessMap variables
//
//
//

#if scmRTOS_PROCESS_COUNT == 1
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1
};

#elif scmRTOS_PROCESS_COUNT == 2
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1, 1 << 2
};

#elif scmRTOS_PROCESS_COUNT == 3
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1, 1 << 2, 1 << 3
};

#elif scmRTOS_PROCESS_COUNT == 4
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4
};

#elif scmRTOS_PROCESS_COUNT == 5
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5
};

#elif scmRTOS_PROCESS_COUNT == 6
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6
};

#elif scmRTOS_PROCESS_COUNT == 7
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7
};

#elif scmRTOS_PROCESS_COUNT == 8
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7,
    1 << 8
};

#elif scmRTOS_PROCESS_COUNT == 9
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7,
    1 << 8, 1 << 9
};

#elif scmRTOS_PROCESS_COUNT == 10
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7,
    1 << 8, 1 << 9, 1 << 10
};

#elif scmRTOS_PROCESS_COUNT == 11
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1, 1 << 2,  1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7,
    1 << 8, 1 << 9, 1 << 10, 1 << 11
};

#elif scmRTOS_PROCESS_COUNT == 12
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1, 1 << 2,  1 << 3,  1 << 4, 1 << 5, 1 << 6, 1 << 7,
    1 << 8, 1 << 9, 1 << 10, 1 << 11, 1 << 12
};

#elif scmRTOS_PROCESS_COUNT == 13
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1, 1 << 2,  1 << 3,  1 << 4,  1 << 5, 1 << 6, 1 << 7,
    1 << 8, 1 << 9, 1 << 10, 1 << 11, 1 << 12, 1 << 13
};

#elif scmRTOS_PROCESS_COUNT == 14
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1, 1 << 2,  1 << 3,  1 << 4,  1 << 5,  1 << 6, 1 << 7,
    1 << 8, 1 << 9, 1 << 10, 1 << 11, 1 << 12, 1 << 13, 1 << 14
};

#elif scmRTOS_PROCESS_COUNT == 15
const OS::TProcessMap OS::Kernel::PrioMaskTable[scmRTOS_PROCESS_COUNT+1] =
{
    1 << 0, 1 << 1, 1 << 2,  1 << 3,  1 << 4,  1 << 5,  1 << 6,  1 << 7,
    1 << 8, 1 << 9, 1 << 10, 1 << 11, 1 << 12, 1 << 13, 1 << 14, 1 << 15
};

#else
    #error "Invalid Process Count specification! Must be from 0 to 15."

#endif // scmRTOS_DEFS_PROC_COUNT

//-----------------------------------------------------------------------------


//------------------------------------------------------------------------------
void OS::Kernel::Run()
{
    for(byte i = 0; i < scmRTOS_PROCESS_COUNT; i++)
    {
        TProcess* p = ProcessTable[i];

        if(!p) return;
    }

#ifdef scmRTOS_MEMORY_MANAGER_ENABLE
    MemoryManager::Init();
#endif

//    EXECUTE_PLATFORM_SPECIFIC_STUFF();
    START_SYSTEM_TIMER();

#ifdef scmRTOS_START_HOOK_ENABLE
    SystemStartUserHook();
#endif


    TStackItem* sp = ProcessTable[0]->StackPointer;
    OS_Start(sp);
}
//------------------------------------------------------------------------------
void OS::Kernel::Scheduler()
{
    TCritSec cs;

    if(ISR_NestCount) return;

    byte NextPrty = GetHighPriority(ReadyProcessMap);
    if(NextPrty != CurProcPriority)
    {
        TStackItem*  Next_SP = ProcessTable[NextPrty]->StackPointer;
        TStackItem** Curr_SP_addr = &(ProcessTable[CurProcPriority]->StackPointer);
        CurProcPriority = NextPrty;
        OS_ContextSwitcher(Curr_SP_addr, Next_SP);
    }
}
//------------------------------------------------------------------------------
void OS::Kernel::ISR_Exit()
{
    TCritSec cs;

    if(--ISR_NestCount) return;

    byte NextProcPriority = GetHighPriority(ReadyProcessMap);
    TStackItem*  Next_SP = ProcessTable[NextProcPriority]->StackPointer;
    CurProcPriority = NextProcPriority;
    OS_ISR_Exit_ContextRestorer(Next_SP);
}
//------------------------------------------------------------------------------
void OS::Kernel::SystemTimer()
{
    #ifdef scmRTOS_SYSTEM_TICKS_ENABLE
    SysTickCount++;

	if(SysTickCount>26) //40ms
	{
		SysTickCount = 0;
		SysTick200ms++;
		if(SysTick200ms>4)//200ms
		{
			SysTick200ms = 0;
			SysTick1s++;
			if(SysTick1s>4)//1s
			{
				SysTick1s = 0;
			}
		}
	}
	#endif

    for(byte i = 0; i < scmRTOS_PROCESS_COUNT; i++)
    {
        TProcess* p = ProcessTable[i];

        if(p->Timeout > 0)
            if(--p->Timeout == 0) SetProcessReady(p->Priority);
    }
}
//------------------------------------------------------------------------------
void OS::TProcess::Sleep(word timeout)
{
    TCritSec cs;

    Kernel::ProcessTable[Kernel::CurProcPriority]->Timeout = timeout;
    Kernel::SetProcessUnready(Kernel::CurProcPriority);
    Kernel::Scheduler();
}
//------------------------------------------------------------------------------
void OS::Kernel::WakeUpProcess(TProcess& p)
{
    TCritSec cs;

    if(p.Timeout)
    {
        p.Timeout = 0;
        SetProcessReady(p.Priority);
        Scheduler();
    }
}
//------------------------------------------------------------------------------
void OS::Kernel::ForceWakeUpProcess(TProcess& p)
{
    TCritSec cs;

    p.Timeout = 0;
    SetProcessReady(p.Priority);
    Scheduler();
}
//------------------------------------------------------------------------------

