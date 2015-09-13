/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 

const int SWEEP_INTERVAL = 3000; //sweep interval of 2 seconds
const int ANGLE_RANGE = 90; // 90 degree angle range

Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position 

void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
} 
 
void loop() 
{ 
  int currentTime = millis();
  int angle = setAngle(currentTime);
  int sensorValue = analogRead(0); // read pin 0
  
  Serial.print(sensorValue);
  Serial.print(", ");
  Serial.println(angle);

} 

int setAngle(int currentTime){
  int timeMod = currentTime % (2*SWEEP_INTERVAL);
  int servoAngle;
  if (timeMod > SWEEP_INTERVAL){
    //the servo should sweep from ANGLE_RANGE to 0 degrees
    servoAngle = 90 - map(timeMod - SWEEP_INTERVAL, 0 , SWEEP_INTERVAL, 0, ANGLE_RANGE);
  } else {
    //the servo should sweep from 0 degrees to ANGLE_RANGE
    servoAngle = map(timeMod, 0 , SWEEP_INTERVAL, 0, ANGLE_RANGE);
  }
  myservo.write(servoAngle);
  return servoAngle;
}

