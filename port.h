#ifndef __PORT_H
#define __PORT_H

#include "types.h"

    /**
    *    Ports can be classified into 4 major genres (I think so :)) ):
    *            |
    *            |---- 8-bit read / write
    *            |
    *            |---- 8-bit slow read / write
    *            |
    *            |---- 16-bit read / write
    *            |
    *            |---- 32-bit read / write
    **/

    class Port {
        
        private:
            uint16_t port_address;
        
        public:
            Port(){};
            Port(uint16_t port_address) {
                this -> port_address = port_address;
            }

            uint16_t getPortAddress() {
                return port_address;
            }

            // Declaring virtual (overridable) functions for each kind of port
            
            // 8-bit read / write
            virtual uint8_t _8BitRead();
            virtual void _8BitWrite(uint8_t data);

            // 8-bit slow read / write
            virtual uint8_t _8BitSlowRead();
            virtual void _8BitSlowWrite(uint8_t data); 
            
            // 16-bit read / write
            virtual uint16_t _16BitRead();
            virtual void _16BitWrite(uint16_t data);

            // 32-bit read / write
            virtual uint32_t _32BitRead();
            virtual void _32BitWrite(uint32_t data);

    };

#endif