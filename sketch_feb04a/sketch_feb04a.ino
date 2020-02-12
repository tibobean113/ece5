
#include <String.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(A4,A5,A0,A1,A2,A3); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
const int buttonPin = 8;
String one= "1";
int arr[]={10000,01000,00100,00010,00001};
void setup() 
{ 
   lcd.begin(16,2);
   pinMode(buttonPin, INPUT);
   lcd.print("Press the button to start the game!");
   Serial.begin(9600);
  
   pinMode(7,INPUT);
   pinMode(10,INPUT);
   
   // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
}

void loop() { 
  // Prints "Arduino" on the LCD 

int button = digitalRead(buttonPin);
String result=hit(7,6,5,4,3);
Serial.println(result);
delay (100);



delay(200);
//String val;
//val=digitalRead(7);
//Serial.print(val);
//String val2;
//val2=digitalRead(10);
//Serial.print(val2);
//delay(100);
  
  


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
String hit(int a, int b, int c, int d, int f){
  String result="";
result+=digitalRead(a);  
result+=digitalRead(b); 
result+=digitalRead(c); 
result+=digitalRead(d); 
result+=digitalRead(f);
return result; 
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
