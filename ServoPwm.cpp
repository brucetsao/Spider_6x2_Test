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
    for (int i=0; i<MaxServoNumber; i++)
      targetPulseWidth[i] = PWM_PulseMid; //90 degree
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
    for (int i=0; i<numberOfServo; i++) {
        digitalWrite(servoPin[i],HIGH); //start pulse
    } 
    unsigned long startMicros = micros();
    unsigned long diffMicros=0;
    while ( (diffMicros=(micros() - startMicros)) < PWM_PulseMax) {
        for (int i=0; i<numberOfServo; i++) {    
            if (diffMicros>targetPulseWidth[i]) {
                digitalWrite(servoPin[i],LOW); //stop pulse
            }
        }        
    }
}

void ServoPwm::setPwmWidth(int servoNo, int pwmWidth) 
{
    if (servoNo > numberOfServo) return;
    if ((pwmWidth<PWM_PulseMin) || (pwmWidth>PWM_PulseMax)) return;
    targetPulseWidth[servoNo] = pwmWidth;
}

void ServoPwm::report()
{
    Serial.print("*** PWM : ");
    for (int i=0; i<numberOfServo; i++) {
        Serial.print(targetPulseWidth[i]);
        Serial.print(" ");    
    }
    Serial.println();
}

