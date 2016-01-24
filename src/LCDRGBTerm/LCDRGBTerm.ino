//define libs
#include "Wire.h"
#include "LCD.h"
#include "LiquidCrystal_I2C.h"
#include "OneWire.h"
#include "DallasTemperature.h"
//Define i2c pins 
#define I2C_ADDR 0x27 // here goes your adress
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int dots=0; // puts the dots
int enddots=20; // ends the dots
// define the RGB pins
int redpin = 9;
int greenpin = 10;
int bluepin = 11;
//define the min/max temprature floats 
float maxtemperature = 25.00;
float mintemperature = 20.00;
// LCD i2c settings
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

// code
void setup() 
{
/////
//LCD setup
/////
lcd.begin (20,4);
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
lcd.clear (); // clears the lcd
lcd.home (); // go home
//////
//LED setup
//////
pinMode(redpin, OUTPUT); 
pinMode(bluepin, OUTPUT); 
pinMode(greenpin, OUTPUT);
///////
//Sensor setup
///////
sensors.begin();
}

void loop()
//////////// 
//LCD job
////////////
{
sensors.requestTemperatures(); //Request of temperature
lcd.clear();
lcd.setCursor (0,0);
lcd.print("Current temperature");
float temperature = sensors.getTempCByIndex(0);
lcd.setCursor (0,1);
lcd.print (temperature);
lcd.print (" C");
if(temperature<mintemperature)
  {
  digitalWrite(bluepin, HIGH);
  digitalWrite(greenpin, LOW);
  digitalWrite(redpin, LOW);
  lcd.setCursor (2,2);
  lcd.print ("It's COLD");
  }
else if(temperature>maxtemperature)
  {
  digitalWrite(bluepin, LOW);
  digitalWrite(greenpin, LOW);
  digitalWrite(redpin, HIGH);
  lcd.setCursor (2,2);
  lcd.print ("It's WARM");
  }
else
  {
  digitalWrite(bluepin, LOW);
  digitalWrite(greenpin, HIGH);
  digitalWrite(redpin, LOW);
  lcd.setCursor (2,2);
  lcd.print ("It's OK");
  }
delay(2000);
}



