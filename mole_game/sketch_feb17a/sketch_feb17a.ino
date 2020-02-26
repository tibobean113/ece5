
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


int choose(String gameList[]){
  delay(400);
  //String gameList[] = {"Whack-a-mole","Laser Hold"};

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
          //lcd.print(gameList[choice] + " chosen!");
          return choice;
        }
      
        delay(50);
      }

      if (duration <= 1){
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
  lcd.print("Play another");
  lcd.setCursor(0,1);
  lcd.print("game? (Press button)");
  
  while(true){
    if (digitalRead(8) == 1){
      String a[] = {"Yes","No"};
      int x = choose(a);
      if (x==0){
        String b[] = {"Whack-a-mole","Laser Hold"};
        x = choose(b);
        if (x==0) whack_a_mole();
        if (x==1) laser_hold();
      }else{ 
        lcd.clear();
        lcd.print("Press to start");
        delay(400);
        return;
      }
        
        
    } 
    
  }
  
}

void memorise_pattern(){ //I'll finish this game if we have time
  int i = 6;
  int a[5];
  int b[5];
  
  for (i-0;i<6;i++){
    a[i] = (int) random(0,4);
  }

  while(true){
    
  }
}

void laser_hold(){
  begin_game();

  digitalWrite(9, HIGH);
  
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
    lcd.print("Player 1 wins!");
    delay(3000);
    end_game();
  }else if (score2 >= 100){
    lcd.print("Player 2 wins!");
    delay(3000);
    end_game();
  }else{
    lcd.print("Tie game!");
    delay(3000);
    end_game();
  }
    
}

void whack_a_mole(){
           
  begin_game();

  int timer = 20;

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
      
    if (arr[rand_num1] == 0){
      arr[rand_num1] == 1;
      if (rand_num1 == 0)
        digitalWrite(9, HIGH);
    }
      


    if (arr[rand_num2] == 0){
      arr[rand_num2] = 1;
      if (rand_num2 == 0)
        digitalWrite(9, HIGH);
    }

    if (arr[rand_num3] == 0){
      arr[rand_num3] = 1;
      if (rand_num3 == 0)
        digitalWrite(9, HIGH);
    }

    if (arr[rand_num4] == 0){
      arr[rand_num4] = 1;
      if (rand_num4 == 0)
        digitalWrite(9, HIGH);
    }
        

    for (int i=0;i<4;i++)
      Serial.print(arr[i]);
    Serial.print("\n");


    for (int i = 0;i<2;i++){
    for(uint32_t t_initial = millis(); millis() - t_initial < 1000; ){
      for (int pin=3;pin<=6;pin++){ //this loop checks for any moles that have been hit
        
        if (getHit(pin) == arr[pin-3]){
          Serial.println("Mole hit on pin: " + (String)pin);

          score += 1;
          if (pin == 3) digitalWrite(9, LOW);
          arr[pin-3] = 0;
          
          for (int i=0;i<4;i++)
            Serial.print(arr[i]);
          Serial.print("\n");
        }
        
      }
      
    }

    timer--;
    timerPrint(timer);
    
    }

    digitalWrite(9, LOW);
    
    lcd.setCursor(0,1);
    lcd.print(score); //updates score
    
  }

  lcd.clear();
  lcd.print("TIME'S UP!");
  delay(2000);
  lcd.clear();
  lcd.print("Your score was:");
  lcd.setCursor(0,1);
  lcd.print(score);
  delay(6000);
  end_game();
  
}
 

void setup() {
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);  
  // Print a message to the LCD.

  pinMode(8,INPUT);
  pinMode(9,OUTPUT);

  String gameList[] = {"Whack-a-mole","Laser Hold"};
  
  Entropy.initialize();
  randomSeed(Entropy.random());

  lcd.print("Press to start");
  
  
}

void loop() {

  if (digitalRead(8) == HIGH){
    lcd.clear();
    String a[] = {"Whack-a-mole","Laser Hold"};
    int x = choose(a);
    
    if (x == 0) whack_a_mole();
    if (x == 1) laser_hold();
  }
  delay(100);
}
