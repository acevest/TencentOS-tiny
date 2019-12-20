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

#include <tos.h>

__KERNEL__ void cpu_systick_init(k_cycle_t cycle_per_tick)
{
}

__KERNEL__ void cpu_init(void) {

}

__API__ cpu_cpsr_t tos_cpu_cpsr_save(void)
{
    cpu_cpsr_t oldSREG = SREG;

    port_int_disable();

    return SREG;
}

__API__ void tos_cpu_cpsr_restore(cpu_cpsr_t cpsr)
{
    SREG = cpsr;
}


__KERNEL__ void cpu_context_switch(void)
{
    SAVE_CONTEXT;

    k_curr_task->sp = (cpu_data_t *) SP;
    SP = k_next_task->sp;

    k_curr_task = k_next_task;

    RESTORE_CONTEXT;

    __asm__ __volatile__("ret");
}

__KERNEL__ void cpu_irq_context_switch(void)
{
    // DO NOTHING
}

__KERNEL__ void cpu_sched_start(void)
{
    port_sched_start();
}

__KERNEL__ k_stack_t *cpu_task_stk_init(void *entry,
                                              void *arg,
                                              void *exit,
                                              k_stack_t *stk_base,
                                              size_t stk_size)
{
    cpu_data_t *sp      = 0;
    cpu_context_t *regs = 0;

    sp = (cpu_data_t *)&stk_base[stk_size];

    sp  -= 3;
    cpu_data_t *p = (cpu_data_t *) sp;
    *(p+0) = (cpu_data_t)(((uint32_t)entry) >> 16);
    *(p+1) = (cpu_data_t)(((uint32_t)entry) >> 8);
    *(p+2) = (cpu_data_t)(((uint32_t)entry) >> 0);

    sp  -= (sizeof(cpu_context_t)/sizeof(cpu_data_t));

    regs = (cpu_context_t*) sp;

    for(int i=0; i<(sizeof(cpu_context_t)/sizeof(cpu_data_t)); i++) {
        *(sp + i) = ((i / 10) << 4) | (i % 10);
    }

    regs->SREG= (cpu_data_t)0;

    return (k_stack_t*)sp;
}

void cpu_trap_entry(cpu_data_t cause, cpu_context_t *regs)
{
    while (1) {
        // TODO
    }
}

__API__ uint32_t tos_cpu_clz(uint32_t val)
{
    uint32_t nbr_lead_zeros = 0;

    if (!(val & 0XFFFF0000)) {
        val <<= 16;
        nbr_lead_zeros += 16;
    }

    if (!(val & 0XFF000000)) {
        val <<= 8;
        nbr_lead_zeros += 8;
    }

    if (!(val & 0XF0000000)) {
        val <<= 4;
        nbr_lead_zeros += 4;
    }

    if (!(val & 0XC0000000)) {
        val <<= 2;
        nbr_lead_zeros += 2;
    }

    if (!(val & 0X80000000)) {
        nbr_lead_zeros += 1;
    }

    if (!val) {
        nbr_lead_zeros += 1;
    }

    return (nbr_lead_zeros);
}

