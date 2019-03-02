
#include <Arduino.h>
#include "A4988.h"


// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 1

#define DIR 2
#define STEP 3
#define ENABLE 4 // optional (just delete ENABLE from everywhere if not used)


#define MS1 5
#define MS2 6
#define MS3 7

#define FDiod 10
#define DLinii 9

A4988 stepper(MOTOR_STEPS, DIR, STEP, ENABLE, MS1, MS2, MS3);

void setup() {
    
    Serial.begin(9600);            // set up Serial library at 9600 bps
    Serial.print("Monitor - OK");
    stepper.setRPM(RPM);
    stepper.disable();
	stepper.setMicrostep(2);
	
	pinMode(DLinii, INPUT);

}

void loop()
{
unsigned int fd_value;
int i = 0;
boolean flag = false;

stepper.disable();
stepper.setMicrostep(4);

while(Serial.available() == 0)
//while(1)
{
//fd_value = analogRead(FDiod);
//   Serial.println(fd_value);
//  delay(500);
}

 Serial.println("start");
stepper.enable();
stepper.move(-50);

 for (int i = 1; i<=100; i++)
 {
   fd_value = analogRead(FDiod);
   Serial.println(fd_value);
   delay(50);
   stepper.move(1);
   delay(50);
 }
 
 Serial.println("end1");

 for (int i = 1; i<=100; i++)
 {
   fd_value = analogRead(FDiod);
   Serial.println(fd_value);
   delay(50);
   stepper.move(-1);
   delay(50);
 }
 
//if (Serial.available() <= 0) 
  
	Serial.println("end");
  stepper.move(50);
  stepper.disable();
  flag = true;
	
while (flag)
{
}


}

