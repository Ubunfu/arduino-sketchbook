int PIN_LED_START = 2;
int NUM_LEDS = 5;
int PIN_LED_INDICATOR = 13;
int DELAY_MILLIS = 100;

void setup() {
  for(int i = PIN_LED_START; i < PIN_LED_START + NUM_LEDS; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(PIN_LED_INDICATOR, OUTPUT);
}

void loop() {
  digitalWrite(PIN_LED_INDICATOR, HIGH);
  for(int i = PIN_LED_START; i < PIN_LED_START + NUM_LEDS; i++){
    digitalWrite(i, HIGH);
    delay(DELAY_MILLIS);
  }
  digitalWrite(PIN_LED_INDICATOR, LOW);
  for(int i = PIN_LED_START; i < PIN_LED_START + NUM_LEDS; i++){
    digitalWrite(i, LOW);
    delay(DELAY_MILLIS);
  }
}
