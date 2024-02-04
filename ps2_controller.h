#ifndef __PS2_CONTROLLER_H
#define __PS2_CONTROLLER_H

#include "types.h"
#include "port.h"

    /**
     * PS/2 Controller act as a translator and intermediator between system and keyboard, mouse.
     * 
     * There are 2 ports which offer capabilities of 
     * 
     * configuring and communicating between system and PS/2 Controller:
     *              |
     *              |---------- 0x60 (read / write): Data Port
     *              |
     *              |---------- 0x64 (read / write)
     *                                  |
     *                                  |------ read: Status Register
     *                                  |
     *                                  |------ write: Command Register  
     * 
    **/



    /**
     *  Data Port (0x60): - Read data from PS/2 device and PS/2 controller itself
     *                   
     *                    - Write data to PS/2 device and PS/2 controller itself
     * 
     *  Status Register (0x64): - Read the state of PS/2 controller (8-bit package)
     * 
     *
     *  Command Register (0x64): - Write command to PS/2 controller (not to PS/2 device)
     * 
    **/



    /**
        *   Moreover, PS/2 Controller offers 2 another ports are first and second, which connect
        * 
        *   with keyboard and mouse respectively 
    */

    class PS2_Controller {

        private:
            Port commandPort = Port();
            Port dataPort = Port();

        public:
            PS2_Controller();

            uint8_t _readMyData();
            uint8_t _readMyStatus();

            void _sendMeCommand(uint8_t command);
            void _sendMeData(uint8_t data);
        
    } __attribute__((packed));


#endif