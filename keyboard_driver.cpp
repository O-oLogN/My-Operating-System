#include "keyboard_driver.h"
#include "io.h"



enum Keyboard_Port {
    KB_COMMAND_PORT                                     = 0x64,
    KB_DATA_PORT                                        = 0x60
};


enum Keyboard_Scan_Code_Set_2_Fundamental_Keys_Press {
    KB_LEFT_CTRL_PRESSED                                = 0x14,
    KB_A_PRESSED                                        = 0x1C,
    KB_E_PRESSED                                        = 0x24,
    KB_G_PRESSED                                        = 0x34,
    KB_U_PRESSED                                        = 0x3C,
    KB_O_PRESSED                                        = 0x44,
    KB_SEMICOLON_PRESSED                                = 0x4C,            // ;
    KB_OPENED_BRACKET_PRESSED                           = 0x54,            // [
    KB_CAPSLOCK_PRESSED                                 = 0x58,
    KB_RIGHT_CTLR_PRESSED                               = 0x14,            // 0xE0, 0x14
    KB_TAB_PRESSED                                      = 0x0D,
    KB_LEFT_ALT_PRESSED                                 = 0x11,
    KB_Q_PRESSED                                        = 0x15,
    KB_W_PRESSED                                        = 0x1D,
    KB_C_PRESSED                                        = 0x21,
    KB_4_PRESSED                                        = 0x25,
    KB_SPACE_PRESSED                                    = 0x29,
    KB_R_PRESSED                                        = 0x2D,
    KB_N_PRESSED                                        = 0x31,
    KB_Y_PRESSED                                        = 0x35,
    KB_7_PRESSED                                        = 0x3D,
    KB_COMMA_PRESSED                                    = 0x41,             // ,
    KB_0_PRESSED                                        = 0x45,
    KB_DOT_PRESSED                                      = 0x49,             // .
    KB_P_PRESSED                                        = 0x4D,
    KB_EQUAL_PRESSED                                    = 0x55,             // =
    KB_RIGHT_SHIFT_PRESSED                              = 0x59, 
    KB_LEFT_SLASH_PRESSED                               = 0x5D,            
    KB_RIGHT_ALT_PRESSED                                = 0x11,             // 0xE0, 0x11
    KB_BACK_TICK_PRESSED                                = 0x0E,             // `
    KB_LEFT_SHIFT_PRESSED                               = 0x12,
    KB_1_PRESSED                                        = 0x16,
    KB_Z_PRESSED                                        = 0x1A,
    KB_2_PRESSED                                        = 0x1E,
    KB_X_PRESSED                                        = 0x22,
    KB_3_PRESSED                                        = 0x26,
    KB_V_PRESSED                                        = 0x2A,
    KB_5_PRESSED                                        = 0x2E,
    KB_B_PRESSED                                        = 0x32,
    KB_6_PRESSED                                        = 0x36,
    KB_M_PRESSED                                        = 0x3A,
    KB_8_PRESSED                                        = 0x3E,
    KB_K_PRESSED                                        = 0x42,
    KB_9_PRESSED                                        = 0x46,
    KB_F_PRESSED                                        = 0x2B,    
    KB_T_PRESSED                                        = 0x2C,
    KB_RIGHT_SLASH_PRESSED                              = 0x4A,             // /
    KB_HYPHEN_PRESSED                                   = 0x4E,             // -
    KB_APOSTROPHE_PRESSED                               = 0x52,             // '
    KB_ENTER_PRESSED                                    = 0x5A,
    KB_BACK_SPACE_PRESSED                               = 0x66,
    KB_ESC_PRESSED                                      = 0x76,
    KB_S_PRESSED                                        = 0x1B,
    KB_D_PRESSED                                        = 0x23,
    KB_H_PRESSED                                        = 0x33,
    KB_J_PRESSED                                        = 0x3B,
    KB_I_PRESSED                                        = 0x43,
    KB_L_PRESSED                                        = 0x4B,
    KB_CLOSED_BRACKET_PRESSED                           = 0x5B
};


