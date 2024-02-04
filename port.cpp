#include "port.h"



// In asm inline, use "Nd" constraint to imply 32-bits value to compiler

// 8-bit read / write
uint8_t Port::_8BitRead() {
    uint8_t data;
    __asm__ volatile ("inb %1, %0" : "=a" (data) : "Nd" (getPortAddress()));
    return data;
}

void Port::_8BitWrite(uint8_t data) {
    __asm__ volatile ("outb %0, %1" : : "a" (data), "Nd" (getPortAddress()));
}


// 8-bit slow read / write
uint8_t Port::_8BitSlowRead() {
    uint8_t data;
    __asm__ volatile ("inb %1, %0" : "=a" (data) : "Nd" (getPortAddress()));
    return data;
}

void Port::_8BitSlowWrite(uint8_t data) {
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (data), "Nd" (getPortAddress()));
}

// 16-bit read / write
uint16_t Port::_16BitRead() {
    uint16_t data;
    __asm__ volatile ("inw %1, %0" : "=a" (data) : "Nd" (getPortAddress()));
    return data;
}

void Port::_16BitWrite(uint16_t data) {
    __asm__ volatile ("outw %0, %1" : : "a" (data), "Nd" (getPortAddress()));
}


// 32-bit read / write
uint32_t Port::_32BitRead() {
    uint32_t data;
    __asm__ volatile ("inl %1, %0" : "=a" (data) : "Nd" (getPortAddress()));
    return data;
}

void Port::_32BitWrite(uint32_t data) {
    __asm__ volatile ("outl %0, %1" : : "a" (data), "Nd" (getPortAddress()));
} 
