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
#define   PhaseAngleResolution   5  // 5 degree
#define   MaxServoTick          36  // 50Hz PWm -> 20ms, 180 degree /5 degree = 36

class ServoPwm {
    public:      
        int targetPhaseAngle[MaxServoNumber]; //ideal angle=0~180, limited by motor design parameter        
        int numberOfServo=0;
        
        ServoPwm(); //constructor
        void add(int pin);  //Add a motor to digital pin
        void PwmControl();
        void report();
        
    private:
        int phaseTickCount=0;
        int servoPin[MaxServoNumber];
        int currentPhaseAngle[MaxServoNumber];
};

extern ServoPwm Motor;

#endif //ServoPwm_h
//
// END OF FILE
//



