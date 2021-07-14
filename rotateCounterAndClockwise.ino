// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
/// \author  Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2009 Mike McCauley
// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>
int Dir = 4;
int Step = 5;
//AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper = AccelStepper(1, 4, 5);
int startMillis = 0;
bool dir_bool = false;
long newposition = 9320;


void setup(){  
   stepper.setMaxSpeed(15000);
   stepper.setAcceleration(1000);
   // 16 step resolution -> max speed 11000 (with more torque)
   // 1 step resolution -> max speed 500 (with less torque)
   //H H H Sixteenth Step 4W1-2 Phase
   //L L L Full Step 2 Phase
   }

void loop(){  
   int currentMillis = millis();
   if ((currentMillis - startMillis >= 2000)){
        if(dir_bool){
          //stepper.moveTo(-10000);
          stepper.runToNewPosition(-newposition);//blocks
          stepper.runToNewPosition(0);
          dir_bool = false;
        }else{
          //stepper.moveTo(10000);
          stepper.runToNewPosition(newposition);
          stepper.runToNewPosition(0);
          dir_bool = true;
        }
        
        startMillis = currentMillis;
   }
   
   
}
