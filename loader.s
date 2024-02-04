.set MAG_NUM, 0x1badb002
.set FLAGS, 0
.set CHKSUM, -MAG_NUM - FLAGS

.section .multiboot
    .long MAG_NUM
    .long FLAGS
    .long CHKSUM

.extern _kernel
.global _loader
.section .text

_loader:
    mov $_kernel_stack, %esp                      # move stack_pointer to the end of stack
    # push %eax
    # push %ebx                                   # just in case of bootloader
    call _kernel                                   # call kernel() from kernel.cpp


.section .bss
.space 4096
_kernel_stack:

_stop:
    cli
    hlt
    jmp _stop
