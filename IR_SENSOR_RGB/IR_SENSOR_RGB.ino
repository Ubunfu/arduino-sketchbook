/*
 * Datasheet for VS1838B IR Receiver:
 * https://www.elecparts101.com/vs1838b-ir-remote-control-infrared-receiver-datasheet-and-pinout/
 * 
 * Article about using IR emitters and receivers on Arduino boards:
 * https://www.circuitbasics.com/arduino-ir-remote-receiver-tutorial/
 * 
 * Arduino-IRremote Library repo:
 * https://github.com/z3t0/Arduino-IRremote
 * 
 * Tested with a Samsung BN59-01179A Smart-TV IR Remote.
 * 
 * Setup Details:
 * Connect the IR sensor to 5V and connect the signal pin of the receiver to the 
 * digital pin assigned to IR_RECV_PIN.  Identify three PWM-enabled pins on the board
 * and assign one to each of R_PIN, G_PIN, and B_PIN.  Find an RGB LED, and connect
 * the PWM-pin assigned to R_PIN to the RGB LED lead controlling the red color channel.
 * Put a 220 Ohm resistor (to start with) in-line between the output pins and the color 
 * channel leads of the LED. Do likewise for the Green and Blue color channels. 
 * Connect the ground lead of the RGB LED to ground.
 * 
 * Get a remote and find 6 buttons to control raising and lowering each of the 3
 * color channels of the RGB LED. Identify the IR signal codes (as unsigned long) 
 * associated with each button.  If you don't know these, use the IR_SENSOR sketch 
 * in this repo to figure them out. Assign each of the codes to the BUTTON_* constants 
 * below.
 * 
 * Behavior Details:
 * When the buttons are pressed on the remote, each of the individual RGB color
 * channels in the LED will be raised or lowered individually.  Each button press also 
 * writes which button was pressed and the current values of all three levels to the 
 * serial monitor.
 * 
 */

#include <IRremote.h>

const int IR_RECV_PIN = 2;
const int R_PIN = 9;
const int G_PIN = 10;
const int B_PIN = 5;

const unsigned long BUTTON_R_UP = 3772833823;
const unsigned long BUTTON_R_DOWN = 3772829743;
const unsigned long BUTTON_G_UP = 3772837903;
const unsigned long BUTTON_G_DOWN = 3772831273;
const unsigned long BUTTON_B_UP = 3772795063;
const unsigned long BUTTON_B_DOWN = 3772778743;

int rLevel = 0;
int gLevel = 0;
int bLevel = 0;
const int LEVEL_STEP = 10;

IRrecv irrecv(IR_RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true); // blink on-board LED (digital-13) on IR-received
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)){
    updateLevels(results);
    writeLevels(rLevel, gLevel, bLevel, R_PIN, G_PIN, B_PIN);
    irrecv.resume();
  }
}

void writeLevels(int rLevel, int gLevel, int bLevel, int rPin, int gPin, int bPin){
  Serial.println("===");
  Serial.println(rLevel);
  Serial.println(gLevel);
  Serial.println(bLevel);
  Serial.println("===");
  
  analogWrite(rPin, rLevel);
  analogWrite(gPin, gLevel);
  analogWrite(bPin, bLevel);
}

void updateLevels(decode_results results){
  switch (results.value){
      case BUTTON_R_UP: 
        Serial.println("Red Up!");
        rLevel = increaseColorLevel(rLevel, LEVEL_STEP); 
        break;
      case BUTTON_R_DOWN: 
        Serial.println("Red Down!");
        rLevel = decreaseColorLevel(rLevel, LEVEL_STEP); 
        break;
      case BUTTON_G_UP: 
        Serial.println("Green Up!");
        gLevel = increaseColorLevel(gLevel, LEVEL_STEP); 
        break;
      case BUTTON_G_DOWN: 
        Serial.println("Green Down!");
        gLevel = decreaseColorLevel(gLevel, LEVEL_STEP); 
        break;
      case BUTTON_B_UP: 
        Serial.println("Blue Up!");
        bLevel = increaseColorLevel(bLevel, LEVEL_STEP); 
        break;
      case BUTTON_B_DOWN: 
        Serial.println("Blue Down!");
        bLevel = decreaseColorLevel(bLevel, LEVEL_STEP); 
        break;
    }
}

int increaseColorLevel(int level, int step){
  int increasedLevel = level + step;
  if (increasedLevel > 255){
    return increasedLevel - 255;
  } else {
    return increasedLevel;
  }
}

int decreaseColorLevel(int level, int step){
  int decreasedLevel = level - step;
  if (decreasedLevel < 0){
    return decreasedLevel + 255;
  } else {
    return decreasedLevel;
  }
}
