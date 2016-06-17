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
#include "SpiderAuto.h"

#define DEBUG_LEVEL 1

Task *pCmdShellTask;

void setup() {
    wdt_disable();    // immediately disable watchdog timer so set will not get interrupted

    pinMode(A0,OUTPUT); //debug pulse

    Serial.begin(57600);        // Debug port on Serial
    CommandShell.init(&Serial); //Command port on Serial
    
    // Add tasks to RTOS
    Motor.pPwmTask = RTOS.taskManager.addTask(MotorPwmTask, "MotorPwmTask", 20000); //50Hz Pulse, 20ms 
    CommandShell.pCmdTask = RTOS.taskManager.addTask(CmdShellTask, "CmdShellTask", 20000); //check input stream every 20ms 
    spiderAuto.pMoveTask = RTOS.taskManager.addTask(SpiderMoveTask, "SpiderMoveTask", 1000000); //move legs every 1s
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
    // Motor.pPwmTask->report();  //cannot report in running mode
}

void CmdShellTask()
{
    CommandShell.getCommand();  //get command from input stream
    //CommandShell.pCmdTask->report();  //cannot report in running mode
}

void SpiderMoveTask()
{
    if (spiderAuto.actionType>0) {
        spiderAuto.nextMove();
    }
    //spiderAuto.pMoveTask->report();
}

