#include <Servo.h>
#include <IRremote.h>
#include <LiquidCrystal.h>
 
int IR_Recv = 11;  
int firstpin = 13;   
int secondpin = 12;
int thirdpin =10;
int potpin = A0;
int potvalue = 0;
int heartrate = 60;
int buzzer = 9;
double angle1 = 0;
double angle2 = 0;
double angle3 = 0;
#define rs 7
#define en 6
#define d4 5
#define d5 4
#define d6 3
#define d7 2
 
IRrecv irrecv(IR_Recv);

decode_results results;

Servo first;		   
Servo second;
Servo third;

String currentMode;

 LiquidCrystal lcd(rs, en, d4, d5, d6, d7);//LCD Object

  

void setup(){
  Serial.begin(9600);
  
  pinMode(buzzer,OUTPUT);
  first.attach(13);  
  second.attach(12);
  third.attach(10);
  
  irrecv.enableIRIn(); 
  first.write(angle1);          
  second.write(angle2);
  third.write(angle3);
  
  // LCD Initialization
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Welcome");

  delay(500);
  
  lcd.setCursor(0, 0);
  lcd.print("Let Check:-");
  
  delay(500);
  
}
 
  

void loop(){
  potvalue = analogRead(potpin);
  heartrate = map(potvalue, 0, 1024, 0, 120);
    
  if (irrecv.decode(&results)){ 
    long int decCode = results.value; 
    //Serial.println(results.value);	
    Serial.println(decCode);	
    
    switch (results.value){ 
      case 16605343: 
      	servo1moveRight(); 
        break;
      case 16589023: 
      	servo1moveLeft(); 
        break;
      case 16613503: 
      	servo2moveRight(); 
        break;
      case 16617583: 
      	servo2moveLeft(); 
        break;
      case 16601263: 
      	servo3moveRight(); 
        break;
      case 16584943: 
      	servo3moveLeft(); 
        break;
      
      
      
    }
    irrecv.resume(); 
  }
  
  
  else if (heartrate>90 )
  {
    lcd.setCursor(0, 2);
    lcd.print("High rate");
    digitalWrite(buzzer, HIGH);
    Serial.println(heartrate);
    delay(100);
    digitalWrite(buzzer, LOW);
  }
  
  
    else if (heartrate<40 )
  {
    lcd.setCursor(0, 2);
    lcd.print("Low rate");
    digitalWrite(buzzer, HIGH);
    Serial.println(heartrate);
    delay(100);
    digitalWrite(buzzer, LOW);
  }
  delay(10); 
}

void servo1moveRight(){
  Serial.println("1 moveRight");   
    angle1=angle1+10;	 
    angle1 = map(angle1, 0, 180, 0, 180); 
    first.write(angle1); 
    delay(50);
  }

void servo1moveLeft(){
  Serial.println("1 moveLeftt");   
    angle1=angle1-10;	 
    angle1 = map(angle1, 0, 180, 0, 180); 
    first.write(angle1); 
    delay(50);
  }

void servo2moveRight(){
  Serial.println("2 moveRight");   
    angle2=angle2+10;	 
    angle2 = map(angle2, 0, 180, 0, 180); 
    second.write(angle2); 
    delay(50);
  }

void servo2moveLeft(){
  Serial.println("2 moveLeftt");   
    angle2=angle2-10;	 
    angle2 = map(angle2, 0, 180, 0, 180); 
    second.write(angle2); 
    delay(50);
  }

void servo3moveRight(){
  Serial.println("3 moveRight");   
    angle3=angle3+10;	 
    angle3 = map(angle3, 0, 180, 0, 180); 
    third.write(angle3); 
    delay(50);
  }

void servo3moveLeft(){
  Serial.println("3 moveLeftt");   
    angle3=angle3-10;	 
    angle3 = map(angle3, 0, 180, 0, 180); 
    third.write(angle3); 
    delay(50);
  }

