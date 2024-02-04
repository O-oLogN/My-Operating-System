#include "interrupt.h"
#include "gdt.h"
#include "pic.h"
#include "keyboard_driver.h"
#include "io.h"

enum IDT_Access {
    IDT_VALID_INT_DESC                          = 0x80,
    IDT_INT_DESC_PRIVILEGE_RING0                = 0x00,          // Kernel
    IDT_INT_DESC_PRIVILEGE_RING1                = 0x20,
    IDT_INT_DESC_PRIVILEGE_RING2                = 0x40,
    IDT_INT_DESC_PRIVILEGE_RING3                = 0x60,          // User
    IDT_BIT_44_ZERO                             = 0x00,
    IDT_TASK_DESC_TYPE                          = 0x05,
    IDT_16_BIT_INT_DESC_TYPE                    = 0x06,
    IDT_16_BIT_TRAP_DESC_TYPE                   = 0x07,
    IDT_32_BIT_INT_DESC_TYPE                    = 0x0E,
    IDT_32_BIT_TRAP_DESC_TYPE                   = 0x0F

};



void InterruptDescriptorTable::_setInterruptDescriptor(uint8_t interrupt_number, 
    void (*interrup_handler_base)(), uint16_t code_segment_base, uint8_t access_rights) {
    
    InterruptDescriptor newInterruptDescriptor;
    
    uint32_t offset = (uint32_t) interrup_handler_base; 
    newInterruptDescriptor.offset_low = offset & 0xFFFF;
    newInterruptDescriptor.offset_high = (offset >> 16) & 0xFFFF;

    newInterruptDescriptor.reserved = 0;

    newInterruptDescriptor.code_segment_base = code_segment_base;

    newInterruptDescriptor.access_rights = access_rights;

    interruptDescriptorTable[interrupt_number] = newInterruptDescriptor;
    return;
        
}

void _interrupt_ignore();

void _exception_interrupt_handler_0x00();
void _exception_interrupt_handler_0x01();
void _exception_interrupt_handler_0x02();
void _exception_interrupt_handler_0x03();
void _exception_interrupt_handler_0x04();
void _exception_interrupt_handler_0x05();
void _exception_interrupt_handler_0x06();
void _exception_interrupt_handler_0x07();
void _exception_interrupt_handler_0x08();
void _exception_interrupt_handler_0x09();
void _exception_interrupt_handler_0x0A();
void _exception_interrupt_handler_0x0B();
void _exception_interrupt_handler_0x0C();
void _exception_interrupt_handler_0x0D();
void _exception_interrupt_handler_0x0E();
void _exception_interrupt_handler_0x0F();
void _exception_interrupt_handler_0x10();
void _exception_interrupt_handler_0x11();
void _exception_interrupt_handler_0x12();
void _exception_interrupt_handler_0x13();

void _request_interrupt_handler_0x00();
void _request_interrupt_handler_0x01();
void _request_interrupt_handler_0x02();
void _request_interrupt_handler_0x03();
void _request_interrupt_handler_0x04();
void _request_interrupt_handler_0x05();
void _request_interrupt_handler_0x06();
void _request_interrupt_handler_0x07();
void _request_interrupt_handler_0x08();
void _request_interrupt_handler_0x09();
void _request_interrupt_handler_0x0A();
void _request_interrupt_handler_0x0B();
void _request_interrupt_handler_0x0C();
void _request_interrupt_handler_0x0D();
void _request_interrupt_handler_0x0E();
void _request_interrupt_handler_0x0F();

void _request_interrupt_handler_0x80();

