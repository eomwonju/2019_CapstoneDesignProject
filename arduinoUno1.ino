#include <SoftwareSerial.h>
#include <Stepper.h>
#include <Servo.h>
#define PIN_RX 2
#define PIN_TX 3
#define PIN_SERVO 6
#define PIN_STEPPER_IN1 13
#define PIN_STEPPER_IN2 12
#define PIN_STEPPER_IN3 11
#define PIN_STEPPER_IN4 10
#define STEPS 3500

int bleData = 0;
int door = 0;
int window = 0;

SoftwareSerial bleSerial(PIN_RX, PIN_TX);
Servo servo;
Stepper stepper(STEPS, PIN_STEPPER_IN1, PIN_STEPPER_IN3, PIN_STEPPER_IN2, PIN_STEPPER_IN4);

void setup(){
  Serial.begin(9600);
  bleSerial.begin(9600);
  //bleSerial.print("AT+ROLE0");
  //pinMode(PIN_RX, INPUT);
  //pinMode(PIN_TX, OUTPUT);
  stepper.setSpeed(8);
  servo.attach(PIN_SERVO);
}

void loop(){
  //Serial.print(bleSerial.available());
  
  if(bleSerial.available()){
    
    bleData = bleSerial.read();
    //Serial.println(bleData);

    if(bleData=='8'){
      if(window==1){
        stepper.step(-STEPS);
        window = 0;
      }
    }
    else if(bleData=='9'){
      if(window==0){
        stepper.step(STEPS);
        window = 1;
      }
    }
  
    if(bleData=='C'){
      servo.write(90);
      door = 0;
    }
    else if(bleData=='D'){
      servo.write(3);
      door = 1;
    }
  }
  delay(100);
}
