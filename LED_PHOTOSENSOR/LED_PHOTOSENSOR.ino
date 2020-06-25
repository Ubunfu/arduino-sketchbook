/*
 * Wire the photocell up to 5V, and add about 5k Ohms 
 * to get room level light to measure ~ half light level. 
 * 
 * Measure the light level by tying the photocell
 * circuit to an analog input pin.
 * 
 * Wire an LED up to 5V with 220 Ohms in line, and 
 * tie it to a digital output pin to drive it HIGH when
 * the light level gets up enough.
 * 
 * Real time light-level readings are written to the serial
 * bus.
 */

int PHOTOCELL = A0;
int LED = 2;
int BAUD_RATE = 9600;
int DELAY = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(PHOTOCELL, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lightLevel = analogRead(PHOTOCELL);
  Serial.println(lightLevel);
  if(lightLevel >= 750){
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}