enum Keyboard_Scan_Code_Set_2_Function_Keys_Pressed {
    KB_F1_PRESSED                                       = 0x05,
    KB_F2_PRESSED                                       = 0x06,
    KB_F3_PRESSED                                       = 0x04,
    KB_F4_PRESSED                                       = 0x0C,
    KB_F5_PRESSED                                       = 0x03,
    KB_F6_PRESSED                                       = 0x0B,
    KB_F7_PRESSED                                       = 0x83,
    KB_F8_PRESSED                                       = 0x0A,
    KB_F9_PRESSED                                       = 0x01,
    KB_F10_PRESSED                                      = 0x09,
    KB_F11_PRESSED                                      = 0x78,
    KB_F12_PRESSED                                      = 0x07
};


enum Keyboard_Scan_Code_Set_2_Keypad_Keys_Pressed {
    KB_KEYPAD_0_PRESSED                                 = 0x70,
    KB_KEYPAD_1_PRESSED                                 = 0x69,
    KB_KEYPAD_2_PRESSED                                 = 0x72,
    KB_KEYPAD_3_PRESSED                                 = 0x7A,
    KB_KEYPAD_4_PRESSED                                 = 0x6B,
    KB_KEYPAD_5_PRESSED                                 = 0x73,
    KB_KEYPAD_6_PRESSED                                 = 0x74,
    KB_KEYPAD_7_PRESSED                                 = 0x6C,
    KB_KEYPAD_8_PRESSED                                 = 0x75,
    KB_KEYPAD_9_PRESSED                                 = 0x7D,
    KB_KEYPAD_STAR_PRESSED                              = 0x7C,             // *
    KB_KEYPAD_DOT_PRESSED                               = 0x71,             // .
    KB_KEYPAD_PLUS_PRESSED                              = 0x79,             // +
    KB_KEYPAD_RIGHT_SLASH_PRESSED                       = 0x4A,             // 0xE0, 0x4A /
    KB_KEYPAD_ENTER_PRESSED                             = 0x5A,             // 0xE0, 0x5A
    KB_KEYPAD_HYPHEN_PRESSED                            = 0x7B,             // -
    KB_NUM_LOCK_PRESSED                                 = 0x77
};


enum Keyboard_Scan_Code_Set_2_Multimedia_Keys_Pressed {
    KB_MULTMDA_WWW_SEARCH_PRESSED                       = 0x10,             // 0xE0, 0x10
    KB_MULTMDA_WWW_FAVOR_PRESSED                        = 0x18,             // 0xE0, 0x18
    KB_MULTMDA_WWW_REFRESH_PRESSED                      = 0x20,             // 0xE0, 0x20
    KB_MULTMDA_WWW_STOP_PRESSED                         = 0x28,             // 0xEO, 0x28
    KB_MULTMDA_WWW_FORWARD_PRESSED                      = 0x30,             // 0xE0, 0x30
    KB_MULTMDA_WWW_HOME_PRESSED                         = 0x3A,             // 0xE0, 0x3A
    KB_MULTMDA_PLAY_PAUSE_PRESSED                       = 0x34,             // 0xEO, 0x34
    KB_MULTMDA_MY_COMP_PRESSED                          = 0x40,             // 0xEO, 0x40
    KB_MULTMDA_EMAIL_PRESSED                            = 0x48,             // 0xE0, 0x48
    KB_MULTMDA_MEDIA_SELECT_PRESSED                     = 0x50,             // 0xE0, 0x50
    KB_MULTMDA_PREV_TRACK_PRESSED                       = 0x15,             // 0xE0, 0x15
    KB_MULTMDA_NEXT_TRACK_PRESSED                       = 0x4D,             // 0xEO, 0x4D
    KB_MULTMDA_VOL_DOWN_PRESSED                         = 0x21,             // 0xE0, 0x21
    KB_MULTMDA_VOL_UP_PRESSED                           = 0x32,             // 0xE0, 0x32
    KB_MULTMDA_MUTE_PRESSED                             = 0x23,             // 0xE0, 0x23
    KB_MULTMDA_STOP_PRESSED                             = 0x3B              // 0xE0, 0x3B
};


enum Keyboard_Scan_Code_Set_2_Cursor_Keys_Pressed {
    KB_CURSOR_UP_PRESSED                                = 0x75,             // 0xE0, 0x75
    KB_CURSOR_DOWN_PRESSED                              = 0x72,             // 0xE0, 0x72
    KB_CURSOR_LEFT_PRESSED                              = 0x6B,             // 0xE0, 0x6B
    KB_CURSOR_RIGHT_PRESSED                             = 0x74              // 0xEO, 0x74
};


