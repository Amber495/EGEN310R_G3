//This program is used to control a robot using a app that communicates with Arduino through a bluetooth module.
//Error Code Chart: Code 01; Turnradius is higher than Speed; Code 02; Speed is higher than 255;

#define in1 5 //L298n Motor Driver pins.
#define in2 6
#define in3 10
#define in4 11

#define in5 4     //deployment arm //2nd L298n Motor Driver pins.
#define in6 7     //deployment arm
#define in7 8     //deployment arm
#define in8 9     //deployment arm

#define LED 13

int command; //Int to store app command state.
int Speed = 204; // 0 - 255.
int Speedsec = 128;
int buttonState = 0;
int lastButtonState = 0;
int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will malfunction if this is higher than int Speed.
int brakeTime = 45;
int brkonoff = 1; //1 for the electronic braking system, 0 for normal.

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(LED, OUTPUT); //Set the LED pin.

  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);

  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    Stop(); //Initialize with motors stopped.
    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'G':
        forwardleft();
        break;
      case 'I':
        forwardright();
        break;
      case 'H':
        backleft();
        break;
      case 'J':
        backright();
        break;
      case '0':
        Speed = 100;
        break;
      case '1':
        Speed = 140;
        break;
      case '2':
        Speed = 153;
        break;
      case '3':
        Speed = 165;
        break;
      case '4':
        Speed = 178;
        break;
      case '5':
        Speed = 191;
        break;
      case '6':
        Speed = 204;
        break;
      case '7':
        Speed = 216;
        break;
      case '8':
        Speed = 229;
        break;
      case '9':
        Speed = 242;
        break;
      case 'q':
        Speed = 255;
        break;
    }
    
    Speedsec = Turnradius;
    if (brkonoff == 1) {
      brakeOn();
    } else {
      brakeOff();
    }
  }
}

void forward() {
  analogWrite(in4, Speed);
  analogWrite(in1, Speed);
}

void back() {
  analogWrite(in3, Speed);
  analogWrite(in2, Speed);
}

void left() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
}

void right() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
}
void forwardleft() {
  analogWrite(in1, Speedsec);
  analogWrite(in4, Speed);
}
void forwardright() {
  analogWrite(in1, Speed);
  analogWrite(in4, Speedsec);
}
void backright() {
  analogWrite(in2, Speed);
  analogWrite(in3, Speedsec);
}
void backleft() {
  analogWrite(in2, Speedsec);
  analogWrite(in3, Speed);
}




void up() {                  ////////////////
  analogWrite(in7, Speed);   ////////////////
  
}

void down() {                 ////////////
  analogWrite(in8, Speed);    ////////////
  
}





void Stop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
}

void brakeOn() {
  //Electronic braking system
  // read the pushbutton input pin:
  buttonState = command;
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (lastButtonState == 'F') {
      if (buttonState == 'S') {
        back();
        delay(brakeTime);
        Stop();
      }
    }
    if (lastButtonState == 'B') {
      if (buttonState == 'S') {
        forward();
        delay(brakeTime);
        Stop();
      }
    }
    if (lastButtonState == 'L') {
      if (buttonState == 'S') {
        right();
        delay(brakeTime);
        Stop();
      }
    }
    if (lastButtonState == 'R') {
      if (buttonState == 'S') {
        left();
        delay(brakeTime);
        Stop();
      }
    }
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
}
void brakeOff() {

}
