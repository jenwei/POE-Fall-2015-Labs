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

int state; // state stays off until button press

// the setup function runs once when you press reset or power the board
void setup() {
  state = 0;
  pinMode(BUTTON, INPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  int buttonState = digitalRead(BUTTON);
  setState(buttonState);
  if (state == FLASHING) {
    flash();
  } else if (state == ON) {
    on();
  } else if (state == BOUNCING) {
    bounce();
  } else if (state == OFF) {
    off();
  }
}

void setState(int buttonState) { //goes off, flashing, on, bouncing, off
  if (buttonState == HIGH) {
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
}

void setAll(int val) {
  digitalWrite(GREEN, val);
  digitalWrite(YELLOW, val);
  digitalWrite(RED, val);
}

void off() {
  setAll(LOW);
  delay(500);
}

void on() {
  setAll(HIGH);
  delay(500);
}

void blinkOnce(int light, int delayLen) {
  digitalWrite(light, HIGH);
  delay(delayLen);
  digitalWrite(light, LOW);
  delay(delayLen);
}

void bounce() {
  setAll(LOW);
  blinkOnce(GREEN, 500);
  blinkOnce(YELLOW, 500);
  blinkOnce(RED, 500);
}

void flash() {
  setAll(HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  setAll(LOW);    // turn the LED off by making the voltage LOW
  delay(500);
}

