#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

//control parameters that are tunable from serial in
double P = .1;
double I = 0;
double D = 0;
byte BASELINE_SPEED = 20;

//last time, error accumulator and last error for I & D
double errorSum;
unsigned long lastTime;
double lastError;

//pin mappings
const byte SENSOR_PIN_0 = A0;
const byte SENSOR_PIN_1 = A1;

//motorshield initialization
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor0 = AFMS.getMotor(1);
Adafruit_DCMotor *motor1 = AFMS.getMotor(2);

//sensor readings and motor settings
byte sensor0Val;
byte sensor1Val;

void setup() {
  AFMS.begin();
  Serial.begin(9600);
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
  int controlCorrection = getPIDCorrection(speedDiff);
  int motor0Speed = BASELINE_SPEED + (controlCorrection/2);
  int motor1Speed = BASELINE_SPEED - (controlCorrection/2);
  motor0 -> setSpeed(motor0Speed);
  motor1 -> setSpeed(motor1Speed);
}

int getPIDCorrection(int speedDiff){
  unsigned long now = millis();
  double timeChange = (double)(now - lastTime);
  errorSum += (speedDiff * timeChange);
  int errorDiff = (speedDiff - lastError) / timeChange;
  return P*speedDiff + I*errorSum + D*errorDiff;
}


