#define TRANSMIT_LED 13
#define BUTTON 8
#define SAMPLING_TIME 20

char* text = " user01 ";


bool led_state = false;
bool button_state = false;
bool transmit_data = true;
int bytes_counter = 20;
int total_bytes;
void setup() {
  
  pinMode(TRANSMIT_LED,OUTPUT);
  total_bytes = strlen(text);
}

void loop() {
int trans = digitalRead(BUTTON);
  if (trans == 1) {
    for (int j = 0; j < 4; j++) { 
      transmit_data = true;
      bytes_counter = total_bytes;
      while (transmit_data) {
        transmit_byte(text[total_bytes - bytes_counter]);
        bytes_counter--;
        if (bytes_counter == 0) {
          transmit_data = false;
        }
        delay(100);
      }
      delay(1000);
    }
  } else {
    digitalWrite(TRANSMIT_LED, LOW);
  }
}
 


void transmit_byte(char data_byte)
{
  digitalWrite(TRANSMIT_LED,LOW); 
  delay(SAMPLING_TIME);
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(TRANSMIT_LED,(data_byte >> i) & 0x01); 
    delay(SAMPLING_TIME);
  }
 digitalWrite(TRANSMIT_LED,HIGH); 
 delay(SAMPLING_TIME);
}
