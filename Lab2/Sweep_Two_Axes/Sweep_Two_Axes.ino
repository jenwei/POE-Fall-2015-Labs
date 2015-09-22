/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 

const int VERT_SWEEP_INTERVAL = 500; //sweep interval of  1 second each way
const int VERT_ANGLE_RANGE = 90; // 90 degree angle range

const long HORI_SWEEP_INTERVAL = 4000*VERT_SWEEP_INTERVAL; // sweep interval of 4 times time of vert sweep
const int HORI_ANGLE_RANGE = 90; // 90 degree angle range

long int timeLastTicked = 0;
int horiAngle = 0;

Servo vert;  
Servo hori; // create servo object to control a servo 

void setup() 
{ 
  vert.attach(9);  // attaches the servo on pin 9 to the servo object 
  hori.attach(10); 
  Serial.begin(9600);
} 
 
void loop() { 
  long currentTime = millis();
  byte vertAngle = setVertAngle(currentTime);
  byte horiAngle = setHoriAngle2(currentTime);
  int sensorValue = analogRead(0); // read pin A0 
  Serial.print(sensorValue);
  Serial.print(", ");
  Serial.print(vertAngle);
  Serial.print(", ");
  Serial.println(horiAngle % HORI_ANGLE_RANGE);  
} 

byte setHoriAngle2(long currentTime){
  if(currentTime - timeLastTicked >= 2*VERT_SWEEP_INTERVAL){
    horiAngle++;
    timeLastTicked = currentTime;
  }
  hori.write(horiAngle % HORI_ANGLE_RANGE);
  return horiAngle;
}

byte setVertAngle(long currentTime){
  long timeMod = currentTime % (2*VERT_SWEEP_INTERVAL);
  int servoAngle;
  if (timeMod > VERT_SWEEP_INTERVAL){
    //the servo should sweep from ANGLE_RANGE to 0 degrees
    servoAngle = 90 - map(timeMod - VERT_SWEEP_INTERVAL, 0 , VERT_SWEEP_INTERVAL, 0, VERT_ANGLE_RANGE); // map(value, fromLow, fromHigh, toLow, toHigh)
  } else {
    //the servo should sweep from 0 degrees to ANGLE_RANGE
    servoAngle = map(timeMod, 0 , VERT_SWEEP_INTERVAL, 0, VERT_ANGLE_RANGE);
  }
  servoAngle = 70;
  vert.write(servoAngle);
  return servoAngle;
}

