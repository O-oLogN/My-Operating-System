#ifndef __INTERRUPT_H
#define __INTERRUPT_H

#include "gdt.h"
#include "types.h"
#include "pic.h"
#include "keyboard_driver.h"


    /**
    *      Interrupt Descriptor acts as an entry 
    * 
    *        of Interrupt Descriptor Table, and can
    * 
    *        be structured according to this pattern:
    *                |
    *                |------------ Offset:               16 bits (low-bits offset)
    *                |
    *                |------------ Code segment base:    16 bits
    *                |
    *                |------------ Reserved:             8 bits
    *                |
    *                |------------ Acess rights:         8 bits
    *                |
    *                |------------ Offset:               16 bits (high-bits offset)    
    **/
    
    struct InterruptDescriptor {
        uint16_t offset_low;
        uint16_t code_segment_base;
        uint8_t reserved;
        uint8_t access_rights;
        uint16_t offset_high;      
    } __attribute__((packed));



    /**
     *  SPECIAL NOTE: FOR LOADING GLOBAL DESCRIPTOR TABLE & INTERRUPT DESCRIPTOR TABLE
     * 
     *  MUST USE APPROPRIATE POINTER:
     *  
     *       GLOBAL DESCRIPTOR TABLE ----> UTILIZING POINTER: 16-BIT SIZE & 32-BIT BASE
     * 
     *       INTERRUPT DESCRIPTOR TABLE ---> UTILIZING POINTER: 16-BIT SIZE & 32-BIT BASE 
     * 
     *  OR YOU WILL SPEND 3 CONSECUTIVE DAYS FOR SEEKING REASON WHY MY OS COULD NOT
     * 
     *  HANDLE INTERRUPTS ! :))
    */

    struct InterruptDescriptorTablePointer {
        uint16_t size;
        uint32_t base;
    } __attribute__((packed));


    
    struct Registers {
        uint32_t epb;
        uint32_t edi, esi;
        uint32_t eax, ebx, ecx, edx;
    } __attribute__((packed));

    
    class InterruptDescriptorTable {
        private:
            InterruptDescriptor interruptDescriptorTable[256];
            ProgrammableInterruptController* programmableInterruptController;
            KeyboardDriver* keyboardDriver;
            
        public:
            InterruptDescriptorTable(GlobalDescriptorTable* globalDescriptorTable,
            ProgrammableInterruptController* programmableInterruptController);

            void _setInterruptDescriptor(uint8_t interrupt_number, void (*interrupt_handler_base)(),
            uint16_t code_segment_base, uint8_t access_rights);

            InterruptDescriptor _getInterruptDescriptor(uint8_t interrupt_number);

            void _general_interrupt_handler(uint8_t interrupt_number, uint32_t esp);


    } __attribute__((packed));

#endif
