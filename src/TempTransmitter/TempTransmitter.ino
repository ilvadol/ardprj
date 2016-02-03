//define libs
//Radio
#include <SPI.h>
#include "RF24.h"
//Temperature
#include "OneWire.h"
#include "DallasTemperature.h"
// define the temperature sensor
#define ONE_WIRE_BUS 10
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//Radio settings
RF24 radio(7,8);
const uint64_t pipe = 0xE8E8F0F0E1LL; //comm pipe

//Int's Floats
unsigned char data[3] = {
  0};
unsigned char data2[2] = {
  0};

// code
void setup(void) 
{
///////
//Serial setup
///////
Serial.begin(115200);

///////
//Radio setup
///////
radio.begin();
radio.openWritingPipe(pipe);
radio.printDetails();
///////
//TempSensor setup
///////
sensors.begin();
}

void loop(void)
{
sensors.requestTemperatures();
data[0] = analogRead(1);
float currentTemp;
  currentTemp = sensors.getTempCByIndex(0);
uint16_t sensorValue = currentTemp*100;
data[1] = sensorValue >> 8;
data[2] = sensorValue;
radio.write(data, sizeof(uint16_t)+1);
delay (10);
}



