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

#include <Arduino.h>
#include "Spider.h"
#include "RTOS.h"

#define NumberOfServo 12
#define PWM_MaxPulseWidth   2500
#define PWM_MinPulseWidth    500 

class ServoPwm {
    public:      
        // variables      
        int targetPulseWidth[NumberOfServo]; //ideal angle=0~180, limited by motor design parameter 
        Task* pPwmTask;   

        // methods
        ServoPwm(); //constructor
        void PwmControl();
        void setPwmWidth(int servoNo, int pwmWidth);
        void setAngle(int servoNo, int angle);
        void report();
        
    private:
        int servoPin[NumberOfServo] =  { 2, 3, 4, 5, 6, 7, 8, 9, A0, A1, A2, A3}; // I/O pin of servo

        // The followint parameters are motor-dependent, they should be adjusted for each motor
        int minPulseWidth[NumberOfServo] = {  600,  600,  600,  600,  600,  600,  600,  600,  600,  600,  600,  600};  // limit of each servo
        int midPulseWidth[NumberOfServo] = { 1500, 1450, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};  // center of each servo
        int maxPulseWidth[NumberOfServo] = { 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400, 2400};  // limit of each servo
        float angleToPwmRatio[NumberOfServo] = { 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0 }; //convert angle to pulse width ratio

        // methods
        int angleToPulseWidth(int servoNo, int angle);  //convert angle to pulse width
};

extern ServoPwm motor;

#endif //ServoPwm_h
//
// END OF FILE
//



