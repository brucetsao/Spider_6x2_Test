/*
 *    Spider_Test: Test PWM Control for 12 Servo Motors
 *    
 *    Note : Each RTOS task must be executed within 1ms (RTOS tick) to generate the correct PWM pulse width.
 */
 
#include <avr/wdt.h>
#include "RTOS.h"
#include "ServoPwm.h"

#define DEBUG_LEVEL 1

ServoPwm Motor;

Task *pMotorPwmTask;

void setup() {
    wdt_disable();    // immediately disable watchdog timer so set will not get interrupted
    
    // Debug port on Serial
    Serial.begin(57600);    

    // Motor setup
    for (int i=2; i<13; i++)  { //12 motors
        Motor.add(i); 
    }
    // Add tasks to RTOS
    pMotorPwmTask = RTOS.taskManager.addTask(MotorPwmTask, "MotorPwmTask", 1); //response time is 1ms    
    // init()
    RTOS.init();    
    wdt_enable(WDTO_1S); //RTOS Task cannot run exceed 1s
}

void loop() {
    wdt_reset();
    RTOS.run(); //Always run th OS
    switch (keyPressed()) {
        case '1': Motor.targetPhaseAngle[1] += 10;
                  if (Motor.targetPhaseAngle[1]>160) Motor.targetPhaseAngle[1]=20;
                  break;
        case '2': Motor.targetPhaseAngle[2] += 10;
                  if (Motor.targetPhaseAngle[2]>160) Motor.targetPhaseAngle[2]=20;
                  break;
        case '?':
                  RTOS.taskManager.taskListReport(); //debug report        
                  #if (DEBUG_LEVEL>0)
                      while (keyPressed()!='!') {
                          wdt_reset();
                          delay(100); //wait key pressed
                      }
                  #endif      
                  break;  
    }
}

int keyPressed()
{
    return Serial.available() ? Serial.read() : -1;
}

void MotorPwmTask()
{
    Motor.PwmControl();
    Motor.report(); //debug mode, cannot report in running mode
    //pMotorPwmTask->report();
}

