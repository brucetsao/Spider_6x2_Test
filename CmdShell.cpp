/*
 *    Module: CmdShell.cpp
 *    Author: Jinn-Kwei Guo
 *    Date: 2016/6/10
 *      
 *    Command Shellf for Spider
 *        
 */
 
#include "CmdShell.h"
#include "ServoPwm.h"

#define DEBUG_LEVEL 0

//Extern
CmdShell CommandShell;

CmdShell::CmdShell()
{
    cmdLength=0;
}

void CmdShell::init(HardwareSerial *port)
{    
    this->port = port;
}

void CmdShell::getCommand() 
{
    while (port->available()) {
        byte inByte = port->read();
        if (inByte=='$') { // Start Of Command
            cmdLength=0;
        }
        cmdBuffer[cmdLength++] = inByte;
        if (inByte=='#') {  // End Of Command
            parseCommand();
        } 
    }
}

void CmdShell::parseCommand()
{
    if ((cmdBuffer[1]=='M') && (cmdBuffer[4]=='A')) {
        int motorID = (cmdBuffer[2]-'0')*10 + (cmdBuffer[3]-'0');
        int phaseAngle = (cmdBuffer[5]-'0')*100 + (cmdBuffer[6]-'0')*10 + (cmdBuffer[7]-'0');
        Motor.targetPhaseAngle[motorID] = phaseAngle;        
        #if (DEBUG_LEVEL>1)
            Serial.print("MotorID=");
            Serial.print(motorID);
            Serial.print(", phaseAngle=");
            Serial.println(phaseAngle);
        #endif
    } else {
        #if (DEBUG_LEVEL>1)
            Serial.print("Bad Command: '");
            Serial.write(cmdBuffer, cmdLength); 
            Serial.println("'");
        #endif
    }
    cmdLength=0; //reset 
}

void CmdShell::runCommand(String cmdString)
{
    for (int i=0; i<cmdString.length(); i++) {
        cmdBuffer[i] = cmdString[i];
    }
    parseCommand();
}

