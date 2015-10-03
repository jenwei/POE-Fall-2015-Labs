#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

const double P = .80;
const double I = 0;
const double D = 0;
const byte BASELINE_SPEED = 50;

int sensorPin0 = A0;    // select the input pin for IR sensor 0
int sensorValue0 = 0;  // variable to store the value coming from the sensor 0

int sensorPin1 = A1;    // select the input pin for IR sensor 1
int sensorValue1 = 0;  // variable to store the value coming from sensor 1

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(3);
Adafruit_DCMotor *motor2 = AFMS.getMotor(4);

void setup() {
  AFMS.begin();
  Serial.begin(9600);
  motor1->setSpeed(BASELINE_SPEED); //between 0 and 255
  motor2->setSpeed(BASELINE_SPEED);
}

void loop() {
  // read the value from the sensor:
  sensorValue0 = analogRead(sensorPin0);
  sensorValue1 = analogRead(sensorPin1);
  // calculate the error, difference in left and right sensor readings
  int error = sensorValue0 - sensorValue1;
  Serial.print("Error :");
  Serial.println(error);
  // get control input value;
  double speedDiff = calculatePID(error);
  Serial.print("SpeedDiff :");
  Serial.println(speedDiff);
  int motor1Speed = (int)(BASELINE_SPEED + speedDiff/2);
  int motor2Speed = (int)(BASELINE_SPEED - speedDiff/2);
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
