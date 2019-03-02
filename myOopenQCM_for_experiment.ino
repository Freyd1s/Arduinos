 /* LICENSE
 * openQCM ia free software licensed under GNU GPL v3.0 General Public License 2016

 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * INTRO
 * openQCM is the unique opensource quartz crystal microbalance http://openqcm.com/
 * openQCM Java software project is available on github repository 
 * https://github.com/marcomauro/openQCM
 * 
 * Measure QCM frequency using FreqCount library developed by Paul Stoffregen 
 * https://github.com/PaulStoffregen/FreqCount
 *
 * NOTE       - designed for 6 and 10 Mhz At-cut quartz crystal
 *            - 3.3 VDC supply voltage quartz crystal oscillator
 *            - Thermistor temperature sensor
 *
 * author     Marco Mauro 
 * version    1.3
 * date       May 2015 
 *
 */

// include library for frequency counting
#include <FreqCount.h>
// include EERPOM library
#include <EEPROM.h>
#include "Adafruit_MCP9808.h"
#include <Wire.h>
#include <math.h> 

// fixed "gate interval" time for counting cycles 1000ms  
#define GATE   1000
// current address in EEPROM series
#define ADDRESS_SERIES 0
// current address in EEPROM first number 
#define ADDRESS_NUMBERFIRST 1
// current address in EEPROM second number 
#define ADDRESS_NUMBERSECOND 2


// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
// QCM frequency by counting the number of pulses in a fixed time 
unsigned long frequency = 0;
// thermistor temperature
int temperature = 0;
int myTemp = 0;

boolean DEBUG = false;

// print data to serial port 
void dataPrint(unsigned long Count, int Temperature, int myTemperature){
  Serial.print("RAWMONITOR");
  Serial.print(Count);
  //Serial.print("_");
  //Serial.print(Temperature);
  Serial.print("_");
  Serial.print(myTemperature);
  Serial.write(255);
}


// measure temperature
int getTemperature(void){
    int Temperature = 0; 
     tempsensor.shutdown_wake(0);   // Don't remove this line! required before reading temp
    // Read and print out the temperature, then convert to *F
    float c = tempsensor.readTempC();
    if (DEBUG){
      Serial.print("Temperature");
      Serial.println(c);
    }
    Temperature = c*10;
    return(Temperature);
}

int getMyTemp(void) {
   int sig = analogRead(2);              // read analog signal from pin 2
   double resistance = 2046.0 / (1023 - sig) - 2;  //calculate actual termorestistor resisance
   double kelvin = 1 / ( ( log(resistance / 100) ) / 3950 + (1.0 / 298) );
   myTemp = int(kelvin) - 273;
   myTemp = myTemp * 10;
}



void setup(){
  Serial.begin(115200);
  // init the frequency counter
  FreqCount.begin(GATE);
  // begin temperature sensor
  tempsensor.begin();
  // wake up sensor temperature
  tempsensor.shutdown_wake(0);   // Don't remove this line! required before reading temp
}

void loop(){
  // read the openQCM serial number at the connection
  if (Serial.available()) {
    int val = Serial.parseInt();
    if (val == 1){
      byte valueSeries = EEPROM.read(ADDRESS_SERIES);
      byte valueNumberFirst = EEPROM.read(ADDRESS_NUMBERFIRST);
      byte valueNumberSecond = EEPROM.read(ADDRESS_NUMBERSECOND);
      Serial.print("SERIALNUMBER");
      Serial.print(valueSeries, DEC);
      Serial.print(valueNumberFirst, DEC);
      Serial.print(valueNumberSecond, DEC);
      Serial.write(255);
    }
  }

  // read quartz crystal microbalance frequency and temperature 
  if (FreqCount.available()) 
  {
    frequency = FreqCount.read();       // measure QCM frequency
    temperature = getTemperature();     // measure temperature
    getMyTemp();
    dataPrint(frequency, temperature, myTemp);  // print data
  }
}


