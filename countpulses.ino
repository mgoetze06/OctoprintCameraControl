int interruptPin1 = 2;
int interruptPin2 = 3;
long pos = 0;

//4100 pulses for 145mm
//28,27 pulse/mm


void setup() {
  // put your setup code here, to run once:
  pinMode(interruptPin1, INPUT);
  pinMode(interruptPin2, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin1), countPin1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), countPin2, CHANGE);
  Serial.begin(9600);
}

void countPin1(){
  bool pin1 = digitalRead(interruptPin1);
  bool pin2 = digitalRead(interruptPin2);
  if(pin1){     //high
    if(pin2){   //high
      //direction A
      pos = pos + 1;
         
    }else{      //low
      //direction B
      pos = pos - 1;
    }
  }else{        //low
    if(pin2){   //high
      //direction B
      pos = pos - 1;
      
    }else{      //low
      //direction A
      pos = pos + 1;
      
    }
  }
}

void countPin2(){
  bool pin1 = digitalRead(interruptPin1);
  bool pin2 = digitalRead(interruptPin2);
  if(pin2){     //high
    if(pin1){   //high
      //direction B
      pos = pos - 1;
         
    }else{      //low
      //direction A
      pos = pos + 1;
    }
  }else{        //low
    if(pin1){   //high
      //direction A
      pos = pos + 1;
      
    }else{      //low
      //direction B
      pos = pos - 1;
      
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  Serial.println(pos);
}
