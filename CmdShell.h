/*
 *    Module: CmdShell.h
 *    Author: Jinn-Kwei Guo
 *    Date: 2016/6/10
 *      
 *    Command Shellf for Spider
 *        
 */

#include <Arduino.h>
#include "Spider.h"

#ifndef CmdShell_h
#define CmdShell_h

#define   CmdBufferLength        12

class CmdShell {
    public:             
        CmdShell(); //constructor
        void init(HardwareSerial *port);    //May changed to SoftwareSerial
        void getCommand();                  //get command from input stream
        void runCommand(String cmdString);  //interpret the command then execute
                
    private:
        char cmdBuffer[CmdBufferLength];
        int  cmdLength=0;
        HardwareSerial *port;
        void parseCommand();
};

extern CmdShell CommandShell;

#endif //CmdShell_h
//
// END OF FILE
//



