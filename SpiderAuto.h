/*
 *    Module: SpiderAuto.h
 *    Author: Jinn-Kwei Guo
 *    Date: 2016/6/10
 *      
 *    Auto Action for Spider
 *        
 */

#include <Arduino.h>

#ifndef SpiderAuto_h
#define SpiderAutol_h

#include "RTOS.h"

class SpiderAuto {
    public:    
        Task* pMoveTask;
        
        SpiderAuto(); //constructor
        void beginAction(int actionType);
        void nextMove();

    private:            
        int movePhase  = 0;
        int actionType = 0; 
};

extern SpiderAuto spiderAuto;

#endif //SpiderAuto

//
// END OF FILE
//

