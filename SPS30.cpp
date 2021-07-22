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

#include <Arduino.h>
#include <Wire.h>

#define SPS30_ADDR 0x69
#define SPS30_SLEEP 0x1001
#define SPS30_WAKE_UP 0x1103
#define SPS30_STOP_MEASUREMENT 0x0104
#define SPS30_READ_MEASURED_VALUES 0x0300
#define SPS30_READ_PRODUCT_TYPE 0xD002
#define SPS30_BUFSIZE 8

unsigned int pm25, pm10;

void sendCommand(unsigned int command) {
  Wire.beginTransmission(SPS30_ADDR);
  Wire.write(highByte(command));
  Wire.write(lowByte(command));
  Wire.endTransmission();
}

void getData(int length, byte *buffer) {
  Wire.requestFrom(SPS30_ADDR, length, false);
  int j = 0;
  for (int i = 0; i < length; i++) {
    if ((i + 1) % 3) {
      buffer[j++] = Wire.read();
    } else {
      Wire.read(); // ignore CRC bytes
    }
  }
}

void wakeUp() {
  // Activating I2C
  Wire.beginTransmission(SPS30_ADDR);
  Wire.endTransmission();

  // Waking up
  sendCommand(SPS30_WAKE_UP);
  delay(100); // allow time for wake-up
}

bool checkSPS30() { // returns true if SPS30 is detected
  char buffer[SPS30_BUFSIZE];

  wakeUp();
  
  sendCommand(SPS30_READ_PRODUCT_TYPE);
  getData(12, buffer);
  return !strncmp(buffer, "00080000", SPS30_BUFSIZE);
}

void readSPS30() {
  char buffer[SPS30_BUFSIZE];

  wakeUp();
  
  // Starting measurement
  Wire.beginTransmission(SPS30_ADDR);
  Wire.write(0x00);
  Wire.write(0x10);
  Wire.write(0x05); // request 16-bit integers
  Wire.write(0x00); // dummy byte
  Wire.write(0xF6); // CRC
  Wire.endTransmission();
  
  delay(10000);
  
  // Requesting readout
  sendCommand(SPS30_READ_MEASURED_VALUES);
  getData(12, buffer);
  pm25 = ((unsigned int)buffer[2] << 8) | buffer[3];
  pm10 = ((unsigned int)buffer[6] << 8) | buffer[7];
  
  // Stopping measurement
  sendCommand(SPS30_STOP_MEASUREMENT);

  // Entering sleep mode
  sendCommand(SPS30_SLEEP);
}
