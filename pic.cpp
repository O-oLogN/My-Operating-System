#include "pic.h"
#include "types.h"
#include "port.h"


enum PIC_PORT {
    PIC_MASTER                              = 0x20,
    PIC_SLAVE                               = 0xA0,
    PIC_MASTER_COM                          = PIC_MASTER,
    PIC_MASTER_DATA                         = PIC_MASTER + 1,
    PIC_SLAVE_COM                           = PIC_SLAVE,
    PIC_SLAVE_DATA                          = PIC_SLAVE + 1
};

enum PIC_INIT {
    ICW1_INIT                               = 0x10,
    ICW1_TRIG_BY_LEVEL                      = 0x08,
    ICW1_TRIG_BY_EDGE                       = 0x00,
    ICW1_ADDRESS_INTERVAL_4                 = 0x04,
    ICW1_ADDRESS_INTERVAL_8                 = 0x00,
    ICW1_SINGLE_MODE                        = 0x02,
    ICW1_CASCADE_MODE                       = 0x00,
    ICW1_ENABLE_ICW4                        = 0x01,

    ICW4_SFNM                               = 0x10,
    ICW4_BUF_MASTER                         = 0x0C,
    ICW4_BUF_SLAVE                          = 0x08,
    ICW4_NO_BUF                             = 0x00,
    ICW4_AUTO_EOI                           = 0x02,
    ICW4_8086_8088                          = 0x01,
    ICW4_MCS_80_85                          = 0x00,
};

ProgrammableInterruptController::ProgrammableInterruptController() {
    
    picMasterCommand = Port(PIC_MASTER_COM);
    picMasterData = Port(PIC_MASTER_DATA);
    picSlaveCommand = Port(PIC_SLAVE_COM);
    picSlaveData = Port(PIC_SLAVE_DATA);
    
    // uint8_t master_mask, slave_mask;                // Save masks
    // master_mask = picMasterData._8BitSlowRead();
    // slave_mask = picSlaveData._8BitSlowRead();

                /* Initialize master and slave PIC */

                    /* ICW1: Initialize  */
    picMasterCommand._8BitSlowWrite(ICW1_INIT | ICW1_TRIG_BY_EDGE | 
        ICW1_ADDRESS_INTERVAL_8 | ICW1_CASCADE_MODE | ICW1_ENABLE_ICW4);

    picSlaveCommand._8BitSlowWrite(ICW1_INIT | ICW1_TRIG_BY_EDGE | 
        ICW1_ADDRESS_INTERVAL_8 | ICW1_CASCADE_MODE | ICW1_ENABLE_ICW4);
                                    

                    /* ICW2: Set vector offset */
    picMasterData._8BitSlowWrite(0x20); 
    picSlaveData._8BitSlowWrite(0x28);

                    /* ICW3: Set up master-slave connection */
    picMasterData._8BitSlowWrite(0x04);             // Master: there is a slave number 2
    picSlaveData._8BitSlowWrite(0x02) ;             // Slave: my number is 2

                    /* ICW4: Other configurations */
    picMasterData._8BitSlowWrite(ICW4_8086_8088 | ICW4_NO_BUF);
    picSlaveData._8BitSlowWrite(ICW4_8086_8088 | ICW4_NO_BUF);

                        
                    /* OCW1: Clear data registers */
    picMasterData._8BitSlowWrite(0);               
    picSlaveData._8BitSlowWrite(0); 

}

void ProgrammableInterruptController::_picSlaveWriteCommand(uint8_t command) {
    picSlaveCommand._8BitSlowWrite(command);
}

void ProgrammableInterruptController::_picSlaveWriteData(uint8_t data) {
    picSlaveData._8BitSlowWrite(data);
}

void ProgrammableInterruptController::_picMasterWriteCommand(uint8_t command) {
    picMasterCommand._8BitSlowWrite(command);
}

void ProgrammableInterruptController::_picMasterWriteData(uint8_t data) {
    picMasterData._8BitSlowWrite(data);
}