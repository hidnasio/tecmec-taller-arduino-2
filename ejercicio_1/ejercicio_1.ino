#define LED_BLUE 2
#define LED_GREEN 3
#define LED_RED 4
#define LED_YELLOW 5

#define INTERVAL 300

void setup() {
  setupLed(LED_BLUE);
  setupLed(LED_GREEN);
  setupLed(LED_RED);
  setupLed(LED_YELLOW);
}

void loop() {
  switchAllLeds(HIGH);
  delay(INTERVAL);
  switchAllLeds(LOW);
  delay(INTERVAL);
}

void setupLed(byte led) {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void switchAllLeds(byte mode) {
  digitalWrite(LED_BLUE, mode);
  digitalWrite(LED_GREEN, mode);
  digitalWrite(LED_RED, mode);
  digitalWrite(LED_YELLOW, mode);
}
