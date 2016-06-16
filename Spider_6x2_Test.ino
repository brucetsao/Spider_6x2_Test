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

    // Motor setup
    #if (NumOfMotor==12) //12 motors
        for (int i=0; i<8; i++)  { //#1~8
            Motor.add(i+2);         
        }
    
        Motor.add(A0);
        Motor.add(A1);
        Motor.add(A2);
        Motor.add(A3);
    #endif        
    #if (NumOfMotor==18) 
        for (int i=0; i<12; i++)  { //#1~12
            Motor.add(i+2);         
        }    
        Motor.add(A0);
        Motor.add(A1);
        Motor.add(A2);
        Motor.add(A3);
        Motor.add(A4);
        Motor.add(A5);    
    #endif
    
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
    //pMotorPwmTask->report();  //cannot report in running mode
}

void CmdShellTask()
{
    CommandShell.getCommand();  //get command from input stream
    //pCmdShellTask->report();  //cannot report in running mode
}

void SpiderMoveTask()
{
    if (Motor.numberOfServo!=12) {  // Check Spider Type with spider Action data
        //Serial.println("Motor.numberOfServo error");
        return;
    }
    if (spiderAuto.actionType>0) {
        spiderAuto.nextMove();
    }
    //spiderAuto.pMoveTask->report();
}

