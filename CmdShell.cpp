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
#include "SpiderAuto.h"

#define DEBUG_LEVEL 2

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
    Serial.print("*** CMD:");
    Serial.write(cmdBuffer,cmdLength);
    Serial.println();
    if ((cmdBuffer[1]=='M') && (cmdBuffer[4]=='W') && (cmdBuffer[9]=='#'))
    { 
        // Command : Motor Angle 
        int motorID = (cmdBuffer[2]-'0')*10 + (cmdBuffer[3]-'0');
        int pulseWidth = (cmdBuffer[5]-'0')*1000 + (cmdBuffer[6]-'0')*100 + (cmdBuffer[7]-'0')*10 + (cmdBuffer[8]-'0');
        Motor.targetPulseWidth[motorID] = pulseWidth;        
        #if (DEBUG_LEVEL>1)
            Serial.print("MotorID=");
            Serial.print(motorID);
            Serial.print(", pulseWidth=");
            Serial.println(pulseWidth);
        #endif
    } else if ((cmdBuffer[1]=='A') && (cmdBuffer[3]=='#')) 
    {
        // Command : AutoAction
        int actionID = (cmdBuffer[2]-'0');        
        spiderAuto.beginAction(actionID);
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

