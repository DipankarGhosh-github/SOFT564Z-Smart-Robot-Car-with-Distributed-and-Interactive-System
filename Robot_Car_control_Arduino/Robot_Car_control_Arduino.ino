#include <Wire.h>
#include <Servo.h>
Servo servo;

int R1 = 2;
int R2 = 4;
int L1 = 5;
int L2 = 7;
int en1=3;
int en2=6;
int Trig=A0;
int Echo=A1;
int servo1 =10;


void setup() {
  

  Serial.begin(9600);
  servo.attach(servo1);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);


  
}

void moveForward() {
  // moving in forward direction 
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH); 
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  Serial.println("Moving forward");
}
  
 void moveBackward() {
  // moving in backward direction
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH); 
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  Serial.println("Moving backward");
}

void turnLeft() {
  // moving left
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH); 
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  Serial.println("Turned left");
}

void turnRight() {
  //moving right
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH); 
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  Serial.println("Turned right");
}

void stop() {
  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
  Serial.println("STOP!");
    
}

int getDistance() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  float duration = pulseIn(Echo, HIGH);
  int distance=(duration/2)*0.0341;
  return (int)distance;
}

void avoidObstacle() 
{ 
    servo.write(90);
    delay(300);
    int middleDistance = getDistance();
    
    if(middleDistance <= 20) {
      stop();
      delay(300);     
      servo.write(0);
      delay(1000);
      int rightDistance = getDistance();
      delay(300);
      
      servo.write(90);
      delay(1000);
      servo.write(180);
      delay(1000);
      int leftDistance = getDistance();
      delay(300);
      
      servo.write(90);              
      delay(1000);
      if(rightDistance > leftDistance) {
        turnRight();
        delay(150);
      }
      else if(rightDistance < leftDistance) {
        turnLeft();
        delay(150);
      }
      else if((rightDistance <= 20) || (leftDistance <= 20)) {
        moveBackward();
        delay(200);
      }
      else {
        moveForward();
      }
    }  
    else {
        moveForward();
    }                     
}

void receiveEvent(int howMany)
{
  while (Wire.available()>1)
  {
    stop();
    char c = Wire.read();
    Serial.print(c);
  }
    int x = Wire.read();
    Serial.println(x);
  }

void loop()
{
  String msgs;
  if (Serial.available() > 0) {

    // read incoming serial data:
    msgs = Serial.readString();
    Serial.print("You typed: ");
    Serial.print(msgs);

    if (msgs.substring(0,7) == "forward"){
      moveForward();
      delay(500);
    }

    if (msgs.substring(0,8) == "backward"){
      moveBackward();
      delay(500);
    }

    if (msgs.substring(0,4) == "left"){
      turnLeft();
      delay(150);
    }
    if (msgs.substring(0,5) == "right"){
      turnRight();
      delay(150);
    }
    if (msgs.substring(0,4) == "stop"){
      stop();
      delay(2000);
    }
    
    else{}
   }
  
  else {
       avoidObstacle();    
   
        }
    delay(500);
}
