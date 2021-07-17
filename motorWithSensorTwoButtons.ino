#include <AccelStepper.h>
int Dir = 4;
int Step = 5;
//AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper = AccelStepper(1, 4, 5);


int interruptPin1 = 2;
int interruptPin2 = 3;
int homePin = 11;
long pos = 0;
int button1 = 10;
int button2 = 12;
int startMillis = 0;

//4100 pulses for 145mm
//28,27 pulse/mm


void setup() {
  // put your setup code here, to run once:
  pinMode(interruptPin1, INPUT);
  pinMode(interruptPin2, INPUT);
  pinMode(homePin, INPUT_PULLUP);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin1), countPin1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), countPin2, CHANGE);
  Serial.begin(9600);
  stepper.setMaxSpeed(15000);
  stepper.setAcceleration(1000);
   // 16 step resolution -> max speed 11000 (with more torque)
   // 1 step resolution -> max speed 500 (with less torque)
  homeMe();
}

void countPin1(){
  bool pin1 = digitalRead(interruptPin1);
  bool pin2 = digitalRead(interruptPin2);
  if(pin1){     //high
    if(pin2){   //high
      //direction A
      pos = pos - 1;
         
    }else{      //low
      //direction B
      pos = pos + 1;
    }
  }else{        //low
    if(pin2){   //high
      //direction B
      pos = pos + 1;
      
    }else{      //low
      //direction A
      pos = pos - 1;
      
    }
  }
}

void homeMe(){
  bool pin = digitalRead(homePin);
  stepper.setSpeed(-12000);
  while(pin != 0){
    pin = digitalRead(homePin);
    //Serial.println("searching home");
    stepper.runSpeed();
  }
  stepper.disableOutputs();
  Serial.println("homed");
  pos = 0;
  return;
}

void countPin2(){
  bool pin1 = digitalRead(interruptPin1);
  bool pin2 = digitalRead(interruptPin2);
  if(pin2){     //high
    if(pin1){   //high
      //direction B
      pos = pos + 1;
         
    }else{      //low
      //direction A
      pos = pos - 1;
    }
  }else{        //low
    if(pin1){   //high
      //direction A
      pos = pos - 1;
      
    }else{      //low
      //direction B
      pos = pos + 1;
      
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int currentMillis = millis();
  if ((currentMillis - startMillis >= 100)){
    Serial.print("pos: ");
    Serial.println(pos);
    startMillis = currentMillis;
  }

  bool button1pin = digitalRead(button1);
  bool button2pin = digitalRead(button2);
  //Serial.print("button 1: ");
  //Serial.println(pin);
  if(button1pin == 0){
    stepper.enableOutputs();
    stepper.setSpeed(14000);
    stepper.runSpeed();  
  }else{
    if((button2pin == 0)and(pos > 5)){
      stepper.enableOutputs();
      stepper.setSpeed(-14000);
      stepper.runSpeed();  
    }else{
      stepper.disableOutputs();
    }
  }
  //stepper.run();
}
