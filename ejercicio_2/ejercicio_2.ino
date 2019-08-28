#include "FTDebouncer.h"

#define LED_BLUE 2
#define LED_GREEN 3
#define LED_RED 4
#define LED_YELLOW 5

#define BTN_BLUE A0
#define BTN_GREEN A1
#define BTN_RED A2
#define BTN_YELLOW A3

#define INTERVAL 300

FTDebouncer pinDebouncer(30);

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
  pinDebouncer.run();
}

void onPinActivated(byte btn) {
  turnOnLed(btnToLed(btn)); 
}

void onPinDeactivated(byte btn) {
  turnOffLed(btnToLed(btn));
}

void setupLed(byte led) {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void setupBtn(byte btn) {
  pinDebouncer.addPin(btn, HIGH); 
}

void turnOnLed(byte led) {
  digitalWrite(led, HIGH);  
}

void turnOffLed(byte led) {
  digitalWrite(led, LOW);
}

byte btnToLed(byte btn) {
  switch(btn) {
    case BTN_BLUE:
      return LED_BLUE;
    case BTN_GREEN:
      return LED_GREEN;
    case BTN_RED:
      return LED_RED;
    case BTN_YELLOW:
      return LED_YELLOW;
  }
}
