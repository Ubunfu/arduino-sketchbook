int message;
int PIN_LED = 13;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  message = Serial.read();
  if(message > 0){
    digitalWrite(PIN_LED, HIGH);
    delay(25);
    digitalWrite(PIN_LED, LOW);
    delay(25);
    Serial.println(message); 
  }
}
