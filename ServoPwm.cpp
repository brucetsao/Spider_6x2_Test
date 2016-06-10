/*
 *    Module: ServoPwm.cpp
 *    Author: Jinn-Kwei Guo
 *    Date: 2016/6/10
 *      
 *    Software PWM Control Library for 50Hz Servo Motor  
 *        
 */

#include <Arduino.h>
#include "ServoPwm.h"

//Extern
ServoPwm Motor;

/*
 * ServoPwm Class
 */
ServoPwm::ServoPwm()
{
    numberOfServo=0;  
    phaseTickCount=0;
    for (int i=0; i<MaxServoNumber; i++)
      targetPhaseAngle[i] = 90; //90 degree
}

void ServoPwm::add(int pin)
{
    if (numberOfServo<MaxServoNumber) {
        servoPin[numberOfServo] = pin;
        pinMode(pin,OUTPUT);
        numberOfServo++;
    } else {
        Serial.println(F("*** Err: MaxServoNumber exceed"));
    }
}

void ServoPwm::PwmControl()
{
    if (phaseTickCount==0) {
        for (int i=0; i<numberOfServo; i++) {
            digitalWrite(servoPin[i],HIGH); //start pulse
            currentPhaseAngle[i] = 0;
        }
    } else {
        for (int i=0; i<numberOfServo; i++) {    
            if (currentPhaseAngle[i]<targetPhaseAngle[i]) {
                currentPhaseAngle[i] += PhaseAngleResolution;
            } else {            
                digitalWrite(servoPin[i],LOW); //stop pulse
            }
        }
    }
    if (++phaseTickCount>=MaxServoTick) {
        phaseTickCount=0;
    }
}

void ServoPwm::report()
{
    Serial.print("t=");
    Serial.print(phaseTickCount);
    Serial.print(": ");
    for (int i=0; i<numberOfServo; i++) {
        Serial.print(currentPhaseAngle[i]);
        Serial.print("/");
        Serial.print(targetPhaseAngle[i]);
        Serial.print(" ");    
    }
    Serial.println();
}

