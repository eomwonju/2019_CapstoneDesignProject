#include <SoftwareSerial.h>
#include <Wire.h>
#include "paj7620.h"
#define PIN_RX 2
#define PIN_TX 3
#define PIN_RX_B 4
#define PIN_TX_B 5
#define PIN_BUZZER 7
#define PIN_FRAME A0
#define PIN_GAS A1
#define PIN_GES1 A2
#define PIN_GES2 A3
#define GES_REACTION_TIME 500       
#define GES_ENTRY_TIME 800 
#define GES_QUIT_TIME 1000

int frameData = 0;
int gasData = 0;
int fire = 0;
int gas = 0;
int mov = 0;
int people = 0;
int count = 0;


SoftwareSerial bleSerial(PIN_RX, PIN_TX);
SoftwareSerial BTSerial(PIN_RX_B, PIN_TX_B);

void setup(){
  uint8_t error = 0;
  Serial.begin(9600);
  bleSerial.begin(9600);
  BTSerial.begin(9600);
  pinMode(PIN_BUZZER, OUTPUT);
  error = paj7620Init();
}

void loop(){
  uint8_t gesData1 = 0;
  uint8_t gesData2 = 0;
  uint8_t error;
  fire = 0;
  gas = 0;
  mov = 0;

  error = paj7620ReadReg(0x43, 1, &gesData1);
  frameData = analogRead(PIN_FRAME);
  gasData = analogRead(PIN_GAS);
    
  if(frameData<500){
    fire = 1;
    tone(PIN_BUZZER, 262, 500);
    BTSerial.println("AT+IBE000000101");

    while (BTSerial.available()){
      byte data = BTSerial.read();
      Serial.write(data);
      }  
 
    while (Serial.available()){
      byte data = Serial.read();
      BTSerial.write(data); 
      }
  }

  else if(frameData>=500&gasData>340){
    gas = 1;
    tone(PIN_BUZZER, 262, 500);
    BTSerial.println("AT+IBE000000102");

    while (BTSerial.available()){
      byte data = BTSerial.read();
      Serial.write(data);
      }  
 
    while (Serial.available()){
      byte data = Serial.read();
      BTSerial.write(data); 
      }
  }
  
   else { BTSerial.println("AT+IBE000000001");

    while (BTSerial.available()){
      byte data = BTSerial.read();
      Serial.write(data);
      }  
 
    while (Serial.available()){
      byte data = Serial.read();
      BTSerial.write(data); 
      }
  }

  
 // Serial.println(gasData);
  
  if(!error){
    switch (gesData1)
    {
      case GES_RIGHT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &gesData1);
        if(gesData1 == GES_FORWARD_FLAG){
          mov = 1;
          delay(GES_QUIT_TIME);
        }
        else if(gesData1 == GES_BACKWARD_FLAG){
          mov = 1;
          delay(GES_QUIT_TIME);
        }
        else{
          mov = 1;
        }          
        break;
        
      case GES_LEFT_FLAG: 
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &gesData1);
        if(gesData1 == GES_FORWARD_FLAG) 
        {
          mov = 1;
          delay(GES_QUIT_TIME);
        }
        else if(gesData1 == GES_BACKWARD_FLAG) 
        {
          mov =1;
          delay(GES_QUIT_TIME);
        }
        else{
          mov = 1;
        }          
        break;
        
      case GES_UP_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &gesData1);
        if(gesData1 == GES_FORWARD_FLAG) 
        {
          mov = 1;
          delay(GES_QUIT_TIME);
        }
        else if(gesData1 == GES_BACKWARD_FLAG) 
        {
          mov = 1;
          delay(GES_QUIT_TIME);
        }
        else
        {
          mov = 1;
        }          
        break;
        
      case GES_DOWN_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &gesData1);
        if(gesData1 == GES_FORWARD_FLAG) 
        {
          mov = 1;
          delay(GES_QUIT_TIME);
        }
        else if(gesData1 == GES_BACKWARD_FLAG){
          mov = 1;
          delay(GES_QUIT_TIME);
        }
        else{
          mov = 1;
        }          
        break;
        
      case GES_FORWARD_FLAG:
        mov = 1;
        delay(GES_QUIT_TIME);
        break;
        
      case GES_BACKWARD_FLAG:     
        mov = 1;
        delay(GES_QUIT_TIME);
        break;
        
      case GES_CLOCKWISE_FLAG:
        mov = 1;
        break;
        
      case GES_COUNT_CLOCKWISE_FLAG:
        mov = 1;
        break; 
         
      default:
        paj7620ReadReg(0x44, 1, &gesData2);
        if (gesData2 == GES_WAVE_FLAG){
          mov = 1;
        }
        break;
    }
  }


  if(mov==1){
    people = 1;
    count = 5; 
  }

  if(mov==0){
    count--;
    if(count<1){
      count = 0;
    }}
  if(count==0){
    people = 0;
  }
    
  bleSerial.print(String(fire));
  bleSerial.print(String(gas));
  bleSerial.print(String(people));
  //Serial.print(fire);
  //Serial.print(mov);
  //Serial.println(people);
  
  delay(1000);
}
