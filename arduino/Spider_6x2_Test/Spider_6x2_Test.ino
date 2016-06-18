/*
 *    Spider_Test: Test PWM Control for 12 Servo Motors
 *    
 *    Note : Each RTOS task must be executed within 1ms (RTOS tick) to generate the correct PWM pulse width.
 */
 
#include <avr/wdt.h>
#include "RTOS.h"
#include "Spider.h"
#include "ServoPwm.h"
#include "CmdPC.h"
#include "CmdBT.h"
#include "SpiderAuto.h"
#include <SoftwareSerial.h>

#define DEBUG_LEVEL 1

#define   BT_RX  10
#define   BT_TX  11
#define   BT_KEY 12

SoftwareSerial BTSerial(BT_RX, BT_TX); // RX | TX

void setup() {
    wdt_disable();    // immediately disable watchdog timer so set will not get interrupted
    
    Serial.begin(57600);        // PC port on Serial
    cmdPC.begin(&Serial);
    
    BTSerial.begin(9600);  // HC-05 default speed in AT command more
    cmdBT.begin(&BTSerial);
    
    // Add tasks to RTOS
    motor.pPwmTask = RTOS.taskManager.addTask(MotorPwmTask, "MotorPwmTask", 20000); //50Hz Pulse, 20ms 
    cmdPC.pGetCommandTask = RTOS.taskManager.addTask(CmdPcTask, "CmdPcTask", 20000); //check input stream every 20ms 
    cmdBT.pGetCommandTask = RTOS.taskManager.addTask(CmdBtTask, "CmdPcTask", 20000); //check input stream every 20ms 
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
    motor.PwmControl();
    //motor.report();           //cannot report in running mode
    //motor.pPwmTask->report();  //cannot report in running mode
}

void CmdPcTask()
{
    cmdPC.getCommand();  //get command from input stream
    //cmdPC.pGetCommandTask->report();  //cannot report in running mode
}

void CmdBtTask()
{
    cmdBT.getCommand();  //get command from input stream
    //cmdBT.pGetCommandTask->report();  //cannot report in running mode
}

void SpiderMoveTask()
{
    if (spiderAuto.actionType>0) {
        spiderAuto.nextMove();
    }
    //spiderAuto.pMoveTask->report();
}

