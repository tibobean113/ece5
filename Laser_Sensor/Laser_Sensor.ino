#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
 Serial.begin(9600);
  // set up the LCD's number of columns and rows:
 pinMode(7,INPUT);
 
}

void loop() {
  // Turn off the blinking cursor:
  int val;
  val=digitalRead(7);
  Serial.print(val);
  delay(100);
}
