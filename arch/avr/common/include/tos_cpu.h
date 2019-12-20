/*----------------------------------------------------------------------------
 * Tencent is pleased to support the open source community by making TencentOS
 * available.
 *
 * Copyright (C) 2019 THL A29 Limited, a Tencent company. All rights reserved.
 * If you have downloaded a copy of the TencentOS binary from Tencent, please
 * note that the TencentOS binary is licensed under the BSD 3-Clause License.
 *
 * If you have downloaded a copy of the TencentOS source code from Tencent,
 * please note that TencentOS source code is licensed under the BSD 3-Clause
 * License, except for the third-party components listed below which are
 * subject to different license terms. Your integration of TencentOS into your
 * own projects may require compliance with the BSD 3-Clause License, as well
 * as the other licenses applicable to the third-party components included
 * within TencentOS.
 *---------------------------------------------------------------------------*/

#ifndef _TOS_CPU_H_
#define _TOS_CPU_H_

typedef struct cpu_context_st {
    //union { struct { uint8_t _2, _1, _0; }; } PC;
    uint8_t  sreg;
    uint8_t  r1;
    uint8_t  r2;
    uint8_t  r3;
    uint8_t  r4;
    uint8_t  r5;
    uint8_t  r6;
    uint8_t  r7;
    uint8_t  r8;
    uint8_t  r9;
    uint8_t r10;
    uint8_t r11;
    uint8_t r12;
    uint8_t r13;
    uint8_t r14;
    uint8_t r15;
    uint8_t r16;
    uint8_t r17;
    uint8_t r18;
    uint8_t r19;
    uint8_t r20;
    uint8_t r21;
    uint8_t r22;
    uint8_t r23;
    uint8_t r24;
    uint8_t r25;
    uint8_t r26;
    uint8_t r27;
    uint8_t r28;
    uint8_t r29;
    uint8_t r30;
    uint8_t r31;
} cpu_context_t;


__API__ uint32_t        tos_cpu_clz(uint32_t val);

__API__ void            tos_cpu_int_disable(void);

__API__ void            tos_cpu_int_enable(void);

__API__ cpu_cpsr_t      tos_cpu_cpsr_save(void);

__API__ void            tos_cpu_cpsr_restore(cpu_cpsr_t cpsr);


__KERNEL__ void         cpu_init(void);

__KERNEL__ void         cpu_reset(void);

__KERNEL__ void         cpu_systick_init(k_cycle_t cycle_per_tick);

__KERNEL__ void         cpu_sched_start(void);

__KERNEL__ void         cpu_context_switch(void);

__KERNEL__ void         cpu_irq_context_switch(void);

__KERNEL__ k_stack_t   *cpu_task_stk_init(void *entry,
                                                          void *arg,
                                                          void *exit,
                                                          k_stack_t *stk_base,
                                                          size_t stk_size);

#if TOS_CFG_TICKLESS_EN > 0u

__KERNEL__ void         cpu_systick_resume(void);

__KERNEL__ void         cpu_systick_suspend(void);

__KERNEL__ void         cpu_systick_reload_reset(void);

__KERNEL__ void         cpu_systick_pending_reset(void);

__KERNEL__ k_time_t     cpu_systick_max_delay_millisecond(void);

__KERNEL__ void         cpu_systick_expires_set(k_time_t millisecond);

__KERNEL__ void         cpu_systick_reset(void);

#endif

#if TOS_CFG_PWR_MGR_EN > 0u

__KERNEL__ void cpu_sleep_mode_enter(void);

__KERNEL__ void cpu_stop_mode_enter(void);

__KERNEL__ void cpu_standby_mode_enter(void);

#endif

#if TOS_CFG_FAULT_BACKTRACE_EN > 0u

#error "unsupport now"

#endif

/* Allocates CPU status register word. */
#define TOS_CPU_CPSR_ALLOC()    cpu_cpsr_t cpu_cpsr = (cpu_cpsr_t)0u

/* Save CPU status word & disable interrupts.*/
#define TOS_CPU_INT_DISABLE() \
    do { \
        cpu_cpsr = tos_cpu_cpsr_save(); \
    } while (0)

/* Restore CPU status word.                     */
#define  TOS_CPU_INT_ENABLE() \
    do { \
        tos_cpu_cpsr_restore(cpu_cpsr); \
    } while (0)


#endif /* _TOS_CPU_H_ */
