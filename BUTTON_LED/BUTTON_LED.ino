int INPUT_BUTTON_1 = 12;
int INPUT_BUTTON_2 = 11;
int OUTPUT_LED = 2;
int STAYON_DELAY_MILLIS = 500;
int stayOn = false; 

void setup() {
  pinMode(INPUT_BUTTON_1, INPUT);
  pinMode(INPUT_BUTTON_2, INPUT);
  pinMode(OUTPUT_LED, OUTPUT);
}

void loop() {
  int buttonOnePushed = digitalRead(INPUT_BUTTON_1);
  int buttonTwoPushed = digitalRead(INPUT_BUTTON_2);

  if (buttonOnePushed && buttonTwoPushed) {
    stayOn = !stayOn;
    stayOnIfNeeded();
    delay(STAYON_DELAY_MILLIS);
  } else if (buttonOnePushed || buttonTwoPushed) {
    digitalWrite(OUTPUT_LED, HIGH);
  } else {
    stayOnIfNeeded();
  }
}

void stayOnIfNeeded() {
  if (stayOn) {
    digitalWrite(OUTPUT_LED, HIGH);
  } else {
    digitalWrite(OUTPUT_LED, LOW);
  }
}