InterruptDescriptorTable::InterruptDescriptorTable(GlobalDescriptorTable* globalDescriptorTable,
    ProgrammableInterruptController* programmableInterruptController) {

    this -> programmableInterruptController = programmableInterruptController;

    uint16_t code_segment_base = globalDescriptorTable -> _getCodeSegmentDescriptorOffset();
    // OR uint16_t code_segment_base = 0x08;

 
    ////////////////////////////////////////////////////
    //  At first, we just need 20 exception handlers //
    //////////////////////////////////////////////////

    _setInterruptDescriptor(0, _exception_interrupt_handler_0x00, code_segment_base, 
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(1, _exception_interrupt_handler_0x01, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(2, _exception_interrupt_handler_0x02, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(3, _exception_interrupt_handler_0x03, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(4, _exception_interrupt_handler_0x04, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(5, _exception_interrupt_handler_0x05, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(6, _exception_interrupt_handler_0x06, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(7, _exception_interrupt_handler_0x07, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(8, _exception_interrupt_handler_0x08, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(9, _exception_interrupt_handler_0x09, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(10, _exception_interrupt_handler_0x0A, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(11, _exception_interrupt_handler_0x0B, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(12, _exception_interrupt_handler_0x0C, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(13, _exception_interrupt_handler_0x0D, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(14, _exception_interrupt_handler_0x0E, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(15, _exception_interrupt_handler_0x0F, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(16, _exception_interrupt_handler_0x10, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(17, _exception_interrupt_handler_0x11, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(18, _exception_interrupt_handler_0x12, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(19, _exception_interrupt_handler_0x13, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);



    ///////////////////////////////////////////////////////////////////////////////
    // And 17 interrupt handlers, remember to add 32 to @param interrupt_number //
    /////////////////////////////////////////////////////////////////////////////

    _setInterruptDescriptor(32, _request_interrupt_handler_0x00, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(33, _request_interrupt_handler_0x01, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(34, _request_interrupt_handler_0x02, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(35, _request_interrupt_handler_0x03, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(36, _request_interrupt_handler_0x04, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(37, _request_interrupt_handler_0x05, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(38, _request_interrupt_handler_0x06, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(39, _request_interrupt_handler_0x07, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(40, _request_interrupt_handler_0x08, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(41, _request_interrupt_handler_0x09, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(42, _request_interrupt_handler_0x0A, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(43, _request_interrupt_handler_0x0B, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(44, _request_interrupt_handler_0x0C, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(45, _request_interrupt_handler_0x0D, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(46, _request_interrupt_handler_0x0E, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);

    _setInterruptDescriptor(47, _request_interrupt_handler_0x0F, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);
 
    _setInterruptDescriptor(128, _request_interrupt_handler_0x80, code_segment_base,
    IDT_VALID_INT_DESC | IDT_INT_DESC_PRIVILEGE_RING0 | IDT_BIT_44_ZERO | IDT_32_BIT_INT_DESC_TYPE);
 

 
    // Loading IDT to MEM
    
    InterruptDescriptorTablePointer interruptDescriptorTablePointer;
    interruptDescriptorTablePointer.base = (uint32_t) this;
    interruptDescriptorTablePointer.size = sizeof(interruptDescriptorTable) - 1;
    __asm__ volatile ("lidt %0" : : "m" (interruptDescriptorTablePointer));
  
}


InterruptDescriptor InterruptDescriptorTable::_getInterruptDescriptor(uint8_t interrupt_number) {
    return interruptDescriptorTable[interrupt_number];
}

void InterruptDescriptorTable::_general_interrupt_handler(uint8_t interrupt_number, uint32_t esp) {
    
    if (interrupt_number >= 0x20 && interrupt_number < 0x30) {
        programmableInterruptController -> _picMasterWriteCommand(0x20);
        if (interrupt_number >= 0x28) {
            programmableInterruptController -> _picSlaveWriteCommand(0x20);
        }
    }    

    IO io;
    int k = 0;
    io._print("INT");
    io._printNum(interrupt_number); 
    if (interrupt_number == 33) {
        KeyboardDriver keyboardDriver = KeyboardDriver();
        keyboardDriver._dataHandler();
    }
}
