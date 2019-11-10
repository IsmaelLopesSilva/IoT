// Programa : Display LCD 16x2 e modulo I2C
// Autor : Arduino e Cia

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

String myString1 = "Sou Display 16x2";
String myString2 = "Comunico Via I2C";

// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3,POSITIVE);
 
void setup()
{
  Serial.begin(9600); // ajusta a comunicação para 9600 (baudrate)
  while (!Serial)
  {
    // aguarda conectar na porta serial
  }
  lcd.begin(16,2);
  lcd.setCursor(0,0); // posiciona o cursor no inicio da primeira linha
  lcd.print(myString1); // escreve na primeira linha do Display
  lcd.setCursor(0,1); // posiciona o cursor no inicio da segunda linha
  lcd.print(myString2); // escreve na segunda linha do Display
}
 
void loop()
{
  while (Serial.available()) // get incoming string
    {
      myString2 = Serial.readString();  // lê a string na serial
      lcd.setCursor(0,1); // posiciona o cursor no inicio da segunda linha
      lcd.print(myString2); // escreve na segunda linha do Display
    }
}