enum Keyboard_Scan_Code_Set_2_Other_Keys_Pressed {
    KB_PRINT_SCREEN_BYTE_2_PRESSED                      = 0x12,             // 0xE0, 0x12
    KB_PRINT_SCREEN_BYTE_4_PRESSED                      = 0x7C,             // 0xE0, 0x7C
    
    KB_SCROLL_LOCK_PRESSED                              = 0x7E,
    KB_INSERT_PRESSED                                   = 0x70,             // 0xE0, 0x70
    KB_HOME_PRESSED                                     = 0x6C,             // 0xE0, 0x6C
    KB_PAGE_UP_PRESSED                                  = 0x7D,             // 0xE0, 0x7D
    KB_PAGE_DOWN_PRESSED                                = 0x7A,             // 0xE0, 0x7A
    KB_END_PRESSED                                      = 0x69,             // 0xE0, 0x69
    KB_DEL_PRESSED                                      = 0x71              // 0xE0, 0x71
};

            //////////////////////////////////////////////////////////////////////
           //                          KEEP IN MIND                            //
          //    Keys released always start with byte: 0xF0 or 0xE0, hence all //
         //     keys below are needed to add the prefix 0xF0, except         //
        //      the keys which starting with 0xE0                           //
       //////////////////////////////////////////////////////////////////////


enum Keyboard_Scan_Code_Set_2_Fundamental_Keys_Release {
                                /* 0xF0, 0x01 */

    KB_TAB_RELEASED                                     = 0x0D, 
    KB_BACK_TICK_RELEASED                               = 0x0E,             // `
    KB_LEFT_ALT_RELEASED                                = 0x11, 
    KB_LEFT_SHIFT_RELEASED                              = 0x12, 
    KB_LEFT_CTRL_RELEASED                               = 0x14, 
    KB_1_RELEASED                                       = 0x16,
    KB_Z_RELEASED                                       = 0x1A,
    KB_S_RELEASED                                       = 0x1B,
    KB_A_RELEASED                                       = 0x1C,
    KB_W_RELEASED                                       = 0x1D,
    KB_2_RELEASED                                       = 0x1E,
    KB_C_RELEASED                                       = 0x21,
    KB_X_RELEASED                                       = 0x22,
    KB_D_RELEASED                                       = 0x23,
    KB_E_RELEASED                                       = 0x24,
    KB_4_RELEASED                                       = 0x25,
    KB_3_RELEASED                                       = 0x26,
    KB_SPACE_RELEASED                                   = 0x29,
    KB_V_RELEASED                                       = 0x2A,
    KB_F_RELEASED                                       = 0x2B,
    KB_T_RELEASED                                       = 0x2C,
    KB_R_RELEASED                                       = 0x2D,
    KB_5_RELEASED                                       = 0x2E,
    KB_N_RELEASED                                       = 0x31,
    KB_B_RELEASED                                       = 0x32,
    KB_H_RELEASED                                       = 0x33,
    KB_G_RELEASED                                       = 0x34,
    KB_Y_RELEASED                                       = 0x35,
    KB_6_RELEASED                                       = 0x36,
    KB_M_RELEASED                                       = 0x3A,
    KB_J_RELEASED                                       = 0x3B,
    KB_U_RELEASED                                       = 0x3C,
    KB_Q_RELEASED                                       = 0x15,
    KB_7_RELEASED                                       = 0x3D,
    KB_8_RELEASED                                       = 0x3E,
    KB_COMMA_RELEASED                                   = 0x41,             // ,
    KB_K_RELEASED                                       = 0x41,
    KB_I_RELEASED                                       = 0x43,
    KB_O_RELEASED                                       = 0x44,
    KB_0_RELEASED                                       = 0x45,
    KB_9_RELEASED                                       = 0x46,
    KB_DOT_RELEASED                                     = 0x49,
    KB_RIGHT_SLASH_RELEASED                             = 0x4A,             // /
    KB_L_RELEASED                                       = 0x4B,
    KB_SEMICOLON_RELEASED                               = 0x4C,             // ;
    KB_P_RELEASED                                       = 0x4D,
    KB_HYPHEN_RELEASED                                  = 0x4E,
    KB_APOSTROPHE_RELEASED                              = 0x52,             // '
    KB_OPENED_BRACKET_RELEASED                          = 0x54,             // [
    KB_EQUAL_RELEASED                                   = 0x55,             // =
    KB_CAPSLOCK_RELEASED                                = 0x58,
    KB_RIGHT_SHIFT_RELEASED                             = 0x59,
    KB_ENTER_RELEASED                                   = 0x5A,
    KB_CLOSED_BRACKET_RELEASED                          = 0x5B,
    KB_LEFT_SLASH_RELEASED                              = 0x5D,
    KB_BACK_SPACE_RELEASED                              = 0x66,
    KB_ESC_RELEASED                                     = 0x76,
    KB_RIGHT_ALT_RELEASED                               = 0x11,         // 0xE0, 0xF0, 0x11
    KB_RIGHT_CTRL_RELEASED                              = 0x14,         // 0xE0, 0xF0, 0x14
};


