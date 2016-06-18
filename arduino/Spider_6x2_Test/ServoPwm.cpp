/*
 *    Module: ServoPwm.cpp
 *    Author: Jinn-Kwei Guo
 *    Date: 2016/6/10
 *      
 *    Software PWM Control Library for 50Hz Servo Motor  
 *        
 */

#include "ServoPwm.h"

#define DEBUG_LEVEL 2

//Extern
ServoPwm motor;

/*
 * ServoPwm Class
 */
ServoPwm::ServoPwm()
{
    for (int i=0; i<NumberOfServo; i++) {
        pinMode(servoPin[i],OUTPUT);    
        targetPulseWidth[i] =  midPulseWidth[i]; //90 degree
    }
}

void ServoPwm::PwmControl()
{
    for (int i=0; i<NumberOfServo; i++) {
        digitalWrite(servoPin[i],HIGH); //start pulse
    } 
    unsigned long startMicros = micros();
    unsigned long diffMicros=0;
    while ( (diffMicros=(micros() - startMicros)) < PWM_MaxPulseLength) {
        for (int i=0; i<NumberOfServo; i++) {    
            if (diffMicros>targetPulseWidth[i]) {
                digitalWrite(servoPin[i],LOW); //stop pulse
            }
        }        
    }
    //ensure to stop pulse
    for (int i=0; i<NumberOfServo; i++) {    
        digitalWrite(servoPin[i],LOW); 
    }            
}

int ServoPwm::angleToPulseWidth(int servoNo, int angle) {
    return (angle-90)*angleToPwmRatio[servoNo] + midPulseWidth[servoNo];
}

void ServoPwm::setPwmWidth(int servoNo, int pwmWidth) 
{  
    if ((servoNo >= NumberOfServo) || (servoNo < 0)) return;
    if ((pwmWidth > maxPulseWidth[servoNo]) || (pwmWidth<minPulseWidth[servoNo])) return;
    targetPulseWidth[servoNo] = pwmWidth;
}

void ServoPwm::setAngle(int servoNo, int angle) 
{
    setPwmWidth(servoNo, angleToPulseWidth(servoNo, angle));
}

void ServoPwm::report()
{
    Serial.print("*** PWM : ");
    for (int i=0; i<NumberOfServo; i++) {
        Serial.print(targetPulseWidth[i]);
        Serial.print(" ");    
    }
    Serial.println();
}

