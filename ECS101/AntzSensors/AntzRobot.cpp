#include <Communication.h>
#include <Display.h>
#include <dll.h>
#include <known_16bit_timers.h>
#include <Motor.h>
#include <MovementTracker.h>
#include <Neighbor.h>
#include <Receiver.h>
#include <Scanner.h>
#include <Sender.h>
#include <TimerOne.h>
#include <TimerThree.h>

/*
 * Antz
 * Antz Framework
 * AntzRobot.cpp
 *		Definition of object factory and various other routines related to the robot.
 *		Contains routines mostly concerned with robot movement.
 *
 * Copyright (c) 2015 Zhi Xing. All rights reserved.
 * License: <#license#>
 */

#include "AntzRobot.h"
#include "EcsBot.h"


using namespace Antz;

uint8_t AntzRobot::avoidCnt = 0;
uint32_t AntzRobot::identifier = 0;
float AntzRobot::condProb[] = {1.f/6};
int64_t AntzRobot::motorStartMillis = -1;
int64_t AntzRobot::motorStopMillis = -1;
AntzRobot::MoveType AntzRobot::curMovement = mt_stop;
Display AntzRobot::display;
Motor AntzRobot::motor;
Receiver AntzRobot::recver;
Scanner AntzRobot::scanner;
Sender AntzRobot::sender;

/*
 * AntzRobot -- Constructor
 */
  
AntzRobot::AntzRobot(uint32_t robotId) {
    identifier = robotId;
    
    for (int i =0; i<6; i++) {
      Neighborhood[i] = NULL;
    }
    list = new Dll();
    
}

/*
 * createAntzRobot -- Object factory
 * @ type:	specifies the type of robot required
 * @ robotId:	given Id of the robot to be created
 */
AntzRobot* AntzRobot::createAntzRobot(char* type, uint32_t robotId) {
  if (strcmp(type, "EcsBot") == 0)
        return new EcsBot(robotId);
  else
    return NULL;
//    if (strcmp(type, "Worker") == 0)
//        return new Worker(robotId);
//    else if (strcmp(type, "Guider") == 0)
//        return new Guider(robotId);
//    else if (strcmp(type, "ExpGuider") == 0)
//        return new ExpGuider(robotId);
//    else if (strcmp(type, "Tester") == 0)
//        return new Tester(robotId);
//    else if (strcmp(type, "BayesWorker") == 0)
//        return new BayesWorker(robotId);
     
//    else
//        return NULL;
}

/*
 * setup -- setup routine for Arduino sketch
 */
void AntzRobot::setup() {
    Timer3.initialize(100000); 		// run the ISR every 100 ms
    Timer3.attachInterrupt(isr);
    scanner.startup();
    randomSeed(analogRead(0));
}

/*
 * loop -- loop routine for Arduino sketch
 */
void AntzRobot::loop() {
}

/*
 * goForward -- move in forward direction for stipulated time
 * @ msec:	time in milli seconds
 * @ async:	flag to specify whether to move forward in synchronous or asynchronous manner
 */
void AntzRobot::goForward(uint64_t msecs, bool async) {
    
    Timer3.detachInterrupt();		// disable the timer interrupt
    motor.forward();			// perform the action
    curMovement = mt_forward;
    motorStartMillis = millis();
    motorStopMillis = motorStartMillis + msecs;
    Timer3.attachInterrupt(isr);	// enable the timer interrupt
    if (!async) {
        delay(msecs);			// introduce the delay if the action is synchronous
        stopMoving();
    }
}

/*
 * goBackward -- move in backward direction for stipulated time
 * @ msec:	time in milli seconds
 * @ async:	flag to specify whether to move backward in synchronous or asynchronous manner
 */
void AntzRobot::goBackward(uint64_t msecs, bool async) {
    
    Timer3.detachInterrupt();		// disable the timer interrupt
    motor.backward();			// perform the action
    curMovement = mt_backward;
    motorStartMillis = millis();
    motorStopMillis = motorStartMillis + msecs;
    Timer3.attachInterrupt(isr);	// enable the timer interrupt
    if (!async) {
        delay(msecs);			// introduce the delay if the action is synchronous
        stopMoving();
    }
}

/*
 * turnLeft --  turn left by stipulated degree
 * @ degree:	stipulated angle
 * @ async:	flag to specify whether to turn left in synchronous or asynchronous manner
 */
void AntzRobot::turnLeft(float degree, bool async) {
     //Serial.printl(degree);
    
    Timer3.detachInterrupt();		// disable the timer interrupt
    motor.left();			// perform the action
    curMovement = mt_left;
    motorStartMillis = millis();
    motorStopMillis = motorStartMillis + MTR_MSPERDEG * degree;
    Timer3.attachInterrupt(isr);	// enable the timer interrupt
    if (!async) {
        delay(MTR_MSPERDEG * degree);	// introduce the delay if the action is synchronous
        stopMoving();
    }
}

