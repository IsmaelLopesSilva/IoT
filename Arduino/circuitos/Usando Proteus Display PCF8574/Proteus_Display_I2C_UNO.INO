// Programa : Display LCD 16x2 e modulo I2C
// Autor : Ismael Lopes
// 02 Jan 2018

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

String myString1 = "Sou Display 16x2";
String myString2 = "Comunico Via I2C";

// Inicializa o display no endereco 0x20 para o Display do Proteus, que utiliza o CI PCF8574 (A0=A1=A2= GND)
LiquidCrystal_I2C lcd(0x20,2,1,0,4,5,6,7);
 
void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    // wait for serial port to connect
  }
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(myString1);
  lcd.setCursor(0,1);
  lcd.print(myString2);
}
 
void loop()
{
  while (Serial.available())
    {
      // get incoming string:
      myString2 = Serial.readString();
      lcd.setCursor(0,1);
      lcd.print(myString2);
    }
}