enum Keyboard_Scan_Code_Set_2_Function_Keys_Release {
    KB_F1_RELEASED                                      = 0x05, 
    KB_F2_RELEASED                                      = 0x06,    
    KB_F3_RELEASED                                      = 0x04, 
    KB_F4_RELEASED                                      = 0x0C, 
    KB_F5_RELEASED                                      = 0x03, 
    KB_F6_RELEASED                                      = 0x0B,
    KB_F7_RELEASED                                      = 0x83,
    KB_F8_RELEASED                                      = 0x0A, 
    KB_F9_RELEASED                                      = 0x01,          
    KB_F10_RELEASED                                     = 0x09, 
    KB_F11_RELEASED                                     = 0x78,
    KB_F12_RELEASED                                     = 0x07
};


enum Keyboard_Scan_Code_Set_2_Multimedia_Keys_Release {
    KB_MULTMDA_WWW_SEARCH_RELEASED                      = 0x18,         // 0xE0, 0xF0, 0x18
    KB_MULTMDA_WWW_FAVOR_RELEASED                       = 0x18,         // 0xE0, 0xF0, 0x18
    KB_MULTMDA_WWW_STOP_RELEASED                        = 0x28,         // 0xE0, 0xF0, 0x28
    KB_MULTMDA_WWW_FORWARD_RELEASED                     = 0x30,         // 0xE0, 0xF0, 0x30
    KB_MULTMDA_WWW_REFRESH_RELEASED                     = 0x20,         // 0xE0, 0xF0, 0x20
    KB_MULTMDA_WWW_BACK_RELEASED                        = 0x38,         // 0xE0, 0xF0, 0x38
    KB_MULTMDA_WWW_HOME_RELEASED                        = 0x3A,         // 0xE0, 0xF0, 0x3A
    KB_MULTMDA_PREV_TRACK_RELEASED                      = 0x15,         // 0xE0, 0xF0, 0x15
    KB_MULTMDA_NEXT_TRACK_RELEASED                      = 0x4D,         // 0xE0, 0xF0, 0x4D
    KB_MULTMDA_VOL_DOWN_RELEASED                        = 0x21,         // 0xE0, 0xF0, 0x21
    KB_MULTMDA_VOL_UP_RELEASED                          = 0x32,         // 0xE0, 0xF0, 0x32
    KB_MULTMDA_MUTE_RELEASED                            = 0x23,         // 0xE0, 0xF0, 0x23
    KB_MULTMDA_PLAY_PAUSE_RELEASED                      = 0x38,         // 0xE0, 0xF0, 0x38
    KB_MULTMDA_STOP_RELEASED                            = 0x3B,         // 0xE0, 0xF0, 0x3B
    KB_MULTMDA_MY_COMP_RELEASED                         = 0x40,         // 0xE0, 0xF0, 0x40
    KB_MULTMDA_EMAIL_RELEASED                           = 0x48,         // 0xE0, 0xF0, 0x48
    KB_MULTMDA_MEDIA_SELECT_RELEASED                    = 0x50          // 0xE0, 0xF0, 0x50
};


