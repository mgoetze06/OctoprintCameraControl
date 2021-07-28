/*Example sketch to control a stepper motor with A4988 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
#define dirPin 4
#define enablePin 5
#define stepPin 6
//#define stepsPerRevolution 200
int switchState = LOW;
int start1Millis = 0;
int state= 0;
bool rising = true;
bool motorDirection = true;

void setup() {
  // configure the serial connection:
  Serial.begin(9600);
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  digitalWrite(dirPin,LOW); //legt initiale Richtung fest
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin,LOW); //legt initiale Richtung fest
  pinMode(6, OUTPUT);
}

void toggleDir(){
  digitalWrite(dirPin,LOW);
  digitalWrite(dirPin,HIGH);
  digitalWrite(dirPin,LOW);
  digitalWrite(dirPin,HIGH);
  digitalWrite(stepPin,LOW);
  digitalWrite(stepPin,HIGH);
  digitalWrite(stepPin,LOW);
  digitalWrite(stepPin,HIGH);
  motorDirection = !motorDirection;
}


void loop() {
  int currentMillis = millis();
  if ((currentMillis - start1Millis >= 30)){
    
    if(rising){
      state = state + 2;
      if(state > 255){
        rising = false;
      }
    }else{
      state = state - 2;
      if(state < 0){
        rising = true;
        toggleDir();
      }
    }


    //Serial.println(state);
    start1Millis = currentMillis;
  }
  analogWrite(enablePin, 255 - state);
}
