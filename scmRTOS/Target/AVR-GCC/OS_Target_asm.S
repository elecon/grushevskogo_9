;******************************************************************************
;*
;*              Single-Chip Microcontroller
;*              Real-Time Operation System
;*
;*            Platform Dependent Low-Level Stuff
;*
;*                       AVR-GCC
;*
;*      Version 1.10
;*
;*      Copyright (c) 2003, Harry E. Zhurov
;*
;*      $Revision: 1.3 $
;*      $Date: 2003/06/24 09:56:16 $
;*
;------------------------------------------------------------------------------


#define SPL   0x3d
#define SPH   0x3e
#define SREG  0x3f
#define RAMPZ 0x3b


;-------------------------------------------------------------------------------
     .macro save_regs

     push  r0
     push  r1
     push  r2
     push  r3
     push  r16
     push  r17
     push  r18
     push  r19
     push  r20
     push  r21
     push  r22
     push  r23
     push  r24
     push  r25
     push  r26
     push  r27
     push  r28
     push  r29
     push  r30
     push  r31

     .endm
;-------------------------------------------------------------------------------
     .macro restore_regs

     pop  r31
     pop  r30
     pop  r29
     pop  r28
     pop  r27
     pop  r26
     pop  r25
     pop  r24
     pop  r23
     pop  r22
     pop  r21
     pop  r20
     pop  r19
     pop  r18
     pop  r17
     pop  r16
     pop  r3
     pop  r2
     pop  r1
     pop  r0

     .endm

;-------------------------------------------------------------------------------
     .macro save_SP                            ; Save stack pointer

     in    r4,SPH
     push  r4
     in    r4,SPL
     push  r4

     .endm
;-------------------------------------------------------------------------------
     .macro restore_SP                         ; Restore stack pointer

     out  SPL,r4
     out  SPH,r5

     .endm
;-------------------------------------------------------------------------------
     .macro save_SREG

     in    r4,SREG
     push  r4

     .endm
;-------------------------------------------------------------------------------
     .macro restore_SREG

     pop  r4     ; SREG
     out  SREG,r4

     .endm
;-------------------------------------------------------------------------------


     .global  OS_Start
     .global  OS_ContextSwitcher
     .global  OS_ISR_Exit_ContextRestorer

     .global  OS_ISR_ProcessStackSave


;-------------------------------------------------------------------------------
     .section .text
;
;
;   r6:r7 are used as ISR SP holder
;
;-------------------------------------------------------------------------------
OS_ISR_ProcessStackSave:

     mov  r30,r24     ; Curr_SP_addr
     mov  r31,r25     ;
     in   r24,SPL
     in   r25,SPH
     adiw r24,2
     std  Z+0,r24     ; save process's Stack Pointer
     std  Z+1,r25     ;
     sbiw r24,2
     out  SPL,r24
     out  SPH,r25

     mov  r24,r6      ; Data Stack Pointer
     mov  r25,r7      ; for ISRs - its value will be loaded in caller function

     ret
;-------------------------------------------------------------------------------
OS_Start:

     in   r30,SPL
     in   r31,SPH
     adiw r30,4            ; refuse two calls (OS::Run and OS_Start)
     mov  r6,r30           ; save stack pointer
     mov  r7,r31           ; for using in ISRs

     out  SPL,r24          ; load next process Stack Pointer
     out  SPH,r25          ;


#ifdef __AVR_ATmega103__

     pop  r4
     out  RAMPZ,r4

#endif

#ifdef __AVR_ATmega128__

     ;pop  r4
     ;out  RAMPZ,r4

#endif

     rjmp L_RestoreContext
;-------------------------------------------------------------------------------
OS_ContextSwitcher:

     save_SREG
     save_regs

#ifdef __AVR_ATmega103__

     in    r4,RAMPZ
     push  r4

#endif

#ifdef __AVR_ATmega128__

     ;in    r4,RAMPZ
     ;push  r4

#endif


     mov  r30,r24     ; Curr_SP_addr
     mov  r31,r25     ;
     in   r24,SPL
     in   r25,SPH
     std  Z+0,r24     ; save process's Stack Pointer
     std  Z+1,r25     ;

     out  SPL,r22     ; load next process Stack Pointer
     out  SPH,r23     ;

#ifdef __AVR_ATmega103__

     in    r4,RAMPZ
     push  r4

#endif

#ifdef __AVR_ATmega128__

     ;in    r4,RAMPZ
     ;push  r4

#endif

L_RestoreContext:
     restore_regs
     restore_SREG
     ret
;-------------------------------------------------------------------------------
OS_ISR_Exit_ContextRestorer:

     out  SPL,r24     ; load next process Stack Pointer
     out  SPH,r25     ;

#ifdef __AVR_ATmega103__

     in    r4,RAMPZ
     push  r4

#endif

#ifdef __AVR_ATmega128__

     ;in    r4,RAMPZ
     ;push  r4

#endif

     rjmp L_RestoreContext
;-------------------------------------------------------------------------------

      .end
