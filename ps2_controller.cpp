#include "ps2_controller.h"
#include "io.h"



enum PS2_Port {
    PS2_DATA_PORT                                    = 0x60,
    PS2_COMMAND_PORT                                 = 0x64
};


enum PS2_Command {
    PS2_ENABLE_FIRST_PORT                           = 0xAE,
    PS2_DISABLE_FIRST_PORT                          = 0xAD,
    PS2_ENABLE_SECOND_PORT                          = 0xA8,
    PS2_DISABLE_SECOND_PORT                         = 0xA7,
    PS2_TEST_FIRST_PORT                             = 0xAB,
    PS2_TEST_SECOND_PORT                            = 0xA9,
    PS2_TEST_CONTROLLER                             = 0xAA,
    PS2_READ_CONFIG_BYTE                            = 0x20,     
    PS2_WRITE_CONFIG_BYTE                           = 0x60,
    PS2_READ_CTRL_INP_PORT                          = 0xC0,
    PS2_READ_CTRL_OUT_PORT                          = 0xD0,
    PS2_WRITE_TO_CTRL_OUT_PORT                      = 0xD1,
    PS2_ENABLE_KEYBOARD_SCAN                        = 0xF4,          // Via Data Port
    PS2_RESET_DEVICE                                = 0xFF
};


enum PS2_Configurations_For_Writing_Configuration_Byte_Only {
    PS2_ENABLE_INT_FIRST_PORT                       = 0x01,
    PS2_ENABLE_INT_SECOND_PORT                      = 0x02,
    PS2_SYS_PASSED_POST                             = 0x04,
    PS2_OS_NOT_TO_RUN                               = 0x00,
    PS2_BIT_3_ZERO                                  = 0x00,
    PS2_FIRST_PORT_ENABLE_CLOCK                     = 0x00,
    PS2_FIRST_PORT_DISABLE_CLOCK                    = 0x10,
    PS2_SECOND_PORT_ENABLE_CLOCK                    = 0x00,
    PS2_SECOND_PORT_DISABLE_CLOCK                   = 0x20,
    PS2_FIRST_PORT_ENABLE_TRANSL                    = 0x40,
    PS2_BIT_7_ZERO                                  = 0x00
};

enum PS2_Response {
    PS2_SUCCESSFULLY_TESTED_SECOND_PORT             = 0x00,
    PS2_SUCCESSFULLY_TESTED_CONTROLLER              = 0x55,
    PS2_FAILED_CONTROLLER_TEST                      = 0xFC,
    PS2_SUCCESSFULLY_TESTED_FIRST_PORT              = 0x00,
    PS2_AVAILABLE_DEVICE                            = 0xFA
};




void PS2_Controller::_sendMeCommand(uint8_t command) {
    commandPort._8BitWrite(command);
}

void PS2_Controller::_sendMeData(uint8_t data) {
    dataPort._8BitWrite(data);
}

uint8_t PS2_Controller::_readMyData() {
    return dataPort._8BitRead();
}

uint8_t PS2_Controller::_readMyStatus() {
    return commandPort._8BitRead();
}



PS2_Controller::PS2_Controller() {

    dataPort = Port(PS2_DATA_PORT);
    commandPort = Port(PS2_COMMAND_PORT);
    IO io;

    /** 
     *  Note: Keep in mind that our PS/2 Controller has 2 port:
     * 
     *          +/ First port for keyboard
     * 
     *          +/ Second port for mouse
     **/


    
                            ///////////////////////////////////
                            //  Initialize PS/2 Controller  //
                            /////////////////////////////////


                            /* Disable all PS/2 devices */
    // _sendMeCommand(PS2_DISABLE_FIRST_PORT);
    // _sendMeCommand(PS2_DISABLE_SECOND_PORT);

    _sendMeCommand(PS2_ENABLE_FIRST_PORT);
    _sendMeCommand(PS2_ENABLE_SECOND_PORT);
    

                            /* Flush Controller output buffer */
    uint8_t redundant_data; 
    uint8_t controller_reply; 
    uint8_t configuration_byte; 
    uint8_t status;
    uint8_t first_port_reply;
    uint8_t second_port_reply;


    redundant_data = _readMyData();

                            /* Set the Controller Configuration Byte */

    configuration_byte = PS2_ENABLE_INT_FIRST_PORT | PS2_ENABLE_INT_SECOND_PORT 
    | PS2_SYS_PASSED_POST | PS2_BIT_3_ZERO | PS2_FIRST_PORT_ENABLE_CLOCK 
    | PS2_SECOND_PORT_ENABLE_CLOCK | PS2_BIT_7_ZERO;

    _sendMeCommand(PS2_WRITE_CONFIG_BYTE);
    _sendMeData(configuration_byte);

    
                            /* Test Controller */
    _sendMeCommand(PS2_TEST_CONTROLLER);  

    controller_reply = _readMyData();
    if (controller_reply == PS2_SUCCESSFULLY_TESTED_CONTROLLER) {
        io._print("PS/2 Controller test PASSED");
    }
    else {
        io._print("PS/2 Controller test FAILED");   
    }

    
                            /* Test available ports - 2 ports expected */

    // First Port
    _sendMeCommand(PS2_TEST_FIRST_PORT);

    status = _readMyStatus();
    first_port_reply = _readMyData();
    if (first_port_reply == PS2_SUCCESSFULLY_TESTED_FIRST_PORT && (status & 0x1)) {
        io._print("PS/2 First Port test PASSED");
    }
    else {
        io._print("PS/2 First Port is NOT AVAILABLE");
    }


    // Second Port
    _sendMeCommand(PS2_TEST_SECOND_PORT);
    
    status = _readMyStatus();
    second_port_reply = _readMyData();
    if (second_port_reply == PS2_SUCCESSFULLY_TESTED_SECOND_PORT && (status & 0x1)) {
        io._print("PS/2 Second Port test PASSED");
    }
    else {
        io._print("PS/2 Second Port is NOT AVAILABLE");
    }
                                              
                        
                        /* Enable all PS/2 devices and test the appearance of devices */

    _sendMeData(PS2_ENABLE_KEYBOARD_SCAN);
      
    // First Port - Keyboard
    // _sendMeCommand(PS2_RESET_DEVICE);            // Enable scanning is sufficient

    first_port_reply = _readMyData();
    if (first_port_reply == PS2_AVAILABLE_DEVICE) {
        io._print("Keyboard READY");
    }
    else {
        io._print("Keyboard is NOT AVAILABLE");
    }


    // Second Port - Mouse

    // At the moment, ACK of keyboard after command "Enable scanning"
    // is still reigning the data port, so the mouse will always 
    // be misunderstood whether it trully exists or not

    // Updated: Definitely can enable the mouse, but still
    // wrestling with problem: how to get data from mouse ?

    // _sendMeCommand(0xd4);
    // _sendMeData(0xf4);

    // second_port_reply = _readMyData();

    // io._convert8(_readMyData());

    // if (second_port_reply == PS2_AVAILABLE_DEVICE) {
    //     io._print("Mouse READY");
    // }
    // else {
    //     io._print("Mouse is NOT AVAILABLE");
    // }
    // io._convert8(_readMyData());
    // io._convert8(_readMyData());
    // io._convert8(_readMyData());         // ACK of Mouse
    // io._convert8(_readMyData());
    // io._convert8(_readMyData());

}
