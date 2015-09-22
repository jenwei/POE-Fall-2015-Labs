#include <Servo.h> 

const int HORZ_SWEEP_START = 80;
const int HORZ_SWEEP_RANGE = 60;
const int VERT_SWEEP_START = 40;
const int VERT_SWEEP_RANGE = 60;
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
  for(int i = VERT_SWEEP_START; i < VERT_SWEEP_START + VERT_SWEEP_RANGE; i++){
    for(int j = HORZ_SWEEP_START; j < HORZ_SWEEP_START + HORZ_SWEEP_RANGE; j++){
      vert.write(i);
      horz.write(j);
      delay(SETTLE_TIME);
      int sensorValue = analogRead(0); 
      Serial.print(i);
      Serial.print(",");
      Serial.print(j);
      Serial.print(",");
      Serial.print(sensorValue);
      Serial.print(",");
      Serial.print("\n");
    }
  }  
}

void loop()
{ 
  /**
   leaving this here because it won't compile otherwise 
   */}
