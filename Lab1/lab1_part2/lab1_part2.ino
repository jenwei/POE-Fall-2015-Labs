// Pin outs
const int GREEN = 3;
const int YELLOW = 5;
const int RED = 6;

// Pin ins
const int BUTTON = 8;
const int POT = 0;

// Modes
const int OFF = 0;
const int FLASHING = 1;
const int BOUNCING = 2;
const int ON = 3;

const int LOOPTIME = 10;
const int MAXBRIGHTNESS = 255;
const int MAXANALOGREADVAL = 1023;

int state; // state stays off until button press
int loopCount; 
int buttonPressedCount; // button state tracking to account for debouncing
int brightness; // where 255 is max LED brightness
boolean flashingOn; // used to track status of LEDs in flashing mode

// the setup function runs once when you press reset or power the board
void setup() {
  state = 0;
  loopCount = 0;
  buttonPressedCount = 0;
  brightness = 0;
  flashingOn = false;
  pinMode(BUTTON, INPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  detectButtonPress();
  brightness = analogRead(POT) * 1.0 / MAXANALOGREADVAL * MAXBRIGHTNESS;
  Serial.print(brightness);
  if (state == FLASHING) {
    flash(loopCount);
  } else if (state == ON) {
    on();
  } else if (state == BOUNCING) {
    bounce(loopCount);
  } else if (state == OFF) {
    off();
  }
  loopCount++;
}

void detectButtonPress(){
  int buttonPressed = digitalRead(BUTTON);
  if (buttonPressed){
    buttonPressedCount ++;
  }
  else{
    buttonPressedCount = 0;
  }
  if (buttonPressedCount == 10){
    switchState();
    buttonPressedCount = 0;
  }
}

void switchState() { // order of modes: off, flashing, on, bouncing, off
  if (state == FLASHING) {
    state = ON;
  } else if (state == ON) {
    state = BOUNCING;
  } else if (state == BOUNCING) {
    state = OFF;
  } else if (state == OFF) {
    state = FLASHING;
  }  
}

void setAll(int val) {
  analogWrite(GREEN, val);
  analogWrite(YELLOW, val);
  analogWrite(RED, val);
}

void off() {
  setAll(LOW);
  delay(LOOPTIME);
}

void on() {
  setAll(brightness);
  delay(LOOPTIME);
}

void bounce(int count) {
  if (count % 100 == 30){
    setAll(LOW);
    analogWrite(GREEN, brightness);
  }
  else if (count % 100 == 60){
    setAll(LOW);
    analogWrite(YELLOW, brightness);
  }
  else if (count % 100 == 90){
    setAll(LOW);
    analogWrite(RED, brightness);
  }
  delay(LOOPTIME);
}

void flash(int count) {
  if (count % 10 == 0){
    toggleAll();
  }
  delay(LOOPTIME);
}

void toggleAll() {
  if(flashingOn){
    analogWrite(GREEN,LOW);
    analogWrite(YELLOW,LOW);
    analogWrite(RED,LOW);
    flashingOn = false;
  } else {
    analogWrite(GREEN,brightness);
    analogWrite(YELLOW,brightness);
    analogWrite(RED,brightness);
    flashingOn = true;
  }
}

