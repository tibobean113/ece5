
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

void loading_bar(){
    byte bar[]{
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
  };

  int duration = 0;
  //button = digitalRead(8);
  duration += 1;
        
  lcd.write(byte(duration));
}

int choose_game(){
  delay(1000);
  String gameList[] = {"Whack-a-mole","Laser Hold"};

  byte bar[]{
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
  };

  for (int i=0;i<8;i++) lcd.createChar(i, bar);
  
  int choice = 0;
  int duration = 0;
  int button = digitalRead(8);

  lcd.clear();
  lcd.print(gameList[choice]);
  
  while(true){
    button = digitalRead(8);
    
    if (button == 1){

    delay(200);
    
    button = digitalRead(8);
    lcd.setCursor(0,1);
      while (button == 1){
        button = digitalRead(8);
        duration += 1;
        
        lcd.write(byte(duration));

        if (duration == 17){
          lcd.clear();
          lcd.print(gameList[choice] + " chosen!");
          return choice;
        }
      
        delay(50);
      }

      if (duration <= 0){
        choice+=1;
        if (choice > 1) choice = 0;
      }
      duration = 0;
      lcd.clear();
      lcd.print(gameList[choice]);
    }

  }
}

void end_game(){
  Serial.println("Ending game");
  lcd.clear();
  lcd.print("Time's up!");
  lcd.clear();
}

void laser_hold(){
  begin_game();
  
  int score1 = 0;
  int score2 = 0;

  lcd.setCursor(0,0);
  lcd.print("P1");
  lcd.setCursor(14,0);
  lcd.print("P2");

  while (score1<100 and score2<100){
    if (getHit(3) == 1) score1 += 1;
    if (getHit(4) == 1) score2 += 1;

    lcd.setCursor(0,1);
    lcd.print(score1);
    timerPrint(score2);

    delay(100);
  }

  lcd.clear();

  if (score1 >= 100){
    Serial.print("Player 1 wins!");
    delay(1000);
    end_game();
  }else if (score2 >= 100){
    Serial.print("Player 2 wins!");
    delay(1000);
    end_game();
  }else{
    Serial.print("Tie game!");
    delay(1000);
    end_game();
  }
    
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

  lcd.print("Press to start");
  
  
}

void loop() {
  if (digitalRead(8) == HIGH){
    lcd.clear();
    int x = choose_game();
    
    if (x == 0) whack_a_mole();
    if (x == 1) laser_hold();
  }
}
