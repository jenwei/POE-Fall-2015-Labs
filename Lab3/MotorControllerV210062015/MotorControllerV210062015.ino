#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

const double P = .15;
const double I = 0;
const double D = 0;
const byte m1_BASELINE_SPEED = 30; // approx 30 is the min baseline for movement 
                                  // where we keep the right wheel (m1) constant
int sensorPin0 = A0;    // select the input pin for IR sensor 0
int sensorValue0 = 0;  // variable to store the value coming from the sensor 0

int sensorPin1 = A1;    // select the input pin for IR sensor 1
int sensorValue1 = 0;  // variable to store the value coming from sensor 1

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

void setup() {
  AFMS.begin();
  Serial.begin(9600);
  motor1->setSpeed(m1_BASELINE_SPEED); //between 0 and 255
  motor2->setSpeed(m1_BASELINE_SPEED);
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
  //int motor1Speed = (int)(BASELINE_SPEED + speedDiff/2);
  int motor2Speed = (int)(m1_BASELINE_SPEED - speedDiff);
  //Serial.println(motor1Speed);
  Serial.println(motor2Speed);
  //motor1->setSpeed(motor1Speed);
  motor2->setSpeed(motor2Speed); 
  motor1->run(FORWARD);
  motor2->run(FORWARD);
  
}

double calculatePID(double error){
  return P*error;
}
