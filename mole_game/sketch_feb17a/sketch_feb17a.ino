
#include <LiquidCrystal.h>

LiquidCrystal lcd(A4,A5,A0,A1,A2,A3);

const int buttonPin = 8;

//String gameList = {"Whack a Mole"};

void setup() {
  Serial.begin(9600);
  
  lcd.begin(16,2);
  pinMode(buttonPin,INPUT);

  lcd.print("Press the button to start the game!");

  pinMode(7,INPUT);
  pinMode(10,INPUT);

  begin_game();
}

void loop() {
  // put your main code here, to run repeatedly:

}

int * getHits(int a,int b,int c,int d){

  static int hit_arr[4];
  
  a = digitalRead(a);
  b = digitalRead(b);
  c = digitalRead(c);
  d = digitalRead(d);
  
  return hit_arr;  
}

void begin_game(){
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
}

void whack_a_mole(){
  int arr[]={0,0,0,0};
  int *p;
    
  begin_game();
  

  while(true){
    int rand_num1 = (int) random(4);
    int rand_num2 = (int) random(4);

    if (arr[rand_num1] == 0)
      arr[rand_num1] = 1;

    if (arr[rand_num2] == 0)
      arr[rand_num2] = 1;

    p = getHits(7,6,5,4);

    for (int i=0;i<4;i++){
      if (p[i] != arr[rand_num1])
        Serial.print("mole " + (String)i + " hit");

      if (p[i] != arr[rand_num2])
        Serial.print("mole " + (String)i + " hit");    
    }


    delay(1000);

    arr[rand_num1] = 0;
    arr[rand_num2] = 0;

    Serial.print(""+arr[0]+arr[1]+arr[2]+arr[3]);
  }
  
}
