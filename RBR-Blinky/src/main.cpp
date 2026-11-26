#include <Arduino.h>
#include "board.h"
#define led LED_BUILTIN
// put function declarations here:
int cycle_time = 1000;
int duty_rate = 50;
bool flag_b1 = false;
bool flag_b2 = false;
bool flag_b3 = false;
bool flag_LED = false;
unsigned long now, last = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(BUTTON_1, BUTTON_MODE);
  pinMode(BUTTON_2, BUTTON_MODE);
  pinMode(BUTTON_3, BUTTON_MODE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(BUTTON_1) == BUTTON_ACTIVE) {
    if (flag_b1 == false) {
      cycle_time += 100;
      flag_b1 = true;
    }
  }
  else flag_b1 = false;

  if (digitalRead(BUTTON_2) == BUTTON_ACTIVE) {
    if (flag_b2 == false) {
      if (cycle_time >= 200) cycle_time -= 100;
      flag_b2 = true;
    }
  }
  else flag_b2 = false;

  if (digitalRead(BUTTON_3) == BUTTON_ACTIVE) {
    if (flag_b3 == false) {
      duty_rate += 25;
      duty_rate %= 100;
      flag_b3 = true;
    }
  }
  else flag_b3 = false;
  
  now = millis();
  unsigned int onTime = cycle_time / 100 * duty_rate;
  unsigned int offTime = cycle_time - onTime;
  if (flag_LED) {
    if (now - last >= onTime) {
      digitalWrite(led, LOW);
      last = now;
      flag_LED = false;
    }
  }
  else {
    if (now - last >= offTime) {
      digitalWrite(led, HIGH);
      last = now;
      flag_LED = true;
    }
  }



}

// put function definitions here:
