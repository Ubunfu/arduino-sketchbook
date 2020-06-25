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
 * Wire the receiver up to 5V, and connect the signal pin to the digital pin assigned to 
 * constant IR_RECV_PIN. Wire an LED up to the digital pin assigned to constant 
 * SECRET_LED_PIN with a 220 Ohm resistor in-line.
 * 
 * Behavior Details:
 * Whenever the receiver detects an IR signal, the on-board LED (D13) will flash.  If the 
 * IRremote library is able to discern the manufacturer of the IR emitter, it will be 
 * printed to the serial  monitor, along with the code of the received IR signal as an 
 * unsigned long.  If a specific button on the remote is pressed which emits the code 
 * assigned to constant SAMSUNG_POWER_BUTTON, the LED connected to the pin connected to 
 * pin SECRET_LED_PIN will flash for SECRET_FLASH_MILLIS milliseconds.
 * 
 */

#include <IRremote.h>

const int IR_RECV_PIN = 2;
const int SECRET_LED_PIN = 3;
const int SECRET_FLASH_MILLIS = 500;
IRrecv irrecv(IR_RECV_PIN);
decode_results results;
const unsigned long SAMSUNG_POWER_BUTTON = 3772793023;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true); // blink on-board LED (digital-13) on IR-received
  pinMode(SECRET_LED_PIN, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)){
    Serial.println(decodeManufacturer(results));
    Serial.println(results.value);
    if (results.value == SAMSUNG_POWER_BUTTON){
      flashPin(SECRET_LED_PIN, SECRET_FLASH_MILLIS);
    }
    irrecv.resume();
  }
}

void flashPin(int pin, int millis){
  digitalWrite(pin, HIGH);
  delay(millis);
  digitalWrite(pin, LOW);
}

String decodeManufacturer(decode_results results){
  switch (results.decode_type){
      case NEC: return "NEC"; break ;
      case SONY: return "SONY"; break ;
      case RC5: return "RC5"; break ;
      case RC6: return "RC6"; break ;
      case DISH: return "DISH"; break ;
      case SHARP: return "SHARP"; break ;
      case JVC: return "JVC"; break ;
      case SANYO: return "SANYO"; break ;
      case MITSUBISHI: return "MITSUBISHI"; break ;
      case SAMSUNG: return "SAMSUNG"; break ;
      case LG: return "LG"; break ;
      case WHYNTER: return "WHYNTER"; break ;
      case AIWA_RC_T501: return "AIWA_RC_T501"; break ;
      case PANASONIC: return "PANASONIC"; break ;
      case DENON: return "DENON"; break ;
    default:
      case UNKNOWN: return "UNKNOWN"; break ;
    }
}
