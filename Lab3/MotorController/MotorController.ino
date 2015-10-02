#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

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
  motor1->setSpeed(100); // from 0 to 255\
  motor2->setSpeed(10); // from 0 to 255

}

void loop() {
  // read the value from the sensor:
  sensorValue0 = analogRead(sensorPin0);
  sensorValue1 = analogRead(sensorPin1);
  // calculate the speed that motors should be driven at
  motor1->run(FORWARD); // FORWARD, BACKWARD, RELEASE
  motor2->run(FORWARD); // FORWARD, BACKWARD, RELEASE

  // set motor speeds
  
}