enum Keyboard_Scan_Code_Set_2_Keypad_Keys_Release {
    KB_KEYPAD_0_RELEASED                                = 0x70,
    KB_KEYPAD_1_RELEASED                                = 0x69,
    KB_KEYPAD_2_RELEASED                                = 0x72,
    KB_KEYPAD_3_RELEASED                                = 0x7A,
    KB_KEYPAD_4_RELEASED                                = 0x6B,
    KB_KEYPAD_5_RELEASED                                = 0x73,
    KB_KEYPAD_6_RELEASED                                = 0x74,
    KB_KEYPAD_7_RELEASED                                = 0x6C,
    KB_KEYPAD_8_RELEASED                                = 0x75,
    KB_KEYPAD_9_RELEASED                                = 0x7D,
    KB_KEYPAD_DOT_RELEASED                              = 0x71,
    KB_KEYPAD_PLUS_RELEASED                             = 0x79,         // +
    KB_KEYPAD_HYPHEN_RELEASED                           = 0x7B,         // -
    KB_KEYPAD_STAR_RELEASED                             = 0x7C,         // *
    KB_KEYPAD_RIGHT_SLASH_RELEASED                      = 0x4A,         // 0xE0, 0xF0, 0x4A
    KB_KEYPAD_ENTER_RELEASED                            = 0x5A,         // 0xE0, 0xF0, 0x5A
    KB_NUM_LOCK_RELEASED                                = 0x77
};


enum Keyboard_Scan_Code_Set_2_Cursor_Keys_Release {
    KB_CURSOR_UP_RELEASED                               = 0x75,         // 0xE0, 0xF0, 0x75
    KB_CURSOR_DOWN_RELEASED                             = 0x72,         // 0xE0, 0xF0, 0x72
    KB_CURSOR_LEFT_RELEASED                             = 0x6B,         // 0xE0, 0xF0, 0x6B
    KB_CURSOR_RIGHT_RELEASED                            = 0x74          // 0xE0, 0xF0, 0x74
};


enum Keyboard_Scan_Code_Set_2_Other_Keys_Release {
    KB_PRINT_SCREEN_BYTE_3_RELEASED                     = 0x7C,         // 0xE0, 0xF0, 0x7C 
    KB_PRINT_SCREEN_BYTE_6_RELEASED                     = 0x12,         // 0xE0, 0xF0, 0x12 

    KB_SCROLL_LOCK_RELEASED                             = 0x7E,
    KB_INSERT_RELEASED                                  = 0x70,         // 0xE0, 0xF0, 0x70
    KB_HOME_RELEASED                                    = 0x6C,         // 0xE0, 0xF0, 0x6C
    KB_PAGE_DOWN_RELEASED                               = 0x7A,         // 0xE0, 0xF0, 0x7A
    KB_PAGE_UP_RELEASED                                 = 0x7D,         // 0xE0, 0xF0, 0x7D
    KB_END_RELEASED                                     = 0x69,         // 0xE0, 0xF0, 0x69
    KB_DEL_RELEASED                                     = 0x71          // 0xE0, 0xF0, 0x71
};


KeyboardDriver::KeyboardDriver() {

    commandPort = Port(KB_COMMAND_PORT);
    dataPort = Port(KB_DATA_PORT);
    suspend_flag = 0;
    shift_key = 0;
    num_lock = 0;
    uppercase = 0;
    capslock = 0;
    pressed_key_starts_with_0xE0 = 0;

                                /* Just in case */
    // while(commandPort._8BitRead() & 0x1) {
    //     dataPort._8BitRead();
    // }
    // commandPort._8BitWrite(0xae); // activate interrupts
    // commandPort._8BitWrite(0x20); // command 0x20 = _8BitRead controller command byte
    // uint8_t status = (dataPort._8BitRead() | 1) & ~0x10;

    // commandPort._8BitWrite(0x60); // command 0x60 = set controller command byte
    // dataPort._8BitWrite(status);
    // dataPort._8BitWrite(0xf4); 
}

