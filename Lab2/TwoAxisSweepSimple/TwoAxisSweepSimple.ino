#include <Servo.h> 

const int HORZ_SWEEP_START = 90;
const int HORZ_SWEEP_RANGE = 30;
const int VERT_SWEEP_START = 10;
const int VERT_SWEEP_RANGE = 45;
const int SETTLE_TIME = 500;

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
  for(int i = VERT_SWEEP_START; i < VERT_SWEEP_START + VERT_SWEEP_RANGE; i++){
    for(int j = HORZ_SWEEP_START; j < HORZ_SWEEP_START + HORZ_SWEEP_RANGE; j++){
      vert.write(i);
      horz.write(j);
      delay(SETTLE_TIME);
      int sensorValue = analogRead(0); 
      Serial.print(sensorValue);
      Serial.print(",");
    }
    Serial.print("\n");
  }  
}

void loop()
{ 
}
