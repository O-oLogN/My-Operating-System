#ifndef __PIC_H
#define __PIC_H

#include "port.h" 

    class ProgrammableInterruptController {

        private:
            Port picMasterCommand = Port();
            Port picMasterData = Port();
            Port picSlaveCommand = Port();
            Port picSlaveData = Port();

        public:
            ProgrammableInterruptController();

            void _picMasterWriteCommand(uint8_t command);
            void _picMasterWriteData(uint8_t data);
            void _picSlaveWriteCommand(uint8_t command);
            void _picSlaveWriteData(uint8_t data);

    };


#endif