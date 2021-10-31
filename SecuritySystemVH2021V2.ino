#include <Arduino.h>
#include <U8g2lib.h>
#include <U8x8lib.h>
#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#define DHTPIN 3     
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
int Light = A6;
int Mic = 2;
int Pot = 0;
int Button = 6;
int Speaker = 5;
int ArmLED = 4;
int val;
int count = 0;
char Password[4]={'0','0','0','0'};
char EnterPassword[9] = {'0','0','0','0','0','0','0','0','0'};
char passchar = '0'; 
String temphumpres;
bool checksum(){
  bool finalcheck = false;
  String check, othercheck;
  for(int i = 0; i < 5; i++){
    String check = check + Password[i];
  }
  for(int i = 5; i < 9; i++){
    String othercheck = othercheck + EnterPassword[i];
  }
  if( check == othercheck){
    finalcheck = true;
  }
  else{
    finalcheck = false;
  }
  return finalcheck;
  
}
int counter(){
   pinMode(Button, INPUT);
   int ButtonPress = digitalRead(Button);
   if(ButtonPress == HIGH){
  count++;
  delay(100);
  }
  return count;
}
void setup() {
Serial.begin(9600);
  pinMode(Light, INPUT);
  pinMode(Mic, INPUT);
  pinMode(Pot, INPUT);
  pinMode(Button, INPUT);
  pinMode(Speaker, OUTPUT);
  pinMode(ArmLED, OUTPUT);
  u8x8.setBusClock(100000);
  u8x8.begin();
  u8x8.setFlipMode(1);
  dht.begin();

}

void loop() {
start:
  float temp, humi;
  temp = dht.readTemperature();
  humi = dht.readHumidity(); 
  int Passlight = analogRead(Light);
  int Footsteps = analogRead(Mic);
  int val = counter();
  int ButtonPress = digitalRead(Button);
  int Pass = analogRead(Pot);
  char lockstate[1];
  if(Pass >= 0 && Pass <= 255){
    u8x8.print("4");
    passchar = '4';
  }
  else{
    u8x8.print("");
  }
  if(Pass >= 266 && Pass <= 521){
    u8x8.print("3");
    passchar = '3';
  }
   else{
    u8x8.print("");
  }
  if(Pass >= 522 && Pass <= 777){
    u8x8.print("2");
    passchar = '2';
  }
   else{
    u8x8.print("");
  } 
  if(Pass < 900 && Pass > 777){
    u8x8.print("1");
    passchar = '1';
  }
  else{
    u8x8.print("");
  }
  if(Pass >= 900){
    u8x8.print("W");
    passchar = 'W';
  }
  else{
    u8x8.print("   ");
  }  
  delay(200);        
         u8x8.setFont(u8x8_font_chroma48medium8_r);
         u8x8.setCursor(0, 0);
         u8x8.print("Please Enter a");
         u8x8.print('\n');
         u8x8.print("Password");
         u8x8.print('\n');
         u8x8.print("Digit: ");
         
      if( passchar == 'W'){
         u8x8.clear();
         u8x8.setFont(u8x8_font_chroma48medium8_r);
         u8x8.setCursor(0, 33);
         u8x8.print("Temp:");
         u8x8.print(temp);
         u8x8.print("C");
         u8x8.setCursor(0,50);
         u8x8.print("Hum:");
         u8x8.print(humi);
         u8x8.print("%");
         u8x8.setCursor(0,59);
         u8x8.print("Light:");
         u8x8.print(Passlight);
         u8x8.print("lm");
         u8x8.setCursor(0,60);
         u8x8.print("Noise:");
         u8x8.print(Footsteps);
         u8x8.print("Hz");
         u8x8.refreshDisplay();
         delay(10000);
         u8x8.clear();
         
  delay(200);
      }
      else if(ButtonPress == HIGH && val == 1){
          analogWrite(Speaker, 100);
           Password[0] = {passchar};
         delay(20);
         analogWrite(Speaker, 0);
        
        
      }
      else if(ButtonPress == HIGH && val ==2 ){
        analogWrite(Speaker, 100);
        Password[1] = {passchar};
         delay(20);
         analogWrite(Speaker, 0);
        Password[1] = {passchar};
         
      }
      else if(ButtonPress == HIGH && val == 3){
        analogWrite(Speaker, 100);
        Password[2] = {passchar};
          delay(20);
         analogWrite(Speaker, 0);
        Password[2] = {passchar};
          
      }
      else if (ButtonPress == HIGH && val == 4){
        analogWrite(Speaker, 100);
        Password[3] = {passchar};
          delay(20);
         analogWrite(Speaker, 0);
        
          
      }
    else if(val == 5){digitalWrite(ArmLED, HIGH);
    u8x8.clear();
    u8x8.print("The System is");
    u8x8.print('\n');
    u8x8.print("Now Armed!!");
    u8x8.print('\n');
    delay(5000);   
    }
    else if(Footsteps > 350 ){
      analogWrite(Speaker, 100);
      delay(2000);
      digitalWrite(ArmLED, LOW);
      delay(2000);
      digitalWrite(ArmLED, HIGH);
      u8x8.print("Intruder!!");
      delay(2000);
      digitalWrite(ArmLED, LOW);
      u8x8.clear();
      delay(2000);    
    }
    else if(ButtonPress == HIGH && val == 7){
      analogWrite(Speaker, 100);
      EnterPassword[6] = {passchar};
       delay(20);
       analogWrite(Speaker, 0);
      
       
    }
    else if(ButtonPress == HIGH && val == 8){
      analogWrite(Speaker, 100);
      EnterPassword[7] = {passchar};
        delay(20);
        analogWrite(Speaker, 0);
      
        
    }
    else if(ButtonPress == HIGH && val == 9){
      analogWrite(Speaker, 100);
      EnterPassword[8] = {passchar};
        delay(20);
        analogWrite(Speaker, 0);
      
        
    }
    else if(ButtonPress == HIGH && val == 10){
      analogWrite(Speaker, 100);
      EnterPassword[9] = {passchar};
        delay(20);
        analogWrite(Speaker, 0);
      
        
    }
    else if(ButtonPress == HIGH && val == 11){
      
    }
  else if(val == 12 && checksum() == true){
    analogWrite(Speaker, 500);
    delay(10);
    analogWrite(Speaker, 0);
    u8x8.clear();
    u8x8.print("The Alarm Has");
    u8x8.print('\n');
    u8x8.print("Disarmed :)");
    u8x8.clear();
    digitalWrite(ArmLED, LOW);
    delay(5000);
    goto start;
    
  }
  else if(Passlight < 3 && passchar == 'W'){
     analogWrite(Speaker, 0);
      digitalWrite(ArmLED, LOW);
      u8x8.clear();
      u8x8.print("Disarmed :)");
      delay(500);
      goto start;
  }
  else if(Passlight < 3 && passchar == '4'){
      analogWrite(Speaker, 0);
      digitalWrite(ArmLED, LOW);
      u8x8.clear();
      u8x8.print("Disarmed :)");
      delay(500);
      goto start;
    }
   else{}
 
}
  