/*
 * turnRight --  turn right by stipulated degree
 * @ degree:	stipulated angle
 * @ async:	flag to specify whether to turn right in synchronous or asynchronous manner
 */
void AntzRobot::turnRight(float degree, bool async) {
    
    Timer3.detachInterrupt();		// disable the timer interrupt
    motor.right();			// perform the action
    curMovement = mt_right;
    motorStartMillis = millis();
    motorStopMillis = motorStartMillis + MTR_MSPERDEG * degree;
    Timer3.attachInterrupt(isr);	// enable the timer interrupt
    if (!async) {
        delay(MTR_MSPERDEG * degree);	// introduce the delay of the action is synchronous
        stopMoving();
    }
}

/*
 * stopMoving -- immediately stop moving
 */
void AntzRobot::stopMoving() {
    
    Timer3.detachInterrupt();		// disable the timer interrupt
    motor.stop();			// perform the action
    curMovement = mt_stop;
    motorStartMillis = -1;
    motorStopMillis = -1;
    Timer3.attachInterrupt(isr);	// enable the timer interrupt
}

/*
 * avoid -- obstacle avoidance
 */
bool AntzRobot::avoid() {
    bool detected = false;
    float angle;
    bool async = true;
    uint8_t deg = 60;
    while (scanner.scan(&angle) <= 30) {// scanner.scan returns distance from obstacle and 30 is the tentative distance
        detected = true;
        ++avoidCnt;
    /*
     * without this if condition, the robot's sensor can eternally keep shaking left-right left-right
     * to break this deadlock, after shaking five times, the robot makes a movement
     */
        if (avoidCnt > 5) { 		// possible deadlock
            async = false;
            deg = 90;
        }
        //if (angle > 30)
            turnRight(deg, async);
        //else
            //turnLeft(deg, async);
    }
    goForward(500);
    if (!detected)
        avoidCnt = 0;
    return detected;
}


/*   Added by Eli 7/24/15 (Called instead of avoid)
 *  Trying to split avoid into two sub functions 
 *  1) Detect if there is there is something in front of the robot
 *  2) move accordingly
 */
bool AntzRobot::blocked() { 
    bool detected1 = false;
    bool detected2 = false; // check twice to make sure that something is actually there
    float angle;
    bool async = true;
    delay(100);
    if (scanner.scan(&angle) <= 20) 
      detected1 = true; // the robot saw something the FIRST time
    delay(100);
    if (scanner.scan(&angle) <= 20) 
      detected2 = true; // the robot saw something the SECOND time


      obstacleSeen = detected1 && detected2;
      return (obstacleSeen); // only returns true if it saw somehting both checks
}

void AntzRobot::evasiveAction(){ // should be improved 
  // assumed that this will be called the first time after "blocked" returns true
  avoidCnt = 0;
  float angle;
  bool async = true;
  uint8_t deg = 20;
  while(obstacleSeen){
    avoidCnt++;
    if (avoidCnt > 5) {     
       // possible deadlock
       async = false;
       deg = 80; // when it turns it should end up 180 degrees from where it started facing
       avoidCnt = 0;
    }
    turnLeft(deg, async);
    obstacleSeen = blocked();

  }
}

/*
 * isr -- the ISR for timer interrupts, this should be called in
 * 	  all the subclasses' ISRs
 */
void AntzRobot::isr() {
    if (motorStopMillis >= 0 && millis() >= motorStopMillis)
        stopMoving();
}

void AntzRobot::sendSignal(int num)
{
    /* 
    *  message can be visualized as follows: ( - => 1 bit )
    *    | ------ | - | - | -------- | -------- | -------- |
    *    NOT USED  1b        8b         8b         8b
    *             role    identifier  curFood    curNest
    */
    uint32_t signalData = num;
    //signalData |= num;
   

    sender.send(signalData, 500);
    
}

//int AntzRobot::receiveSignal(int rec) //helper function for receive not used by ECS101
//{
//    //int counter = 0;
//  bool received = false;
//  uint32_t number;
//  int num;
//    
//        if (recver.recvFrom(rec, &number))
//        {
//            received = true;
//            num = number;
//        }else{
//          num = -1 ;
//        }
//    
//    
//        return num;
//
//  
//}



int AntzRobot::receiveSignal(int rec) //helper function for receive not used by ECS101
{
    bool received = false;
    uint32_t number;
    int num;
    if (recver.recvFrom(rec, &number))
    {
        received = true;
        Serial.print("rec: ");
        Serial.print(number);
        Serial.print(" ");
        num = number;
    }else{
        num = -1 ;
    }
    
    return num;
    
}

//int AntzRobot::receive(int n)
//{
//    
//}







