/*
 *    Module: SpiderAuto.cpp
 *    Author: Jinn-Kwei Guo
 *    Date: 2016/6/10
 *      
 *    Auto Action for Spider
 *        
 */
 
#include "SpiderAuto.h"
#include "ServoPWM.h"

SpiderAuto spiderAuto;

int spiderAutoAction1[][13]= { 
        {1000,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30}, //action time in mini-seconds, angle1, angle2, angle3 ...... angle12
        {1000,  60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60},
        {1000,  90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90},
        {1000, 120,120,120,120,120,120,120,120,120,120,120,120},
        {1000, 150,150,150,150,150,150,150,150,150,150,150,150}
    };
int spiderAutoAction2[][13]= { 
        {1000,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30}, //action time in mini-seconds, angle1, angle2, angle3 ...... angle12
        {1000,  60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60},
        {1000,  90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90},
        {1000, 120,120,120,120,120,120,120,120,120,120,120,120},
    };
int spiderAutoAction3[][13]= { 
        {1000,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30}, //action time in mini-seconds, angle1, angle2, angle3 ...... angle12
        {1000,  60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60},
        {1000,  90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90},
    };


SpiderAuto::SpiderAuto() //constructor
{
    moveStep  = 0;
    actionType = 0; // no action
}

void SpiderAuto::beginAction(int actionType)
{ 
    this->actionType = actionType;
    moveStep  = 0;  
}

int AngleToPWM(int angle) {
    return (angle-90)*10 + PWM_PulseMid;
}

void SpiderAuto::nextMove()
{  
    if (actionType==1) {
        pMoveTask->tickInterval = (unsigned long)spiderAutoAction1[moveStep][0]*1000L;  
        for (int i=0; i<Motor.numberOfServo; i++) {
            Motor.setPwmWidth(i,AngleToPWM(spiderAutoAction1[moveStep][i+1]));
        }
        if (++moveStep>4) moveStep=0;
    }      
    if (actionType==2) {
        pMoveTask->tickInterval = (unsigned long)spiderAutoAction2[moveStep][0]*1000L;  
        for (int i=0; i<Motor.numberOfServo; i++) {
             Motor.setPwmWidth(i,AngleToPWM(spiderAutoAction2[moveStep][i+1]));
        }
        if (++moveStep>3) moveStep=0;
    } 
    if (actionType==3) {
        pMoveTask->tickInterval = (unsigned long)spiderAutoAction3[moveStep][0]*1000L;  
        for (int i=0; i<Motor.numberOfServo; i++) {
            Motor.setPwmWidth(i,AngleToPWM(spiderAutoAction3[moveStep][i+1]));
        }
        if (++moveStep>2) moveStep=0;
    } 
}

