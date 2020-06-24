int PIN_LED = 3;
int level = 0;

void setup()
{
  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
  for(int level = 0; level < 256; level++) {
    analogWrite(PIN_LED, level);
    delay(1);
  }
  for(int level = 255; level > 0; level--){
    analogWrite(PIN_LED, level);
    delay(1);
  }
}
