#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#define PIN_RX 2
#define PIN_TX 3
#define PIN_YELLOW 4
#define PIN_ATOMIZATION 5
#define PIN_LED1 6
#define PIN_LED2 7
#define PIN_LED3 8
#define PIN_LED4 9
#define PIN_FAN 10
#define NUM_PIXELS 5

int bleData = 0;

SoftwareSerial bleSerial(PIN_RX, PIN_TX);
Adafruit_NeoPixel led1 = Adafruit_NeoPixel(NUM_PIXELS, PIN_LED1, NEO_GRB+NEO_KHZ800);
Adafruit_NeoPixel led2 = Adafruit_NeoPixel(NUM_PIXELS, PIN_LED2, NEO_GRB+NEO_KHZ800);
Adafruit_NeoPixel led3 = Adafruit_NeoPixel(NUM_PIXELS, PIN_LED3, NEO_GRB+NEO_KHZ800);
Adafruit_NeoPixel led4 = Adafruit_NeoPixel(NUM_PIXELS, PIN_LED4, NEO_GRB+NEO_KHZ800);

void setup(){
  Serial.begin(9600);
  bleSerial.begin(9600);
  led1.begin();
  led2.begin();
  led3.begin();
  led4.begin();
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_ATOMIZATION, OUTPUT);
  pinMode(PIN_FAN, OUTPUT);
}

void loop(){  
  if(bleSerial.available()){
    
    bleData = bleSerial.read();
  
    if(bleData=='2'){
      for(int i=0; i<NUM_PIXELS; i++){
        led1.setPixelColor(i, led1.Color(255, 0, 0));
        led2.setPixelColor(i, led2.Color(255, 0 ,0));
        led3.setPixelColor(i, led3.Color(255, 0, 0));
        led4.setPixelColor(i, led4.Color(0, 255 ,0));
        led1.show();
        led2.show();
        led3.show();
        led4.show();
      }
      digitalWrite(PIN_YELLOW, HIGH);
      digitalWrite(PIN_ATOMIZATION, HIGH);
      digitalWrite(PIN_FAN, LOW);
    }
    else if(bleData=='1'){
      for(int i=0; i<NUM_PIXELS; i++){
        led1.setPixelColor(i, led1.Color(150, 0, 150));
        led2.setPixelColor(i, led2.Color(150, 0, 150));
        led3.setPixelColor(i, led3.Color(150, 0, 150));
        led4.setPixelColor(i, led4.Color(150, 0, 150));
        led1.show();
        led2.show();
        led3.show();
        led4.show();
      }
      digitalWrite(PIN_YELLOW, LOW);
      digitalWrite(PIN_ATOMIZATION, LOW);
      digitalWrite(PIN_FAN, HIGH);
    }
    else if(bleData=='0'){
      for(int i=0; i<NUM_PIXELS; i++){
        led1.setPixelColor(i, led1.Color(0, 0, 0));
        led2.setPixelColor(i, led2.Color(0, 0, 0));
        led3.setPixelColor(i, led3.Color(0, 0, 0));
        led4.setPixelColor(i, led4.Color(0, 0, 0));
        led1.show();
        led2.show();
        led3.show();
        led4.show();
      }
      digitalWrite(PIN_YELLOW, LOW);
      digitalWrite(PIN_ATOMIZATION, LOW);
      digitalWrite(PIN_FAN, LOW);
    }
  }
  delay(100);
}
