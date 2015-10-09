#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// VARIABLES FOR SERIAL COM
String validInput = "PIDS"; // string of Inputs (Proportion, Integral, Derivative, Speed)that can be toggled via Serial
char paramToSet = ' ';
boolean readingFirstChar = true;

// control parameters that are tunable from serial in
double P = 0.30;
double I = 0;
double D = 0;
byte BASELINE_SPEED = 30;

// tested with 0.3 proportion and 25 speed and worked

// last time, error accumulator, and last error for I & D
unsigned long lastTime;
double errorSum;
double lastError;

//pin mappings
const byte SENSOR_PIN_0 = A0;
const byte SENSOR_PIN_1 = A1;

// motorshield initialization
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor0 = AFMS.getMotor(1);
Adafruit_DCMotor *motor1 = AFMS.getMotor(2);

// sensor readings
byte sensor0Val;
byte sensor1Val;

void setup() {
  AFMS.begin();
  Serial.begin(9600);

  // motor settings (initial state = go forward at baseline speed)
  motor0 -> setSpeed(BASELINE_SPEED);
  motor1 -> setSpeed(BASELINE_SPEED);
  motor0 -> run(FORWARD);
  motor1 -> run(FORWARD);
  
  //Serial.print("Enter the first letter of the parameter you want to tune: ");
}

void loop() {
  //serialEvent();
  collectSensorValues();
  setMotorSpeeds();
}

void collectSensorValues(){
  sensor0Val = map(analogRead(SENSOR_PIN_0), 0, 1023, 0, 255);
  Serial.print(sensor0Val);
  Serial.print(", ");
  sensor1Val = map(analogRead(SENSOR_PIN_1), 0, 1023, 0, 255);
  Serial.print(sensor1Val);
  Serial.print(", ");
}

void setMotorSpeeds(){
  int speedDiff = sensor0Val - sensor1Val;

  // pass in speedDiff between the two motors and apply PID
  int controlCorrection = getPIDCorrection(speedDiff);
  
  int motor0Speed = BASELINE_SPEED + (controlCorrection/2);

  // if else statements to prevent too drastic of changes in speed
  if(motor0Speed < 0){
    motor0Speed = 0;
  }
  if(motor0Speed > 50){
    motor0Speed = 50;
  }
  int motor1Speed = BASELINE_SPEED - (controlCorrection/2);
  if(motor1Speed < 0){
    motor1Speed = 0;
  }
  if(motor1Speed > 50){
    motor1Speed = 50;
  }
  
  Serial.print(motor0Speed);
  Serial.print(", ");
  Serial.println(motor1Speed);
  
  motor0 -> setSpeed(motor0Speed);
  motor1 -> setSpeed(motor1Speed); // what is motor1Speed equail to??
}

int getPIDCorrection(int speedDiff){
  unsigned long now = millis();
  double timeChange = (double)(now - lastTime);

  // calculating the integral
  errorSum += (speedDiff * timeChange);

  // calculating the derivative
  int errorDiff = (speedDiff - lastError) / timeChange;

  // return the post-PID corrected speed
  return P*speedDiff + I*errorSum + D*errorDiff;
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
        BASELINE_SPEED = val;  
      }
      break;
  }
  Serial.println(P);
  Serial.println(I);
  Serial.println(D);
  Serial.println(BASELINE_SPEED);
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

