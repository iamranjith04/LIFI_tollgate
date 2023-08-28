#include <LiquidCrystal.h>
#define LDR_PIN A0
#define REDLED A1
#define GREENLED A2
#define SAMPLING_TIME 20
#define buzzer 11
#define IR 8
#include <string.h>
#include <Servo.h>
int servoPin = 9;

//Declaration 
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
bool led_state = false;
bool previous_state = true;
bool current_state = true;
char buff[64];
String data_word="";
String data_sentence="";
Servo servo1;


void setup() 
{
  pinMode(REDLED,OUTPUT);
  pinMode(GREENLED,OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  servo1.attach(servoPin);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("LIFI TOLL GATE");
}

void loop() 
{
  digitalWrite(REDLED,HIGH);
  servo1.write(0);
  current_state = get_ldr(); 
  if(!current_state && previous_state)
  {
    sprintf(buff, "%c", get_byte());
    ///Serial.println(buff); 
    data_word += buff;
    if(data_word.endsWith(" ")){
    data_sentence += data_word;
    data_sentence += " ";
    Serial.println(data_sentence);
    gate_control();
    }
  }
  
  previous_state = current_state;
  
}

  
bool get_ldr()
{
  bool val = analogRead(LDR_PIN) > 90 ? true : false;
  return val;
}


char get_byte()
{
  char data_byte = 0;
  delay(SAMPLING_TIME * 1.5);
  for(int i = 0; i < 8; i++)
  {
    data_byte = data_byte | (char)get_ldr() << i;
    delay(SAMPLING_TIME);
  }
  return data_byte;

}


void gate_control(){
  if (data_sentence.indexOf(" user01 ")>=0){
    digitalWrite(REDLED,LOW);
    servo1.write(120);
    digitalWrite(GREENLED,HIGH);
    int IR_pin = digitalRead(IR);
    lcd.clear();
    lcd.print("CAR TNX1323 ");
    lcd.setCursor(0,1);
    lcd.print("amount credited ");
    while (IR_pin == 1) {
      IR_pin = digitalRead(IR);
    }
    servo1.write(0);
    digitalWrite(GREENLED,LOW);
    data_word=" ";
    data_sentence=" ";
    lcd.clear();
    lcd.print(" LIFI TOLL GATE");
    delay(100);
    }
    if (data_sentence.indexOf(" user02 ")>=0){
    tone(buzzer,2000);
    lcd.clear();
    lcd.print("CAR KL13X2345 ");
    lcd.setCursor(0,1);
    lcd.print("Access denied ");
    delay(10000);
    data_word=" ";
    data_sentence=" ";
    noTone(buzzer);
    lcd.clear();
    lcd.print(" LIFI TOLL GATE");
    delay(100);
    }
}