#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

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
}

void loop() {
  collectSensorValues();
  setMotorSpeeds();
}

void collectSensorValues(){
  sensor0Val = map(analogRead(SENSOR_PIN_0), 0, 1023, 0, 255);
  sensor1Val = map(analogRead(SENSOR_PIN_1), 0, 1023, 0, 255);
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


