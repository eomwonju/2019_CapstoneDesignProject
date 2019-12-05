#include <SoftwareSerial.h>
#define PIN_RX 2
#define PIN_TX 3
#define PIN_FRAME1 A0
#define PIN_FRAME2 A1
#define PIN_FRAME3 A2
#define PIN_FRAME4 A3

int frameData1 = 0;
int frameData2 = 0;
int frameData3 = 0;
int frameData4 = 0;
int fire1 = 0;
int fire2 = 0;
int fire3 = 0;
int fire4 = 0;

int PIN_RX_B = 4;
int PIN_TX_B = 5;

SoftwareSerial bleSerial(PIN_RX, PIN_TX);
SoftwareSerial BTSerial(PIN_RX_B, PIN_TX_B);

void setup(){
  Serial.begin(9600);
  bleSerial.begin(9600);
  BTSerial.begin(9600);
}

void loop(){
  fire1 = 0;
  fire2 = 0;
  fire3 = 0;
  fire4 = 0;

  frameData1 = analogRead(PIN_FRAME1);
  frameData2 = analogRead(PIN_FRAME2);
  frameData3 = analogRead(PIN_FRAME3);
  frameData4 = analogRead(PIN_FRAME4);


   if(frameData1<500){
    fire1 = 1;
    BTSerial.println("AT+IBE000000201");

    while (BTSerial.available()){
      byte data = BTSerial.read();
      Serial.write(data);
      }  
    while (Serial.available()){
      byte data = Serial.read();
      BTSerial.write(data); 
      } 
   }
       
   if(frameData2<500){
    fire2 = 1;
    BTSerial.println("AT+IBE000000202");

    while (BTSerial.available()){
      byte data = BTSerial.read();
      Serial.write(data);
      }  
    while (Serial.available()){
      byte data = Serial.read();
      BTSerial.write(data); 
      }  
   }
   
    
  if(frameData3<500){
    fire3 = 1;
    BTSerial.println("AT+IBE000000203");

    while (BTSerial.available()){
      byte data = BTSerial.read();
      Serial.write(data);
      }  
    while (Serial.available()){
      byte data = Serial.read();
      BTSerial.write(data); 
      } 
  }
  
    
  if(frameData4<500){
    fire4 = 1;
    BTSerial.println("AT+IBE000000204");

    while (BTSerial.available()){
      byte data = BTSerial.read();
      Serial.write(data);
      }  
    while (Serial.available()){
      byte data = Serial.read();
      BTSerial.write(data); 
      } 
  }
  
  
  if (frameData1>500 & frameData2>500 & frameData3>500& frameData4>500){
    BTSerial.println("AT+IBE000000002");

    while (BTSerial.available()){
      byte data = BTSerial.read();
      Serial.write(data);
      }  
    while (Serial.available()){
      byte data = Serial.read();
      BTSerial.write(data); 
      } 
  }
          
  
  bleSerial.print(String(fire1));
  bleSerial.print(String(fire2));
  bleSerial.print(String(fire3));
  bleSerial.print(String(fire4));

  delay(1000);
}
