#ifndef _PORT_H
#define _PORT_H

#if 1
#include <avr/io.h>
#else
#define __SFR_OFFSET 0x20
#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define _MMIO_WORD(mem_addr) (*(volatile uint16_t *)(mem_addr))

#define _SFR_IO8(io_addr) _MMIO_BYTE((io_addr) + __SFR_OFFSET)
#define _SRF_IO16(io_addr) _MMIO_WORD((io_addr) + __SFR_OFFSET)

#define DDRB    _SFR_IO8(0x04)
#define PORTB   _SFR_IO8(0x05)
#define DDRC    _SFR_IO8(0x07)
#define PORTC   _SFR_IO8(0x08)
#define DDRD    _SFR_IO8(0x0A)
#define PORTD   _SFR_IO8(0x0B)
#define SPL     _SRF_IO8(0x3D)
#define SPH     _SRF_IO8(0x3E)
#define SP      _SFR_IO16(0x3D)
#define SREG    _SFR_IO8(0x3F)
#endif


#ifndef __ASSEMBLER__

#define cli()  __asm__ __volatile__ ("cli" ::: "memory")
#define sei()  __asm__ __volatile__ ("sei" ::: "memory")

#define port_int_disable() cli()

#define port_int_enable()  sei()


#define SAVE_CONTEXT  \
    __asm__ __volatile__( \
    "PUSH R31\n"    \
    "PUSH R30\n"    \
    "PUSH R29\n"    \
    "PUSH R28\n"    \
    "PUSH R27\n"    \
    "PUSH R26\n"    \
    "PUSH R25\n"    \
    "PUSH R24\n"    \
    "PUSH R23\n"    \
    "PUSH R22\n"    \
    "PUSH R21\n"    \
    "PUSH R20\n"    \
    "PUSH R19\n"    \
    "PUSH R18\n"    \
    "PUSH R17\n"    \
    "PUSH R16\n"    \
    "PUSH R15\n"    \
    "PUSH R14\n"    \
    "PUSH R13\n"    \
    "PUSH R12\n"    \
    "PUSH R11\n"    \
    "PUSH R10\n"    \
    "PUSH R09\n"    \
    "PUSH R08\n"    \
    "PUSH R07\n"    \
    "PUSH R06\n"    \
    "PUSH R05\n"    \
    "PUSH R04\n"    \
    "PUSH R03\n"    \
    "PUSH R02\n"    \
    "PUSH R01\n"    \
    "PUSH R00\n"    \
    "IN R00, __SREG__\n"    \
    "PUSH R00\n"    \
    );

#define RESTORE_CONTEXT    \
    __asm__ __volatile__(    \
    "POP R00\n"    \
    "OUT __SREG__, R00\n"    \
    "POP R00\n"    \
    "POP R01\n"    \
    "POP R02\n"    \
    "POP R03\n"    \
    "POP R04\n"    \
    "POP R05\n"    \
    "POP R06\n"    \
    "POP R07\n"    \
    "POP R08\n"    \
    "POP R09\n"    \
    "POP R10\n"    \
    "POP R11\n"    \
    "POP R12\n"    \
    "POP R13\n"    \
    "POP R14\n"    \
    "POP R15\n"    \
    "POP R16\n"    \
    "POP R17\n"    \
    "POP R18\n"    \
    "POP R19\n"    \
    "POP R20\n"    \
    "POP R21\n"    \
    "POP R22\n"    \
    "POP R23\n"    \
    "POP R24\n"    \
    "POP R25\n"    \
    "POP R26\n"    \
    "POP R27\n"    \
    "POP R28\n"    \
    "POP R29\n"    \
    "POP R30\n"    \
    "POP R31\n"    \
    );

#endif  /* __ASSEMBLER__ */

#endif  /* _PORT_H */
