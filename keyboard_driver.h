#ifndef __KEYBOARD_DRIVER_H
#define __KEYBOARD_DRIVER_H

#include "port.h"
#include "io.h"
    
    /**
     *  Keyboard driver acts as a data handler, which receives data from
     * 
     *  keyboard, consiting of:
     *              |
     *              |----------- Scan code of key pressed 
     *              |                    |
     *              |                    |---------- Pressing code (0xF0, 0xE0)
     *              |                    |
     *              |                    |---------- Pressing key code   
     *              |                    |
     *              |----------- Scan code of key released
     *              |                    |
     *              |                    |---------- Releasing code (0xF0, 0xE0)
     *              |                    |
     *              |                    |---------- Releaing key code
     *              |
     *              |----------- Responding codes from keyboard
     *
    **/
    
    class KeyboardDriver {

        private:
            Port commandPort = Port();
            Port dataPort = Port();
            uint8_t suspend_flag;
            uint8_t shift_key;
            uint8_t num_lock;
            uint8_t uppercase;
            uint8_t capslock;
            uint8_t pressed_key_starts_with_0xE0;
            IO io;

        public:
            KeyboardDriver();

            void _dataHandler();
    };


#endif