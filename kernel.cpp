#include "io.h"
#include "interrupt.h"
#include "gdt.h"
#include "pic.h"
#include "ps2_controller.h"
#include "types.h"



extern "C" void _kernel() {
    
    IO io;    
    io._clearScreen();
    io._print("Kernel");

    
    // Initializing Global Descriptor Table (GDT)
    GlobalDescriptorTable globalDescriptorTable = GlobalDescriptorTable();

    // Initializing Programmable Interrupt Controller (PIC)
    ProgrammableInterruptController programmableInterruptController = ProgrammableInterruptController();

    // Initializing Interrupt Descriptor Table (IDT)
    InterruptDescriptorTable interruptDescriptorTable = InterruptDescriptorTable(&globalDescriptorTable, 
    &programmableInterruptController);


    // Initializing PS/2 Controller
    PS2_Controller ps2_controller = PS2_Controller();

    
    __asm__ volatile ("sti");


    while (1);

}
