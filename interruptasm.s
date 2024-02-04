    # This file creates _interrupt_handler functions and will be supported by .macro

    # Remember to add .global to the prefix of function for invoking from cpp file which

    # will use the address of these functions as parameter in IDT


.set ERQ_BASE, 32

.section .text

.extern _ZN24InterruptDescriptorTable26_general_interrupt_handlerEhj

    ////////////////////////////////////////
    // Macro pattern for request_handler //
    //////////////////////////////////////

.macro _request_interrupt_handler num
.global _Z31_request_interrupt_handler_\num\()v          # E.g: _request_interrupt_handler_1
_Z31_request_interrupt_handler_\num\()v:
    push $0                                              # Dummy error code
    movb $\num + ERQ_BASE, (interrupt_number)
    jmp _call_interrupt_handler    
.endm

    //////////////////////////////////////////
    // Macro pattern for exception_handler //
    ////////////////////////////////////////

.macro _exception_interrupt_handler num
.global _Z33_exception_interrupt_handler_\num\()v       # E.g: _exception_interrupt_handler_1
_Z33_exception_interrupt_handler_\num\()v:
    movb $\num, (interrupt_number)
    jmp _call_interrupt_handler
.endm


_exception_interrupt_handler 0x00
_exception_interrupt_handler 0x01
_exception_interrupt_handler 0x02
_exception_interrupt_handler 0x03
_exception_interrupt_handler 0x04
_exception_interrupt_handler 0x05
_exception_interrupt_handler 0x06
_exception_interrupt_handler 0x07
_exception_interrupt_handler 0x08
_exception_interrupt_handler 0x09
_exception_interrupt_handler 0x0A
_exception_interrupt_handler 0x0B
_exception_interrupt_handler 0x0C
_exception_interrupt_handler 0x0D
_exception_interrupt_handler 0x0E
_exception_interrupt_handler 0x0F
_exception_interrupt_handler 0x10
_exception_interrupt_handler 0x11
_exception_interrupt_handler 0x12
_exception_interrupt_handler 0x13

_request_interrupt_handler 0x00
_request_interrupt_handler 0x01
_request_interrupt_handler 0x02
_request_interrupt_handler 0x03
_request_interrupt_handler 0x04
_request_interrupt_handler 0x05
_request_interrupt_handler 0x06
_request_interrupt_handler 0x07
_request_interrupt_handler 0x08
_request_interrupt_handler 0x09
_request_interrupt_handler 0x0A
_request_interrupt_handler 0x0B
_request_interrupt_handler 0x0C
_request_interrupt_handler 0x0D
_request_interrupt_handler 0x0E
_request_interrupt_handler 0x0F

_request_interrupt_handler 0x80

_call_interrupt_handler:
    
    # Preserve current state of executing program
    pushl %ebp
    pushl %edi
    pushl %esi

    pushl %edx
    pushl %ecx
    pushl %ebx
    pushl %eax

    # Invoke _general_interrupt_handler
    push (interrupt_number)                       # Push 2 params to stack
    pushl %esp
    call _ZN24InterruptDescriptorTable26_general_interrupt_handlerEhj


    # Turn back to state preserved of executing program
    popl %eax
    popl %ebx
    popl %ecx
    popl %edx

    popl %esi
    popl %edi
    popl %ebp
    
    add $4, %esp

    iret

.data
    interrupt_number: .byte 0