//define libs
#include "Wire.h"
#include "LCD.h"
#include "LiquidCrystal_I2C.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "RTClib.h"
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
// define the temperature sensor
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
// define the RGB pins
int redpin = 9;
int greenpin = 10;
int bluepin = 11;
//define the min/max temprature floats 
float maxtemperature = 25.00;
float mintemperature = 20.00;
// define the soilhumidity sensor
int humidsenPin = 3;
int humidsenPinVal = 0;
// define the dry and humid vals
int SDry = 600;
int SHumid = 800;
// define the buzzer pin
int buzzerPin = 7;
// LCD i2c settings
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
// define the RTC settings
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wed", "Thur", "Fri", "Sat"};

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
//TempSensor setup
///////
sensors.begin();
pinMode(buzzerPin, OUTPUT);
lcd.clear();
}

void loop()
{
DateTime now = rtc.now(); // Time request
sensors.requestTemperatures(); //Request of temperature
// Time
lcd.setCursor(0,0);
lcd.print(now.year(), DEC);
lcd.print('/');
lcd.print(now.month(), DEC);
lcd.print('/');
lcd.print(now.day(), DEC);
lcd.print(" ");
lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
lcd.print(" ");
lcd.print(now.hour(), DEC);
lcd.print(':');
lcd.print(now.minute(), DEC);
// Temperature and moisture
lcd.setCursor (0,1);
lcd.print("Temp");
lcd.setCursor (9,1);
lcd.print("Soil Moist");
float temperature = sensors.getTempCByIndex(0);
lcd.setCursor (0,2);
lcd.print (temperature);
lcd.print (" C");
humidsenPinVal = analogRead(humidsenPin);
lcd.setCursor(9,2);
lcd.print (humidsenPinVal);

// Temperature IF'S
if(temperature<mintemperature)
  {
  digitalWrite(bluepin, HIGH);
  digitalWrite(greenpin, LOW);
  digitalWrite(redpin, LOW);
  lcd.setCursor (0,3);
  lcd.print ("COLD");
  digitalWrite(buzzerPin, HIGH);
  delay(100); 
  digitalWrite(buzzerPin, LOW);
  }
else if(temperature>maxtemperature)
  {
  digitalWrite(bluepin, LOW);
  digitalWrite(greenpin, LOW);
  digitalWrite(redpin, HIGH);
  lcd.setCursor (0,3);
  lcd.print ("WARM");
  digitalWrite(buzzerPin, HIGH);
  delay(100); 
  digitalWrite(buzzerPin, LOW);
  }
else
  {
  digitalWrite(bluepin, LOW);
  digitalWrite(greenpin, HIGH);
  digitalWrite(redpin, LOW);
  lcd.setCursor (0,3);
  lcd.print ("Norm");
  };
// Moisture IF'S
if (humidsenPinVal<SDry)
	{
	lcd.setCursor (9,3);
    lcd.print ("Too DRY");
	digitalWrite(buzzerPin, HIGH);
    delay(100); 
    digitalWrite(buzzerPin, LOW);
	}
else if (humidsenPinVal>SHumid)
	{
	lcd.setCursor(9,3);
	lcd.print ("Too MOI");
	digitalWrite(buzzerPin, HIGH);
    delay(100); 
    digitalWrite(buzzerPin, LOW);
	}
else
	{
	lcd.setCursor(9,3);
	lcd.print ("NormMOI");
	}
delay(2000);
}



