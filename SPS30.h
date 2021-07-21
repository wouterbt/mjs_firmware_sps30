/* Simple library for reading out the SPS30 particulate matter
 * sensor using I2C. Only the values for PM2.5 and PM10 (in ug/m3)
 * are read out. Pin 4 of the sensor must be connected to GND.
 * 
 * checkSPS30() returns true when the sensor is detected.
 * 
 * readSPS30() wakes up the sensor, starts a measurement of 10s, 
 * reads out the values, stores these in the global variables and
 * puts the sensor to sleep.
 * 
 * Copyright 2021 Wouter Bergmann Tiest
 */

extern unsigned int pm25; // PM2.5 (not PM25)
extern unsigned int pm10; // PM10

bool checkSPS30();
void readSPS30();
