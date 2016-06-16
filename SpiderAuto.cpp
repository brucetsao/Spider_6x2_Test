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
        {250,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30}, //action time in mini-seconds, angle1, angle2, angle3 ...... angle12
        {250,  60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60},
        {250,  90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90},
        {250, 120,120,120,120,120,120,120,120,120,120,120,120},
        {250, 150,150,150,150,150,150,150,150,150,150,150,150},
        {250, 120,120,120,120,120,120,120,120,120,120,120,120},
        {250,  90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90},
        {250,  60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60}
    };
int spiderAutoAction2[][13]= { 
        {250,  30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30}, //action time in mini-seconds, angle1, angle2, angle3 ...... angle12        
        {250,  90, 90, 90, 90, 90, 90, 30, 30, 30, 30, 30, 30},
        {250,  90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90},
        {250, 150,150,150,150,150,150, 90, 90, 90, 90, 90, 90},
        {250, 150,150,150,150,150,150,150,150,150,150,150,150},
        {250, 150,150,150,150,150,150, 90, 90, 90, 90, 90, 90},
        {250,  90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90},
        {250,  90, 90, 90, 90, 90, 90, 30, 30, 30, 30, 30, 30}
    };
int spiderAutoAction3[][13]= { 
        {1000,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, //action time in mini-seconds, angle1, angle2, angle3 ...... angle12
        {1000,  90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90},
        {1000, 180,180,180,180,180,180,180,180,180,180,180,180}
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


void SpiderAuto::nextMove()
{  
    if (actionType==1) {
        pMoveTask->tickInterval = (unsigned long)spiderAutoAction1[moveStep][0]*1000L;  
        for (int i=0; i<Motor.numberOfServo; i++) {
            Motor.setAngle(i,spiderAutoAction1[moveStep][i+1]);
        }
        if (++moveStep>7) moveStep=0;
    }      
    if (actionType==2) {
        pMoveTask->tickInterval = (unsigned long)spiderAutoAction2[moveStep][0]*1000L;  
        for (int i=0; i<Motor.numberOfServo; i++) {
              Motor.setAngle(i,spiderAutoAction2[moveStep][i+1]);
        }
        if (++moveStep>7) moveStep=0;
    } 
    if (actionType==3) {
        pMoveTask->tickInterval = (unsigned long)spiderAutoAction3[moveStep][0]*1000L;  
        for (int i=0; i<Motor.numberOfServo; i++) {
             Motor.setAngle(i,spiderAutoAction3[moveStep][i+1]);
        }
        if (++moveStep>2) moveStep=0;
    } 
}

