/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */
const int GREEN = 9;
const int YELLOW = 10;
const int RED = 11;
const int BUTTON = 8;

const int OFF = 0;
const int FLASHING = 1;
const int BOUNCING = 2;
const int ON = 3;

const int LOOPTIME = 10;

int state; // state stays off until button press
int loopCount; 
int buttonPressedCount; //button state tracking to account for debouncing
// the setup function runs once when you press reset or power the board
void setup() {
  state = 0;
  pinMode(BUTTON, INPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  loopCount = 0;
  buttonPressedCount = 0;
}

// the loop function runs over and over again forever
void loop() {
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

void switchState() { //goes off, flashing, on, bouncing, off
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
  digitalWrite(GREEN, val);
  digitalWrite(YELLOW, val);
  digitalWrite(RED, val);
}

void off() {
  setAll(LOW);
  delay(LOOPTIME);
}

void on() {
  setAll(HIGH);
  delay(LOOPTIME);
}

void bounce(int count) {
  if (count % 100 == 30){
    setAll(LOW);
    digitalWrite(GREEN, HIGH);
  }
  else if (count % 100 == 60){
    setAll(LOW);
    digitalWrite(YELLOW, HIGH);
  }
  else if (count % 100 == 90){
    setAll(LOW);
    digitalWrite(RED, HIGH);
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
  int greenState = digitalRead(GREEN);
  int yellowState = digitalRead(YELLOW);
  int redState = digitalRead(RED);
  digitalWrite(GREEN, greenState ? LOW : HIGH);
  digitalWrite(YELLOW, yellowState ? LOW : HIGH);
  digitalWrite(RED, redState ? LOW : HIGH);
}

