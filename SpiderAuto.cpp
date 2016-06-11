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
    movePhase  = 0;
    actionType = 0; // no action
}

void SpiderAuto::beginAction(int actionType)
{ 
    this->actionType = actionType;
    movePhase  = 0;  
}

void SpiderAuto::nextMove()
{  
    if (actionType==1) {
        pMoveTask->tickInterval = (unsigned long)spiderAutoAction1[movePhase][0]*1000L;  //1ms=1000us
        for (int i=0; i<Motor.numberOfServo; i++) {
            Motor.targetPhaseAngle[i] = spiderAutoAction1[movePhase][i+1];
        }
        if (++movePhase>4) movePhase=0;
    }      
    if (actionType==2) {
        pMoveTask->tickInterval = (unsigned long)spiderAutoAction2[movePhase][0]*1000L;  //1ms=1000us
        for (int i=0; i<Motor.numberOfServo; i++) {
            Motor.targetPhaseAngle[i] = spiderAutoAction2[movePhase][i+1];
        }
        if (++movePhase>3) movePhase=0;
    } 
    if (actionType==3) {
        pMoveTask->tickInterval = (unsigned long)spiderAutoAction3[movePhase][0]*1000L;  //1ms=1000us
        for (int i=0; i<Motor.numberOfServo; i++) {
            Motor.targetPhaseAngle[i] = spiderAutoAction3[movePhase][i+1];
        }
        if (++movePhase>2) movePhase=0;
    } 
}

