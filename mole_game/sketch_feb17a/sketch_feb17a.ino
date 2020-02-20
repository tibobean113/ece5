

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include <Entropy.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(A4,A5,A0,A1,A2,A3);


int getHit(int a){
  if (digitalRead(a) == 1)
    return 1;
  else
    return 2;
}

int numPlaces (int n) {
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
}

void timerPrint(int a){
  int numSize = numPlaces(a);

  lcd.setCursor(15 - numSize,1);
  lcd.print(" ");
  lcd.setCursor(16 - numSize,1);
  lcd.print(a);
  
}

void begin_game(){
  Serial.println("Beginning game \n");
  lcd.clear();
  lcd.print("Ready...");
  delay(1000);
  lcd.clear();
  lcd.print("Set...");
  delay(1000);
  lcd.clear();
  lcd.print("GO!!!");
  delay(1000);
  lcd.clear();
}

void end_game(){
  Serial.println("Ending game");
  lcd.clear();
  lcd.print("Time's up!");
  lcd.clear();
}

void whack_a_mole(){
           
  begin_game();

  int timer = 120;

  int score = 0;
  lcd.setCursor(0,0);
  lcd.print("Score:");
  lcd.setCursor(0,1);
  lcd.print(score);
  lcd.setCursor(16 - numPlaces(timer),1);
  lcd.print(timer);
  
  while(timer > 0){
    int arr[]={0,0,0,0}; 
    int rand_num1 = (int) random(0,4);
    int control = (int) random(1,11);
    //Serial.println(control);
    int rand_num2 = rand_num1;
    int rand_num3 = rand_num1;
    int rand_num4 = rand_num1;
    
    if (control >= 9){ //chance for 2 moles to pop up at once
      rand_num2 = (int) random(0,4);

      control = (int) random(1,11);
      //Serial.println(control);
      if (control >= 8){ //3 moles
        rand_num3 = (int) random(0,4);
        rand_num4 = (int) random(0,4);
      }
    }
      
    if (arr[rand_num1] == 0)
      arr[rand_num1] = 1;

    if (arr[rand_num2] == 0)
      arr[rand_num2] = 1;

    if (arr[rand_num3] == 0)
      arr[rand_num3] = 1;

    if (arr[rand_num4] == 0)
      arr[rand_num4] = 1;
        

    for (int i=0;i<4;i++)
      Serial.print(arr[i]);
    Serial.print("\n");

    delay(1000);
        
    timer -= 1;
    timerPrint(timer);
    
      for (int pin=3;pin<=6;pin++){ //this loop checks for any moles that have been hit
        
        if (getHit(pin) == arr[pin-3]){
          Serial.println("Mole hit on pin: " + (String)pin);

          score += 1;
          arr[pin-3] = 0;
          
          for (int i=0;i<4;i++)
            Serial.print(arr[i]);
          Serial.print("\n");
        }
        
      }
      
    
    lcd.setCursor(0,1);
    lcd.print(score); //updates score
    
    
    delay(1000);
    timer -= 1;
    timerPrint(timer);
    delay(1000);
    timer -= 1;
    timerPrint(timer);
    
  }

  lcd.clear();
  lcd.print("TIME'S UP!");
  delay(2000);
  lcd.clear();
  lcd.print("Your score was:");
  lcd.setCursor(0,1);
  lcd.print(score);
  
}
 

void setup() {
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);  
  // Print a message to the LCD.

  pinMode(8,INPUT);
  
  Entropy.initialize();
  randomSeed(Entropy.random());
  whack_a_mole();
}

void loop() {
  
}
