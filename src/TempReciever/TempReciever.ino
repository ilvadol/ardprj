//define libs
//LCD
#include "Wire.h"
#include "LCD.h"
#include "LiquidCrystal_I2C.h"
//RTC
#include "RTClib.h"
//Radio
#include <SPI.h>
#include "RF24.h"

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

// LCD i2c settings
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

//Radio settings
RF24 radio(7,8);
const uint64_t pipe = 0xE8E8F0F0E1LL; //comm pipe

//RTC settings
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wed", "Thur", "Fri", "Sat"};

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
/////
//LCD setup
/////
lcd.begin (20,4);
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
lcd.clear (); // clears the lcd
lcd.home (); // go home

///////
//Radio setup
///////
radio.begin();
radio.openReadingPipe(1,pipe);
radio.startListening();
}

void loop(void)
{
//Time on lcd
DateTime now = rtc.now(); // Time request
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
//Radio listening
if ( radio.available() )
  {
    radio.read(data, sizeof(uint16_t)+1);
    
    uint16_t sensorValue = data[2] | data[1] << 8;
    float temp = (float) sensorValue/100;
    radio.read(data2, sizeof(data2));
    int moi = data[0];
      // Fetch the data payload
      lcd.setCursor(0,1);
      lcd.print("Temperature:");
      lcd.print(temp);
      lcd.setCursor(0,2);
      lcd.print("Soil moisture: ");      
      lcd.print(moi);
      
  }
else
  {    
     lcd.setCursor(0,1);
     lcd.print("No radio available");
  }

delay(1000);
lcd.clear();
}



