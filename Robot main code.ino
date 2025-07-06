#include <Servo.h>
Servo servo;

//motor one
int enA = 3;
int in1 = 2;
int in2 = 4;
//motor two
int enB = 5;
int in3 = 6;
int in4 = 7;

//UltraSonic pins
int trig = 10, echo = 11;

//High Power LED pins
const int hpLed = 8, ldrPin = A0, roomLight = 1;

//IR pins
const int irLPin = 12, irRPin = 13;

bool pressed = false;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }
  
  servo.attach(9);
  servo.write(90);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  analogWrite(enA, 400);
  analogWrite(enB, 400);

  pinMode(hpLed,OUTPUT);
  pinMode(ldrPin,INPUT);
  digitalWrite(hpLed, LOW);

  pinMode(irRPin, INPUT);
  pinMode(irLPin, INPUT);
  
  stopMove();
 // delay(5000);
}

void loop() {
  if(Serial.read() == 'S'){
  stopMove();
    while(true){
      //checkLight()
      if(Serial.read() == 'F'){
        pressed = true;
        forwardMove();
      }
      if(Serial.read() == 'B'){
        pressed = true;
        backwardMove();
      }
      if(Serial.read() == 'L'){
        pressed = true;
        turnLeft();
      }
      if(Serial.read() == 'R'){
        pressed = true;
        turnRight();
      }
      if(Serial.read() == 'S' && pressed == true){
        pressed = false;
        break;
      }
    }
  }
  else{
    checkLight();
    int leftIR = digitalRead(irLPin);
    int rightIR = digitalRead(irRPin);
    
    if(checkDist() <= 15 || (rightIR==LOW&&leftIR==LOW)){
      
      stopMove();
      checkLight();
      delay(500);
      
      backwardMove();
      checkLight();
      delay(400);
      
      stopMove();
      checkLight();
      delay(500);
      
      servo.write(35);
      delay(100);
      float distanceR = checkDist();
      checkLight();
      delay(2000);
      
      servo.write(145);
      delay(100);
      float distanceL = checkDist();
      checkLight();
      delay(2000);
      
      if(distanceR >= distanceL){
        turnRight();
        checkLight();
        delay(400);
      }
      else{
        turnLeft();
        checkLight();
        delay(400);
      }
      
      servo.write(90);
      stopMove();
      checkLight();
      delay(1000);
    }
    else if(rightIR == LOW){
      checkLight();
      stopMove();
      delay(500);
      backwardMove();
      delay(500);
      turnLeft();
      delay(800);
    }
    else if(leftIR == LOW){
      checkLight();
 
      stopMove();
      delay(700);
      backwardMove();
      delay(500);
      turnRight();
      delay(800);
    }
    else
    {
      checkLight();
      forwardMove();
      delay(200);
    }
  }
}

void stopMove(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void forwardMove(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void backwardMove(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void turnLeft(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void turnRight(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

int checkDist(){
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  float duration = pulseIn(echo, HIGH);
  float distance = duration/29/2;
  return distance;
}

void checkLight(){
  int ldrstatus = analogRead(ldrPin);
  if (ldrstatus <= roomLight){
    digitalWrite(hpLed,HIGH);
  }
  else{
     digitalWrite(hpLed,LOW); 
  }
}
