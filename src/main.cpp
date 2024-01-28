#include <AFMotor.h>
#include <Arduino.h>
typedef void (*FunctionPointer)();


const int IN_1 = A0;
const int IN_2 = A1;
const int IN_3 = A2;


int LEFT, MIDDLE, RIGHT; //Sensor 
// Black = 1, White = 0

AF_DCMotor backRight(1, MOTOR12_64KHZ); // Động cơ 1
AF_DCMotor frontRight(2, MOTOR12_64KHZ); // Động cơ 2
AF_DCMotor backLeft(3, MOTOR34_64KHZ); // Động cơ 3
AF_DCMotor frontLeft(4, MOTOR34_64KHZ); // Động cơ 4

int default_speed = 160;
void stop();

void read(){
  LEFT = digitalRead(IN_1);
  MIDDLE = digitalRead(IN_2);
  RIGHT = digitalRead(IN_3);
}

void setSpeed(int speed = default_speed){
  backRight.setSpeed(default_speed); //động cơ bị yếu
  frontRight.setSpeed(default_speed); 
  backLeft.setSpeed(default_speed);  
  frontLeft.setSpeed(default_speed);//động cơ bị yếu
}
void goStraight(){
  backRight.run(FORWARD);
  frontRight.run(FORWARD);
  backLeft.run(FORWARD);
  frontLeft.run(FORWARD);
}

FunctionPointer lastAction = goStraight;



void turnRight(){
  setSpeed();
  lastAction = turnRight;
  backRight.run(BACKWARD);
  frontRight.run(BACKWARD);
  backLeft.run(FORWARD);
  frontLeft.run(FORWARD);
}

void turnLeft(){
  setSpeed();
  lastAction = turnLeft;
  backRight.run(FORWARD);
  frontRight.run(FORWARD);
  backLeft.run(BACKWARD);
  frontLeft.run(BACKWARD);
}


void stop(){
  backRight.run(RELEASE);
  frontRight.run(RELEASE);
  backLeft.run(RELEASE);
  frontLeft.run(RELEASE);
}
// Black = 1, White = 0
void adjust(){
  if (MIDDLE){
    if (LEFT&&RIGHT){
      stop();
      return;
    }
    goStraight();
  }
  else if (!MIDDLE){
    if (LEFT){
      turnLeft();
    } else if (RIGHT){
      turnRight();
    } else {
      lastAction();
    }
  }
}

void setup(){
  Serial.begin(9600);
  setSpeed();


  pinMode(IN_1, INPUT_PULLUP);
  pinMode(IN_2, INPUT_PULLUP);
  pinMode(IN_3, INPUT_PULLUP);
}

void loop(){
  read();
  adjust();
}
