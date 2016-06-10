/*
 *    Spider_Test: Test PWM Control for 12 Servo Motors
 *    
 *    Note : Each RTOS task must be executed within 1ms (RTOS tick) to generate the correct PWM pulse width.
 */
 
#include <avr/wdt.h>
#include "RTOS.h"
#include "Spider.h"
#include "ServoPwm.h"
#include "CmdShell.h"

#define DEBUG_LEVEL 1

Task *pMotorPwmTask, *pCmdShellTask;

void setup() {
    wdt_disable();    // immediately disable watchdog timer so set will not get interrupted
    

    Serial.begin(57600);        // Debug port on Serial
    CommandShell.init(&Serial); //Command port on Serial

    // Motor setup
    for (int i=2; i<13; i++)  { //12 motors
        Motor.add(i); 
    }
    // Add tasks to RTOS
    pMotorPwmTask = RTOS.taskManager.addTask(MotorPwmTask, "MotorPwmTask", 1000); //response time is 1000us
    pCmdShellTask = RTOS.taskManager.addTask(CmdShellTask, "CmdShellTask", 1000); //response time is 1000us 
    // init()
    RTOS.init();    
    wdt_enable(WDTO_1S); //RTOS Task cannot run exceed 1s
}

void loop() {
    wdt_reset();
    RTOS.run(); //Always run th OS
}

void MotorPwmTask()
{
    Motor.PwmControl();
    //Motor.report();           //cannot report in running mode
    //pMotorPwmTask->report();  //cannot report in running mode
}

void CmdShellTask()
{
    CommandShell.getCommand();
    //pCmdShellTask->report();  //cannot report in running mode
}

