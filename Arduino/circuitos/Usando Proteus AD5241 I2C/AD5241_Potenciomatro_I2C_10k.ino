#include<Wire.h>

// AD5241 I2C address is 0x2C(44)
#define Addr 0x2C

int x = 0;

void setup()
{
  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
}

void loop()
{
  unsigned int data;
  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Send command byte
  Wire.write(0x00);
  // Input resistance value (valor 0 a 256 em decimal representa de 0 a 10kohms)
  Wire.write(x);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(250);

  // lê a tensão no pino A0 (entrada analogica)
  int pinA0 = map(analogRead(0),0,1023,0,5000);
  
  // converter para float o valor de tensão no pino A0
  float pinA0Volts = pinA0/1000.0;
  
  // Request 1 byte of data (solicita o escravo AD5241 a enviar informação de resistencia atual
  Wire.requestFrom(Addr, 1);

  // Read 1 byte of data
  if (Wire.available() == 1)
  {
    data = Wire.read();
  }

  // Convert the data
  float resistance = (data / 256.0 ) * 10.0;

  // Output data to serial monitor
  Serial.print("Resistance : ");
  Serial.print(resistance);
  Serial.println(" K");
  Serial.print("Tensao no pino A0 : ");
  Serial.print(pinA0Volts);
  Serial.println(" V");  
  delay(250);
  x++;
  if (x==255)
  {
    x=0;
  }
}
