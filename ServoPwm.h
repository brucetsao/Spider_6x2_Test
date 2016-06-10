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

#define   MaxServoNumber        12
#define   MaxServoTick          20  // 50Hz PWm -> 20ms, if RTOS run tick is 1ms, max tick is 20
#define   PhaseAngleResolution   9  // 50Hz PWm -> 20ms, if RTOS run tick is 1ms, resolution = 180/20 = 9 degree

class ServoPwm {
    public:      
        int targetPhaseAngle[MaxServoNumber]; //ideal angle=0~180, limited by motor design parameter
        
        ServoPwm(); //constructor
        void add(int pin);  //Add a motor to digital pin
        void PwmControl();
        void report();
        
    private:
        int numberOfServo=0;
        int phaseTickCount=0;
        int servoPin[MaxServoNumber];
        int currentPhaseAngle[MaxServoNumber];
};

extern ServoPwm Motor;

#endif //ServoPwm_h
//
// END OF FILE
//



