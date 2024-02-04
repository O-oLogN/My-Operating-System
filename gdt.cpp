#include "gdt.h"


enum GDT_Access {
    GDT_VALID_SEG_DESC                                  = 0x80,
    GDT_SEG_DESC_PRIVILEGE_RING0                        = 0x00,       // Kernel
    GDT_SEG_DESC_PRIVILEGE_RING1                        = 0x20,
    GDT_SEG_DESC_PRIVILEGE_RING2                        = 0x40,
    GDT_SEG_DESC_PRIVILEGE_RING3                        = 0x60,       // User
    GDT_CODE_OR_DATA_SEG_DESC                           = 0x10,
    GDT_SYS_SEG_DESC                                    = 0x00,
    GDT_DATA_SEG_DESC                                   = 0x00,
    GDT_CODE_SEG_DESC                                   = 0x08,
    GDT_DATA_SEG_GROW_UP                                = 0x00,
    GDT_DATA_SEG_GROW_DOWN                              = 0x04,
    GDT_CODE_SEG_EXEC_ONLY_BY_CUR_PRIVILEGE             = 0x00,
    GDT_CODE_SEG_EXEC_BY_EQU_LOWER_PRIVILEGE            = 0x04,
    GDT_DATA_SEG_WRITABLE                               = 0x02,
    GDT_DATA_SEG_UNWRITABLE                             = 0x00,
    GDT_CODE_SEG_READABLE                               = 0x02,
    GDT_CODE_SEG_UNREADABLE                             = 0x00
};

enum GDT_Flags {
    GDT_BYTE_GRANULARITY                                = 0x00,
    GDT_PAGE_GRANULARITY                                = 0x80,        // More blocks for limit  
    GDT_16_BIT_PROTECTED_SEG                            = 0x00,
    GDT_32_BIT_PROTECTED_SEG                            = 0x40,
    GDT_64_BIT_CODE_SEG                                 = 0x20
};


SegmentDescriptor GlobalDescriptorTable::_setNewSegmentDescriptor(uint32_t base, uint32_t limit, 
    uint8_t access_rights, uint8_t flags_and_limit_high) {
        SegmentDescriptor newSegmentDescriptor;
        newSegmentDescriptor.base_low = base & 0xFFFF;
        newSegmentDescriptor.base_mid = (base >> 16) & 0xFF;
        newSegmentDescriptor.base_high = (base >> 24) & 0xFF;
        
        newSegmentDescriptor.limit_low = limit & 0xFFFF;

        newSegmentDescriptor.access_rights = access_rights;
        newSegmentDescriptor.flags_and_limit_high = flags_and_limit_high;

        return newSegmentDescriptor;
    }

GlobalDescriptorTable::GlobalDescriptorTable() {
    
    nullSegmentDescriptor = _setNewSegmentDescriptor(0, 0, 0, 0);

    codeSegmentDescriptor = _setNewSegmentDescriptor(0, 0xFFFFF, 
       GDT_VALID_SEG_DESC | GDT_SEG_DESC_PRIVILEGE_RING0 | GDT_CODE_OR_DATA_SEG_DESC | GDT_CODE_SEG_DESC 
       | GDT_CODE_SEG_EXEC_ONLY_BY_CUR_PRIVILEGE | GDT_CODE_SEG_READABLE,
       GDT_PAGE_GRANULARITY | GDT_32_BIT_PROTECTED_SEG);

    dataSegmentDescriptor = _setNewSegmentDescriptor(0, 0xFFFFF,
        GDT_VALID_SEG_DESC | GDT_SEG_DESC_PRIVILEGE_RING0 | GDT_CODE_OR_DATA_SEG_DESC | GDT_DATA_SEG_DESC
        | GDT_DATA_SEG_GROW_UP | GDT_DATA_SEG_WRITABLE,
        GDT_PAGE_GRANULARITY | GDT_32_BIT_PROTECTED_SEG);

   
    // Loading GDT to MEM

    GlobalDescriptorTablePointer globalDescriptorTablePointer;
    globalDescriptorTablePointer.base = (uint32_t) this;    
    globalDescriptorTablePointer.size = sizeof(GlobalDescriptorTable) - 1;
    __asm__ volatile ("lgdt %0" : : "m" (globalDescriptorTablePointer));


}

uint16_t GlobalDescriptorTable::_getCodeSegmentDescriptorOffset() {
    return (uint8_t*) &codeSegmentDescriptor - (uint8_t*) this;     /// ?????????
}
