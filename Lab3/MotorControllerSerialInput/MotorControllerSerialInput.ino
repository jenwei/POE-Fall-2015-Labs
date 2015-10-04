#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

double P = .80; // proportion between 0 and 1
double I = 0; // integral between 0 and 1
double D = 0; // derivative between 0 and 1
byte S = 50; // speed between 0 and 255

int sensorPin0 = A0;    // select the input pin for IR sensor 0
int sensorValue0 = 0;  // variable to store the value coming from the sensor 0

int sensorPin1 = A1;    // select the input pin for IR sensor 1
int sensorValue1 = 0;  // variable to store the value coming from sensor 1

// VARIABLES FOR SERIAL COM
String validInput = "PIDS"; // string of Inputs (Proportion, Integral, Derivative, Speed)that can be toggled via Serial
char paramToSet = ' ';
boolean readingFirstChar = true;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(3);
Adafruit_DCMotor *motor2 = AFMS.getMotor(4);

void setup() {
  AFMS.begin();
  Serial.begin(9600);
  motor1->setSpeed(S); //between 0 and 255
  motor2->setSpeed(S);
  Serial.print("Enter the first letter of the parameter you want to tune: ");
}

void loop() {
  serialEvent(); // call the function for serial com
  
  // read the value from the sensors
  sensorValue0 = analogRead(sensorPin0);
  sensorValue1 = analogRead(sensorPin1);
  
  // calculate the error, difference in left and right sensor readings
  int error = sensorValue0 - sensorValue1;
  Serial.print("Error :");
  Serial.println(error);
  
  // get control input value
  double speedDiff = calculatePID(error);
  Serial.print("SpeedDiff :");
  Serial.println(speedDiff);
  int motor1Speed = (int)(S + speedDiff/2);
  int motor2Speed = (int)(S - speedDiff/2);
  Serial.println(motor1Speed);
  Serial.println(motor2Speed);
  motor1->setSpeed(min(motor1Speed, 255));
  motor2->setSpeed(max(motor2Speed, 1)); 
  motor1->run(BACKWARD);
  motor2->run(FORWARD);
}

double calculatePID(double error){
  return P*error;
}

void serialEvent() {
  while (Serial.available()) { // get the new byte
    if(readingFirstChar){ // if searching for valid input
      char inChar = (char)Serial.read();  
      if(validInput.indexOf(inChar) != -1){ // if input is one of our valid inputs (P, I, D, or S)
        readingFirstChar = false;
        paramToSet = inChar;
        Serial.println(inChar);
        Serial.print("Now enter a value: ");
      }
    } else {
      float val = Serial.parseFloat();
      Serial.println(val);
      setParameter(paramToSet, val);
      readingFirstChar = true;
      Serial.print("Enter the first letter of the parameter you want to tune: ");
    }
  }
}

void setParameter(char p, double val){ // set the chosen parameter with the new value inputted
  switch(p){
    case 'P':
      if(isValidRange(0,1,val)){
        P = val;  
      }
      break;
    case 'I':
      if(isValidRange(0,1,val)){
        I = val;  
      }
      break;
    case 'D':
      if(isValidRange(0,1,val)){
        D = val;  
      }
      break;
    case 'S':
      if(isValidRange(0,255,val)){
        S = doubleToByte(val);  
      }
      break;
  }
  Serial.println(P);
  Serial.println(I);
  Serial.println(D);
  Serial.println(S);
}

boolean isValidRange(double lower, double upper, double val){
  if(val < lower || val > upper){
    Serial.print("Invalid input! Enter a value between ");
    Serial.print(lower);
    Serial.print(" and ");
    Serial.println(upper);
    return false;
  }
  return true;
}

byte doubleToByte(double val){
  return (byte)(int) val;
}

