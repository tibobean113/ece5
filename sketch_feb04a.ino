

#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(12,11,5,4,3,2); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
const int buttonPin = 8;

void setup() { 
   lcd.begin(16,2);
   pinMode(buttonPin, INPUT);
   lcd.print("Press the button to start the game!");
   Serial.begin(9600);
  
   pinMode(7,INPUT);
   
   // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
}

void loop() { 
  // Prints "Arduino" on the LCD 

  int button = digitalRead(buttonPin);

  int val;
  val=digitalRead(7);
  Serial.print(val);
  delay(100);

  if (button == HIGH){
    lcd.clear();
    lcd.print("Ready...");
    delay(1000);
    lcd.clear();
    lcd.print("Set...");
    delay(1000);
    lcd.clear();
    lcd.print("GO");
    delay(1000);
    lcd.clear();
    game();
  }

  
}

void game() {
  int t = 20;
  while (t > 0){
  
    lcd.print(t);
    t=t-1;
    delay(1000);
    lcd.clear();
  }

  lcd.print("GAME OVER!");
}
