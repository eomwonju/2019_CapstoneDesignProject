#include <SoftwareSerial.h>
#include <Stepper.h>
#include <Servo.h>
#define PIN_RX 2
#define PIN_TX 3
#define PIN_SERVO 5
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
Stepper stepper(STEPS, PIN_STEPPER_IN1, PIN_STEPER_IN3, PIN_STEPPER_IN2, PIN_STEPPER_IN4);

void setup(){
  Serial.begin(9600);
  bleSerial.begin(9600);
  stepper.setSpeed(7);
  servo.attach(PIN_SERVO);
}

void loop(){  
  if(bleSerial.available()){
    
    bleData = bleSerial.read();
  
    if(bleData=='6'){
      if(window==1){
        stepper.step(-STEPS);
        window = 0;
      }
    }
    else if(bleData=='7'){
      if(window==0){
        stepper.step(STEPS);
        window = 1;
      }
    }
  
    if(bleData=='A'){
      servo.write(90);
      door = 0;
    }
    else if(bleData=='B'){
      servo.write(3);
      door = 1;
    }
  }
  delay(100);
}
