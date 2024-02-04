#include "io.h"


uint16_t* IO::fb = (uint16_t*) 0xb8000;

// void IO::_twinklingCursor() {
    // __asm__ volatile (
    //             "movw $0xFF00, (%0)\n          \
    //             movl $3000000, %%ecx\n      \
    //             _on:\n                      \
    //             nop\n                       \
    //             loop _on\n                  \
    //             movw $0, (%0)\n               \
    //             movl $3000000, %%ecx\n      \
    //             _off:\n                     \
    //             nop\n                       \
    //             loop _off\n"                               
    //             : : "Nd" (fb)
    //         );
// }

void IO::_print(char *str) {
    // *fb = 0; 
    ++fb;
    for (int i = 0; str[i] != '\0'; ++i) {
        fb[0] = (fb[0] & 0xFF00) | str[i];         // Convert to 16-bit format
        ++fb;
    }
}

void IO::_printNum(uint16_t num) {
    char digit[20], temp[20];
    int8_t cur_1 = 0, cur_2 = 0;
    while (num != 0) {
        temp[cur_1] = num % 10 + '0';
        num /= 10;
        ++cur_1;
    }
    --cur_1;
    while (cur_1 >= 0) {
        digit[cur_2] = temp[cur_1];
        --cur_1;
        ++cur_2;
    }
    digit[cur_2] = '\0';
    _print(digit);
}


void IO::_convert8(uint8_t num) {
    char digit[20], temp[20];
    int8_t cur_1 = 0, cur_2 = 0;
    while (num != 0) {
        temp[cur_1] = num % 2 + '0';
        num /= 2;
        ++cur_1;
    }
    while (cur_1 < 8) {
        temp[cur_1] = '0';
        ++cur_1;
    }
    --cur_1;
    while (cur_1 >= 0) {
        digit[cur_2] = temp[cur_1];
        --cur_1;
        ++cur_2;
        if ((cur_2 + 1) % 5 == 0) {
            digit[cur_2] = ' ';
            ++cur_2;
        }        
    }
    digit[cur_2] = '\0';
    _print(digit);
}

void IO::_convert16(uint16_t num) {
    char digit[20], temp[20];
    int8_t cur_1 = 0, cur_2 = 0;
    while (num != 0) {
        temp[cur_1] = num % 2 + '0';
        num /= 2;
        ++cur_1;
    }
    while (cur_1 < 16) {
        temp[cur_1] = '0';
        ++cur_1;
    }
    --cur_1;
    while (cur_1 >= 0) {
        digit[cur_2] = temp[cur_1];
        --cur_1;
        ++cur_2;
        if ((cur_2 + 1) % 5 == 0) {
            digit[cur_2] = ' ';
            ++cur_2;
        }
    }
    digit[cur_2] = '\0';
    _print(digit);
}

void IO::_write(char *str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        fb[0] = (fb[0] & 0xFF00) | str[i]; 
        ++fb;
    }    
}

void IO::_backspace() {
    --fb;
    *fb = 0;
}

void IO::_clearScreen() {
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 80; ++j) {
            *(fb + (i * 80 + j)) = (fb[i * 80 + j] & 0xFF00) | (' '); 
        }
    }
}