void KeyboardDriver::_dataHandler() {

    while (true) {

        // Only print when Output Buffer is ready and allowed

        while ((commandPort._8BitRead() & 0x01)) {   
            uint8_t data = dataPort._8BitRead();
            if (suspend_flag) {
                --suspend_flag;
                continue;
            }
            if (data == 0xE0) {                      // Releasing signal or first byte of key pressed
                data = dataPort._8BitRead();
                if (data == 0xF0) {                  // Releasing signal 
                    data = dataPort._8BitRead();
                    suspend_flag = (data == 0x7C ? 3 : 0);
                    continue;
                }
                suspend_flag = 0;
                pressed_key_starts_with_0xE0 = 1;    // Pressed key 
            }
            if (data == 0xF0) {                      // Releasing signal
                data = dataPort._8BitRead();
                if (data == KB_LEFT_SHIFT_RELEASED || data == KB_RIGHT_SHIFT_RELEASED) {
                    shift_key = 0;
                    uppercase = capslock;
                }
                suspend_flag = 0;
                continue;
            }

            // Seperate 2 circumstances: data from key pressed has first byte is 0xE0 or does not have 
            if (pressed_key_starts_with_0xE0) {
                pressed_key_starts_with_0xE0 = 0;

                /** TODO: All pressed keys starting with 0xE0 are not printable keys. 
                *   Therefore, I will implement them later
                **/
               continue;
            }
            switch (data) {
                case KB_CAPSLOCK_PRESSED: {
                    capslock = !capslock;
                    uppercase = capslock ^ shift_key;
                    break;
                } 
                case KB_LEFT_SHIFT_PRESSED: {
                    shift_key = 1;
                    uppercase = capslock ^ shift_key;
                    break;
                }
                case KB_RIGHT_SHIFT_PRESSED: {
                    shift_key = 1;
                    uppercase = capslock ^ shift_key;
                    break;                   
                }
                case KB_1_PRESSED: {
                    if (shift_key) {
                        io._write("!");
                        break;
                    }
                    io._write("1");
                    break;   
                }
                case KB_2_PRESSED: {
                    if (shift_key) {
                        io._write("@");
                        break;
                    }
                    io._write("2");
                    break;   
                }
                case KB_3_PRESSED: {
                    if (shift_key) {
                        io._write("#");
                        break;
                    }
                    io._write("3");
                    break;   
                }
                case KB_4_PRESSED: {
                    if (shift_key) {
                        io._write("$");
                        break;
                    }
                    io._write("4");
                    break;   
                }
                case KB_5_PRESSED: {
                    if (shift_key) {
                        io._write("!");
                        break;
                    }
                    io._write("5");
                    break;   
                }
                case KB_6_PRESSED: {
                    if (shift_key) {
                        io._write("^");
                        break;
                    }
                    io._write("6");
                    break;   
                }
                case KB_7_PRESSED: {
                    if (shift_key) {
                        io._write("&");
                        break;
                    }
                    io._write("7");
                    break;   
                }
                case KB_8_PRESSED: {
                    if (shift_key) {
                        io._write("*");
                        break;
                    }
                    io._write("8");
                    break;   
                }
                case KB_9_PRESSED: {
                    if (shift_key) {
                        io._write("(");
                        break;
                    }
                    io._write("9");
                    break;   
                }
                case KB_0_PRESSED: {
                    if (shift_key) {
                        io._write(")");
                        break;
                    }
                    io._write("0");
                    break;   
                }
                case KB_HYPHEN_PRESSED: {
                    if (shift_key) {
                        io._write("_");
                        break;
                    }
                    io._write("-");
                    break;
                }
                case KB_EQUAL_PRESSED: {
                    if (shift_key) {
                        io._write("+");
                        break;
                    }
                    io._write("=");
                    break;
                }                
                case KB_BACK_SPACE_PRESSED: {
                    io._backspace();
                    break;
                }  
                case KB_BACK_TICK_PRESSED: {
                    if (shift_key) {
                        io._write("~");
                        break;
                    }
                    io._write("`");
                    break;
                }  
                case KB_TAB_PRESSED: {
                    io._write("     ");
                    break;
                }  
                case KB_A_PRESSED: {
                if (uppercase) {
                    io._write("A");
                    break;
                }
                io._write("a");
                break;
                }
                case KB_B_PRESSED: {
                if (uppercase) {
                    io._write("B");
                    break;
                }
                io._write("b");
                break;
                }
                case KB_C_PRESSED: {
                if (uppercase) {
                    io._write("C");
                    break;
                }
                io._write("c");
                break;
                }
                case KB_D_PRESSED: {
                if (uppercase) {
                    io._write("D");
                    break;
                }
                io._write("d");
                break;
                }
                case KB_E_PRESSED: {
                if (uppercase) {
                    io._write("E");
                    break;
                }
                io._write("e");
                break;
                }
                case KB_F_PRESSED: {
                if (uppercase) {
                    io._write("F");
                    break;
                }
                io._write("f");
                break;
                }
                case KB_G_PRESSED: {
                if (uppercase) {
                    io._write("G");
                    break;
                }
                io._write("g");
                break;
                }
                case KB_H_PRESSED: {
                if (uppercase) {
                    io._write("H");
                    break;
                }
                io._write("h");
                break;
                }
                case KB_I_PRESSED: {
                if (uppercase) {
                    io._write("I");
                    break;
                }
                io._write("i");
                break;
                }
                case KB_J_PRESSED: {
                if (uppercase) {
                    io._write("J");
                    break;
                }
                io._write("j");
                break;
                }
                case KB_K_PRESSED: {
                if (uppercase) {
                    io._write("K");
                    break;
                }
                io._write("k");
                break;
                }
                case KB_L_PRESSED: {
                if (uppercase) {
                    io._write("L");
                    break;
                }
                io._write("l");
                break;
                }
                case KB_M_PRESSED: {
                if (uppercase) {
                    io._write("M");
                    break;
                }
                io._write("m");
                break;
                }
                case KB_N_PRESSED: {
                if (uppercase) {
                    io._write("N");
                    break;
                }
                io._write("n");
                break;
                }
                case KB_O_PRESSED: {
                if (uppercase) {
                    io._write("O");
                    break;
                }
                io._write("o");
                break;
                }
                case KB_P_PRESSED: {
                if (uppercase) {
                    io._write("P");
                    break;
                }
                io._write("p");
                break;
                }
                case KB_Q_PRESSED: {
                if (uppercase) {
                    io._write("Q");
                    break;
                }
                io._write("q");
                break;
                }
                case KB_R_PRESSED: {
                if (uppercase) {
                    io._write("R");
                    break;
                }
                io._write("r");
                break;
                }
                case KB_S_PRESSED: {
                if (uppercase) {
                    io._write("S");
                    break;
                }
                io._write("s");
                break;
                }
                case KB_T_PRESSED: {
                if (uppercase) {
                    io._write("T");
                    break;
                }
                io._write("t");
                break;
                }
                case KB_U_PRESSED: {
                if (uppercase) {
                    io._write("U");
                    break;
                }
                io._write("u");
                break;
                }
                case KB_V_PRESSED: {
                if (uppercase) {
                    io._write("V");
                    break;
                }
                io._write("v");
                break;
                }
                case KB_W_PRESSED: {
                if (uppercase) {
                    io._write("W");
                    break;
                }
                io._write("w");
                break;
                }
                case KB_X_PRESSED: {
                if (uppercase) {
                    io._write("X");
                    break;
                }
                io._write("x");
                break;
                }
                case KB_Y_PRESSED: {
                if (uppercase) {
                    io._write("Y");
                    break;
                }
                io._write("y");
                break;
                }
                case KB_Z_PRESSED: {
                if (uppercase) {
                    io._write("Z");
                    break;
                }
                io._write("z");
                break;
                }                                                      
                case KB_OPENED_BRACKET_PRESSED: {
                if (shift_key) {
                    io._write("{");
                    break;
                }
                io._write("[");
                break;
                }                                                      
                case KB_CLOSED_BRACKET_PRESSED: {
                if (shift_key) {
                    io._write("}");
                    break;
                }
                io._write("]");
                break;
                }                                                      
                case KB_SEMICOLON_PRESSED: {
                if (shift_key) {
                    io._write(":");
                    break;
                }
                io._write(";");
                break;
                }                                                      
                case KB_APOSTROPHE_PRESSED: {
                io._write("'");
                break;
                }                                                      
                case KB_LEFT_SLASH_PRESSED: {
                if (shift_key) {
                    io._write("|");
                    break;
                }
                break;
                }                                                      
                case KB_COMMA_PRESSED: {
                if (shift_key) {
                    io._write("<");
                    break;
                }
                io._write(",");
                break;
                }                                                      
                case KB_DOT_PRESSED: {
                if (shift_key) {
                    io._write(".");
                    break;
                }
                io._write(">");
                break;
                }                                                      
                case KB_RIGHT_SLASH_PRESSED: {
                if (shift_key) {
                    io._write("?");
                    break;
                }
                io._write("/");
                break;
                }                                                      
                case KB_SPACE_PRESSED: {
                io._write(" ");
                break;
                }                                                      
                                                                                                                                                                
                
                
                default:
                    continue;
            }
        }
    }
}
