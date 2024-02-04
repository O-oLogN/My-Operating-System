#ifndef __PRINT_H
#define __PRINT_H

#include "types.h"

    class IO {

        public:
            static uint16_t* fb;

            void _twinklingCursor();

                    // AVOID CREATING FUNCTIONS THAT RETURN POINTER (DANGEROUS!) 

            void _print(char *str);             // This is for printing with default setting
            void _printNum(uint16_t num);
            void _convert8(uint8_t num);
            void _convert16(uint16_t num);  
            void _write(char *str);             // And this is for printing characters when user type
            void _backspace();
            void _clearScreen();
    } ;


#endif