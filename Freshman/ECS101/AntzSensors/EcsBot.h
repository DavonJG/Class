//
//  EcsBot.hpp
//  
//
//  Created by Eli Goldweber on 10/29/15.
//
//

#include <Display.h>
#include <dll.h>
#include <Motor.h>
#include <MovementTracker.h>
#include <Receiver.h>
#include <Scanner.h>
#include <Sender.h>
#include <TimerOne.h>
#include <TimerThree.h>
/*
 * Antz
 * Antz Framework
 * Worker.h
 *
 * Copyright (c) 2015 Zhi Xing. All rights reserved.
 * License: <#license#>
 */


#ifndef __Antz__EcsBot__
#define __Antz__EcsBot__

#include "AntzRobot.h"

namespace Antz {
    class EcsBot: public AntzRobot {
    public:
        EcsBot(uint32_t robotId);
        virtual ~EcsBot() {}
        virtual void setup();
        virtual void loop();
        
        
        
    protected:
        
    };
}

#endif /* defined(__Antz__EcsBot__) */
