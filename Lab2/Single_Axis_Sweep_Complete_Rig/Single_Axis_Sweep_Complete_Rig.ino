#include <Servo.h> 

const int HORZ_SWEEP_START = 80;
const int HORZ_SWEEP_RANGE = 60;
const int SETTLE_TIME = 200;

Servo horz;  
Servo vert;
 
void setup() 
{ 
  horz.attach(10);
  vert.attach(9);
  Serial.begin(9600);
  runScan();
} 

void runScan()
{
  // runScan collects the angle and sensor values from 80 to 140 degrees
  vert.write(60); 
  for(int j = HORZ_SWEEP_START; j < HORZ_SWEEP_START + HORZ_SWEEP_RANGE; j++){
    horz.write(j);
    delay(SETTLE_TIME);
    int sensorValue = analogRead(0); 
    Serial.print(j);
    Serial.print(",");
    Serial.print(sensorValue);
    Serial.print(",");
    Serial.print("\n");
  }  
}

void loop()
{ 
  /**
   leaving this here because it won't compile otherwise 
   */
 }
