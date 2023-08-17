    .global delay1s
    .text
    .global _start
_start:
    b reset
    ldr pc, _undefined_instruction
    ldr pc, _software_interrupt
    ldr pc, _prefetch_abort
    ldr pc, _data_abort
    ldr pc, _not_used
    ldr pc, _irq
    ldr pc, _fiq

_undefined_instruction: .word _undefined_instruction
_software_interrupt:    .word _software_interrupt
_prefetch_abort:        .word _prefetch_abort
_data_abort:            .word _data_abort
_not_used:              .word _not_used
_irq:                   .word _irq
_fiq:                   .word _fiq

reset:
    ldr r0, =0x40008000     
    mcr p15, 0, r0, c12, c0, 0

init_stack:
    ldr r0, stacktop

    /* svc mode stack */
    mov sp, r0
    sub r0, #128*4 /* 128 words for svc mode */
    /* irq mode stack */
    msr cpsr, #0xd2 /* switch to irq mode */
    mov sp, r0
    sub r0, #128*4 /* 128 words for irq mode */
    /* fiq mode stack */
    msr cpsr, #0xd1 /* switch to fiq mode */
    mov sp, r0
    sub r0, #0
    /* abort mode stack */
    msr cpsr, #0xd7 /* switch to abort mode */
    mov sp, r0
    sub r0, #0
    /* undef mode stack */
    msr cpsr, #0xdb /* switch to undef mode */
    mov sp, r0
    sub r0, #0
    /* sys mode stack */
    msr cpsr, #0xdf /* switch to sys mode */
    mov sp, r0 /* 1024 bytes for sys mode */

    b main

delay1s:
    ldr r4, =0x1fffffff
delay1s_loop:
    sub r4, r4, #1
    cmp r4, #0
    bne delay1s_loop
    bx lr

    .align 4

stacktop: .word stack+4*512

    .data
stack:  .space 4*512
    .end
