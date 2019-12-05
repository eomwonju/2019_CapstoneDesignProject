#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#define PIN_RX 2
#define PIN_TX 3
#define PIN_LED1 7
#define PIN_LED2 8
#define NUM_PIXELS 5

int bleData = 0;

SoftwareSerial bleSerial(PIN_RX, PIN_TX);
Adafruit_NeoPixel led1 = Adafruit_NeoPixel(NUM_PIXELS, PIN_LED1, NEO_GRB+NEO_KHZ800);
Adafruit_NeoPixel led2 = Adafruit_NeoPixel(NUM_PIXELS, PIN_LED2, NEO_GRB+NEO_KHZ800);

void setup(){
  Serial.begin(9600);
  bleSerial.begin(9600);
  //bleSerial.print("AT+ROLE0");
  //pinMode(PIN_RX, INPUT);
  //pinMode(PIN_TX, OUTPUT);
  led1.begin();
  led2.begin();
}

void loop(){
  //Serial.print(bleSerial.available());
  
  if(bleSerial.available()){
    
    bleData = bleSerial.read();
    //Serial.println(bleData);

    if(bleData=='2'){
      for(int i=0; i<NUM_PIXELS; i++){
        led1.setPixelColor(i, led1.Color(255, 0, 0));
        led2.setPixelColor(i, led2.Color(0, 255 ,0));
        led1.show();
        led2.show();
      }
    }
    else if(bleData=='1'){
      for(int i=0; i<NUM_PIXELS; i++){
        led1.setPixelColor(i, led1.Color(150, 0, 150));
        led2.setPixelColor(i, led2.Color(150, 0, 150));
        led1.show();
        led2.show();
      }
    }
    else if(bleData=='0'){
      for(int i=0; i<NUM_PIXELS; i++){
        led1.setPixelColor(i, led1.Color(0, 0, 0));
        led2.setPixelColor(i, led2.Color(0, 0, 0));
        led1.show();
        led2.show();
      }
    }
  }
  delay(100);
}
