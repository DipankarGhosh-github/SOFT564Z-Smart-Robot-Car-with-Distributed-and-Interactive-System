#include <Wire.h>
#include <Servo.h>
Servo servo;

              //L298N pins
int R1 = 2; //right motor forward
int R2 = 4; //right motor backward
int L1 = 5; //leftt motor forward
int L2 = 7; //leftt motor backward
int en1= 3; //enable A pin
int en2= 6; //enable B pin

int Trig= A0;  //trig pin of ultrasonic sensor
int Echo= A1;  //echo pin of ultrasonic sensor

int servo1 = 10; //pin connecting servo

int redLed = 13;  //red led pin
int greenLed = 12;//green led pin
int yellowLed = 11;//yellow led pin

int sound_d =9;   //Sound sensor digital pin
int sound_a =A3;  //Sound sensor analog pin
String msgs;

void setup() {
  
  Serial.begin(9600);           // starts serial for output
  servo.attach(servo1);
  Wire.begin(4);                 // join i2c bus with address #4          
  Wire.onReceive(receiveEvent);   // register event
  pinMode(R1, OUTPUT);    //sets L298N pins as output
  pinMode(R2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  
  pinMode(Echo, INPUT); //sets echo pin as input
  pinMode(Trig, OUTPUT);//sets trig pin as output

  pinMode (redLed, OUTPUT);   //sets led pins as output
  pinMode (greenLed, OUTPUT);
  pinMode (yellowLed, OUTPUT);
  pinMode(sound_a, INPUT);    //sets sound sensor pin as input
}

void moveForward() {
  // moving in forward direction 
  digitalWrite(en1, HIGH);  
  digitalWrite(en2, HIGH); 
  digitalWrite(R1, HIGH);             //moves right motor forward
  digitalWrite(R2, LOW);
  digitalWrite(L1, HIGH);             //moves left motor forward
  digitalWrite(L2, LOW);  
  digitalWrite (greenLed, HIGH);      //turns green led on
  digitalWrite (redLed, LOW);         //turns red led off
  Serial.println("Moving forward");   //prints on serial monitor
}
  
 void moveBackward() {
  // moving in backward direction
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);              //moves right motor backward
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);               //moves left motor backward
  Serial.println("Moving backward");  //prints on serial monitor
}

void turnLeft() {
  // moving left
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH); 
  digitalWrite(R1, HIGH);             //moves right motor forward
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);              //moves left motor backward
  Serial.println("Turned left");       //prints on serial monitor
}

void turnRight() {
  //moving right
  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH); 
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);              //moves right motor backward
  digitalWrite(L1, HIGH);              //moves left motor forwardward
  digitalWrite(L2, LOW);
  Serial.println("Turned right");  //prints on serial monitor
}

void stop() {
  // stops robot
  digitalWrite(en1, LOW);
  digitalWrite(en2, LOW);
  digitalWrite (redLed, HIGH);      //turns red led on
  digitalWrite (greenLed, LOW);    //turns green led off
  Serial.println("STOP!");         //prints on serial monitor
    
}

int getDistance() {
  // calculates distance between obstacle and ultrasonic sensor
  digitalWrite(Trig, LOW);    //sets trig pin low
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH); //sets trig pin high
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);  //sets trig pin low
  float duration = pulseIn(Echo, HIGH); //gets duration
  int distance=(duration/2)*0.0341;     //calculates distance
  return (int)distance;                 //returns integer value
}


void avoidObstacle() {
    // avoids obstacle in the path of movement
    servo.write(90);      //positions servo at 90 degree
    delay(300);
    int middleDistance = getDistance(); //measures middle distance
    
    if(middleDistance <= 20) {  //compares middle distance
      stop();                   //stops the motors
      delay(300);     
      servo.write(0);      //positions servo at 0 degree
      delay(500);
      int rightDistance = getDistance(); //measures right distance
      delay(300);
      
      servo.write(90);      //positions servo at 90 degree
      delay(1000);
      servo.write(180);      //positions servo at 90 degree
      delay(500);
      int leftDistance = getDistance(); //measures left distance
      delay(300);
      
      servo.write(90);      //positions servo at 90 degree              
      delay(500);
      if(rightDistance > leftDistance) {  //compares right and left distance
        turnRight();                      //turns right
        delay(65);
      }
      else if(rightDistance < leftDistance) { //compares right and left distance
        turnLeft();                      //turns left
        delay(65);
      }
      else if((rightDistance <= 20) || (leftDistance <= 20)) {  //compares right and left distance
        moveBackward();                 //moves backward 
        delay(200);
      }
      else {
        moveForward();      //moves forward
      }
    }  
    else {
        moveForward();      //moves forward
    }                     
}

void sound() {
    //sound sensor 
    int sound = analogRead(sound_a); //reads analogue value of sound
    if (sound >= 410)                //compares with threshold value
    { digitalWrite(yellowLed, HIGH);  //turns led on
      delay(1000);
     }
    else {
      digitalWrite(yellowLed, LOW);   //turns led off
    }
}

void receiveEvent(int howMany){
  //receive event for I2C communication
  while (Wire.available()>1)  //data received from ESP
  {
    char c = Wire.read(); //reads incoming char value
    Serial.print(c);      //prints char on serial monitor
  } 
    int x = Wire.read();  //reads incoming integer value
    Serial.println(x);    //prints integer on serial monitor
    stop();               //stops the motors
  }

void loop(){
  // main loop
  
 if (Serial.available() > 0) {

    // read incoming serial data:
    msgs = Serial.readString(); //reads inputs
    Serial.print("You typed: "); //prints on serial monitor
    Serial.print(msgs);       //prints on serial monitor

  if (msgs.substring(0,7) == "forward"){
      moveForward();      //moves forward
      delay(500);
    }

  if (msgs.substring(0,8) == "backward"){
      moveBackward();      //moves backward
      delay(500);
    }

  if (msgs.substring(0,4) == "left"){
      turnLeft();         //turns left
      delay(250);
    }
  if (msgs.substring(0,5) == "right"){
      turnRight();         //turns left
      delay(250);
    }
  if (msgs.substring(0,4) == "stop"){
      stop();             //stops the motors
      delay(2000);
    }
    
  else{}
   }
  
    else {
       avoidObstacle();     //obstacle avoiding mode
       
        }
    delay(500);
    sound();  //calls sound sensor loop
    
}
