//define libs
#include <Wire.h>
#include "LCD.h"
#include "LiquidCrystal_I2C.h"

#define I2C_ADDR 0x27 // here goes your adress
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

int dots=0; // puts the dots
int enddots=20; // ends the dots

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);


void setup() 
{
lcd.begin (20,4); // My LCD was 16x2

lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
lcd.clear (); // clears the lcd
lcd.home (); // go home
}

void loop()
{
lcd.setCursor (0,0);
lcd.print("TEST for the LCD I2C");
lcd.setCursor (0,1);
lcd.print("Please wait...");
lcd.setCursor (0,2);
if (dots<enddots)
{  
  lcd.setCursor (dots++,2);
  lcd.print(".");
  delay (500);
}
else
{
  lcd.setCursor (0,3);
  lcd.print("Test is SUCCESSFUL");
  delay(1000);
  
}
}

