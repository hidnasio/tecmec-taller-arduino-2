#include "FTDebouncer.h"

#define LED_BLUE 2
#define LED_GREEN 3
#define LED_RED 4
#define LED_YELLOW 5
#define BTN_BLUE A0
#define BTN_GREEN A1
#define BTN_RED A2
#define BTN_YELLOW A3
#define ANIMATION_DELAY 500
#define USER_DELAY 200

FTDebouncer pinDebouncer(30);

byte mSeq[8] = {
  LED_YELLOW,
  LED_YELLOW,
  LED_BLUE,
  LED_RED,
  LED_GREEN,
  LED_RED,
  LED_YELLOW,
  LED_BLUE
};

byte uSeq[8];
int level = 1;
byte pressed = 0;
int velocity = 1000;

void setup() {
  setupLed(LED_BLUE);
  setupLed(LED_GREEN);
  setupLed(LED_RED);
  setupLed(LED_YELLOW);
  setupBtn(BTN_BLUE);
  setupBtn(BTN_GREEN);
  setupBtn(BTN_RED);
  setupBtn(BTN_YELLOW);
  pinDebouncer.init();
}

void loop() {
  showSeq();
  getSeq();
}

void setupLed(byte led) {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void setupBtn(byte btn) {
  pinDebouncer.addPin(btn, HIGH); 
}

void showSeq() {
  turnOffAllLeds();

  for (int i = 0; i < level; i++) {
    delay(velocity);
    digitalWrite(mSeq[i], HIGH);
    delay(velocity);
    digitalWrite(mSeq[i], LOW);
  }
}

void getSeq() {
  for (int i = 0, flag = 0; i < level; i++, flag = 0) {
    while(flag == 0) {
      if (pressed != 0) {
   
        uSeq[i] = pressed;
        pressed = 0;
        flag = 1;
        
        delay(USER_DELAY);
        
        if (uSeq[i] != mSeq[i]) {
          wrongSeq();
          return;  
        }
      }

      pinDebouncer.run();
    }
  }

  level++;
}

void wrongSeq() {
  resetEnv();

  for (int i = 0; i < 3; i++) {
    turnOnAllLeds();
    delay(ANIMATION_DELAY);
    turnOffAllLeds();  
  }
}

void resetEnv() {
  level = 1;
  pressed = 0;
}

void onPinActivated(byte btnPin) {
  turnOnLed(btnToLed(btnPin));
}

void onPinDeactivated(byte btnPin) {
  turnOffLed(btnToLed(btnPin));
  pressed = btnToLed(btnPin);
}

byte btnToLed(byte btnPin) {
  switch(btnPin) {
    case BTN_YELLOW:
      return LED_YELLOW;
    case BTN_BLUE:
      return LED_BLUE;
    case BTN_RED:
      return LED_RED;
    case BTN_GREEN:
      return LED_GREEN;
  }
}

void turnOnLed(byte led) {
  digitalWrite(led, HIGH);
}

void turnOffLed(byte led) {
  digitalWrite(led, LOW);  
}

void turnOffAllLeds() {
  turnOffLed(LED_YELLOW);
  turnOffLed(LED_BLUE);
  turnOffLed(LED_RED);
  turnOffLed(LED_GREEN);
}

void turnOnAllLeds() {
  turnOnLed(LED_YELLOW);
  turnOnLed(LED_BLUE);
  turnOnLed(LED_RED);
  turnOnLed(LED_GREEN);
}
