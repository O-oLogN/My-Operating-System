#ifndef __GDT_H
#define __GDT_H
     
#include "types.h"

    /**
    *    Interrupt Descriptor acts as an entry 
    *
    *    of Interrupt Descriptor Table, and can
    * 
    *    be structured according to this pattern:
    *                |
    *                |------------ Limit:            16 bits (low-bits limit)
    *                |
    *                |------------ Base:             16 bits (low-bits base)
    *                |
    *                |------------ Base:             8 bits (mid-bits base)
    *                |
    *                |------------ Acess rights:     8 bits
    *                |
    *                |------------ Flag and Limit
    *                                |
    *                                |------ Flag:   4 bits
    *                                |
    *                                |------ Limit:  4 bits (high-bits limit)  
    *                |
    *                |------------ Base:             8 bits (high-bits base)
    * 
    **/

    struct SegmentDescriptor {
        uint16_t limit_low;
        uint16_t base_low;
        uint8_t base_mid;
        uint8_t access_rights;
        uint8_t flags_and_limit_high;
        uint8_t base_high;
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
   

    struct GlobalDescriptorTablePointer {
        uint16_t size;
        uint32_t base;
    } __attribute__((packed));

    /**
    *    GlobalDescriptorTable is initialized with 4
    * 
    *    segment descriptors inside:  -------- Null Segment Descriptor 
    *                                    | 
    *                                    |---- Unused Segment Descriptor
    *                                    |
    *                                    |---- Code Segment Descriptor
    *                                    |
    *                                    |---- Data Segment Descriptor
    *
    **/

    class GlobalDescriptorTable {
             
        /** 
        *    SegmentDescriptor is another name of entry in GDT
        *    
        *    and can be utilized for managing each segment in GDT
        */
            private:
                SegmentDescriptor nullSegmentDescriptor;
                SegmentDescriptor codeSegmentDescriptor;
                SegmentDescriptor dataSegmentDescriptor;

            public:
                GlobalDescriptorTable();

                uint16_t _getCodeSegmentDescriptorOffset();

                SegmentDescriptor _setNewSegmentDescriptor(uint32_t base, uint32_t limit, 
                uint8_t access_rights, uint8_t flags_and_limit_high);

    };


#endif
