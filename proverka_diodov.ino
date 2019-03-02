
#include <Arduino.h>
#include "A4988.h"


// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 6

#define DIR 2
#define STEP 3
#define ENABLE 4 // optional (just delete ENABLE from everywhere if not used)


#define MS1 5
#define MS2 6
#define MS3 7

#define FDiod 8
#define DLinii 9

A4988 stepper(MOTOR_STEPS, DIR, STEP, ENABLE, MS1, MS2, MS3);

void setup() {
    
    Serial.begin(9600);            // set up Serial library at 9600 bps
    Serial.print("Monitor - OK");
    stepper.setRPM(RPM);
    stepper.disable();
  stepper.setMicrostep(4);
  
  pinMode(DLinii, INPUT);

}

void loop()
{
unsigned int fd_value;
bool flag = true;
int i = 0;

  stepper.enable();
  
  stepper.move(100);
  

if (Serial.available() <= 0) 
   {
      Serial.print("i = ");
      Serial.println(i);
   }

   delay(1000);
}

