int BUTTON_R = 3;
int BUTTON_G = 4;
int BUTTON_B = 5;
int LED_R = 9;
int LED_G = 10;
int LED_B = 11;

int levelR = 0;
int levelG = 0;
int levelB = 0;

int DELAY_BUTTON_MILLIS = 10;
int BAUD_RATE = 9600;

void setup() {
  pinMode(BUTTON_R, INPUT);
  pinMode(BUTTON_G, INPUT);
  pinMode(BUTTON_B, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  debugPrintLevels();
  int buttonRPushed = digitalRead(BUTTON_R);
  int buttonGPushed = digitalRead(BUTTON_G);
  int buttonBPushed = digitalRead(BUTTON_B);
  updateLevels(buttonRPushed, buttonGPushed, buttonBPushed);
  lightLed(levelR, levelG, levelB);
}

void updateLevels(int buttonRPushed, int buttonGPushed, int buttonBPushed) {
  if(buttonRPushed == HIGH) {
    levelR = incrementLevel(levelR);
    Serial.println(levelR);
    delay(DELAY_BUTTON_MILLIS);
  }
  if(buttonGPushed == HIGH) {
    levelG = incrementLevel(levelG);
    Serial.println(levelG);
    delay(DELAY_BUTTON_MILLIS);
  }
  if(buttonBPushed == HIGH) {
    levelB = incrementLevel(levelB);
    Serial.println(levelB);
    delay(DELAY_BUTTON_MILLIS);
  }
}

int incrementLevel(int level) {
  if(level == 255){
    return 0;
  } else { 
    return level + 1;
  }
}

void lightLed(int r, int g, int b) {
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}
