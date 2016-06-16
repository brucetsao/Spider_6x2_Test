/*
 *    Module: ServoPwm.h
 *    Author: Jinn-Kwei Guo
 *    Date: 2016/6/10
 *      
 *    Software PWM Control Library for 50Hz Servo Motor  
 *        
 */

#ifndef ServoPwm_h
#define ServoPwm_h

#include "Spider.h"

#define   MaxServoNumber        NumOfMotor

#define   PWM_PulseMin           500 //center position of PWM
#define   PWM_PulseMid          1500 //center position of PWM
#define   PWM_PulseMax          2500 //pucenter position of PWM

class ServoPwm {
    public:      
        int targetPulseWidth[MaxServoNumber]; //ideal angle=0~180, limited by motor design parameter        
        int numberOfServo=0;
        
        ServoPwm(); //constructor
        void add(int pin);  //Add a motor to digital pin
        void PwmControl();
        void setPwmWidth(int servoNo, int pwmWidth);
        void report();
        
    private:
        int servoPin[MaxServoNumber];
};

extern ServoPwm Motor;

#endif //ServoPwm_h
//
// END OF FILE
//



