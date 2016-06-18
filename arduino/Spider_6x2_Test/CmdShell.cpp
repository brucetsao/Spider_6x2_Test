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

#define DEBUG_LEVEL 0

//Extern
CmdShell CommandShell;

CmdShell::CmdShell()
{
    cmdLength=0;
}

int CmdShell::parseCommand()
{
    int retCode=0;
    
    #if (DEBUG_LEVEL>0)
      Serial.print("*** CMD:");
      Serial.write(cmdBuffer,cmdLength);
      Serial.println();
    #endif
    
    if ((cmdBuffer[1]=='M') && (cmdBuffer[4]=='W') && (cmdBuffer[9]=='#'))
    { 
        // Command : Motor Pulse Width
        int motorID = (cmdBuffer[2]-'0')*10 + (cmdBuffer[3]-'0');
        int pulseWidth = (cmdBuffer[5]-'0')*1000 + (cmdBuffer[6]-'0')*100 + (cmdBuffer[7]-'0')*10 + (cmdBuffer[8]-'0');
        motor.targetPulseWidth[motorID] = pulseWidth;        
        retCode=1;
        
        #if (DEBUG_LEVEL>1)
            Serial.print(F("MotorID="));
            Serial.print(motorID);
            Serial.print(F(", pulseWidth="));
            Serial.println(pulseWidth);
        #endif
    } 
    else if ((cmdBuffer[1]=='M') && (cmdBuffer[4]=='A') && (cmdBuffer[8]=='#'))
    { 
        // Command : Motor Angle 
        int motorID = (cmdBuffer[2]-'0')*10 + (cmdBuffer[3]-'0');
        int angle = (cmdBuffer[5]-'0')*100 + (cmdBuffer[6]-'0')*10 + (cmdBuffer[7]-'0');
        motor.setAngle(motorID, angle);        
        retCode=1;
        
        #if (DEBUG_LEVEL>1)
            Serial.print(F("MotorID="));
            Serial.print(motorID);
            Serial.print(F(", angle="));
            Serial.println(angle);
        #endif        
    } 
    else if ((cmdBuffer[1]=='S') && (cmdBuffer[5]=='#'))
    { 
        // Command : Set
        int angle = (cmdBuffer[2]-'0')*100 + (cmdBuffer[3]-'0')*10 + (cmdBuffer[4]-'0');
        for (int i=0; i<NumberOfServo; i++) {
            motor.setAngle(i, angle);
        }     
        retCode=1;
    } 
    else if ((cmdBuffer[1]=='Q') && (cmdBuffer[2]=='#')) 
    {
        // Command : Query
        Serial.print("*** PWM: ");
        for (int i=0; i<NumberOfServo; i++) {
            Serial.print(motor.targetPulseWidth[i]);
            Serial.print(" ");
        }    
        Serial.println();
        retCode=1;
    } else if ((cmdBuffer[1]=='A') && (cmdBuffer[3]=='#')) 
    {
        // Command : AutoAction
        int actionID = (cmdBuffer[2]-'0');        
        spiderAuto.beginAction(actionID);
    } else {
        spiderAuto.beginAction(0); //reset and stop
        #if (DEBUG_LEVEL>0)
            Serial.print("Bad Command: '");
            Serial.write(cmdBuffer, cmdLength); 
            Serial.println("'");
        #endif
        retCode = -1;
    }
    cmdLength=0; //reset 
    return retCode;
}
